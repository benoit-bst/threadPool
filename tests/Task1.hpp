#ifndef _TASK1_HPP
#define _TASK1_HPP

#include <ThreadPool/Task.hpp>

/**
 * @brief Test class
 */
class Task1 : public TP::Task
{
  public:
    Task1(int id, int maxLoop);
    ~Task1();
    int id();
    bool executeTask();

  private:
    int m_id;
    int m_maxLoop;
};

#endif