//
//  MazeGame.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "Cell.hpp"

//

class MazeGame {
    
private:
    vector <vector<Cell> > maze;
    int height;
    int width;
    int cells;
public:
    //methods actions on the attributes
    void constructor(int h, int w ){setHeight(h);setWidth(w);}
    void setMaze(vector<vector<Cell> > newMaze){maze = newMaze;}
    vector<vector<Cell> > getMaze(){return maze;}
    int getCells(){return cells;}
    void setCells(int newCell){cells = newCell;}
    void setHeight(int h){height = h;}
    void setWidth(int w){width = w;}
    int getHeight(){return height;}
    int getWidth(){return width;}
    void creatingMaze(int seed);
};

//out of range
// Returns true if x is in range [low..high], else false


