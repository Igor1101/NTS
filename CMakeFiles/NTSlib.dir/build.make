# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/igor/NTS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/igor/NTS

# Include any dependencies generated for this target.
include CMakeFiles/NTSlib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NTSlib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NTSlib.dir/flags.make

CMakeFiles/NTSlib.dir/src/init_nts.c.o: CMakeFiles/NTSlib.dir/flags.make
CMakeFiles/NTSlib.dir/src/init_nts.c.o: src/init_nts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/NTS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/NTSlib.dir/src/init_nts.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NTSlib.dir/src/init_nts.c.o   -c /home/igor/NTS/src/init_nts.c

CMakeFiles/NTSlib.dir/src/init_nts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NTSlib.dir/src/init_nts.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/igor/NTS/src/init_nts.c > CMakeFiles/NTSlib.dir/src/init_nts.c.i

CMakeFiles/NTSlib.dir/src/init_nts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NTSlib.dir/src/init_nts.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/igor/NTS/src/init_nts.c -o CMakeFiles/NTSlib.dir/src/init_nts.c.s

CMakeFiles/NTSlib.dir/src/init_nts.c.o.requires:

.PHONY : CMakeFiles/NTSlib.dir/src/init_nts.c.o.requires

CMakeFiles/NTSlib.dir/src/init_nts.c.o.provides: CMakeFiles/NTSlib.dir/src/init_nts.c.o.requires
	$(MAKE) -f CMakeFiles/NTSlib.dir/build.make CMakeFiles/NTSlib.dir/src/init_nts.c.o.provides.build
.PHONY : CMakeFiles/NTSlib.dir/src/init_nts.c.o.provides

CMakeFiles/NTSlib.dir/src/init_nts.c.o.provides.build: CMakeFiles/NTSlib.dir/src/init_nts.c.o


CMakeFiles/NTSlib.dir/src/log_process.c.o: CMakeFiles/NTSlib.dir/flags.make
CMakeFiles/NTSlib.dir/src/log_process.c.o: src/log_process.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/NTS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/NTSlib.dir/src/log_process.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NTSlib.dir/src/log_process.c.o   -c /home/igor/NTS/src/log_process.c

CMakeFiles/NTSlib.dir/src/log_process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NTSlib.dir/src/log_process.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/igor/NTS/src/log_process.c > CMakeFiles/NTSlib.dir/src/log_process.c.i

CMakeFiles/NTSlib.dir/src/log_process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NTSlib.dir/src/log_process.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/igor/NTS/src/log_process.c -o CMakeFiles/NTSlib.dir/src/log_process.c.s

CMakeFiles/NTSlib.dir/src/log_process.c.o.requires:

.PHONY : CMakeFiles/NTSlib.dir/src/log_process.c.o.requires

CMakeFiles/NTSlib.dir/src/log_process.c.o.provides: CMakeFiles/NTSlib.dir/src/log_process.c.o.requires
	$(MAKE) -f CMakeFiles/NTSlib.dir/build.make CMakeFiles/NTSlib.dir/src/log_process.c.o.provides.build
.PHONY : CMakeFiles/NTSlib.dir/src/log_process.c.o.provides

CMakeFiles/NTSlib.dir/src/log_process.c.o.provides.build: CMakeFiles/NTSlib.dir/src/log_process.c.o


CMakeFiles/NTSlib.dir/src/logfile_proc.c.o: CMakeFiles/NTSlib.dir/flags.make
CMakeFiles/NTSlib.dir/src/logfile_proc.c.o: src/logfile_proc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/NTS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/NTSlib.dir/src/logfile_proc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NTSlib.dir/src/logfile_proc.c.o   -c /home/igor/NTS/src/logfile_proc.c

CMakeFiles/NTSlib.dir/src/logfile_proc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NTSlib.dir/src/logfile_proc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/igor/NTS/src/logfile_proc.c > CMakeFiles/NTSlib.dir/src/logfile_proc.c.i

