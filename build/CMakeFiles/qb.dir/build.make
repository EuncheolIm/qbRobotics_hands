# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/kist/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/kist/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kist/test/qbRobotics_hands

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kist/test/qbRobotics_hands/build

# Include any dependencies generated for this target.
include CMakeFiles/qb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qb.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qb.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qb.dir/flags.make

CMakeFiles/qb.dir/src/hand_controller.cpp.o: CMakeFiles/qb.dir/flags.make
CMakeFiles/qb.dir/src/hand_controller.cpp.o: /home/kist/test/qbRobotics_hands/src/hand_controller.cpp
CMakeFiles/qb.dir/src/hand_controller.cpp.o: CMakeFiles/qb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kist/test/qbRobotics_hands/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qb.dir/src/hand_controller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qb.dir/src/hand_controller.cpp.o -MF CMakeFiles/qb.dir/src/hand_controller.cpp.o.d -o CMakeFiles/qb.dir/src/hand_controller.cpp.o -c /home/kist/test/qbRobotics_hands/src/hand_controller.cpp

CMakeFiles/qb.dir/src/hand_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qb.dir/src/hand_controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kist/test/qbRobotics_hands/src/hand_controller.cpp > CMakeFiles/qb.dir/src/hand_controller.cpp.i

CMakeFiles/qb.dir/src/hand_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qb.dir/src/hand_controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kist/test/qbRobotics_hands/src/hand_controller.cpp -o CMakeFiles/qb.dir/src/hand_controller.cpp.s

# Object files for target qb
qb_OBJECTS = \
"CMakeFiles/qb.dir/src/hand_controller.cpp.o"

# External object files for target qb
qb_EXTERNAL_OBJECTS =

qb: CMakeFiles/qb.dir/src/hand_controller.cpp.o
qb: CMakeFiles/qb.dir/build.make
qb: /home/kist/test/qbRobotics_hands/libs//qbdevice-api-7.x.x/build/qbrobotics-driver/libqbrobotics_driver.a
qb: /home/kist/test/qbRobotics_hands/libs//qbdevice-api-7.x.x/build/serial/libSerial.a
qb: CMakeFiles/qb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kist/test/qbRobotics_hands/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable qb"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qb.dir/build: qb
.PHONY : CMakeFiles/qb.dir/build

CMakeFiles/qb.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qb.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qb.dir/clean

CMakeFiles/qb.dir/depend:
	cd /home/kist/test/qbRobotics_hands/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kist/test/qbRobotics_hands /home/kist/test/qbRobotics_hands /home/kist/test/qbRobotics_hands/build /home/kist/test/qbRobotics_hands/build /home/kist/test/qbRobotics_hands/build/CMakeFiles/qb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qb.dir/depend
