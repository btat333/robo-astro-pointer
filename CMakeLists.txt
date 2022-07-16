cmake_minimum_required(VERSION 3.18)

project(ASTRO_POINTER VERSION 1.0)

add_subdirectory(gps)
add_subdirectory(magnetometer)
add_subdirectory(acs)
add_subdirectory(telemetry)
add_subdirectory(commands)