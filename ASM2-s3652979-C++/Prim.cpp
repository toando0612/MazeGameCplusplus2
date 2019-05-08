//
//  Prim.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/5/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "Prim.hpp"

Prim::Prim() {}

Prim::~Prim() {
    
}

Prim::Prim(int height, int width) : MazeGame(height, width) {}

vector<vector<Cell> > Prim::createWall(int seed){
    cout << "createWall of Prim class" << endl;
    vector<vector<Cell>> temp;
    return temp;
}

int Prim::creatingMaze(int seed, MazeGame *mazeGame){
    //    setMaze(createWall(seed));         //set newvalue for maze
    cout << "createMaze of Prim class." << endl;
    vector<isCell> listOfFrontiers;
    isCell frontier;
    int x = rand() % (width-1);         //set starting point to draw at (0,0)
    int y = rand() % (height-1);
    frontier = {x,y};
    maze[x][y].setVisited(true);
    listOfFrontiers.push_back(frontier);
    vector<int> neighbours;
    while (true){
        /*      check available neighbour    */
        int run = rand() % listOfFrontiers.size();       //random to find the location of array
        x = listOfFrontiers[run][0];
        y = listOfFrontiers[run][1];
        listOfFrontiers.erase(listOfFrontiers.begin() + run);
        maze[x][y].setInMaze(true);
        
        if (inRange(0, width-1, x+1) && inRange(0, height -1, y) && maze[x+1][y].getVisited() == false){ //check east is it new frontier or it is in Maze
            maze[x+1][y].setVisited(true); //make frontier as visited
            frontier = {x+1, y};
            listOfFrontiers.push_back(frontier);
        }else if (inRange(0, width-1, x+1) && inRange(0, height -1, y) && maze[x+1][y].isInMaze()){
            neighbours.push_back(0);
        }
        
        if (inRange(0, width-1, x) && inRange(0, height -1, y + 1) && maze[x][y+1].getVisited()== false){//check south is it new frontier or it is in Maze
            maze[x][y+1].setVisited(true);  //make frontier as visited
            frontier = {x, y+1};
            listOfFrontiers.push_back(frontier);
        }else if (inRange(0, width-1, x) && inRange(0, height -1, y + 1) && maze[x][y+1].isInMaze()){
            neighbours.push_back(1);
        }
        
        if (inRange(0, width-1, x-1) && inRange(0, height -1, y) && maze[x-1][y].getVisited()== false){//check west is it new frontier or it is in Maze
            maze[x-1][y].setVisited(true);  //make frontier as visited
            frontier = {x-1, y};
            listOfFrontiers.push_back(frontier);
        }else if (inRange(0, width-1, x-1) && inRange(0, height -1, y) && maze[x-1][y].isInMaze()){
            neighbours.push_back(2);
        }
        
        if (inRange(0, width-1, x) && inRange(0, height -1, y - 1) && maze[x][y-1].getVisited()== false){//check north is it new frontier or it is in Maze
            maze[x][y-1].setVisited(true);  //make frontier as visited
            frontier = {x, y-1};
            listOfFrontiers.push_back(frontier);
        }else if (inRange(0, width-1, x) && inRange(0, height -1, y - 1) && maze[x][y-1].isInMaze()){
            neighbours.push_back(3);
        }
        //random move
        if (!neighbours.empty() && !listOfFrontiers.empty()){     /* case have neighbour for sure   */
            int go = rand() % neighbours.size();       //random to find the location of array
            int move = neighbours[go];
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
            }else if (move == 1){ //go to bottom
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y+1].getEdgeList();
                temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y+1].setEdgeList(temp_edges2);
            }else if (move == 2){ //go to left
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x-1][y].getEdgeList();
                temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                maze[x][y].setEdgeList(temp_edges1);
//                maze[x][y].setKilled(true);
                maze[x-1][y].setEdgeList(temp_edges2);
//                cell[0] = x-1;
//                cell[1] = y;
//                listOfCells.push_back(cell);
//                maze[x-1][y].setVisited(true);
//                maze[x-1][y].setKilled(true);
//                cells++;
            }else if (move == 3){ //go to top   //is move absolutely be 3 if it go here???
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y-1].getEdgeList();
                temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                maze[x][y].setEdgeList(temp_edges1);
//                maze[x][y].setKilled(true);
                maze[x][y-1].setEdgeList(temp_edges2);
//                cell[0] = x;
//                cell[1] = y-1;
//                listOfCells.push_back(cell);
//                maze[x][y-1].setVisited(true);
//                maze[x][y-1].setKilled(true);
//                cells++;
            } else{
                cout <<"error path!" <<endl;
            }
        }else if(listOfFrontiers.empty()) { //case dont have neighbour and check if it is end of the maze
            cout << "Your seed is: " << seed << endl;
            //            cout << "Your push is: " << push <<"pop: " << pop << endl;
            return 0;
        }
//        else {
//            cout << "final if condition:" << endl;
//        }
    }
}
