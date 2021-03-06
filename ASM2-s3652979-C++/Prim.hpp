//
//  Prim.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#ifndef Prim_hpp
#define Prim_hpp

#include "MazeGame.hpp"
class Prim : public MazeGame {

public:
    Prim();
    
    virtual ~Prim();
    
    Prim(unsigned short int height, unsigned short int width);
    
    int creatingMaze(int seed, MazeGame *mazeGame);
    
    vector<vector<Cell> > createWall();

    

};

#endif /* Prim_hpp */
