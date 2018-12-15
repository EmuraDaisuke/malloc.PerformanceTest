#pragma once



#include <chrono>
#include "./ConsoleLog.h"



class Lapse final {
    public:
        ~Lapse()        { clog(Now() - mLapse); }
        Lapse()         :mLapse(Now()){}
    
    private:
        double Now()    { using namespace std::chrono; return static_cast<double>(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count()) / 1000000000; }
    
    
    private:
        double mLapse;
};
