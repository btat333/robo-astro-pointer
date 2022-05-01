cmake_minimum_required(VERSION 3.18)

# set the project name
project(GPS VERSION 1.0)

configure_file(gps.h.in gps.h)

# add the MathFunctions library
add_subdirectory(../util Util)

# add the executable
add_executable(GPS gps.c)

target_link_libraries(GPS 
                        PUBLIC Utils
                        PUBLIC zmq
                        PUBLIC wiringPi)

target_include_directories(GPS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS GPS DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/gps.h"
  DESTINATION include
  )

enable_testing()

# does the application run
add_test(NAME Runs COMMAND GPS)
