Do Quoc Toan
s3652979
Assignment 2 - C++ RMIT

This program have a following functions:
+Generate a maze from user input with three difference algorithms
+Save the maze as .svg .bin
+Generating a maze with unlimited value of width and height.
+Valid user input

*Instructions:
**Note that: seed value is optional. Default value is 10

./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file\n
        
./mazer --gg seed width height --sb filename.maze # generate with seed value, save binary file
        
./mazer --gp seed width height --sb filename.maze # generate with seed value, save binary file
        
./mazer --gr seed width height --sv filename.svg # generate with seed value, save svg file
        
./mazer --(gg, gp or gr) seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg

_To open the BINARY file using command:
	od -h Bin.maze  

 _An appropriate error message must be given if inappropriate args are entered.
