cmake_minimum_required(VERSION 3.14)
project(ASM2_s3652979_C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ASM2_s3652979_C__
		Timer.cpp
                Timer.hpp
                Cell.cpp
                Cell.hpp
                MazeGame.cpp
                MazeGame.hpp
                GTreeAndBRecursive.cpp
                GTreeAndBRecursive.hpp
 		Prim.cpp
                Prim.hpp
                mazer.cpp)