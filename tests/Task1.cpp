#include "Task1.hpp"

#include <thread>
#include <chrono>

Task1::Task1(int id, int maxLoop)
 : m_id(id)
 , m_maxLoop(maxLoop)
{
}

Task1::~Task1()
{
}

int Task1::id()
{
  return m_id;
}

bool Task1::executeTask()
{
  // test loop
  int localCounter = 0;
  while(localCounter < m_maxLoop){
    localCounter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  return true;
}