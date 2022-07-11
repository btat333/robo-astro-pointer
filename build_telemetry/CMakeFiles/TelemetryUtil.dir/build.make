# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Documents/robo-astro-pointer/telemetry_service

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/robo-astro-pointer/build_telemetry

# Include any dependencies generated for this target.
include CMakeFiles/TelemetryUtil.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TelemetryUtil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TelemetryUtil.dir/flags.make

CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o: CMakeFiles/TelemetryUtil.dir/flags.make
CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o: /home/pi/Documents/robo-astro-pointer/telemetry_service/telemetry_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/robo-astro-pointer/build_telemetry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o -c /home/pi/Documents/robo-astro-pointer/telemetry_service/telemetry_util.c

CMakeFiles/TelemetryUtil.dir/telemetry_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TelemetryUtil.dir/telemetry_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Documents/robo-astro-pointer/telemetry_service/telemetry_util.c > CMakeFiles/TelemetryUtil.dir/telemetry_util.c.i

CMakeFiles/TelemetryUtil.dir/telemetry_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TelemetryUtil.dir/telemetry_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Documents/robo-astro-pointer/telemetry_service/telemetry_util.c -o CMakeFiles/TelemetryUtil.dir/telemetry_util.c.s

# Object files for target TelemetryUtil
TelemetryUtil_OBJECTS = \
"CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o"

# External object files for target TelemetryUtil
TelemetryUtil_EXTERNAL_OBJECTS =

libTelemetryUtil.a: CMakeFiles/TelemetryUtil.dir/telemetry_util.c.o
libTelemetryUtil.a: CMakeFiles/TelemetryUtil.dir/build.make
libTelemetryUtil.a: CMakeFiles/TelemetryUtil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/robo-astro-pointer/build_telemetry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libTelemetryUtil.a"
	$(CMAKE_COMMAND) -P CMakeFiles/TelemetryUtil.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TelemetryUtil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TelemetryUtil.dir/build: libTelemetryUtil.a

.PHONY : CMakeFiles/TelemetryUtil.dir/build

CMakeFiles/TelemetryUtil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TelemetryUtil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TelemetryUtil.dir/clean

CMakeFiles/TelemetryUtil.dir/depend:
	cd /home/pi/Documents/robo-astro-pointer/build_telemetry && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/robo-astro-pointer/telemetry_service /home/pi/Documents/robo-astro-pointer/telemetry_service /home/pi/Documents/robo-astro-pointer/build_telemetry /home/pi/Documents/robo-astro-pointer/build_telemetry /home/pi/Documents/robo-astro-pointer/build_telemetry/CMakeFiles/TelemetryUtil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TelemetryUtil.dir/depend
