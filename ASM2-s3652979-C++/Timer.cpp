//
//  Timer.cpp
//  ASM2-s3652979-C++
//
//  Created by Toan Do on 5/9/19.
//  Copyright © 2019 Toan Do. All rights reserved.
//

#include "Timer.hpp"


Timer::Timer()
{
    current_time = chrono::steady_clock::now();
}

/* Return the number of milliseconds since last call */
double Timer::milliseconds_since()
{
    
    /* Adapted from snippet http://en.cppreference.com/w/cpp/chrono/time_point
     (accessed 16/9/14) */
    
    chrono::steady_clock::time_point finish = chrono::steady_clock::now();
    
    double milliseconds_since_last_call =
    chrono::duration_cast<chrono::milliseconds>(finish - current_time).count();
    
    current_time = finish;
    
    return milliseconds_since_last_call;
    
}
