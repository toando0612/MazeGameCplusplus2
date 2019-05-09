//
//  MazeGame.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "MazeGame.hpp"

bool inRange(unsigned low, unsigned high, unsigned x)
{
    return  ((x-low) <= (high-low));
}

MazeGame::MazeGame() {}

MazeGame::~MazeGame() {
    
}
MazeGame::MazeGame(unsigned short int height, unsigned short int width) : height(height), width(width) {}

const vector<vector<Cell>> &MazeGame::getMaze() const {
    return maze;
}

void MazeGame::setMaze(const vector<vector<Cell>> &maze) {
    MazeGame::maze = maze;
}

unsigned short int MazeGame::getHeight() const {
    return height;
}

void MazeGame::setHeight(unsigned short int height) {
    MazeGame::height = height;
}

unsigned short int MazeGame::getWidth() const {
    return width;
}

void MazeGame::setWidth(unsigned short int width) {
    MazeGame::width = width;
}



vector<vector<Cell>> MazeGame::createWall(){
//    cout << "createWall of MazeGame class." << endl;
    //1st draw of maze
    vector<vector<Cell> > temp_maze;
    for (auto i = 0; i < width; i++)
    {
        vector<Cell> colums;
        for (auto j = 0; j < height; j++)
        {
            array<edge, 4> temp_edges;
            //
            temp_edges[0][0] = i+1;     // set coord for each edge
            temp_edges[0][1] = j;
            temp_edges[0][2] = i+1;
            temp_edges[0][3] = j+1;
            //
            temp_edges[1][0] = i+1;
            temp_edges[1][1] = j+1;
            temp_edges[1][2] = i;
            temp_edges[1][3] = j+1;
            //
            temp_edges[2][0] = i;
            temp_edges[2][1] = j+1;
            temp_edges[2][2] = i;
            temp_edges[2][3] = j;
            //
            temp_edges[3][0] = i;
            temp_edges[3][1] = j;
            temp_edges[3][2] = i+1;
            temp_edges[3][3] = j;
            
            Cell cell;
            if (i==0 && j == 0){
                cell.setVisited(true);      //visited true for (0,0)
            }else{
                cell.setVisited(false);
            }
            cell.setEdgeList(temp_edges);      //push edge to cell
            array<int, 2> temp_arr;
            temp_arr[0] = i;
            temp_arr[1] = j;
            cell.setCoord(temp_arr);
            colums.push_back(cell);             //push cells to the colum
        }
        temp_maze.push_back(colums);        //push colums to be a maze
    }
    return temp_maze;
}


int MazeGame::creatingMaze(int seed, MazeGame *mazeGame){
//    cout << "createMaze of MazeGame class." << endl;

    return 0;
}


