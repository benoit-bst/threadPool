#pragma once

namespace TP {

/**
 * @brief Abstract task class
 */
class Task
{
  public:
    Task(){};
    virtual ~Task(){};
    virtual void run() = 0;
};

} // namespace TP
