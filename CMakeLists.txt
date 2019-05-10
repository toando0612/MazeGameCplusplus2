cmake_minimum_required(VERSION 3.14)
project(ASM2_s3652979_C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(ASM2-s3652979-C++)

add_executable(ASM2_s3652979_C__
	ASM2-s3652979-C++/Timer.cpp
        ASM2-s3652979-C++/Timer.hpp
        ASM2-s3652979-C++/Cell.cpp
        ASM2-s3652979-C++/Cell.hpp
        ASM2-s3652979-C++/MazeGame.cpp
        ASM2-s3652979-C++/MazeGame.hpp
        ASM2-s3652979-C++/RecursiveBacktracking.cpp
        ASM2-s3652979-C++/RecursiveBacktracking.hpp
	ASM2-s3652979-C++/Prim.cpp
        ASM2-s3652979-C++/Prim.hpp
	ASM2-s3652979-C++/GrowingTree.cpp
        ASM2-s3652979-C++/GrowingTree.hpp
        ASM2-s3652979-C++/mazer.cpp)