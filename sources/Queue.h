#pragma once

#include "Job.h"
#include "scheduler/Scheduler.h"
#include <vector>

class Queue {
private:
    std::vector <Job*> jobsInQueue;
    int numJobsProcessed;
    double totalWaitTime;
public:
    Queue();
    void insertJob(Job* job);
    Job nextJob();
    void removeJob();
    std::vector <Job*> getJobsInQueue();
    void incrNumJobsProcessed();
    void addWaitTime(double time);
};

