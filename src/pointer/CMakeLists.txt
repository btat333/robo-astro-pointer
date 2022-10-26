cmake_minimum_required(VERSION 3.18)

# set the project name
project(POINTER VERSION 1.0)

configure_file(pointer.h.in pointer.h)

# add the MathFunctions library
add_subdirectory(../util Util)
add_subdirectory(../stepper-driver StepperDriver)
add_subdirectory(../laser-driver LaserDriver)

# add the executable
add_executable(POINTER pointer.c)

add_library(PointerUtil pointer_util.c)
target_link_libraries(POINTER 
                        PUBLIC PointerUtil
                        PUBLIC Utils
                        PUBLIC LaserDriver
                        PUBLIC StepperDriver
                        PUBLIC zmq
                        PUBLIC pthread
                        PUBLIC m
                        PUBLIC wiringPi)

target_include_directories(POINTER PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS POINTER DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/pointer.h"
  DESTINATION include
  )

enable_testing()
