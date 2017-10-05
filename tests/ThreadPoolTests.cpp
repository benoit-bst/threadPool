#include <gtest/gtest.h>

#include "Task1.hpp"
#include <ThreadPool/ThreadPool.hpp>
#include <random>

#define NB_THREAD 4
#define NB_TASK 25

using namespace TP;

/*
  Tests ThreadPool with dynamic allocation.

  1.  We create 7 Task for a thread pool of 4.
      Each task wait 400 ms.
      We test thread loading and the waiting queue with 7 tasks.

  2.  We wait until all the tasks have finished to test the main loop.

  3.  When it's finish we reload 6 tasks to test thread loading and 
      the waiting queue
*/
TEST(ThreadPoolTests, dynamicAllocation){

  ThreadPool<NB_THREAD, Task1> *threadPool = new ThreadPool<NB_THREAD, Task1>;

  Task1 task1(0,2);
  Task1 task2(1,2);
  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool->addTask(task1);
  ASSERT_EQ(threadPool->nbRunningTask(), 1);
  threadPool->addTask(task2);
  ASSERT_EQ(threadPool->nbRunningTask(), 2);
  threadPool->addTask(task3);
  ASSERT_EQ(threadPool->nbRunningTask(), 3);
  threadPool->addTask(task4);
  ASSERT_EQ(threadPool->nbRunningTask(), 4);
  threadPool->addTask(task5);
  ASSERT_EQ(threadPool->nbRunningTask(), 4); // NB_THREAD == 4
  threadPool->addTask(task6);
  threadPool->addTask(task7);

  ASSERT_EQ(threadPool->eventLoopIsActive(), true);

  while (threadPool->nbRunningTask() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(threadPool->eventLoopIsActive(), false);

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool->addTask(task8);
  ASSERT_EQ(threadPool->nbRunningTask(), 1);
  threadPool->addTask(task9);
  ASSERT_EQ(threadPool->nbRunningTask(), 2);
  threadPool->addTask(task10);
  ASSERT_EQ(threadPool->nbRunningTask(), 3);
  threadPool->addTask(task11);
  ASSERT_EQ(threadPool->nbRunningTask(), 4);
  threadPool->addTask(task12);
  ASSERT_EQ(threadPool->nbRunningTask(), 4); // NB_THREAD == 4
  threadPool->addTask(task13);

  ASSERT_EQ(threadPool->eventLoopIsActive(), true);

  while (threadPool->nbRunningTask() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(threadPool->eventLoopIsActive(), false);

  delete threadPool;
}

/*
  Tests ThreadPool with static allocation.

  1.  We create 7 Task for a thread pool of 4.
      Each task wait 400 ms.
      We test thread loading and the waiting queue with 7 tasks.

  2.  We wait until all the tasks have finished to test the main loop.

  3.  When it's finish we reload 6 tasks to test thread loading and 
      the waiting queue
*/
TEST(ThreadPoolTests, staticAllocation){

  ThreadPool<NB_THREAD, Task1> threadPool;

  Task1 task1(0,2);
  Task1 task2(1,2);
  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool.addTask(task1);
  ASSERT_EQ(threadPool.nbRunningTask(), 1);
  threadPool.addTask(task2);
  ASSERT_EQ(threadPool.nbRunningTask(), 2);
  threadPool.addTask(task3);
  ASSERT_EQ(threadPool.nbRunningTask(), 3);
  threadPool.addTask(task4);
  ASSERT_EQ(threadPool.nbRunningTask(), 4);
  threadPool.addTask(task5);
  ASSERT_EQ(threadPool.nbRunningTask(), 4); // NB_THREAD == 4
  threadPool.addTask(task6);
  threadPool.addTask(task7);

  ASSERT_EQ(threadPool.eventLoopIsActive(), true);

  while (threadPool.nbRunningTask() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(threadPool.eventLoopIsActive(), false);

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool.addTask(task8);
  ASSERT_EQ(threadPool.nbRunningTask(), 1);
  threadPool.addTask(task9);
  ASSERT_EQ(threadPool.nbRunningTask(), 2);
  threadPool.addTask(task10);
  ASSERT_EQ(threadPool.nbRunningTask(), 3);
  threadPool.addTask(task11);
  ASSERT_EQ(threadPool.nbRunningTask(), 4);
  threadPool.addTask(task12);
  ASSERT_EQ(threadPool.nbRunningTask(), 4); // NB_THREAD == 4
  threadPool.addTask(task13);

  ASSERT_EQ(threadPool.eventLoopIsActive(), true);

  while (threadPool.nbRunningTask() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(threadPool.eventLoopIsActive(), false);
}

/*
  Tests ThreadPool with with tasks random loop time
*/
TEST(ThreadPoolTests, randomTask){

  // Random
  random_device rd;
  mt19937 eng(rd());
  uniform_int_distribution<> distr(0,20);

  ThreadPool<NB_THREAD, Task1> threadPool;

  // Create tasks with random loop time
  vector<Task1> tasks;
  for (unsigned int i = 0; i < NB_TASK; ++i){
    tasks.push_back(Task1(i,distr(eng)));
  }

  // Add tasks
  for (unsigned int i = 0; i < tasks.size(); ++i){
    threadPool.addTask(tasks[i]);
  }

  ASSERT_EQ(threadPool.nbRunningTask(), 4); // NB_THREAD == 4
  ASSERT_EQ(threadPool.eventLoopIsActive(), true);

  while (threadPool.nbRunningTask() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(threadPool.eventLoopIsActive(), false);

}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
