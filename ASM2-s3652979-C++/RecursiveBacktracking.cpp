//
//  GTreeAndBRecursive.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "RecursiveBacktracking.hpp"


RecursiveBacktracking::RecursiveBacktracking() {}

RecursiveBacktracking::RecursiveBacktracking(unsigned short int height, unsigned short int width) : MazeGame(height, width) {}

RecursiveBacktracking::~RecursiveBacktracking() {
}

vector<vector<Cell> > RecursiveBacktracking::createWall(){
//    cout << "createWall of GTreeAndBRecursive class" << endl;
    vector<vector<Cell>> temp;
    return temp;
}

int RecursiveBacktracking::creatingMaze(int seed, MazeGame *mazeGame){
    srand(seed);
    rand();
    int x,y;
    cout << "createMaze of RecursiveBacktracking class." << endl;
    stack<isCell> listOfCells;
    isCell cell;
    cell[0] = rand() % (width-1);         //set starting point to draw at (0,0)
    cell[1] = rand() % (height-1);
    listOfCells.push(cell);
    maze[cell[0]][cell[1]].setVisited(true);
    vector<int> neighbours;
    while (true){   //looping for destroying the wall
        /*      check available neighbour  first    */
        if (!listOfCells.empty()) { //finish generating
            isCell temp = listOfCells.top();
            x = temp[0];
            y = temp[1];
            
        }else{
            cout << "Your seed is: " << seed << endl;
            return 0;
        }
        if (inRange(0, width-1, x+1) && inRange(0, height -1, y) && maze[x+1][y].getVisited() == false){ //check east neighbor
            neighbours.push_back(0);
        }
        if (inRange(0, width-1, x) && inRange(0, height -1, y + 1) && maze[x][y+1].getVisited()== false){//check south neighbor
            neighbours.push_back(1);
        }
        if (inRange(0, width-1, x-1) && inRange(0, height -1, y) && maze[x-1][y].getVisited()== false){//check west neighbor
            neighbours.push_back(2);
        }
        if (inRange(0, width-1, x) && inRange(0, height -1, y - 1) && maze[x][y-1].getVisited()== false){//check north  neighbor
            neighbours.push_back(3);
        }
        //random move
        if (!neighbours.empty()){     /* case have neighbour for sure   */
            int ran = rand() % neighbours.size();       //random to find the location of array
            int move = neighbours[ran];
            neighbours.clear();
            if (move == 0){ //go to right
                
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x+1][y].getEdgeList();
                temp_edges1.at(0)[2] = temp_edges1.at(0)[0];
                temp_edges1.at(0)[3] = temp_edges1.at(0)[1];
                temp_edges2[2][2] = temp_edges2[2][0];
                temp_edges2[2][3] = temp_edges2[2][1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x+1][y].setEdgeList(temp_edges2);
                cell[0] = x+1;
                cell[1] = y;
                listOfCells.push(cell);
                maze[x+1][y].setVisited(true);
            }else if (move == 1){ //go to bottom
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y+1].getEdgeList();
                temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y+1].setEdgeList(temp_edges2);
                cell[0] = x;
                cell[1] = y+1;
                listOfCells.push(cell);
                maze[x][y+1].setVisited(true);
            }else if (move == 2){ //go to left
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x-1][y].getEdgeList();
                temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x-1][y].setEdgeList(temp_edges2);
                cell[0] = x-1;
                cell[1] = y;
                listOfCells.push(cell);
                maze[x-1][y].setVisited(true);
            }else if (move == 3){ //go to top
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y-1].getEdgeList();
                temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y-1].setEdgeList(temp_edges2);
                cell[0] = x;
                cell[1] = y-1;
                listOfCells.push(cell);
                maze[x][y-1].setVisited(true);
            } else{
                cout <<"error path!" <<endl;
            }
        }else{
            listOfCells.pop();
        }
    }
}
