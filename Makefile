# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luka/projects/pnetlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luka/projects/pnetlib

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/luka/projects/pnetlib/CMakeFiles /home/luka/projects/pnetlib/CMakeFiles/progress.make
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/luka/projects/pnetlib/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pnet

# Build rule for target.
pnet: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pnet
.PHONY : pnet

# fast build rule for target.
pnet/fast:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/build
.PHONY : pnet/fast

main.o: main.c.o
.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i
.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s
.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/main.c.s
.PHONY : main.c.s

pnet-connection.o: pnet-connection.c.o
.PHONY : pnet-connection.o

# target to build an object file
pnet-connection.c.o:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-connection.c.o
.PHONY : pnet-connection.c.o

pnet-connection.i: pnet-connection.c.i
.PHONY : pnet-connection.i

# target to preprocess a source file
pnet-connection.c.i:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-connection.c.i
.PHONY : pnet-connection.c.i

pnet-connection.s: pnet-connection.c.s
.PHONY : pnet-connection.s

# target to generate assembly for a file
pnet-connection.c.s:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-connection.c.s
.PHONY : pnet-connection.c.s

pnet-error.o: pnet-error.c.o
.PHONY : pnet-error.o

# target to build an object file
pnet-error.c.o:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-error.c.o
.PHONY : pnet-error.c.o

pnet-error.i: pnet-error.c.i
.PHONY : pnet-error.i

# target to preprocess a source file
pnet-error.c.i:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-error.c.i
.PHONY : pnet-error.c.i

pnet-error.s: pnet-error.c.s
.PHONY : pnet-error.s

# target to generate assembly for a file
pnet-error.c.s:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-error.c.s
.PHONY : pnet-error.c.s

pnet-tcp-connection.o: pnet-tcp-connection.c.o
.PHONY : pnet-tcp-connection.o

# target to build an object file
pnet-tcp-connection.c.o:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-tcp-connection.c.o
.PHONY : pnet-tcp-connection.c.o

pnet-tcp-connection.i: pnet-tcp-connection.c.i
.PHONY : pnet-tcp-connection.i

# target to preprocess a source file
pnet-tcp-connection.c.i:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-tcp-connection.c.i
.PHONY : pnet-tcp-connection.c.i

pnet-tcp-connection.s: pnet-tcp-connection.c.s
.PHONY : pnet-tcp-connection.s

# target to generate assembly for a file
pnet-tcp-connection.c.s:
	$(MAKE) -f CMakeFiles/pnet.dir/build.make CMakeFiles/pnet.dir/pnet-tcp-connection.c.s
.PHONY : pnet-tcp-connection.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... pnet"
	@echo "... rebuild_cache"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... pnet-connection.o"
	@echo "... pnet-connection.i"
	@echo "... pnet-connection.s"
	@echo "... pnet-error.o"
	@echo "... pnet-error.i"
	@echo "... pnet-error.s"
	@echo "... pnet-tcp-connection.o"
	@echo "... pnet-tcp-connection.i"
	@echo "... pnet-tcp-connection.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

