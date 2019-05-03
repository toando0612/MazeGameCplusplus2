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
    bool killed;
public://method or action on the attribubtes
    void setEdgeList(array<edge, 4> new_edge_list){edge_list = new_edge_list;}
    void setVisited(bool status){visited = status;}
    void setKilled(bool status){killed = status;}
    void setCoord(array<int, 2> newCoord){coord = newCoord;}
    array<edge, 4> getEdgeList(){return edge_list;}
    bool getVisited(){return visited;}
    bool getKilled(){return killed;}
    array<int, 2> getCoord(){return coord;}
};
