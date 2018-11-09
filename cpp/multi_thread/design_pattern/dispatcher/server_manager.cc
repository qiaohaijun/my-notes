#include "server_manager.h"

namespace sgs {
namespace framework {

server_manager::server_manager() {
  m_receive_task = nullptr;
  m_pre_predict_task = nullptr;
  m_predict_task = nullptr;
  m_post_predict_task = nullptr;
  m_reply_task = nullptr;
  req_res_handler_ = nullptr;
}

server_manager::~server_manager() {
}

int server_manager::activate() {

  m_reply_task->activate();
  m_post_predict_task->activate();
  m_predict_task->activate();
  m_pre_predict_task->activate();
  m_receive_task->activate();

  return 0;
}

int server_manager::stop() {
  m_receive_task->stop();
  m_pre_predict_task->stop();
  m_predict_task->stop();
  m_post_predict_task->stop();
  m_reply_task->stop();
  return 0;
}

// receive task
void server_manager::register_task(server_receive *receive_task) {
  m_receive_task = receive_task;
  m_receive_task->register_manager(this);
}

// before predict task
void server_manager::register_task(PrePredictTask *pre_predict_task) {
  m_pre_predict_task = pre_predict_task;
  m_pre_predict_task->register_manager(this);
}

// predict task
void server_manager::register_task(PredictTask *predict_task) {
  m_predict_task = predict_task;
  m_predict_task->register_manager(this);
}
// after predict
void server_manager::register_task(PostPredictTask *post_predict_task) {
  m_post_predict_task = post_predict_task;
  m_post_predict_task->register_manager(this);
}
// reply
void server_manager::register_task(server_reply *reply_task) {
  m_reply_task = reply_task;
  m_reply_task->register_manager(this);
}

void server_manager::dispatch_worker(server_worker *&worker, server_receive *receive_task) {
  if (worker->validType == NORMAL_)
    m_pre_predict_task->put(worker);
  else
    m_reply_task->put(worker);
  worker = nullptr;

}

// case pre_predict_task
void server_manager::dispatch_worker(server_worker *&worker, PrePredictTask *pre_predict_task) {
  m_predict_task->put(worker);
  worker = nullptr;
}

// case predict_task
void server_manager::dispatch_worker(server_worker *&worker, PredictTask *predict_task) {
  m_post_predict_task->put(worker);
  worker = nullptr;
}

// case post_predict_task
void server_manager::dispatch_worker(server_worker *&worker, PostPredictTask *post_predict_task) {
  m_reply_task->put(worker);
  worker = nullptr;
}

// case reply_task
void server_manager::dispatch_worker(server_worker *&worker, server_reply *reply_task) {
  release_worker(worker);
  worker = nullptr;
}

server_worker* server_manager::acquire_worker() {

  server_worker *worker = new server_worker();
  worker->req_res_handler = req_res_handler_;
  worker->request = req_res_handler_->CreateRequest();
  worker->response = req_res_handler_->CreateResponse();

  using tensorflow::serving::TFSCPUTensor;
  worker->m_tfs_inputs  = new std::map<std::string, TFSCPUTensor>;
  worker->m_tfs_outputs = new std::map<std::string, TFSCPUTensor>;

  return worker;

}

void server_manager::release_worker(server_worker *worker) {
  worker->req_res_handler->DeleteRequest(worker->request);
  worker->req_res_handler->DeleteResponse(worker->response);

  delete worker;
}

} // namespace framework
} // namespace sgs
