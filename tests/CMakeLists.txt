if(ENABLE_TESTING)

  MESSAGE(STATUS  "[Threadpool] Compile tests")

  # Add google test
  include(gtest.cmake)
  find_package (Threads)

  set(Sources
    ThreadPoolTests.cc
    Task1.cc
  )

  # ThreadPool tests
  add_executable(ThreadPoolTests ${Sources})
  target_link_libraries(ThreadPoolTests PRIVATE gtest ${CMAKE_THREAD_LIBS_INIT})

  # tests compilation Flags
  set(THREADPOOL_TEST_FLAGS "-O3 -std=c++11 -Wall -Wextra")
  set_target_properties( ThreadPoolTests PROPERTIES COMPILE_FLAGS ${THREADPOOL_TEST_FLAGS})

endif()
