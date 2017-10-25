#pragma once

// Your class must to inherit of TP::Task
#include <ThreadPool/Task.h>

/**
 * @brief Test class
 */
class Task1 : public TP::Task
{
  public:

    //---------------------------------------
    // Your task have to default constructor
    // and run method.
    Task1() = default;
    void run();
    //---------------------------------------

    Task1(int id, int maxLoop);
    ~Task1();
    int id();

  private:
    int m_id;
    int m_maxLoop;
};
