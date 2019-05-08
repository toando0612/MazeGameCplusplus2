//
//  MazeGame.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//
#pragma once
#include <iostream>
#include <fstream>
#include "Cell.hpp"

//
bool inRange(unsigned low, unsigned high, unsigned x);

typedef array<int, 2> isCell;


class MazeGame {
    
protected:
    vector <vector<Cell> > maze;
    int height;
    int width;
public:
    //methods actions on the attributes
    MazeGame();
    
    virtual ~MazeGame();
    
    MazeGame(int height, int width);
    
    const vector<vector<Cell>> &getMaze() const;
    
    void setMaze(const vector<vector<Cell>> &maze);
    
    int getHeight() const;
    
    void setHeight(int height);
    
    int getWidth() const;
    
    void setWidth(int width);
    
    virtual int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall(int seed);
    
};

//out of range
// Returns true if x is in range [low..high], else false


