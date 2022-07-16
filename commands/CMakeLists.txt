cmake_minimum_required(VERSION 3.18)

# set the project name
project(CMD VERSION 1.0)

configure_file(commands.h.in commands.h)

# add the utility library
add_subdirectory(../util Util)

# add the executable
add_executable(CMDS commands.c)

# add_library(TelemetryUtil telemetry_util.c)
target_link_libraries(CMDS 
                        PUBLIC Utils
                        PUBLIC zmq
                        PUBLIC pthread
                        PUBLIC m)

target_include_directories(CMDS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS CMDS DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/commands.h"
  DESTINATION include
  )

enable_testing()

# does the application run
add_test(NAME Runs COMMAND CMDS)
