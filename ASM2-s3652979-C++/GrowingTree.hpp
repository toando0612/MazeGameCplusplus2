//
//  GrowingTree.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//



#include "MazeGame.hpp"

class GrowingTree : public MazeGame{
    
public:
    GrowingTree();
    
    virtual ~GrowingTree();
    
    GrowingTree(unsigned short int height, unsigned short int width);
    
    int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall();
    
};

