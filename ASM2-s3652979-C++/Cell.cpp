//
//  Cell.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "Cell.hpp"

Cell::Cell() {}

Cell::~Cell() {
    
}

bool Cell::getVisited() const {
    return visited;
}

void Cell::setVisited(bool visited) {
    Cell::visited = visited;
}

const array<edge, 4> &Cell::getEdgeList() const {
    return edge_list;
}

void Cell::setEdgeList(const array<edge, 4> &edgeList) {
    edge_list = edgeList;
}

const array<int, 2> &Cell::getCoord() const {
    return coord;
}

void Cell::setCoord(const array<int, 2> &coord) {
    Cell::coord = coord;
}

bool Cell::getKilled() const {
    return killed;
}

void Cell::setKilled(bool killed) {
    Cell::killed = killed;
}
