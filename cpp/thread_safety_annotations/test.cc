/*
 * This is an adapted example from https://clang.llvm.org/docs/ThreadSafetyAnalysis.html#mutexheader
 */

#include "Mutex.h"

class BankAccount {
private:
  YouCompleteMe::Mutex mu;
  int balance GUARDED_BY(mu);

  void depositImpl(int amount) {
    balance += amount;       // WARNING! Cannot write balance without locking mu.
  }

  void withdrawImpl(int amount) REQUIRES(mu) {
    balance -= amount;       // OK. Caller must have locked mu.
  }

public:
  void withdraw(int amount) {
    // Change UniqueLock to LockGuard to use a std::lock_guard< std::mutex> wrapper
    YouCompleteMe::UniqueLock lock(mu);
    withdrawImpl(amount);    // OK.  We've locked mu.
  }                          // WARNING!  Failed to unlock mu. - Not triggered with UniqueLock or LockGuard

  void transferFrom(BankAccount& b, int amount) {
    mu.lock();
    b.withdrawImpl(amount);  // WARNING!  Calling withdrawImpl() requires locking b.mu.
    depositImpl(amount);     // OK.  depositImpl() has no requirements.
    mu.unlock();
  }
};
