# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jinurung/VEDA/Linux/vote/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinurung/VEDA/Linux/vote/build/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/common.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/common.dir/flags.make

lib/CMakeFiles/common.dir/common.cpp.o: lib/CMakeFiles/common.dir/flags.make
lib/CMakeFiles/common.dir/common.cpp.o: /Users/jinurung/VEDA/Linux/vote/build/lib/common.cpp
lib/CMakeFiles/common.dir/common.cpp.o: lib/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/jinurung/VEDA/Linux/vote/build/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/common.dir/common.cpp.o"
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/common.dir/common.cpp.o -MF CMakeFiles/common.dir/common.cpp.o.d -o CMakeFiles/common.dir/common.cpp.o -c /Users/jinurung/VEDA/Linux/vote/build/lib/common.cpp

lib/CMakeFiles/common.dir/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/common.dir/common.cpp.i"
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinurung/VEDA/Linux/vote/build/lib/common.cpp > CMakeFiles/common.dir/common.cpp.i

lib/CMakeFiles/common.dir/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/common.dir/common.cpp.s"
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinurung/VEDA/Linux/vote/build/lib/common.cpp -o CMakeFiles/common.dir/common.cpp.s

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/common.cpp.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

lib/libcommon.a: lib/CMakeFiles/common.dir/common.cpp.o
lib/libcommon.a: lib/CMakeFiles/common.dir/build.make
lib/libcommon.a: lib/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/jinurung/VEDA/Linux/vote/build/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcommon.a"
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/common.dir/build: lib/libcommon.a
.PHONY : lib/CMakeFiles/common.dir/build

lib/CMakeFiles/common.dir/clean:
	cd /Users/jinurung/VEDA/Linux/vote/build/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/common.dir/clean

lib/CMakeFiles/common.dir/depend:
	cd /Users/jinurung/VEDA/Linux/vote/build/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinurung/VEDA/Linux/vote/build /Users/jinurung/VEDA/Linux/vote/build/lib /Users/jinurung/VEDA/Linux/vote/build/build /Users/jinurung/VEDA/Linux/vote/build/build/lib /Users/jinurung/VEDA/Linux/vote/build/build/lib/CMakeFiles/common.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/CMakeFiles/common.dir/depend

