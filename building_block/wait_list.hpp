#ifndef BASE_WAIT_LIST_HPP__
#define BASE_WAIT_LIST_HPP__

#include <pthread.h>
#include "linked_list.hpp"

template<typename T, linked_list_node_t T::*list_node>
class wait_list_t : public linked_list_t<T, list_node> {
 public:
  wait_list_t() : _alive(1), _num(0) {
    pthread_mutex_init(&_mutex, NULL);
    pthread_cond_init(&_cond, NULL);
  }

  ~wait_list_t() {
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_mutex);
  }

  int len() {
    return _num;
  }

  void put(T &node) {
    pthread_mutex_lock(&_mutex);
    if (_alive) {
      this->add(node);
      ++_num;
    }
    pthread_cond_signal(&_cond);
    pthread_mutex_unlock(&_mutex);
  }

  T *get() {
    T *ret;
    pthread_mutex_lock(&_mutex);
    while (_alive && linked_list_t<T, list_node>::is_empty())
      pthread_cond_wait(&_cond, &_mutex);
    if (_alive) {
      ret = this->entry(*linked_list_t<T, list_node>::_head.prev);
      this->del(*ret);
      --_num;
    } else {
      ret = NULL;
    }
    pthread_mutex_unlock(&_mutex);
    return ret;
  }

  T *get(const struct timespec *abstime) {
    T *ret;
    pthread_mutex_lock(&_mutex);
    while (_alive && linked_list_t<T, list_node>::is_empty()) {
      if (pthread_cond_timedwait(&_cond, &_mutex, abstime) != 0) {
        pthread_mutex_unlock(&_mutex);
        return NULL;
      }
    }
    if (_alive) {
      ret = this->entry(*linked_list_t<T, list_node>::_head.prev);
      this->del(*ret);
      --_num;
    } else {
      ret = NULL;
    }
    pthread_mutex_unlock(&_mutex);
    return ret;
  }

  T *get_from_head() {
    T *ret;
    pthread_mutex_lock(&_mutex);
    while (_alive && linked_list_t<T, list_node>::is_empty())
      pthread_cond_wait(&_cond, &_mutex);
    if (_alive) {
      ret = this->entry(*linked_list_t<T, list_node>::_head.next);
      this->del(*ret);
      --_num;
    } else {
      ret = NULL;
    }
    pthread_mutex_unlock(&_mutex);
    return ret;
  }

  void flush() {
    pthread_mutex_lock(&_mutex);
    _alive = 0;
    pthread_cond_broadcast(&_cond);
    pthread_mutex_unlock(&_mutex);
  }

 protected:
  pthread_mutex_t _mutex;
  pthread_cond_t _cond;
  int _alive;
  int _num;
};

#endif /* BASE_WAIT_LIST_HPP__ */

