//
//  Timer.hpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/9/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//


#include <chrono>

using namespace std;


class Timer {
protected:
    chrono::steady_clock::time_point current_time;
    
public:
    Timer();
    
    double milliseconds_since();
};


