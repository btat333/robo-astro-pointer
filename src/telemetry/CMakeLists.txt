cmake_minimum_required(VERSION 3.18)

# set the project name
project(TELEMETRY VERSION 1.0)

configure_file(telemetry.h.in telemetry.h)

# add the MathFunctions library
add_subdirectory(../util Util)

# add the executable
add_executable(TELEMETRY telemetry.c)

add_library(TelemetryUtil telemetry_util.c)
target_link_libraries(TELEMETRY 
                        PUBLIC Utils
                        PUBLIC TelemetryUtil
                        PUBLIC zmq
                        PUBLIC pthread
                        PUBLIC m
                        PUBLIC ws)

target_include_directories(TELEMETRY PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

install(TARGETS TELEMETRY DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/telemetry.h"
  DESTINATION include
  )

enable_testing()
