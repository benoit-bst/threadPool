#pragma once

// Std
#include <thread>
#include <vector>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "JoinThreads.h"

using namespace std;

namespace TP {

/**
 * @brief Thread pool pattern design
 * 
 * @details Create multi thread slot. Task are loaded in thread slot.
 * If there is to much task compared to the number of thread slot,
 * task are saved in a queue for waiting empty slot.
 * 
 * To run with ThreadPool, your task must inherit of Task <ThreadPool/Task.hpp>.
 * Task is a pur virtual class. It give you rules to create
 * your own task :
 * - Add default constructor
 * - Add void run() method (run is the core method in Tread)
 * 
 * @nwarning Beware, ThreadPool class is not a singleton. 
 * You have to make sure you create only one instance in your program.
 */
template<size_t NbThread, typename TaskType>
class ThreadPool
{

public:

  explicit ThreadPool();
  ~ThreadPool();

  void submit(const TaskType & task);
  void submit(TaskType && task);

  ThreadPool (const ThreadPool &) = delete;
  ThreadPool & operator = (const ThreadPool &) = delete;

  ThreadPool(ThreadPool&& other) = delete;
  ThreadPool& operator=(ThreadPool&& other) = delete;

private:

  std::atomic_bool _done;
  std::queue<TaskType> _work_queue;
  std::vector<std::thread> _threads;
  JoinThreads _joiner;
  std::condition_variable _cond;
  std::mutex _mutex;

  bool try_pop(TaskType & poppedValue);
  void worker_thread();

};

/**
 * @brief Create thread pool
 *
 * @tparam NbThread Number of thread
 * @tparam TaskType The type structure
 */
template<size_t NbThread, typename TaskType>
ThreadPool<NbThread, TaskType>::ThreadPool()
  :_done(false),
  _joiner(_threads)
{
  try{
    for(unsigned i = 0; i < NbThread; ++i){
      _threads.push_back(
      std::thread(&ThreadPool::worker_thread,this));
    }
  }
  catch(...){
    _done=true;
    throw;
  }
}

/**
 * @brief Destruct thread pool
 * 
 * @warning Threadpool is design with no synch thread.
 * When you call destructor, an order is sending to all threads.
 * When Runing tasks are finish, the associated thread is destruct.
 */
template <size_t NbThread, typename TaskType>
ThreadPool<NbThread, TaskType>::~ThreadPool()
{
  _done=true;
  _cond.notify_all();
}

/**
 * @brief Add new task in Threadpool
 * @param task The new task to load
 */
template <size_t NbThread, typename TaskType>
void ThreadPool<NbThread, TaskType>::submit(const TaskType & task)
{
  std::unique_lock<std::mutex> mlock(_mutex);
  _work_queue.push(task);
  mlock.unlock();
  _cond.notify_one();
}

/**
 * @brief Add new task in Threadpool
 * @param task The new task to load
 * 
 * @note Overload for move semantic
 */
template <size_t NbThread, typename TaskType>
void ThreadPool<NbThread, TaskType>::submit(TaskType && task)
{
  std::unique_lock<std::mutex> mlock(_mutex);
  _work_queue.push(std::move(task));
  mlock.unlock();
  _cond.notify_one();
}

/**
 * @brief Private Simple try and pop for internal queue.
 * If internal queue is empty, we don't
 * pop element and return false.
 * This function is not blocking.
 * 
 * @param poppedValue the Popped element
 * @return If data is popped return true, else false
 */
template <size_t NbThread, typename TaskType>
bool ThreadPool<NbThread, TaskType>::try_pop(TaskType& poppedValue)
{
  std::unique_lock<std::mutex> mlock(_mutex);
  if (_work_queue.empty()){
    return false;
  }
  poppedValue = _work_queue.front();
  _work_queue.pop();
  return true;
}

/**
 * @brief private worker_thread loop
 * Internal loop for one thread slot.
 */
template <size_t NbThread, typename TaskType>
void ThreadPool<NbThread, TaskType>::worker_thread()
{
  while(!_done){
    TaskType task;
    if(try_pop(task)){
      task.run();
    }
    else
    {
      std::unique_lock<std::mutex> mlock(_mutex);
      std::this_thread::yield();
      _cond.wait(mlock);
    }
  }
}

} // namespace TP
