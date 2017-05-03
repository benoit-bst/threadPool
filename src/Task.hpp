#ifndef ABSTRACT_TASK_HPP
#define ABSTRACT_TASK_HPP

using namespace std;

namespace TP {

/**
 * @brief Abstract task class
 */
class Task
{
  public:
    Task(){};
    virtual ~Task(){};
    virtual int id() = 0;
    virtual bool executeTask() = 0;
};

} // namespace TP

#endif