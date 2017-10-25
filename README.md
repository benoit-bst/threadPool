[![Build Status](https://travis-ci.org/benoit-bst/threadPool.svg?branch=master)](https://travis-ci.org/benoit-bst/threadPool)
[![Coverage Status](https://coveralls.io/repos/github/benoit-bst/threadPool/badge.svg?branch=master)](https://coveralls.io/github/benoit-bst/threadPool?branch=master)

# Introduction

Threadpool Class follows the threadpool pattern design :
- Create multi thread slot
- Task are loaded in thread slot.
- If there is to much task compared to the number of thread slot, task are saved in a queue for waiting empty slot.

Your own Task must follow rules by inherinting from Task in *<ThreadPool/Task.hpp>* :

* Add default constructor
* Add *void run()* method (run is the core method in Tread)

ThreadPool class is not a singleton. You have to make sure you create only one instance in your program. Furthermore, ThreadPool is non-copyable.

Using of **C++11 std::thread**.

## Examples

```c++

  #include <ThreadPool/ThreadPool.h>
  #include "PersonalTask.h"

  using namespace TP;

  ThreadPool<NB_THREAD, PersonalTask> threadPool;

  threadPool.submit( PersonalTask(0) );
  threadPool.submit( PersonalTask(1) );
  threadPool.submit( PersonalTask(2) );

```

## Environment

Required tools and libraries :

* CMake >= 2.8.0
* gcc >= 4.9.2
* clang >= 3.5.0

debian installation :

```shell
$ sudo apt-get install cmake gcc
```

## Source recovery

```
git clone https://github.com/benoit-bst/threadPool
```

## Compilation

```shell
# Create project_root/build
$ mkdir build
$ cd build
$ cmake -DENABLE_TESTING=ON ..
$ make
```

NOTES :

* `ENABLE_TESTING` allows testing compilation
* if you want to compile with clang, add `-DCMAKE_CXX_COMPILER="/usr/bin/clang++"` option

## Running tests

```shell
# Inside project_root/tests
$ ./ThreadPoolTests
```

## Library integration

Active modern c++ flag in your compiler like -std=c++11 and put in your cmake file :

```cmake
add_subdirectory(ThreadPool)
include_directories( ${ThreadPool_headers_dir} )
```
