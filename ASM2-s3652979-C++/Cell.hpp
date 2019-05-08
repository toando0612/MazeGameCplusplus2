//
//  Cell.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#define Cell_hpp
#pragma once
#include <iostream>
#include <array>
#include <vector>

using namespace std;

typedef array<int, 4> edge;


class Cell {
private:
    bool visited;
    array<edge, 4> edge_list;
    array<int, 2> coord;
    bool inMaze;

public://method or action on the attribubtes
    Cell();
    
    virtual ~Cell();
    
    bool getVisited() const;
    
    void setVisited(bool visited);
    
    const array<edge, 4> &getEdgeList() const;
    
    void setEdgeList(const array<edge, 4> &edgeList);
    
    const array<int, 2> &getCoord() const;
    
    void setCoord(const array<int, 2> &coord);
    
    bool isInMaze() const;
    
    void setInMaze(bool inMaze);
};
