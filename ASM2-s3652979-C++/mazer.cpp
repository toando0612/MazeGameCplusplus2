//
//  main.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 4/27/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

//C++ Assignment 2
//Do Quoc Toan - s3652979


#include "GTreeAndBRecursive.hpp"
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
    if ( fileType == "svg" || fileType == "bin") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .svg or .bin";
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

string checkBinFile(string input) {
    string fileType = input.substr(input.find_last_of(".") + 1);
    if (fileType == "bin") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .bin";
    }
}

string checkSvgFile(string input) {
    string fileType = input.substr(input.find_last_of(".") + 1);
    if ( fileType == "svg") {
        return input;
    }else{
        throw "_Invalid fileType : fileType must be .svg";
    }
}



// Saving to .svg function
void genSvg(MazeGame maze, string filename) {
    int x1,y1,x2,y2;
    ofstream svgFile(filename, ofstream::out);
    svgFile << "<svg"<< " viewBox="<< "\"0 0 " << width << " " << height << "\""<< " width=\""<<width << "\""<<" height=\"" << height << "\""
    << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svgFile << "<rect width=\""<<width << "\" "<< "height=\""<< height << "\" "<< " style=\'" << "fill: black\' " << "/>" << endl;
    for (int i = 0; i < maze.getWidth(); i++) {
        for (int j = 0; j < maze.getHeight(); j++) {
            for (int k = 0; k < 4; k++) {
                x1 =  maze.getMaze()[i][j].getEdgeList()[k][0];
                y1 =  maze.getMaze()[i][j].getEdgeList()[k][1];
                x2 =  maze.getMaze()[i][j].getEdgeList()[k][2];
                y2 =  maze.getMaze()[i][j].getEdgeList()[k][3];
                svgFile << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.5\'" << " x1=\'" << x1 << "\' y1=\'" << y1
                << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
            }
        }
    }
    svgFile << "</svg>" << endl;
    svgFile.close();
}

//saving to .bin function
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
        string gen = checkGen(argv [i]);
        if (argc == 7 ){ //One savingType with seed from user
            //collect seed
            //check seed
            try {
                i++;
                seed = (int) stol(argv [i]);
            }catch (const invalid_argument){
                cout << "_Seed must be a number" <<endl;
                return 1;
            }catch (const out_of_range) {
                cout << "_Seed must be lower than: " << UID_MAX << endl;
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
                cout << "_Height and width must be numbers" <<endl;
            }
            string filename = checkFileName(argv[i+1]);
            Timer timer;
            MazeGame *mazeGame;
            if (gen == "--gg" || gen == "--gr") {
                GTreeAndBRecursive gb(height, width);
                mazeGame = &gb;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else{
                Prim prim(height, width);
                mazeGame = &prim;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }
            
            
            
        } else if(argc == 6){ //One savingType with no seed from user
            int seed = 10; //default
            // check h,w
            try {
                i++;
                width = (int) stol(argv [i]);
                i++;
                height = (int) stol(argv [i]);
                i++;
            }catch (const invalid_argument){
                cout << "Height and width must be numbers" <<endl;
            }
            string filename = checkFileName(argv[i+1]);
            Timer timer;
            if (gen == "--gg" || gen == "--gr") {
                MazeGame *mazeGame;
                GTreeAndBRecursive gb(height, width);
                mazeGame = &gb;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else{
                MazeGame *mazeGame;
                Prim prim(height, width);
                mazeGame = &prim;
                mazeGame->setMaze(mazeGame->createWall());
                mazeGame->creatingMaze(seed, mazeGame);
                double t = timer.milliseconds_since();
                cout << "+Generation time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                if (checkType(argv[i]) == SAVE_SVG) {
                    genSvg(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .SVG time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    genBin(*mazeGame, filename);
                    t = timer.milliseconds_since();
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }
        } else if(argc == 9){ //Two savingType with seed from user
            //collect seed
            //check seed
            try {
                i++;
                seed = (int) stol(argv [i]);
            }catch (const invalid_argument){
                cout << "_Seed must be a number" <<endl;
                return 1;
            }catch (const out_of_range) {
                cout << "_Seed must be lower than: " << UID_MAX << endl;
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
                cout << "_Height and width must be numbers" <<endl;
            }
            Timer timer;
            if (gen == "--gg" || gen == "--gr") {
                MazeGame *mazeGame;
                GTreeAndBRecursive gb(height, width);
                mazeGame = &gb;
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
                cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
            }else{
                MazeGame *mazeGame;
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
                cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
            }
            }else if (argc == 8) { ///Two savingType with no seed from user
                int seed = 10; //default
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
                if (gen == "--gg" || gen == "--gr") {
                    MazeGame *mazeGame;
                    GTreeAndBRecursive gb(height, width);
                    mazeGame = &gb;
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
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }else{
                    MazeGame *mazeGame;
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
                    cout << "+Saving to .BIN time: " << t << "=>milliseconds("<< setprecision(9) << t/1000 << " seconds)." <<endl;
                }
            }else{
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
