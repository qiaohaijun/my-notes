#include <iostream>
#include <vector>
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/protobuf/meta_graph.pb.h"
#include  "tensorflow/cc/saved_model/tag_constants.h"

#include <tensorflow/core/public/session.h>
#include <tensorflow/core/graph/default_device.h>
#include <tensorflow/core/graph/graph_def_builder.h>

using namespace std;
using namespace tensorflow;

int main(int argc ,char *argv[]) {

    string modelpath;

    if(argc<2){
         modelpath = "/Users/xxxx/Documents/python/credit-nlp-ner/bi-lstm-crf/model/1";


    }else{
        modelpath=argv[1];
    }

    tensorflow::SessionOptions sess_options;

   //   tensorflow::ConfigProto config=sess_options.config;
//    config.mutable_gpu_options()->set_visible_device_list("0");
//    config.mutable_gpu_options()->set_allow_growth(true);
//    config.set_allow_soft_placement(true);

    tensorflow::RunOptions run_options;


    tensorflow::SavedModelBundle bundle;

    TF_CHECK_OK(tensorflow::LoadSavedModel(sess_options, run_options, modelpath, {tensorflow::kSavedModelTagServe}, &bundle));



    tensorflow::MetaGraphDef graph_def = bundle.meta_graph_def;




    std::unique_ptr<tensorflow::Session>& session = bundle.session;

    GraphDef graphdef;
    session->Create(graphdef);
    //gpu設置
    graph::SetDefaultDevice("/gpu:0", &graphdef);
    sess_options.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
    sess_options.config.mutable_gpu_options()->set_allow_growth(true);



    vector<int> vec={7997, 1945, 8471, 14127, 17565, 7340, 20224, 17529, 3796, 16033, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ndim=vec.size();
    Tensor x(tensorflow::DT_INT32, tensorflow::TensorShape({1, ndim})); // New Tensor shape [1, ndim]
    auto x_map = x.tensor<int, 2>();
    for (int j = 0; j < ndim; j++) {
        x_map(0, j) = vec[j];
    }
    std::vector<std::pair<string, tensorflow::Tensor>> inputs;
    inputs.push_back(std::pair<std::string, tensorflow::Tensor>("input_x", x));

    Tensor keep_prob(tensorflow::DT_FLOAT, tensorflow::TensorShape({1}));
    keep_prob.vec<float>()(0) = 1.0f;

    inputs.push_back(std::pair<std::string, tensorflow::Tensor>("keep_prob", keep_prob));



    Tensor tensor_out(tensorflow::DT_INT32, TensorShape({1,ndim}));
    std::vector<tensorflow::Tensor> outputs={{ tensor_out }};
    TF_CHECK_OK(session->Run(inputs, {"crf_pred/ReverseSequence_1"}, {}, &outputs));


    for(int i=0;i<40;++i) {
        std::cout << outputs[0].matrix<int>()(0,i)<<" ";
    }





    return 0;

}
