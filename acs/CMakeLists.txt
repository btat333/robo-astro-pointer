cmake_minimum_required(VERSION 3.18)

# set the project name
project(ACS VERSION 1.0)

configure_file(acs.h.in acs.h)

# add the MathFunctions library
add_subdirectory(../util Util)

# add the executable
add_executable(ACS acs.c)

target_link_libraries(ACS 
                        PUBLIC Utils
                        PUBLIC zmq
                        PUBLIC pthread)

target_include_directories(ACS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS ACS DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/acs.h"
  DESTINATION include
  )

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ACS)
