Do Quoc Toan
s3652979
Assignment 2 - C++ RMIT

This program have a following functions:
+Generate a maze from user input with three difference algorithms
+Save the maze as .svg .maze
+Generating a maze with unlimited value of width and height.
+Valid user input

Either can compile the program with CMakeList.txt file or using command:

g++ -std=c++14 -o mazer mazer.cpp RecursiveBacktracking.cpp GrowingTree.cpp Cell.cpp MazeGame.cpp Timer.cpp Prim.cpp

*Instructions:
**Note that: seed value is optional. Default value is 10 if users leave seed empty

***Calculate average generating time of <10 times 2000x2000> for each algorithm using:
./mazer -cal (note that it will take a bit long around 30 minutes based on different computers)

./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file\n
        
./mazer --gg seed width height --sb filename.maze # generate with seed value, save binary file
        
./mazer --gp seed width height --sb filename.maze # generate with seed value, save binary file
        
./mazer --gr seed width height --sv filename.svg # generate with seed value, save svg file
        
./mazer --(gg, gp or gr) seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg

_To open the BINARY file using command:
	od -h Bin.maze  

 _Note that:
If user not input valid arguments: appropriate error messages are given.
User's input is checked carefully
