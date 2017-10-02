#include <gtest/gtest.h>

#include "Task1.hpp"
#include <ThreadPool/ThreadPool.hpp>

#define NB_THREAD 4

using namespace TP;

/*
  Tests ThreadPool with dynamic and static allocation.

  1.  We create 8 Task for a thread pool of 4. 
      Each task wait 400 ms.
      We test thread loading and the waiting queue with 8 tasks.
     
  2.  We wait until all the tasks have finished to test the main loop.
     
  3.  When it's finish we reload 6 tasks to test thread loading and 
      the waiting queue
*/

TEST(ThreadPoolTests, dynamicAllocation){

  ThreadPool<NB_THREAD> *threadPool = new ThreadPool<NB_THREAD>();

  Task1 task1(0,2);
  Task1 task2(1,2);
  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool->addThread(task1);
  threadPool->addThread(task2);
  threadPool->addThread(task3);
  threadPool->addThread(task4);
  threadPool->addThread(task5);
  threadPool->addThread(task6);
  threadPool->addThread(task7);

  while (threadPool->nbRunningThread() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool->addThread(task8);
  threadPool->addThread(task9);
  threadPool->addThread(task10);
  threadPool->addThread(task11);
  threadPool->addThread(task12);
  threadPool->addThread(task13);

  while (threadPool->nbRunningThread() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(ThreadPoolTests, staticAllocation){

  ThreadPool<NB_THREAD> threadPool;

  Task1 task1(0,2);
  Task1 task2(1,2);
  Task1 task3(2,2);
  Task1 task4(3,2);
  Task1 task5(4,2);
  Task1 task6(5,2);
  Task1 task7(6,2);

  threadPool.addThread(task1);
  threadPool.addThread(task2);
  threadPool.addThread(task3);
  threadPool.addThread(task4);
  threadPool.addThread(task5);
  threadPool.addThread(task6);
  threadPool.addThread(task7);

  while (threadPool.nbRunningThread() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  Task1 task8(7,2);
  Task1 task9(8,2);
  Task1 task10(9,2);
  Task1 task11(10,2);
  Task1 task12(11,2);
  Task1 task13(12,2);

  threadPool.addThread(task8);
  threadPool.addThread(task9);
  threadPool.addThread(task10);
  threadPool.addThread(task11);
  threadPool.addThread(task12);
  threadPool.addThread(task13);

  while (threadPool.nbRunningThread() > 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}