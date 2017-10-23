[![Build Status](https://travis-ci.org/benoit-bst/threadPool.svg?branch=master)](https://travis-ci.org/benoit-bst/threadPool)

# Introduction

Threadpool Class follows the threadpool pattern design :
- Create multi thread slot
- Task are loaded in thread slot.
- If there is to much task compared to the number of thread slot, task are saved in a queue for waiting empty slot.

Using of C++11 std::thread

## Examples

See tests in /tests

## Environment

Required tools et library :

* CMake >= 3.5.1
* gcc >= 5.4.0

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
NOTES:

* `ENABLE_TESTING` allow tests compilation

## Running tests

```shell
# Inside project_root/tests
$ ./ThreadPoolTests
```
