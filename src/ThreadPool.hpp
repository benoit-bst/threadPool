#pragma once

// Std
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <cassert>

#include "Task.hpp"

using namespace std;

namespace TP {

enum ThreadState
{
  Running = 0,
  Finish
};

mutex myMutex;

/**
 * @brief Threadpool follow the thread pool pattern design
 * 
 * @details Create multi thread slot. Task are loaded in thread slot.
 * If there is to much task compared to the number of thread slot,
 * task are saved in a queue for waiting empty slot.
 * A event loop is created to manage the thread pool.
 * 
 * @nwarning Beware, ThreadPool class is not a singleton. 
 * You have to make sure you create only one instance in your program.
 */
template <size_t NbThread, typename TaskType>
class ThreadPool
{
  public:

    explicit ThreadPool();
    ~ThreadPool();

    void addTask(TaskType& task);
    int nbRunningTask() const ;
    bool eventLoopIsActive() const ;

    ThreadPool (const ThreadPool &) = delete;
    ThreadPool & operator = (const ThreadPool &) = delete;

    ThreadPool(ThreadPool&& other) = delete;
    ThreadPool& operator=(ThreadPool&& other) = delete;

  private:

    std::thread m_threads[NbThread]; // Threadpool core
    int m_threadStates[NbThread];    // Each thread state are saved Finish/Running

    queue<TaskType> m_queue; // The task queue

    bool m_createEventLoop; // even loop launch flag
    void eventLoop();       // Private event loop
};

/**
 * @brief Create thread pool
 *
 * @tparam NbThread Number of thread
 * @tparam TaskType The type structure
 */
template <size_t NbThread, typename TaskType>
ThreadPool<NbThread, TaskType>::ThreadPool()
  : m_createEventLoop(false)
{
  for (unsigned int i = 0; i < NbThread; ++i){
    m_threadStates[i] = Finish;
  }
}

/**
 * @brief Destruct thread pool
 * 
 * @warning Threadpool is design with no synch thread (detach). So when a task is loaded, 
 * you no longer the hand on it. You have to make sure that all threads are finished
 * before the destruction.
 */
 template <size_t NbThread, typename TaskType>
ThreadPool<NbThread, TaskType>::~ThreadPool()
{
  assert(nbRunningTask() == 0);
}

/**
 * @brief Add new task in Threadpool
 * @details If there is not thread slot available, the task is kept in backup queue
 *
 * @param task The new task
 */
template <size_t NbThread, typename TaskType>
void ThreadPool<NbThread, TaskType>::addTask(TaskType& task)
{
  myMutex.lock(); //----------------

  // Create event loop
  if (!m_createEventLoop){
    thread(&ThreadPool::eventLoop, this).detach();
    m_createEventLoop = true;
  }

  bool addInQueue = true;

  for (unsigned int i = 0; i < NbThread; ++i)
  {
    // If a thread is Finish
    if (m_threadStates[i] == Finish){
      m_threadStates[i] = Running;
      task.state        = &m_threadStates[i];
      m_threads[i]      = thread(&TaskType::executeTask, task);
      m_threads[i].detach();
      addInQueue = false;
      break;
    }
  }

  // Add new task in queue
  if (addInQueue){
    m_queue.push(task);
  }

  myMutex.unlock(); //----------------
}

/**
 * @return Active thread Number
 */
template <size_t NbThread, typename TaskType>
int ThreadPool<NbThread, TaskType>::nbRunningTask() const 
{
  unsigned int nbTask = 0;
  for (unsigned int i = 0; i < NbThread; ++i){
    if (m_threadStates[i] == Running)
      nbTask++;
  }
  return nbTask;
}

/**
 * @return Event loop state
 */
template <size_t NbThread, typename TaskType>
bool ThreadPool<NbThread, TaskType>::eventLoopIsActive() const 
{
  return m_createEventLoop;
}

/**
 * @brief Event loop
 * @details Used to refresh threads states and insert task in threadpool if a slot is available
 */
template <size_t NbThread, typename TaskType>
void ThreadPool<NbThread, TaskType>::eventLoop(){

  // Forever
  for(;;){

    unsigned int emptySlotNumber = 0;

    // Check threads states
    bool lockOK = myMutex.try_lock(); //----------------
    if (lockOK){

      for (unsigned int i = 0; i < NbThread; ++i){

        if (m_threadStates[i] == Finish){

          // Create new task
          if (!m_queue.empty()){
            TaskType & tmp    = m_queue.front();
            m_threadStates[i] = Running;
            tmp.state         = &m_threadStates[i];
            m_threads[i]      = thread(&TaskType::executeTask, tmp);
            m_threads[i].detach();
            m_queue.pop();
            break;
          }
          // increment empty slot number
          else{
            emptySlotNumber++;
          }
        }
      }

      // Stop loop if empty slot == number of slot
      if (emptySlotNumber == NbThread){
        m_createEventLoop = false;
        myMutex.unlock(); //----------------
        return;
      }
      
      myMutex.unlock(); //----------------
    } // lockOK

  }// for(;;)
}

} // namespace TP
