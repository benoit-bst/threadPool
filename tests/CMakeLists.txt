if(ENABLE_TESTING)

  MESSAGE("-- [Threadpool] - Compile tests")
  
  include(gtest.cmake)
  find_package (Threads)

  SET(Sources
  ThreadPoolTests.cpp
  Task1.cpp
  )

  add_executable(ThreadPoolTests ${Sources})
  target_link_libraries(ThreadPoolTests PRIVATE gtest ${CMAKE_THREAD_LIBS_INIT})
  # target_link_libraries(ThreadPoolTests gtest pthread)

endif()
