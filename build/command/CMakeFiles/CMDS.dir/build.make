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
CMAKE_SOURCE_DIR = /home/pi/Documents/robo-astro-pointer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/robo-astro-pointer/build

# Include any dependencies generated for this target.
include command/CMakeFiles/CMDS.dir/depend.make

# Include the progress variables for this target.
include command/CMakeFiles/CMDS.dir/progress.make

# Include the compile flags for this target's objects.
include command/CMakeFiles/CMDS.dir/flags.make

command/CMakeFiles/CMDS.dir/command.c.o: command/CMakeFiles/CMDS.dir/flags.make
command/CMakeFiles/CMDS.dir/command.c.o: ../command/command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/robo-astro-pointer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object command/CMakeFiles/CMDS.dir/command.c.o"
	cd /home/pi/Documents/robo-astro-pointer/build/command && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CMDS.dir/command.c.o -c /home/pi/Documents/robo-astro-pointer/command/command.c

command/CMakeFiles/CMDS.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CMDS.dir/command.c.i"
	cd /home/pi/Documents/robo-astro-pointer/build/command && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Documents/robo-astro-pointer/command/command.c > CMakeFiles/CMDS.dir/command.c.i

command/CMakeFiles/CMDS.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CMDS.dir/command.c.s"
	cd /home/pi/Documents/robo-astro-pointer/build/command && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Documents/robo-astro-pointer/command/command.c -o CMakeFiles/CMDS.dir/command.c.s

# Object files for target CMDS
CMDS_OBJECTS = \
"CMakeFiles/CMDS.dir/command.c.o"

# External object files for target CMDS
CMDS_EXTERNAL_OBJECTS =

command/CMDS: command/CMakeFiles/CMDS.dir/command.c.o
command/CMDS: command/CMakeFiles/CMDS.dir/build.make
command/CMDS: gps/Util/libUtils.a
command/CMDS: command/CMakeFiles/CMDS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/robo-astro-pointer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CMDS"
	cd /home/pi/Documents/robo-astro-pointer/build/command && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CMDS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
command/CMakeFiles/CMDS.dir/build: command/CMDS

.PHONY : command/CMakeFiles/CMDS.dir/build

command/CMakeFiles/CMDS.dir/clean:
	cd /home/pi/Documents/robo-astro-pointer/build/command && $(CMAKE_COMMAND) -P CMakeFiles/CMDS.dir/cmake_clean.cmake
.PHONY : command/CMakeFiles/CMDS.dir/clean

command/CMakeFiles/CMDS.dir/depend:
	cd /home/pi/Documents/robo-astro-pointer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/robo-astro-pointer /home/pi/Documents/robo-astro-pointer/command /home/pi/Documents/robo-astro-pointer/build /home/pi/Documents/robo-astro-pointer/build/command /home/pi/Documents/robo-astro-pointer/build/command/CMakeFiles/CMDS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : command/CMakeFiles/CMDS.dir/depend
