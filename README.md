# Introduction

Threadpool follow the threadpool pattern design :
- Create multi thread slot
- Task are loaded in thread slot.
- If there is to much task compared to the number of thread slot, task are saved in a queue for waiting empty slot.

# Examples

See tests in /tests

# Compilation

## Environment

Required tools et library :

* CMake, version >= 2.8.0
* libqt4-test, version >= 4.8

debian installation :
```shell
$ sudo apt-get install cmake libqt4-test
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