/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

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

// A simple CPU allocator that intercepts malloc/free calls from SOGO library
// and redirects them to Tensorflow allocator

#ifndef TENSORFLOW_CORE_COMMON_RUNTIME_SOGO_CPU_ALLOCATOR_H_
#define TENSORFLOW_CORE_COMMON_RUNTIME_SOGO_CPU_ALLOCATOR_H_


#include <cstdlib>
#include <string>
#include "tensorflow/core/common_runtime/bfc_allocator.h"
#include "tensorflow/core/common_runtime/visitable_allocator.h"
#include "tensorflow/core/lib/strings/numbers.h"
#include "tensorflow/core/lib/strings/str_util.h"
#include "tensorflow/core/platform/mem.h"


namespace tensorflow {

class SogoSubAllocator : public SubAllocator {
 public:
  ~SogoSubAllocator() override {}

  void* Alloc(size_t alignment, size_t num_bytes) override {
    return port::AlignedMalloc(num_bytes, alignment);
  }
  void Free(void* ptr, size_t num_bytes) override { port::AlignedFree(ptr); }
};

/// CPU allocator for SOGO that wraps BFC allocator and intercepts
/// and redirects memory allocation calls from SOGO.
class SogoCPUAllocator : public VisitableAllocator {
 public:
  // Constructor and other standard functions

  /// Environment variable that user can set to upper bound on memory allocation
  static constexpr const char* kMaxLimitStr = "TF_SOGO_ALLOC_MAX_BYTES";

  /// Default upper limit on allocator size - 64GB
  static constexpr size_t kDefaultMaxLimit = 64LL << 30;

  SogoCPUAllocator() { TF_CHECK_OK(Initialize()); }

  ~SogoCPUAllocator() override { delete allocator_; }

  Status Initialize() {
    VLOG(2) << "SogoCPUAllocator: In SogoCPUAllocator";

    // Set upper bound on memory allocation to physical RAM available on the
    // CPU unless explicitly specified by user
    uint64 max_mem_bytes = kDefaultMaxLimit;
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
    max_mem_bytes =
        (uint64)sysconf(_SC_PHYS_PAGES) * (uint64)sysconf(_SC_PAGESIZE);
#endif
    char* user_mem_bytes = getenv(kMaxLimitStr);

    if (user_mem_bytes != NULL) {
      uint64 user_val = 0;
      if (!strings::safe_strtou64(user_mem_bytes, &user_val)) {
        return errors::InvalidArgument("Invalid memory limit (", user_mem_bytes,
                                       ") specified for Sogo allocator through ",
                                       kMaxLimitStr);
      }
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
      if (user_val > max_mem_bytes) {
        LOG(WARNING) << "The user specified a memory limit " << kMaxLimitStr
                     << "=" << user_val
                     << " greater than available physical memory: "
                     << max_mem_bytes
                     << ". This could significantly reduce performance!";
      }
#endif
      max_mem_bytes = user_val;
    }

    VLOG(1) << "SogoCPUAllocator: Setting max_mem_bytes: " << max_mem_bytes;
    allocator_ = new BFCAllocator(new SogoSubAllocator, max_mem_bytes,
                                  kAllowGrowth, kName);

    return Status::OK();
  }

  inline string Name() override { return kName; }

  inline void* AllocateRaw(size_t alignment, size_t num_bytes) override {
    return allocator_->AllocateRaw(alignment, num_bytes);
  }

  inline void DeallocateRaw(void* ptr) override {
    allocator_->DeallocateRaw(ptr);
  }

  void GetStats(AllocatorStats* stats) override { allocator_->GetStats(stats); }

  void ClearStats() override { allocator_->ClearStats(); }

  void AddAllocVisitor(Visitor visitor) override {
    allocator_->AddAllocVisitor(visitor);
  }

  void AddFreeVisitor(Visitor visitor) override {
    allocator_->AddFreeVisitor(visitor);
  }

 private:
  // Hooks provided by this allocator for memory allocation routines from MKL(SOGO)

  static inline void* MallocHook(size_t size) {
    VLOG(3) << "SogoCPUAllocator: In MallocHook";
    return cpu_allocator()->AllocateRaw(kAlignment, size);
  }

  static inline void FreeHook(void* ptr) {
    VLOG(3) << "SogoCPUAllocator: In FreeHook";
    cpu_allocator()->DeallocateRaw(ptr);
  }

  static inline void* CallocHook(size_t num, size_t size) {
    Status s = Status(error::Code::UNIMPLEMENTED,
                      "Unimplemented case for hooking SOGO function.");
    TF_CHECK_OK(s);  // way to assert with an error message
  }

  static inline void* ReallocHook(void* ptr, size_t size) {
    Status s = Status(error::Code::UNIMPLEMENTED,
                      "Unimplemented case for hooking SOGO function.");
    TF_CHECK_OK(s);  // way to assert with an error message
  }

  /// Do we allow growth in BFC Allocator
  static const bool kAllowGrowth = true;

  /// Name
  static constexpr const char* kName = "sogo-cpu";

  /// The alignment that we need for the allocations
  static constexpr const size_t kAlignment = 64;

  VisitableAllocator* allocator_;  // owned by this class
};

}  // namespace tensorflow


#endif  // TENSORFLOW_CORE_COMMON_RUNTIME_SOGO_CPU_ALLOCATOR_H_
