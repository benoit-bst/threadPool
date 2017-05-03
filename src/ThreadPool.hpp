#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

// Std
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

#include "Task.hpp"

namespace TP {

enum ThreadState
{
  Running = 0,
  Finish
};

/**
 * @brief Threadpool follow the threadpool pattern design
 * @details Create multi thread slot. Task are loaded in thread slot.
 * If there is to much task compared to the number of thread slot,
 * task are saved in a queue for waiting empty slot.
 */
template <size_t T>
class ThreadPool
{
  public:
    explicit ThreadPool();

    // Non-copyable
    ThreadPool (const ThreadPool &) = delete;
    ThreadPool & operator = (const ThreadPool &) = delete;

    ~ThreadPool();

    void addThread(TP::Task& task);
    int nbRunningThread();

  private:
    int m_nbThread; // Number of thread
    bool m_createEventLoop; // Authorizes event loop creation

    vector<future<bool> > m_threads; // Threadpool core
    vector<ThreadState > m_threadStates; // Each thread state are saved Finish/Running

    queue<TP::Task* > m_queue; // The task queue

    void eventLoop(); // Private event loop
};

/**
 * @brief Create threadpool
 *
 * @tparam T Number of thread
 */
template <size_t T>
ThreadPool<T>::ThreadPool()
  :m_nbThread(T)
{
  // Thread Table
  m_threads.resize(m_nbThread);

  // State Table
  m_threadStates.reserve(m_nbThread);
  for (int i = 0; i < m_nbThread; ++i){
    m_threadStates.push_back(Finish);
  }

  // Active event loop creation
  m_createEventLoop = true;
}

/**
 * @brief Add new task in Threadpool
 * @details Is a thread slot is available, the task is load also it is place in the queue
 *
 * @param task The new task
 */
template <size_t T>
void ThreadPool<T>::addThread(TP::Task& task)
{
  // Create event loop
  if (m_createEventLoop){
    thread(&ThreadPool::eventLoop, this).detach();
    m_createEventLoop = false;
  }

  // Add new task in a thread slot
  int enableSlot = false;
  for (int i = 0; i < m_nbThread; ++i)
  {
    // If a thread is Finish
    if (m_threadStates[i] == Finish){

      m_threads[i] = async(std::launch::async, &Task::executeTask, &task);
      m_threadStates[i] = Running;
      enableSlot = true;
      break;
    }
  }

  // Add new task in queue
  if (enableSlot == false){
    m_queue.push(&task);
  }
}

/**
 * @return Active thread Number
 */
template <size_t T>
int ThreadPool<T>::nbRunningThread()
{
  int counter = 0;
  for (int i = 0; i < m_nbThread; ++i)
  {
    if (m_threadStates[i] == Running){
      counter++;
    }
  }
  return counter;
}

/**
 * @brief Destructor
 */
 template <size_t T>
ThreadPool<T>::~ThreadPool()
{
  assert(nbRunningThread() == 0);
}

/**
 * @brief Event loop
 * @details Used to refresh threads states and insert task in threadpool if a slot is available
 */
template <size_t T>
void ThreadPool<T>::eventLoop(){

  // Forever
  for(;;){

    int enableSlot = false;
    int emptySlotNumber = 0;

    // Check threads states
    for (int i = 0; i < m_nbThread; ++i)
    {
      if (m_threadStates[i] == Running){

        std::future_status status = m_threads[i].wait_for(std::chrono::milliseconds(0));

        if (status == std::future_status::ready){
          m_threadStates[i] = Finish;
          enableSlot = true;
        }
      }
      else{
        enableSlot = true;
        emptySlotNumber++;
      }
    }

    // Insert task in the queue, if a slot is available
    if ((m_queue.size() > 0) && (enableSlot)){

      for (unsigned int i = 0; i < m_queue.size(); ++i)
      {
        for (int j = 0; j < m_nbThread; ++j)
        {
          if (m_threadStates[i] == Finish){

            m_threads[i] = async(std::launch::async, &Task::executeTask, m_queue.front());
            m_threadStates[i] = Running;
            m_queue.pop();
            break;
          }
        }
      }
    }

    // Stop loop
    if ((m_queue.size() == 0) && (emptySlotNumber == m_nbThread)){
       m_createEventLoop = true;
      break;
    }
  }
}

} // namespace TP

#endif