CMakeFiles/NTSlib.dir/src/logfile_proc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NTSlib.dir/src/logfile_proc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/igor/NTS/src/logfile_proc.c -o CMakeFiles/NTSlib.dir/src/logfile_proc.c.s

CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.requires:

.PHONY : CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.requires

CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.provides: CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.requires
	$(MAKE) -f CMakeFiles/NTSlib.dir/build.make CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.provides.build
.PHONY : CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.provides

CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.provides.build: CMakeFiles/NTSlib.dir/src/logfile_proc.c.o


CMakeFiles/NTSlib.dir/src/signal.c.o: CMakeFiles/NTSlib.dir/flags.make
CMakeFiles/NTSlib.dir/src/signal.c.o: src/signal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/NTS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/NTSlib.dir/src/signal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NTSlib.dir/src/signal.c.o   -c /home/igor/NTS/src/signal.c

CMakeFiles/NTSlib.dir/src/signal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NTSlib.dir/src/signal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/igor/NTS/src/signal.c > CMakeFiles/NTSlib.dir/src/signal.c.i

CMakeFiles/NTSlib.dir/src/signal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NTSlib.dir/src/signal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/igor/NTS/src/signal.c -o CMakeFiles/NTSlib.dir/src/signal.c.s

CMakeFiles/NTSlib.dir/src/signal.c.o.requires:

.PHONY : CMakeFiles/NTSlib.dir/src/signal.c.o.requires

CMakeFiles/NTSlib.dir/src/signal.c.o.provides: CMakeFiles/NTSlib.dir/src/signal.c.o.requires
	$(MAKE) -f CMakeFiles/NTSlib.dir/build.make CMakeFiles/NTSlib.dir/src/signal.c.o.provides.build
.PHONY : CMakeFiles/NTSlib.dir/src/signal.c.o.provides

CMakeFiles/NTSlib.dir/src/signal.c.o.provides.build: CMakeFiles/NTSlib.dir/src/signal.c.o


# Object files for target NTSlib
NTSlib_OBJECTS = \
"CMakeFiles/NTSlib.dir/src/init_nts.c.o" \
"CMakeFiles/NTSlib.dir/src/log_process.c.o" \
"CMakeFiles/NTSlib.dir/src/logfile_proc.c.o" \
"CMakeFiles/NTSlib.dir/src/signal.c.o"

# External object files for target NTSlib
NTSlib_EXTERNAL_OBJECTS =

libNTSlib.a: CMakeFiles/NTSlib.dir/src/init_nts.c.o
libNTSlib.a: CMakeFiles/NTSlib.dir/src/log_process.c.o
libNTSlib.a: CMakeFiles/NTSlib.dir/src/logfile_proc.c.o
libNTSlib.a: CMakeFiles/NTSlib.dir/src/signal.c.o
libNTSlib.a: CMakeFiles/NTSlib.dir/build.make
libNTSlib.a: CMakeFiles/NTSlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/igor/NTS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libNTSlib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/NTSlib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NTSlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NTSlib.dir/build: libNTSlib.a

.PHONY : CMakeFiles/NTSlib.dir/build

CMakeFiles/NTSlib.dir/requires: CMakeFiles/NTSlib.dir/src/init_nts.c.o.requires
CMakeFiles/NTSlib.dir/requires: CMakeFiles/NTSlib.dir/src/log_process.c.o.requires
CMakeFiles/NTSlib.dir/requires: CMakeFiles/NTSlib.dir/src/logfile_proc.c.o.requires
CMakeFiles/NTSlib.dir/requires: CMakeFiles/NTSlib.dir/src/signal.c.o.requires

.PHONY : CMakeFiles/NTSlib.dir/requires

CMakeFiles/NTSlib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NTSlib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NTSlib.dir/clean

CMakeFiles/NTSlib.dir/depend:
	cd /home/igor/NTS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/igor/NTS /home/igor/NTS /home/igor/NTS /home/igor/NTS /home/igor/NTS/CMakeFiles/NTSlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NTSlib.dir/depend

