# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = E:\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\WorkSpace\openGL\Exp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\WorkSpace\openGL\Exp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/STB_IMAGE.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/STB_IMAGE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/STB_IMAGE.dir/flags.make

CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj: CMakeFiles/STB_IMAGE.dir/flags.make
CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj: CMakeFiles/STB_IMAGE.dir/includes_CXX.rsp
CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj: ../src/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\WorkSpace\openGL\Exp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj"
	E:\Cpp\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\STB_IMAGE.dir\src\stb_image.cpp.obj -c E:\WorkSpace\openGL\Exp\src\stb_image.cpp

CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.i"
	E:\Cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\WorkSpace\openGL\Exp\src\stb_image.cpp > CMakeFiles\STB_IMAGE.dir\src\stb_image.cpp.i

CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.s"
	E:\Cpp\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\WorkSpace\openGL\Exp\src\stb_image.cpp -o CMakeFiles\STB_IMAGE.dir\src\stb_image.cpp.s

# Object files for target STB_IMAGE
STB_IMAGE_OBJECTS = \
"CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj"

# External object files for target STB_IMAGE
STB_IMAGE_EXTERNAL_OBJECTS =

libSTB_IMAGE.a: CMakeFiles/STB_IMAGE.dir/src/stb_image.cpp.obj
libSTB_IMAGE.a: CMakeFiles/STB_IMAGE.dir/build.make
libSTB_IMAGE.a: CMakeFiles/STB_IMAGE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\WorkSpace\openGL\Exp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSTB_IMAGE.a"
	$(CMAKE_COMMAND) -P CMakeFiles\STB_IMAGE.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\STB_IMAGE.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/STB_IMAGE.dir/build: libSTB_IMAGE.a

.PHONY : CMakeFiles/STB_IMAGE.dir/build

CMakeFiles/STB_IMAGE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\STB_IMAGE.dir\cmake_clean.cmake
.PHONY : CMakeFiles/STB_IMAGE.dir/clean

CMakeFiles/STB_IMAGE.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\WorkSpace\openGL\Exp E:\WorkSpace\openGL\Exp E:\WorkSpace\openGL\Exp\cmake-build-debug E:\WorkSpace\openGL\Exp\cmake-build-debug E:\WorkSpace\openGL\Exp\cmake-build-debug\CMakeFiles\STB_IMAGE.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/STB_IMAGE.dir/depend

