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
CMAKE_SOURCE_DIR = /home/pi/Documents/robo-astro-pointer/acs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/robo-astro-pointer/build_acs

# Include any dependencies generated for this target.
include CMakeFiles/ACS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ACS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ACS.dir/flags.make

CMakeFiles/ACS.dir/acs.c.o: CMakeFiles/ACS.dir/flags.make
CMakeFiles/ACS.dir/acs.c.o: /home/pi/Documents/robo-astro-pointer/acs/acs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/robo-astro-pointer/build_acs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ACS.dir/acs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ACS.dir/acs.c.o -c /home/pi/Documents/robo-astro-pointer/acs/acs.c

CMakeFiles/ACS.dir/acs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ACS.dir/acs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Documents/robo-astro-pointer/acs/acs.c > CMakeFiles/ACS.dir/acs.c.i

CMakeFiles/ACS.dir/acs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ACS.dir/acs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Documents/robo-astro-pointer/acs/acs.c -o CMakeFiles/ACS.dir/acs.c.s

# Object files for target ACS
ACS_OBJECTS = \
"CMakeFiles/ACS.dir/acs.c.o"

# External object files for target ACS
ACS_EXTERNAL_OBJECTS =

ACS: CMakeFiles/ACS.dir/acs.c.o
ACS: CMakeFiles/ACS.dir/build.make
ACS: Util/libUtils.a
ACS: CMakeFiles/ACS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/robo-astro-pointer/build_acs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ACS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ACS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ACS.dir/build: ACS

.PHONY : CMakeFiles/ACS.dir/build

CMakeFiles/ACS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ACS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ACS.dir/clean

CMakeFiles/ACS.dir/depend:
	cd /home/pi/Documents/robo-astro-pointer/build_acs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/robo-astro-pointer/acs /home/pi/Documents/robo-astro-pointer/acs /home/pi/Documents/robo-astro-pointer/build_acs /home/pi/Documents/robo-astro-pointer/build_acs /home/pi/Documents/robo-astro-pointer/build_acs/CMakeFiles/ACS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ACS.dir/depend

