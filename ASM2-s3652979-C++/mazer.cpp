//
//  main.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

//C++ Assignment 2
//Do Quoc Toan - s3652979


#include "RecursiveBacktracking.hpp"
#include "GrowingTree.hpp"
#include "Prim.hpp"
#include "Timer.hpp"
#include <iomanip>
#include <string>
const string SAVE_BIN = "--sb";
const string SAVE_SVG = "--sv";
unsigned seed;
unsigned width;
unsigned height;

string checkType(string input){
    if (input == SAVE_SVG || input == SAVE_BIN) {
        return input;
    }else{
        throw "_Saving argument must be: --sv or --sb";
    }
}

string checkFileName(string input){
    string fileType = input.substr(input.find_last_of(".") + 1);
    if ( fileType == "svg" || fileType == "maze") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .svg or .maze";
    }
}

string checkGen(string input){
    if (input == "--gg" || input == "--gp" || input == "--gr") {
        return input;
    }else{
        throw "_Must be --gg or --gp or --gr at first";
    }
}

string checkBin(string input) {
    if (input == "--sb") {
        return input;
    }else{
        throw "_Invalid arguments for --sb";
    }
}

string checkSvg(string input) {
    if (input == "--sv") {
        return input;
    }else{
        throw "_Invalid arguments for --sv";
    }
}

//check extension
string checkBinFile(string input) {
    string fileType = input.substr(input.find_last_of(".") + 1);
    if (fileType == "maze") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .maze";
    }
}

//check extension
string checkSvgFile(string input) {
    string fileType = input.substr(input.find_last_of(".") + 1);
    if ( fileType == "svg") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .svg";
    }
}

//check valid argurment -cal for calculating time
string checkCalculator(string input) {
    if ( input == "-cal") {
        return input;
    }else{
        throw "Must be \"-cal\" to calculating time generating!";
    }
}



// Saving to .svg function
void genSvg(MazeGame maze, string filename) {
    int x1,y1,x2,y2;
    ofstream svgFile(filename, ofstream::out);
    svgFile << "<svg"<< " viewBox="<< "\"0 0 " << width << " " << height << "\""<< " width=\""<<500 << "\""<<" height=\"" << 500 << "\""
    << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svgFile << "<rect width=\""<<width << "\" "<< "height=\""<< height << "\" "<< " style=\'" << "fill: black\' " << "/>" << endl;
    for (int i = 0; i < maze.getWidth(); i++) {
        for (int j = 0; j < maze.getHeight(); j++) {
            for (int k = 0; k < 4; k++) {
                x1 =  maze.getMaze()[i][j].getEdgeList()[k][0];
                y1 =  maze.getMaze()[i][j].getEdgeList()[k][1];
                x2 =  maze.getMaze()[i][j].getEdgeList()[k][2];
                y2 =  maze.getMaze()[i][j].getEdgeList()[k][3];
                svgFile << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.4\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
            }
        }
    }
    svgFile << "</svg>" << endl;
    svgFile.close();
}

