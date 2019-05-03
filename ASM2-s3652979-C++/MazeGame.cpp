//
//  MazeGame.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "MazeGame.hpp"

//int MazeGame::creatingMaze(int seed){
//
//}

bool inRange(unsigned low, unsigned high, unsigned x)
{
    return  ((x-low) <= (high-low));
}

void MazeGame::creatingMaze(int seed){
    array<int, 2> currentLocation;
    srand(seed);
    //1st draw of maze
    cells = 1;
    currentLocation[0] = 0;         //set starting point to draw at (0,0)
    currentLocation[1] = 0;
    vector<vector<Cell> > temp_maze;
    for (auto i = 0; i < width; i++)
    {
        vector<Cell> colums;
        for (auto j = 0; j < height; j++)
        {
            array< array<int, 4> , 4> temp_edges;
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
            cell.setKilled(false);
            array<int, 2> temp_arr;
            temp_arr[0] = i;
            temp_arr[1] = j;
            cell.setCoord(temp_arr);
            colums.push_back(cell);             //push cells to the colum
        }
        temp_maze.push_back(colums);        //push colums to be a maze
    }
    setMaze(temp_maze);         //set newvalue for maze
    //become of maze, make the Path
    vector<int> neighbours;
    while (true){   //looping for destroying the wall
        /*      check available neighbour  first    */
        int x = currentLocation[0];
        int y = currentLocation[1];
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
            rand();
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
                maze[x][y].setKilled(true);
                maze[x+1][y].setEdgeList(temp_edges2);
                currentLocation[0] = x+1;
                currentLocation[1] = y;
                maze[x+1][y].setVisited(true);
                maze[x+1][y].setKilled(true);
                
                cells++;
            }else if (move == 1){ //go to bottom
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y+1].getEdgeList();
                temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x][y+1].setEdgeList(temp_edges2);
                currentLocation[0] = x;
                currentLocation[1] = y+1;
                maze[x][y+1].setVisited(true);
                maze[x][y+1].setKilled(true);
                
                cells++;
            }else if (move == 2){ //go to left
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x-1][y].getEdgeList();
                temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x-1][y].setEdgeList(temp_edges2);
                currentLocation[0] = x-1;
                currentLocation[1] = y;
                maze[x-1][y].setVisited(true);
                maze[x-1][y].setKilled(true);
                
                cells++;
            }else if (move == 3){ //go to top
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y-1].getEdgeList();
                temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x][y-1].setEdgeList(temp_edges2);
                currentLocation[0] = x;
                currentLocation[1] = y-1;
                maze[x][y-1].setVisited(true);
                maze[x][y-1].setKilled(true);
                cells++;
            } else{
                cout <<"error path!" <<endl;
            }
        }else if(!maze[x][y].getKilled()){      // case dont have any neighbor but the cell is not visisted yet
            //this case to avoid infinity loop
            if (inRange(0, width-1, x+1) && inRange(0, height -1, y)){ //check east neighbor
                neighbours.push_back(0);
            }
            if (inRange(0, width-1, x) && inRange(0, height -1, y + 1)){//check south neighbor
                neighbours.push_back(1);
            }
            if (inRange(0, width-1, x-1) && inRange(0, height -1, y)){//check west neighbor
                neighbours.push_back(2);
            }
            if (inRange(0, width-1, x) && inRange(0, height -1, y - 1)){//check north  neighbor
                neighbours.push_back(3);
            }
            int ran = rand() % neighbours.size();
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
                maze[x][y].setKilled(true);
                maze[x+1][y].setEdgeList(temp_edges2);
            }else if (move == 1){ //go to bottom
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y+1].getEdgeList();
                temp_edges1.at(1)[2] = temp_edges1.at(1)[0];
                temp_edges1.at(1)[3] = temp_edges1.at(1)[1];
                temp_edges2.at(3)[2] = temp_edges2.at(3)[0];
                temp_edges2.at(3)[3] = temp_edges2.at(3)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x][y+1].setEdgeList(temp_edges2);
            }else if (move == 2){ //go to left
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x-1][y].getEdgeList();
                temp_edges1.at(2)[2] = temp_edges1.at(2)[0];
                temp_edges1.at(2)[3] = temp_edges1.at(2)[1];
                temp_edges2.at(0)[2] = temp_edges2.at(0)[0];
                temp_edges2.at(0)[3] = temp_edges2.at(0)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x-1][y].setEdgeList(temp_edges2);
            }else if (move == 3){ //go to top
                array<edge, 4> temp_edges1 = maze[x][y].getEdgeList();
                array<edge, 4> temp_edges2 = maze[x][y-1].getEdgeList();
                temp_edges1.at(3)[2] = temp_edges1.at(3)[0];
                temp_edges1.at(3)[3] = temp_edges1.at(3)[1];
                temp_edges2.at(1)[2] = temp_edges2.at(1)[0];
                temp_edges2.at(1)[3] = temp_edges2.at(1)[1];
                maze[x][y].setEdgeList(temp_edges1);
                maze[x][y].setKilled(true);
                maze[x][y-1].setEdgeList(temp_edges2);
            } else{
                cout <<"error path!" <<endl;
            }
        } else if(cells == height*width) { //case dont have neighbour and check if it is end of the maze
            cout << "Your seed is: " << seed << endl;
        }else{          //case dont have neighbour and start to Hunt algorithm
            int y_loop = 0;
            bool condition = true;
            while (y_loop < height && condition){
                for (int x_loop = 0; x_loop < width; x_loop++) {
                    if(!maze[x_loop][y_loop].getVisited()){
                        currentLocation[0] = x_loop;
                        currentLocation[1] = y_loop;
                        maze[x_loop][y_loop].setVisited(true);
                        cells++;
                        condition = false; //to break while loop
                        break;//break for loop
                    }
                }
                y_loop++;
            }
        }
    }
}
