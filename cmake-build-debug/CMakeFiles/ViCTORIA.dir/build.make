# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/gaetanserre/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/gaetanserre/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ViCTORIA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ViCTORIA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ViCTORIA.dir/flags.make

CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o: ../src/classes/bitboard/magic_bitboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/bitboard/magic_bitboard.cpp

CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/bitboard/magic_bitboard.cpp > CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/bitboard/magic_bitboard.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o: ../src/classes/board/pieces/bishop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/bishop.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/bishop.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/bishop.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o: ../src/classes/board/pieces/king.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/king.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/king.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/king.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o: ../src/classes/board/pieces/knight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/knight.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/knight.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/knight.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o: ../src/classes/board/pieces/pawn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/pawn.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/pawn.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/pawn.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o: ../src/classes/board/pieces/piece.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/piece.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/piece.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/piece.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o: ../src/classes/board/pieces/queen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/queen.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/queen.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/queen.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o: ../src/classes/board/pieces/rook.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/rook.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/rook.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/pieces/rook.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o: ../src/classes/board/board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/board.cpp

CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/board.cpp > CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/board/board.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o: ../src/classes/engine/score/score.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/score/score.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/score/score.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/score/score.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o: ../src/classes/engine/transposition_table/hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hash.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hash.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hash.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o: ../src/classes/engine/transposition_table/hashKey.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hashKey.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hashKey.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/transposition_table/hashKey.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o: ../src/classes/engine/engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/engine.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/engine.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/engine.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o: ../src/classes/engine/evaluation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/evaluation.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/evaluation.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/evaluation.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.s

CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o: ../src/classes/engine/parse_expr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/parse_expr.cpp

CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/parse_expr.cpp > CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.i

CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/classes/engine/parse_expr.cpp -o CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.s

CMakeFiles/ViCTORIA.dir/src/main.cpp.o: CMakeFiles/ViCTORIA.dir/flags.make
CMakeFiles/ViCTORIA.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/ViCTORIA.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ViCTORIA.dir/src/main.cpp.o -c /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/main.cpp

CMakeFiles/ViCTORIA.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ViCTORIA.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/main.cpp > CMakeFiles/ViCTORIA.dir/src/main.cpp.i

CMakeFiles/ViCTORIA.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ViCTORIA.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/src/main.cpp -o CMakeFiles/ViCTORIA.dir/src/main.cpp.s

# Object files for target ViCTORIA
ViCTORIA_OBJECTS = \
"CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o" \
"CMakeFiles/ViCTORIA.dir/src/main.cpp.o"

# External object files for target ViCTORIA
ViCTORIA_EXTERNAL_OBJECTS =

ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/bitboard/magic_bitboard.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/bishop.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/king.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/knight.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/pawn.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/piece.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/queen.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/pieces/rook.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/board/board.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/score/score.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hash.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/transposition_table/hashKey.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/engine.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/evaluation.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/classes/engine/parse_expr.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/src/main.cpp.o
ViCTORIA: CMakeFiles/ViCTORIA.dir/build.make
ViCTORIA: CMakeFiles/ViCTORIA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX executable ViCTORIA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ViCTORIA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ViCTORIA.dir/build: ViCTORIA

.PHONY : CMakeFiles/ViCTORIA.dir/build

CMakeFiles/ViCTORIA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ViCTORIA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ViCTORIA.dir/clean

CMakeFiles/ViCTORIA.dir/depend:
	cd /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug /Users/gaetanserre/Documents/Projets/Chess/Engines/ViCTORIA/cmake-build-debug/CMakeFiles/ViCTORIA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ViCTORIA.dir/depend
