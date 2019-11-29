#pragma once

#include "../src/Scheduler.h"

class MockScheduler : public Scheduler {
public:
    MockScheduler();
    std::vector<Job*> getJobs(int state, std::array <int,5> &running, int &runningTotal, double currentTime);

};

