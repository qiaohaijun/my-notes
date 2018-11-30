#pragma once

#include "tensorflow_serving/model_servers/pipeline/pipe_base.h"
namespace tensorflow {
namespace serving {
namespace pipeline {

class ResponseToJsonPipe : public PipeBase {
 public:
  explicit ResponseToJsonPipe(int thread_num);

  // TODO should use status as ret_val
  void ThreadFunc() override final;
  net_http::HTTPStatusCode ToHTTPStatusCode(const Status &status);



 private:
  int thread_num_;
  muduo::CountDownLatch latch_;

};

} // namespace pipeline
} // namespace serving
} // namespace tensorflow
