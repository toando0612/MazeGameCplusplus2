//
//  GrowingTree.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/5/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//



#include "MazeGame.hpp"

class GrowingTree : public MazeGame{
    
public:
    GrowingTree();
    
    virtual ~GrowingTree();
    
    GrowingTree(int height, int width);
    
    int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall(int seed);
    
};

 /* GrowingTree_hpp */
