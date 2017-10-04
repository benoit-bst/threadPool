#pragma once

#define FINISH_TASK_FLAG *state = 1;

using namespace std;

namespace TP {

/**
 * @brief Abstract task class
 */
class Task
{
  public:
    Task():state(0){};
    virtual ~Task(){};
    virtual int id() = 0;
    virtual void executeTask() = 0;

    int* state;
};

} // namespace TP
