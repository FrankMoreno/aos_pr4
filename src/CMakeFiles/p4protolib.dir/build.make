# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /aos/projects

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /aos/projects

# Include any dependencies generated for this target.
include src/CMakeFiles/p4protolib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/p4protolib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/p4protolib.dir/flags.make

src/masterworker.pb.cc: src/masterworker.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/aos/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating proto messages ..."
	cd /aos/projects/src && /usr/local/bin/protoc --proto_path=/aos/projects/src --cpp_out=/aos/projects/src --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin --grpc_out=/aos/projects/src /aos/projects/src/masterworker.proto

src/masterworker.grpc.pb.cc: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.grpc.pb.cc

src/masterworker.pb.h: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.pb.h

src/masterworker.grpc.pb.h: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/masterworker.grpc.pb.h

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o: src/CMakeFiles/p4protolib.dir/flags.make
src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o: src/masterworker.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/aos/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p4protolib.dir/masterworker.pb.cc.o -c /aos/projects/src/masterworker.pb.cc

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p4protolib.dir/masterworker.pb.cc.i"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /aos/projects/src/masterworker.pb.cc > CMakeFiles/p4protolib.dir/masterworker.pb.cc.i

src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p4protolib.dir/masterworker.pb.cc.s"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /aos/projects/src/masterworker.pb.cc -o CMakeFiles/p4protolib.dir/masterworker.pb.cc.s

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o: src/CMakeFiles/p4protolib.dir/flags.make
src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o: src/masterworker.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/aos/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o -c /aos/projects/src/masterworker.grpc.pb.cc

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /aos/projects/src/masterworker.grpc.pb.cc > CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.i

src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s"
	cd /aos/projects/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /aos/projects/src/masterworker.grpc.pb.cc -o CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.s

# Object files for target p4protolib
p4protolib_OBJECTS = \
"CMakeFiles/p4protolib.dir/masterworker.pb.cc.o" \
"CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o"

# External object files for target p4protolib
p4protolib_EXTERNAL_OBJECTS =

src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/masterworker.pb.cc.o
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/masterworker.grpc.pb.cc.o
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/build.make
src/libp4protolib.a: src/CMakeFiles/p4protolib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/aos/projects/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libp4protolib.a"
	cd /aos/projects/src && $(CMAKE_COMMAND) -P CMakeFiles/p4protolib.dir/cmake_clean_target.cmake
	cd /aos/projects/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p4protolib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/p4protolib.dir/build: src/libp4protolib.a

.PHONY : src/CMakeFiles/p4protolib.dir/build

src/CMakeFiles/p4protolib.dir/clean:
	cd /aos/projects/src && $(CMAKE_COMMAND) -P CMakeFiles/p4protolib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/p4protolib.dir/clean

src/CMakeFiles/p4protolib.dir/depend: src/masterworker.grpc.pb.cc
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.grpc.pb.h
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.pb.cc
src/CMakeFiles/p4protolib.dir/depend: src/masterworker.pb.h
	cd /aos/projects && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /aos/projects /aos/projects/src /aos/projects /aos/projects/src /aos/projects/src/CMakeFiles/p4protolib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/p4protolib.dir/depend

