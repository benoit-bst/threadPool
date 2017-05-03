if(ENABLE_TESTING)

  MESSAGE("-- [Threadpool] - Compile tests")

   # QT
  find_package(Qt4 4.6.0 COMPONENTS QtCore QtTest REQUIRED)
  include(${QT_USE_FILE})

  unset( MOC_SOURCES)
  qt4_wrap_cpp( MOC_SOURCES ThreadPoolTests.hpp)
  add_executable( ThreadPoolTests ThreadPoolTests.cpp Task1.cpp ${MOC_SOURCES})
  target_link_libraries( ThreadPoolTests ${QT_LIBRARIES})

endif()