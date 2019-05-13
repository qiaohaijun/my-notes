/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/c/c_api_experimental.h"

#include "tensorflow/c/c_api_internal.h"
#include "tensorflow/compiler/jit/legacy_flags/mark_for_compilation_pass_flags.h"
#include "tensorflow/core/graph/graph.h"
#include "tensorflow/core/graph/node_builder.h"
#include "tensorflow/core/lib/strings/strcat.h"
#include "tensorflow/core/platform/platform.h"
#include "tensorflow/core/protobuf/config.pb.h"

using tensorflow::FunctionDef;
using tensorflow::Node;
using tensorflow::NodeBuilder;
using tensorflow::Status;

namespace {
typedef std::unique_ptr<TF_Function, decltype(&TF_DeleteFunction)>
    UniqueFuncPtr;
}

// struct TF_Operation { tensorflow::Node node; };
static TF_Operation* ToTF_Operation(Node* node) {
  return static_cast<TF_Operation*>(static_cast<void*>(node));
}

void TF_EnableXLACompilation(TF_SessionOptions* options, unsigned char enable) {
  tensorflow::ConfigProto& config = options->options.config;
  auto* optimizer_options =
      config.mutable_graph_options()->mutable_optimizer_options();
  if (enable) {
    optimizer_options->set_global_jit_level(tensorflow::OptimizerOptions::ON_1);

    // These XLA flags are needed to trigger XLA properly from C (more generally
    // non-Python) clients. If this API is called again with `enable` set to
    // false, it is safe to keep these flag values as is.
    tensorflow::legacy_flags::MarkForCompilationPassFlags* flags =
        tensorflow::legacy_flags::GetMarkForCompilationPassFlags();
    flags->tf_xla_cpu_global_jit = true;
    flags->tf_xla_min_cluster_size = 1;
  } else {
    optimizer_options->set_global_jit_level(tensorflow::OptimizerOptions::OFF);
  }
}

TF_Buffer* TF_CreateConfig(unsigned char enable_xla_compilation,
                           unsigned char gpu_memory_allow_growth) {
  tensorflow::ConfigProto config;
  auto* optimizer_options =
      config.mutable_graph_options()->mutable_optimizer_options();
  if (enable_xla_compilation) {
    optimizer_options->set_global_jit_level(tensorflow::OptimizerOptions::ON_1);

    // These XLA flags are needed to trigger XLA properly from C (more generally
    // non-Python) clients. If this API is called again with `enable` set to
    // false, it is safe to keep these flag values as is.
    tensorflow::legacy_flags::MarkForCompilationPassFlags* flags =
        tensorflow::legacy_flags::GetMarkForCompilationPassFlags();
    flags->tf_xla_cpu_global_jit = true;
    flags->tf_xla_min_cluster_size = 1;
  } else {
    optimizer_options->set_global_jit_level(tensorflow::OptimizerOptions::OFF);
  }

  auto* gpu_options = config.mutable_gpu_options();
  gpu_options->set_allow_growth(gpu_memory_allow_growth);

  TF_Buffer* ret = TF_NewBuffer();
  TF_CHECK_OK(MessageToBuffer(config, ret));
  return ret;
}

TF_Buffer* TF_CreateRunOptions(unsigned char enable_full_trace) {
  tensorflow::RunOptions options;
  if (enable_full_trace) {
    options.set_trace_level(tensorflow::RunOptions::FULL_TRACE);
  } else {
    options.set_trace_level(tensorflow::RunOptions::NO_TRACE);
  }
  TF_Buffer* ret = TF_NewBuffer();
  TF_CHECK_OK(MessageToBuffer(options, ret));
  return ret;
}

const char* TF_GraphDebugString(TF_Graph* graph, size_t* len) {
  tensorflow::mutex_lock c(graph->mu);
  const auto& debug_str = graph->graph.ToGraphDefDebug().DebugString();
  *len = debug_str.size();
  char* ret = static_cast<char*>(malloc(*len + 1));
  memcpy(ret, debug_str.c_str(), *len + 1);
  return ret;
}

// On success, returns a set of TF_Function instances from `text_proto` of
// GraphDef type. These functions must be deleted by calling TF_DeleteFunction.
//
// If `mutate_proto_func` is non-NULL, run it over each FunctionDef proto,
// before creating a TF_Function out of the possibly mutated proto.
static std::vector<UniqueFuncPtr> CreateFunctionsFromTextProto(
    const char* text_proto,
    std::function<void(FunctionDef*)>* mutate_proto_func, TF_Status* status) {
  tensorflow::GraphDef gdef;
  if (!tensorflow::protobuf::TextFormat::ParseFromString(text_proto, &gdef)) {
    status->status = tensorflow::errors::Internal(
        "Invalid text proto for GraphDef: ", text_proto);
    return {};
  }
  const auto& fdef_lib = gdef.library();
  if (fdef_lib.gradient_size() > 0) {
    status->status = tensorflow::errors::Internal(
        "GradientDef is not supported in reading Dataset related functions: ",
        text_proto);
    return {};
  }
  std::vector<UniqueFuncPtr> ret;
  for (const FunctionDef& fdef : fdef_lib.function()) {
    // Make a copy so that we can mutate it.
    FunctionDef fdef_to_load = fdef;
    if (mutate_proto_func) {
      (*mutate_proto_func)(&fdef_to_load);
    }
    VLOG(1) << "Adding func to graph: " << fdef_to_load.DebugString();
    std::vector<char> binary_proto_buf(fdef_to_load.ByteSizeLong());
    fdef_to_load.SerializeToArray(binary_proto_buf.data(),
                                  binary_proto_buf.size());
    TF_Function* func = TF_FunctionImportFunctionDef(
        binary_proto_buf.data(), binary_proto_buf.size(), status);
    if (!status->status.ok()) return {};
    ret.push_back(UniqueFuncPtr(func, TF_DeleteFunction));
  }
  return ret;
}