//saving to .maze function
void genBin(MazeGame mazeGame, string filename){
    fstream output(filename,fstream::out | fstream::binary | fstream::trunc);
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
    try {
        int i = 1;
        if (argc == 7 ){ //One savingType with seed from user
            //collect seed
            //check seed
            string gen = checkGen(argv [i]);
            try {
                i++;
                seed = (int) stol(argv [i]);
            }catch (const invalid_argument){
                cout << "_Seed must be a number" <<endl;    //check valid seed
                return 1;
            }
            // check h,w
            try {
                i++;
                width = (int) stol(argv [i]);
                i++;
                height = (int) stol(argv [i]);
                i++;
            }catch (const invalid_argument){                //check valid h,w
                cout << "_Height and width must be numbers" <<endl;
            }
            string filename = checkFileName(argv[i+1]);
            Timer timer;
            MazeGame *mazeGame;
            if (gen == "--gr") {    //recursive backtracking
                RecursiveBacktracking rb(height, width);
                mazeGame = &rb;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else if(gen == "--gg"){ //growing tree
                GrowingTree gt(height, width);
                mazeGame = &gt;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else{  // prim
                Prim prim(height, width);
                mazeGame = &prim;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }
            
            
            
        } else if(argc == 6){ //One savingType with no seed from user
            int seed = 10; //default
            // check h,w
            string gen = checkGen(argv [i]);
            try {
                i++;
                width = (int) stol(argv [i]);
                i++;
                height = (int) stol(argv [i]);
                i++;
            }catch (const invalid_argument){            //check valid h,w
                cout << "Height and width must be numbers" <<endl;
            }
            string filename = checkFileName(argv[i+1]);
            Timer timer;
            MazeGame *mazeGame;
            if (gen == "--gr") {    //recursive backtracking
                RecursiveBacktracking rb(height, width);
                mazeGame = &rb;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else if(gen == "--gg"){    //growing tree
                GrowingTree gt(height, width);
                mazeGame = &gt;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else{  //prim
                Prim prim(height, width);
                mazeGame = &prim;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, checkSvgFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, checkBinFile(filename));
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }
        } else if(argc == 9){ //Two savingType with seed from user
            //collect seed
            //check seed
            string gen = checkGen(argv [i]);  // i = 1
            try {
                i++;
                seed = (int) stol(argv [i]);
            }catch (const invalid_argument){
                cout << "_Seed must be a number" <<endl; //check valid seed
                return 1;
            }
            // check h,w
            try {
                i++;
                width = (int) stol(argv [i]);
                i++;
                height = (int) stol(argv [i]);
                i++;
            }catch (const invalid_argument){
                cout << "_Height and width must be numbers" <<endl; //check valid h,w
            }
            Timer timer;
            MazeGame *mazeGame;
            if (gen == "--gr") {
                RecursiveBacktracking rb(height, width);
                mazeGame = &rb;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                string bin = checkBin(argv[i]);
                i++;
                cout << argv[i] << endl;
                string fileBin = checkBinFile(argv[i]);
                i++;
                string svg = checkSvg(argv[i]);
                i++;
                string fileSvg = checkSvgFile(argv[i]);
                genSvg(*mazeGame, fileSvg);
                t = timer.milliseconds_since();
                cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                genBin(*mazeGame, fileBin);
                t = timer.milliseconds_since();
                cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
            }else if (gen == "--gg"){
                GrowingTree gt(height, width);
                mazeGame = &gt;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                string bin = checkBin(argv[i]);
                i++;
                cout << argv[i] << endl;
                string fileBin = checkBinFile(argv[i]);
                i++;
                string svg = checkSvg(argv[i]);
                i++;
                string fileSvg = checkSvgFile(argv[i]);
                genSvg(*mazeGame, fileSvg);
                t = timer.milliseconds_since();
                cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                genBin(*mazeGame, fileBin);
                t = timer.milliseconds_since();
                cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
            
            } else{
                Prim prim(height, width);
                mazeGame = &prim;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                string bin = checkBin(argv[i]);
                i++;
                cout << argv[i] << endl;
                string fileBin = checkBinFile(argv[i]);
                i++;
                string svg = checkSvg(argv[i]);
                i++;
                string fileSvg = checkSvgFile(argv[i]);
                genSvg(*mazeGame, fileSvg);
                t = timer.milliseconds_since();
                cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                genBin(*mazeGame, fileBin);
                t = timer.milliseconds_since();
                cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
        }else if (argc == 8) { ///Two savingType with no seed from user
                int seed = 10; //default
                string gen = checkGen(argv [i]);
                // check h,w
                try {
                    i++;
                    width = (int) stol(argv [i]);
                    i++;
                    height = (int) stol(argv [i]);
                    i++;
                }catch (const invalid_argument){
                    cout << "_Height and width must be numbers" <<endl;
                }
                Timer timer;
                MazeGame *mazeGame;
                if (gen == "--gr") {
                    RecursiveBacktracking rb(height, width);
                    mazeGame = &rb;
                    mazeGame->setMaze(mazeGame->createWall());
                    mazeGame->creatingMaze(seed, mazeGame);
                    double t = timer.milliseconds_since();
                    cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    string bin = checkBin(argv[i]);
                    i++;
                    cout << argv[i] << endl;
                    string fileBin = checkBinFile(argv[i]);
                    i++;
                    string svg = checkSvg(argv[i]);
                    i++;
                    string fileSvg = checkSvgFile(argv[i]);
                    genSvg(*mazeGame, fileSvg);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    genBin(*mazeGame, fileBin);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else if (gen == "--gg"){
                    GrowingTree gt(height, width);
                    mazeGame = &gt;
                    mazeGame->setMaze(mazeGame->createWall());
                    mazeGame->creatingMaze(seed, mazeGame);
                    double t = timer.milliseconds_since();
                    cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    string bin = checkBin(argv[i]);
                    i++;
                    cout << argv[i] << endl;
                    string fileBin = checkBinFile(argv[i]);
                    i++;
                    string svg = checkSvg(argv[i]);
                    i++;
                    string fileSvg = checkSvgFile(argv[i]);
                    genSvg(*mazeGame, fileSvg);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    genBin(*mazeGame, fileBin);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    
                } else{
                    Prim prim(height, width);
                    mazeGame = &prim;
                    mazeGame->setMaze(mazeGame->createWall());
                    mazeGame->creatingMaze(seed, mazeGame);
                    double t = timer.milliseconds_since();
                    cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    string bin = checkBin(argv[i]);
                    i++;
                    cout << argv[i] << endl;
                    string fileBin = checkBinFile(argv[i]);
                    i++;
                    string svg = checkSvg(argv[i]);
                    i++;
                    string fileSvg = checkSvgFile(argv[i]);
                    genSvg(*mazeGame, fileSvg);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                    genBin(*mazeGame, fileBin);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .maze time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else if (argc == 2) {
                checkCalculator(argv[i]);
                int sum = 0;
                for (int count = 0; count < 10; count ++) {
                    Timer timer;
                    MazeGame *mazeGame;
                    Prim prim(2000, 2000);
                    mazeGame = &prim;
                    mazeGame->setMaze(mazeGame->createWall());
                    mazeGame->creatingMaze(0, mazeGame);
                    genSvg(*mazeGame, "svvgFile.svg");
                    genBin(*mazeGame, "binFile.maze");
                    double t = timer.milliseconds_since();
                    sum = sum + t;
                }
                int average = sum/10;
                sum = 0;
                cout << "+Average time of 10x2000/2000 with Prim's Algorithm: " << average << "=>milliseconds("<< setprecision(9) << average/1000 << " seconds)." <<endl;
                for (int count = 0; count < 10; count ++) {
                    Timer timer;
                    MazeGame *mazeGame;
                    RecursiveBacktracking rb(2000, 2000);
                    mazeGame = &rb;
                    mazeGame->setMaze(mazeGame->createWall());
                    mazeGame->creatingMaze(0, mazeGame);
                    genSvg(*mazeGame, "svvgFile.svg");
                    genBin(*mazeGame, "binFile.maze");
                    double t = timer.milliseconds_since();
                    sum = sum + t;
                }
                average = sum/10;
                sum = 0;
                cout << "+Average time of 10x2000/2000 with Recursive Backtracking 's Algorithm: " << average << "=>milliseconds("<< setprecision(9) << average/1000 << " seconds)." <<endl;
            }
            else{
                throw "Invalid argument";
            }
        
    }catch (const char* msg) {
        cerr << msg << endl;
        cout << "-------------Example------------" << endl;
        cout << "./mazer --gg seed width height --sb filename.maze \n"
                "./mazer --gp seed width height --sb filename.maze \n"
                "./mazer --gr seed width height --sv filename.svg \n"
                "./mazer --(gg, gp or gr) seed width height --sb filename.maze --sv filename.svg \n";
    }
    return 0;
}
