#ifndef BENCHMARK_MUTEX_H_
#define BENCHMARK_MUTEX_H_

#include <mutex>

// Enable thread safety attributes only with clang.
// The attributes can be safely erased when compiling with other compilers.
#if defined(__clang__) && (!defined(SWIG))
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   __attribute__((x))
#else
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   // no-op
#endif

#define CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(capability(x))

#define SCOPED_CAPABILITY THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)

#define GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))

#define PT_GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))

#define ACQUIRED_BEFORE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))

#define ACQUIRED_AFTER(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))

#define REQUIRES(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(requires_capability(__VA_ARGS__))

#define REQUIRES_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(requires_shared_capability(__VA_ARGS__))

#define ACQUIRE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

#define ACQUIRE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquire_shared_capability(__VA_ARGS__))

#define RELEASE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define RELEASE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(release_shared_capability(__VA_ARGS__))

#define TRY_ACQUIRE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_capability(__VA_ARGS__))

#define TRY_ACQUIRE_SHARED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_shared_capability(__VA_ARGS__))

#define EXCLUDES(...) THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

#define ASSERT_CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(assert_capability(x))

#define ASSERT_SHARED_CAPABILITY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_capability(x))

#define RETURN_CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))

#define NO_THREAD_SAFETY_ANALYSIS \
  THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)

namespace YouCompleteMe {

// NOTE: Wrappers for std::mutex and std::unique_lock are provided so that
// we can annotate them with thread safety attributes and use the
// -Wthread-safety warning with clang. The standard library types cannot be
// used directly because they do not provided the required annotations.
class CAPABILITY("mutex") Mutex {
 public:
  Mutex() {}

  void lock() ACQUIRE() { mut_.lock(); }
  void unlock() RELEASE() { mut_.unlock(); }
  std::mutex& native_handle() { return mut_; }

 private:
  std::mutex mut_;
};

class SCOPED_CAPABILITY UniqueLock {
  typedef std::unique_lock<std::mutex> UniqueLockImp;

 public:
  UniqueLock(Mutex& m) ACQUIRE(m) : ul_(m.native_handle()) {}
  ~UniqueLock() RELEASE() {}
  UniqueLockImp& native_handle() { return ul_; }

 private:
  UniqueLockImp ul_;
};

class SCOPED_CAPABILITY LockGuard {
  typedef std::lock_guard< std::mutex > LockGuardImp;
public:
  LockGuard(Mutex& m) ACQUIRE(m) : lg_(m.native_handle()) {}
  ~LockGuard() RELEASE() {}
  LockGuardImp& native_handle() { return lg_; }
private:
  LockGuardImp lg_;
};

} // namespace YouCompleteMe

#endif
