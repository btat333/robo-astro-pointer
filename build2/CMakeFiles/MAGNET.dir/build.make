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
CMAKE_SOURCE_DIR = /home/pi/Documents/robo-astro-pointer/magnetometer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/robo-astro-pointer/build2

# Include any dependencies generated for this target.
include CMakeFiles/MAGNET.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MAGNET.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MAGNET.dir/flags.make

CMakeFiles/MAGNET.dir/magnetometer.c.o: CMakeFiles/MAGNET.dir/flags.make
CMakeFiles/MAGNET.dir/magnetometer.c.o: /home/pi/Documents/robo-astro-pointer/magnetometer/magnetometer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/robo-astro-pointer/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MAGNET.dir/magnetometer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MAGNET.dir/magnetometer.c.o -c /home/pi/Documents/robo-astro-pointer/magnetometer/magnetometer.c

CMakeFiles/MAGNET.dir/magnetometer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MAGNET.dir/magnetometer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Documents/robo-astro-pointer/magnetometer/magnetometer.c > CMakeFiles/MAGNET.dir/magnetometer.c.i

CMakeFiles/MAGNET.dir/magnetometer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MAGNET.dir/magnetometer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Documents/robo-astro-pointer/magnetometer/magnetometer.c -o CMakeFiles/MAGNET.dir/magnetometer.c.s

# Object files for target MAGNET
MAGNET_OBJECTS = \
"CMakeFiles/MAGNET.dir/magnetometer.c.o"

# External object files for target MAGNET
MAGNET_EXTERNAL_OBJECTS =

MAGNET: CMakeFiles/MAGNET.dir/magnetometer.c.o
MAGNET: CMakeFiles/MAGNET.dir/build.make
MAGNET: Util/libUtils.a
MAGNET: CMakeFiles/MAGNET.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/robo-astro-pointer/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MAGNET"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MAGNET.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MAGNET.dir/build: MAGNET

.PHONY : CMakeFiles/MAGNET.dir/build

CMakeFiles/MAGNET.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MAGNET.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MAGNET.dir/clean

CMakeFiles/MAGNET.dir/depend:
	cd /home/pi/Documents/robo-astro-pointer/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/robo-astro-pointer/magnetometer /home/pi/Documents/robo-astro-pointer/magnetometer /home/pi/Documents/robo-astro-pointer/build2 /home/pi/Documents/robo-astro-pointer/build2 /home/pi/Documents/robo-astro-pointer/build2/CMakeFiles/MAGNET.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MAGNET.dir/depend

