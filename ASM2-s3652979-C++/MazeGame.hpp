//
//  MazeGame.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//
#pragma once
#include <iostream>
#include <fstream>
#include "Cell.hpp"

//out of range
// Returns true if x is in range [low..high], else false
bool inRange(unsigned low, unsigned high, unsigned x);

typedef array<int, 2> isCell;


class MazeGame {
    
protected:
    vector <vector<Cell> > maze;
    unsigned short int height;
    unsigned short int width;
public:
    //methods actions on the attributes
    MazeGame();
    
    virtual ~MazeGame();
    
    MazeGame(unsigned short int height, unsigned short int width);
    
    const vector<vector<Cell>> &getMaze() const;
    
    void setMaze(const vector<vector<Cell>> &maze);
    
    unsigned short int getHeight() const;
    
    void setHeight(unsigned short int height);
    
    unsigned short int getWidth() const;
    
    void setWidth(unsigned short int width);
    
    virtual int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall();
    
};


