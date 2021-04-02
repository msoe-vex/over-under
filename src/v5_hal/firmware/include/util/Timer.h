#pragma once

#include "api.h"
#include <chrono>
#include <time.h>
#include "adaptive_pursuit_controller/Logger.h"

class Timer {
private:
    double m_startTime = 0;
    double m_stopTime = 0;
    bool m_started = false;
    bool m_stopped = false;
public:
    static double getTime();
    double Get();
    void Stop();
    void Reset();
    void Start();
};