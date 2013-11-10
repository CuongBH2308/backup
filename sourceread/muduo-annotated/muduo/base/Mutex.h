// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_MUTEX_H
#define MUDUO_BASE_MUTEX_H

#include <muduo/base/CurrentThread.h>
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>

#ifdef CHECK_PTHREAD_RETURN_VALUE

#ifdef NDEBUG
// lzprgmr: for extern "C"  in C++ and nothing in C
__BEGIN_DECLS
extern void __assert_perror_fail (int errnum,
                                  const char *file,
                                  unsigned int line,
                                  const char *function)
    __THROW __attribute__ ((__noreturn__)); // lzprgmr: 该属性通知编译器函数从不返回值，当遇到类似函数需要返回值而却不可能运行到返回值处就已经退出来的情况，该属性可以避免出现错误信息。C库函数中的abort（）和exit（）的声明格式就采用了这种格式
__END_DECLS
#endif

// lzprgmr: __builtin_expect: tell compiler which branch is mostly expected, thus generate machine code in more efficient way (place true/false branch)
#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})  //lzprgmr: the predefined func name?

#else  // CHECK_PTHREAD_RETURN_VALUE

// lzprmgr: typeof是gcc对C语言的一个扩展保留字，用于声明变量类型
// __typeof__(errnum) == decltype(errnum) in C++11
#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       assert(errnum == 0); (void) errnum;})      // lzprgmr: what is (void) errnum for?

#endif // CHECK_PTHREAD_RETURN_VALUE

namespace muduo
{

// Use as data member of a class, eg.
//
// class Foo
// {
//  public:
//   int size() const;
//
//  private:
//   mutable MutexLock mutex_; //lzprgmr: why mutable? because a const Foo object also need to be guided using mutex_, which would change the state of mutex_
//   std::vector<int> data_; // GUARDED BY mutex_
// };

// lzprgmr: pthread function used:
// pthread_mutex_init 
// pthread_mutex_lock
// pthread_mutext_unlock
// pthread_mutex_destroy
class MutexLock : boost::noncopyable
{
 public:
  MutexLock()
    : holder_(0)
  {
    MCHECK(pthread_mutex_init(&mutex_, NULL));
  }

  ~MutexLock()
  {
    assert(holder_ == 0);
    MCHECK(pthread_mutex_destroy(&mutex_));
  }

  // must be called when locked, i.e. for assertion
  bool isLockedByThisThread() const
  {
    return holder_ == CurrentThread::tid();
  }

  void assertLocked() const
  {
    assert(isLockedByThisThread());
  }

  // internal usage

  void lock()
  {
    MCHECK(pthread_mutex_lock(&mutex_));
    assignHolder();
  }

  void unlock()
  {
    unassignHolder();
    MCHECK(pthread_mutex_unlock(&mutex_));
  }

  pthread_mutex_t* getPthreadMutex() /* non-const */
  {
    return &mutex_;
  }

 private:
  friend class Condition;

  // lzprgmr: what is this for?
  class UnassignGuard : boost::noncopyable
  {
   public:
    UnassignGuard(MutexLock& owner)
      : owner_(owner)
    {
      owner_.unassignHolder();
    }

    ~UnassignGuard()
    {
      owner_.assignHolder();
    }

   private:
    MutexLock& owner_;
  };

  void unassignHolder()
  {
    holder_ = 0;
  }

  void assignHolder()
  {
    holder_ = CurrentThread::tid();
  }

  pthread_mutex_t mutex_;
  pid_t holder_;
};

// Use as a stack variable, eg.
// int Foo::size() const
// {
//   MutexLockGuard lock(mutex_);
//   return data_.size();
// }
class MutexLockGuard : boost::noncopyable
{
 public:
  explicit MutexLockGuard(MutexLock& mutex)
    : mutex_(mutex)
  {
    mutex_.lock();
  }

  ~MutexLockGuard()
  {
    mutex_.unlock();
  }

 private:

  MutexLock& mutex_;
};

}

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif  // MUDUO_BASE_MUTEX_H
