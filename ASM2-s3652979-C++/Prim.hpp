//
//  Prim.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/5/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#ifndef Prim_hpp
#define Prim_hpp

#include "MazeGame.hpp"
class Prim : public MazeGame {

public:
    Prim();
    
    virtual ~Prim();
    
    Prim(int height, int width);
    
    int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall(int seed);

    

};

#endif /* Prim_hpp */
