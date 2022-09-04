cmake_minimum_required(VERSION 3.18)

# set the project name
project(MAGNET VERSION 1.0)

configure_file(magnetometer.h.in magnetometer.h)

# add the Util library
add_subdirectory(../util Util)

# add the executable
add_executable(MAGNET magnetometer.c)

target_link_libraries(MAGNET 
                        PUBLIC Utils
                        PUBLIC zmq
                        PUBLIC wiringPi
                        PUBLIC m)

target_include_directories(MAGNET PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS MAGNET DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/magnetometer.h"
  DESTINATION include
  )

enable_testing()
