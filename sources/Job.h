#pragma once

#include <string>
#include "users/User.h"

class Job {
private:
    std::string category;
    int cores;
    bool GPU;
    double runtime;
    double timeEnteredQueue;
    double timeLeftQueue;
    User* owner;
    // May not be necessary
    double endTime;
public:
    Job(User* owner, std::string category, int cores, bool GPU, double runtime);
    std::string getCategory();
    int getCores();
    bool needsGPU();
    double getRuntime();
    double getTimeEnteredQueue();
    void setTimeEnteredQueue(double time);
    double getTimeLeftQueue();
    void setTimeLeftQueue(double time);
    User* getOwner();
};


