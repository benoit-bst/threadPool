if(ENABLE_TESTING)

  MESSAGE("-- [Threadpool] - Compile tests")

  SET(Sources
  ThreadPoolTests.cpp
  Task1.cpp
  )

   # gtest
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})

  add_executable(ThreadPoolTests ${Sources})
  target_link_libraries(ThreadPoolTests ${GTEST_LIBRARIES} pthread)

endif()