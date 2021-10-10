#ifndef ASD_PS_TIMER_H
#define ASD_PS_TIMER_H

#include <chrono>

using f64 = double;

struct Timer
{
    Timer(f64* timeStorageVar);
    ~Timer();

    const std::chrono::time_point<std::chrono::high_resolution_clock> beginTimer;

    private: f64* _duration;
};


#endif