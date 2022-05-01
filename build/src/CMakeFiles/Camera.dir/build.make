# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/alex/Fun/ascii-graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Fun/ascii-graphics/build

# Include any dependencies generated for this target.
include src/CMakeFiles/Camera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/Camera.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Camera.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Camera.dir/flags.make

src/CMakeFiles/Camera.dir/Camera.cpp.o: src/CMakeFiles/Camera.dir/flags.make
src/CMakeFiles/Camera.dir/Camera.cpp.o: ../src/Camera.cpp
src/CMakeFiles/Camera.dir/Camera.cpp.o: src/CMakeFiles/Camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Fun/ascii-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Camera.dir/Camera.cpp.o"
	cd /home/alex/Fun/ascii-graphics/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/Camera.dir/Camera.cpp.o -MF CMakeFiles/Camera.dir/Camera.cpp.o.d -o CMakeFiles/Camera.dir/Camera.cpp.o -c /home/alex/Fun/ascii-graphics/src/Camera.cpp

src/CMakeFiles/Camera.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Camera.dir/Camera.cpp.i"
	cd /home/alex/Fun/ascii-graphics/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Fun/ascii-graphics/src/Camera.cpp > CMakeFiles/Camera.dir/Camera.cpp.i

src/CMakeFiles/Camera.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Camera.dir/Camera.cpp.s"
	cd /home/alex/Fun/ascii-graphics/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Fun/ascii-graphics/src/Camera.cpp -o CMakeFiles/Camera.dir/Camera.cpp.s

# Object files for target Camera
Camera_OBJECTS = \
"CMakeFiles/Camera.dir/Camera.cpp.o"

# External object files for target Camera
Camera_EXTERNAL_OBJECTS =

src/libCamera.so: src/CMakeFiles/Camera.dir/Camera.cpp.o
src/libCamera.so: src/CMakeFiles/Camera.dir/build.make
src/libCamera.so: src/CMakeFiles/Camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Fun/ascii-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libCamera.so"
	cd /home/alex/Fun/ascii-graphics/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Camera.dir/build: src/libCamera.so
.PHONY : src/CMakeFiles/Camera.dir/build

src/CMakeFiles/Camera.dir/clean:
	cd /home/alex/Fun/ascii-graphics/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Camera.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Camera.dir/clean

src/CMakeFiles/Camera.dir/depend:
	cd /home/alex/Fun/ascii-graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Fun/ascii-graphics /home/alex/Fun/ascii-graphics/src /home/alex/Fun/ascii-graphics/build /home/alex/Fun/ascii-graphics/build/src /home/alex/Fun/ascii-graphics/build/src/CMakeFiles/Camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Camera.dir/depend

