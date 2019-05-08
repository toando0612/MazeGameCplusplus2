//
//  main.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/3/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

//C++ Assignment 2
//Do Quoc Toan - s3652979


#include "GrowingTree.hpp"
#include "Prim.hpp"


const string GENERATE = "--g";
const string SAVE_BIN = "--sb";
const string SAVE_SVG = "--sv";
unsigned seed;
unsigned width;
unsigned height;
string current = "";
string nextseg = "";

void at(int index) {
    if(index < 1 || index >= 1001) {throw out_of_range("1233333");}
}


// Generation of the two segments

void genSvg(MazeGame maze, string filename) {
    ofstream svgFile(filename, ofstream::out);
    svgFile << "<svg"<< " viewBox="<< "\"0 0 100 100\""<< " width" << "=" <<"\"500\""<<" height=\"" << 500 << "\""
    << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svgFile << "<rect width =" <<"\'100\' " << "height=\'" << "100" << "\' " << "style=\'" << "fill: black\' " << "/>" << endl;
    for (int i = 0; i < maze.getWidth(); ++i) {
        for (int j = 0; j < maze.getHeight(); ++j) {
            for (int k = 0; k < 4; ++k) {
                int x1 =  maze.getMaze()[i][j].getEdgeList()[k][0];
                int y1 =  maze.getMaze()[i][j].getEdgeList()[k][1];
                int x2 =  maze.getMaze()[i][j].getEdgeList()[k][2];
                int y2 =  maze.getMaze()[i][j].getEdgeList()[k][3];
                svgFile << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.4\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
            }
        }
    }
    svgFile << "</svg>" << endl;
    svgFile.close();
}

void genBin(MazeGame mazeGame, string filename){
    std::fstream output(filename,std::fstream::out | std::fstream::binary | std::fstream::trunc);
    //     Write headers
    const int cells = height*width;
    const int height = mazeGame.getHeight();
    const int width = mazeGame.getWidth();
    output.write((char*)&width, sizeof(width));
    output.write((char*)&height, sizeof(height));
    output.write((char*)&cells, sizeof(cells));
    
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int x1 =  mazeGame.getMaze()[i][j].getCoord()[0];
            int y1 =  mazeGame.getMaze()[i][j].getCoord()[1];
            int x2 =  mazeGame.getMaze()[i][j].getCoord()[2];
            int y2 =  mazeGame.getMaze()[i][j].getCoord()[3];
            /* x1 */
            output.write((char*)&x1, sizeof(x1));
            /* y1 */
            output.write((char*)&y1, sizeof(y1));
            /* x2 */
            output.write((char*)&x2, sizeof(x2));
            /* y2 */
            output.write((char*)&y2, sizeof(y2));
        }
    }
    output.close();
}

int main(int argc, char* argv[]) {
//
    if (argc <= 1){ // shortest input and the instructions
        cout << "./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file\n"
        "./mazer --g seed width height --sb filename.maze # generate with seed value, save binary file\n"
        "./mazer --g seed width height --sv filename.svg # generate with seed value, save svg file\n"
        "./mazer --g seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg\n";
        return 0;
    }
    try {
        int i = 1;
        nextseg = argv [i+1];
        if (argc == 7 ){ //have seed
            //collect seed
            try {
                seed = (int) stol(argv [i+1]);
            }catch (const invalid_argument){
                cout << "Seed must be a number" <<endl;
                return 1;
            }catch (const out_of_range) {
                cout << "Seed must be lower than: " << UID_MAX << endl;
                return 1;
            }

            try {
                width = (int) stol(argv [i+2]);
                height = (int) stol(argv [i+3]);
            }catch (const invalid_argument &e){
                cout << "Height and width must be numbers" <<endl;
                at(width);
                at(height);
                e.what();
            }catch (int n) {
                cout << n << "out of range" << endl;
                return 1;
            }
            if (argv[i+4] == SAVE_SVG){     //save svg
                string filename = argv[i+5];
                MazeGame *mazeGame;
                
//                GrowingTree growingTree(height, width);
//                mazeGame = &growingTree;
                
                Prim prim(height, width);
                mazeGame = &prim;
//                cout << "here" << endl;
                mazeGame->setMaze(mazeGame->createWall(seed));
                mazeGame->creatingMaze(seed, mazeGame);
                genSvg(*mazeGame, filename);
            }else if(argv[i+4] == SAVE_BIN){    //save binary
                string filename = argv[i+5];
                MazeGame *mazeGame = new MazeGame(height, width);
//                mazeGame->creatingMaze(seed);
                genBin(*mazeGame, filename);
            }
        } else if(argc == 6){ //no seed
            seed = 10; //default seed
            try {
                width = (int)stol(argv [i+1]);
                height = (int)stol(argv [i+2]);
            }catch (const invalid_argument &e){
                cout << "Height and width must be numbers" <<endl;
                at(width);
                at(height);
                e.what();
            }catch (int n) {
                cout << n << "out of range" << endl;
                return 1;
            }
            if (argv[i+3] == SAVE_SVG){
                string filename = argv[i+4];
                MazeGame *mazeGame = new MazeGame(height, width);
//                mazeGame->creatingMaze(seed);
                genSvg(*mazeGame, filename);
            }else if(argv[i+3] == SAVE_BIN){
                string filename = argv[i+4];
                MazeGame *mazeGame = new MazeGame(height, width);
//                mazeGame->creatingMaze(seed);
                genBin(*mazeGame, filename);
            }
        } else if(argv[i] == GENERATE){ //there must be save both types or loading
            //save binary
            //save svg
            //                "./mazer --g seed width height --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg\n";
            if(argc==9){    //save both size
                //have seed
                //collect seed
                try {
                    seed = (int)stol(argv [i+1]);
                }catch (const invalid_argument){
                    cout << "Seed must be a number" <<endl;
                    return 1;
                }catch (const out_of_range) {
                    cout << "Seed must be lower than: " << UID_MAX << endl;
                    return 1;
                }

                //collect height
                try {
                    width = (int)stol(argv [i+2]);
                    height = (int)stol(argv [i+3]);

                }catch (const invalid_argument &e){
                    cout << "Height and width must be numbers" <<endl;
                    at(width);
                    at(height);
                    e.what();
                }catch (int n) {
                    cout << n << "out of range" << endl;
                    return 1;
                }
                string filenameB = argv[i+5];
                string filenameS = argv[i+7];
                MazeGame *mazeGame = new MazeGame(height, width);
//                mazeGame->creatingMaze(seed);
                genSvg(*mazeGame, filenameS);
                genBin(*mazeGame, filenameB);
            } else if (argc==8){
                //no seed
                seed = 10; //default seed
                //collect height
                try {
                    width = (int)stol(argv [i+1]);
                    height = (int)stol(argv [i+2]);
                }catch (const invalid_argument &e){
                    cout << "Height and width must be numbers" <<endl;
                    at(width);
                    at(height);
                    e.what();
                }catch (int n) {
                    cout << n << "out of range" << endl;
                    return 1;
                }
                string filenameB = argv[i+4];
                string filenameS = argv[i+6];
                MazeGame *mazeGame = new MazeGame(height, width);
//                mazeGame->creatingMaze(seed);
                genSvg(*mazeGame, filenameS);
                genBin(*mazeGame, filenameB);
            } else{
                cout << "Invalid input!";
            }
        }    }catch (char const* param)
    {
        cout << param << ".\nMissing generated maze." << endl;
    }
    return 0;
}
