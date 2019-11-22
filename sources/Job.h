#pragma once

#include <string>
#include "users/User.h"

class Job {
private:
    int category;
    int cores;
    bool GPU;
    double runtime;
    double timeEnteredQueue;
    double timeLeftQueue;
    User* owner;
    // May not be necessary
    double endTime;
public:
    Job(User* owner, int category, int cores, bool GPU, double runtime);
    int getCategory();
    int getCores();
    bool needsGPU();
    double getRuntime();
    double getTimeEnteredQueue();
    void setTimeEnteredQueue(double time);
    double getTimeLeftQueue();
    void setTimeLeftQueue(double time);
    User* getOwner();
};


