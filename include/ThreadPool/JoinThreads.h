#pragma once

#include <thread>
#include <vector>

using namespace std;

namespace TP {

/**
 * @brief Join threads pattern class
 * 
 * @detials This class makes sure that all threads are reachable
 * during the destruction.
 */
class JoinThreads
{
public:

  explicit JoinThreads(std::vector<std::thread> & threads):
    _threads(threads)
  {}

  ~JoinThreads()
  {
    for(unsigned long i = 0; i < _threads.size(); ++i)
    {
      if(_threads[i].joinable())
      _threads[i].join();
    }
  }

private:
  std::vector<std::thread> & _threads;
};

} // namespace TP
