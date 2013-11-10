// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef MUDUO_BASE_THREADPOOL_H
#define MUDUO_BASE_THREADPOOL_H

#include "Condition.h"
#include "Mutex.h"
#include "Thread.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <deque>

namespace muduo
{

class ThreadPool : boost::noncopyable
{
 public:
  typedef boost::function<void ()> Task;

  explicit ThreadPool(const std::string& name = std::string());
  ~ThreadPool();

  void start(int numThreads);
  void stop();

  void run(const Task& f);

 private:
  void runInThread();
  Task take();

  MutexLock mutex_;
  Condition cond_;
  std::string name_;
  boost::ptr_vector<muduo::Thread> threads_; //lzprgmr: start will have the threads run tasks - are the threads reused? yes :
                                              // in one thread: one task finished, it will try to get the next task fom queue_, if it is empty, it is wait, until next task get put in by (run)
  std::deque<Task> queue_;    // lzprgmr: put task into the threadpool
  bool running_;
};

}

#endif
