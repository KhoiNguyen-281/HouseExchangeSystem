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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nguyenhoangminhkhoi/SED_GROUP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SED_GROUP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SED_GROUP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SED_GROUP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SED_GROUP.dir/flags.make

CMakeFiles/SED_GROUP.dir/main.cpp.o: CMakeFiles/SED_GROUP.dir/flags.make
CMakeFiles/SED_GROUP.dir/main.cpp.o: ../main.cpp
CMakeFiles/SED_GROUP.dir/main.cpp.o: CMakeFiles/SED_GROUP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SED_GROUP.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SED_GROUP.dir/main.cpp.o -MF CMakeFiles/SED_GROUP.dir/main.cpp.o.d -o CMakeFiles/SED_GROUP.dir/main.cpp.o -c /Users/nguyenhoangminhkhoi/SED_GROUP/main.cpp

CMakeFiles/SED_GROUP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SED_GROUP.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nguyenhoangminhkhoi/SED_GROUP/main.cpp > CMakeFiles/SED_GROUP.dir/main.cpp.i

CMakeFiles/SED_GROUP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SED_GROUP.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nguyenhoangminhkhoi/SED_GROUP/main.cpp -o CMakeFiles/SED_GROUP.dir/main.cpp.s

# Object files for target SED_GROUP
SED_GROUP_OBJECTS = \
"CMakeFiles/SED_GROUP.dir/main.cpp.o"

# External object files for target SED_GROUP
SED_GROUP_EXTERNAL_OBJECTS =

SED_GROUP: CMakeFiles/SED_GROUP.dir/main.cpp.o
SED_GROUP: CMakeFiles/SED_GROUP.dir/build.make
SED_GROUP: CMakeFiles/SED_GROUP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SED_GROUP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SED_GROUP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SED_GROUP.dir/build: SED_GROUP
.PHONY : CMakeFiles/SED_GROUP.dir/build

CMakeFiles/SED_GROUP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SED_GROUP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SED_GROUP.dir/clean

CMakeFiles/SED_GROUP.dir/depend:
	cd /Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nguyenhoangminhkhoi/SED_GROUP /Users/nguyenhoangminhkhoi/SED_GROUP /Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug /Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug /Users/nguyenhoangminhkhoi/SED_GROUP/cmake-build-debug/CMakeFiles/SED_GROUP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SED_GROUP.dir/depend

