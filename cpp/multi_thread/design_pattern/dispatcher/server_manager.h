#pragma once

#include <time.h>

#include "asset_manager.h"
#include "server_manager.h"
#include "server_worker.h"
#include "server_receive.h"
#include "server_reply.h"
#include "pre_predict_task.h"
#include "predict_task.h"
#include "post_predict_task.h"

namespace sgs {
namespace framework {

class server_manager {
 public:
  explicit server_manager();
  ~server_manager();

  int activate();
  int stop();

  /************************
   * init & release worker*
   ************************/

  server_worker *acquire_worker();
  void release_worker(server_worker *worker);

  /*******************
   * register_task *
   ******************/

  void register_task(server_receive *receive_task);
  void register_task(PrePredictTask *pre_prediction_task);
  void register_task(PredictTask *predict_task);
  void register_task(PostPredictTask *post_predict_task);
  void register_task(server_reply *reply_task);


  /*******************
   * dispatch_worker *
   ******************/


  // pipeline 5 steps
  // 1. receive
  void dispatch_worker(server_worker *&worker, server_receive *receive_task);
  // 2. before prediction
  void dispatch_worker(server_worker *&worker, PrePredictTask *pre_predict_task);
  // 3. prediction
  void dispatch_worker(server_worker *&worker, PredictTask *prediction_task);
  // 4. after prediction
  void dispatch_worker(server_worker *&worker, PostPredictTask *post_predict_task);
  // 5. reply
  void dispatch_worker(server_worker *&worker, server_reply *reply_task);

  void set_req_res_handler(sgs::ReqResHandler *req_res_handler) {
    req_res_handler_ = req_res_handler;
  }

  sgs::ReqResHandler *req_res_handler_;

 public:
  server_receive *get_server_receive() const {
    return m_receive_task;
  }
  server_receive *get_server_receive() {
    return m_receive_task;
  }

  server_reply *get_server_reply() const {
    return m_reply_task;
  }

  server_reply *get_server_reply() {
    return m_reply_task;
  }

  PrePredictTask *get_pre_predict_task() const {
    return m_pre_predict_task;
  }

  PrePredictTask *get_pre_predict_task() {
    return m_pre_predict_task;
  }

  PredictTask *get_predict_task() const {
    return m_predict_task;
  }

  PredictTask *get_predict_task() {
    return m_predict_task;
  }

  PostPredictTask *get_post_predict_task() const {
    return m_post_predict_task;
  }

  PostPredictTask *get_post_predict_task() {
    return m_post_predict_task;
  }

 public:

  void set_asset_manager(AssetManager *asset_manager) {
    m_asset_manager = asset_manager;
  }

  const AssetManager *get_asset_manager() const {
    return m_asset_manager;
  }

  AssetManager *get_asset_manager() {
    return m_asset_manager;
  }

 protected:
  pthread_mutex_t _stat_mutex;

 protected:
  server_receive *m_receive_task;
  PrePredictTask *m_pre_predict_task;
  PostPredictTask *m_post_predict_task;
  PredictTask *m_predict_task;
  server_reply *m_reply_task;
  AssetManager *m_asset_manager;
};

} // namespace framework
} // namespace sgs
