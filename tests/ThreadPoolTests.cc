#include <gtest/gtest.h>

#include "Task1.h"
#include <ThreadPool/ThreadPool.h>
#include <random>

#define NB_THREAD 4

using namespace TP;

/*
  Tests ThreadPool with dynamic allocation.

  1.  We create 7 Task for a thread pool of 4.
      Each task wait 80 ms.
      We test thread loading and the waiting queue with 7 tasks.

  2.  We wait until all the tasks are finished.

  3.  When it's finish we reload 6 tasks to test thread loading and 
      the waiting queue
*/
TEST(ThreadPoolTests, dynamicAllocation){

  ThreadPool<NB_THREAD, Task1> *threadPool = new ThreadPool<NB_THREAD, Task1>;

  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool->submit(Task1(0,2));
  threadPool->submit(Task1(1,2));
  threadPool->submit(task3);
  threadPool->submit(task4);
  threadPool->submit(task5);
  threadPool->submit(task6);
  threadPool->submit(task7);

  std::this_thread::sleep_for(std::chrono::milliseconds(1200));

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool->submit(task8);
  threadPool->submit(task9);
  threadPool->submit(task10);
  threadPool->submit(task11);
  threadPool->submit(task12);
  threadPool->submit(task13);

  std::this_thread::sleep_for(std::chrono::milliseconds(1200));

  delete threadPool;
}

/*
  Tests ThreadPool with static allocation.

  1.  We create 7 Task for a thread pool of 4.
      Each task wait 400 ms.
      We test thread loading and the waiting queue with 7 tasks.

  2.  We wait until all the tasks have finished

  3.  When it's finish we reload 6 tasks to test thread loading and 
      the waiting queue
*/
TEST(ThreadPoolTests, staticAllocation){

  ThreadPool<NB_THREAD, Task1> threadPool;

  const Task1 task2(1,2);
  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool.submit(Task1(0,2));
  threadPool.submit(task2);
  threadPool.submit(task3);
  threadPool.submit(task4);
  threadPool.submit(task5);
  threadPool.submit(task6);
  threadPool.submit(task7);

  std::this_thread::sleep_for(std::chrono::milliseconds(1200));

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool.submit(task8);
  threadPool.submit(task9);
  threadPool.submit(task10);
  threadPool.submit(task11);
  threadPool.submit(task12);
  threadPool.submit(task13);

  std::this_thread::sleep_for(std::chrono::milliseconds(1200));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
