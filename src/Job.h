#pragma once

#include <string>
#include "User.h"

class Job {
private:
    int category;
    int nodes;
    bool GPU;
    double runtime;
	double reservedTime; // need to adjust code to account for this User-defined parameter
    double timeEnteredQueue;
    double timeLeftQueue;
    User* owner;
public:
    Job(User* owner, int category, int cores, bool GPU, double runtime, double reservedTime);
    int getCategory();
    int getNodes();
    bool needsGPU();
    double getRuntime();
    double getReservedTime();
    double getTimeEnteredQueue();
    void setTimeEnteredQueue(double time);
    double getTimeLeftQueue();
    void setTimeLeftQueue(double time);
	bool doneRunning(double time);
    User* getOwner();
};


