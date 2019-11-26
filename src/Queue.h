#pragma once

#include "Job.h"
#include "scheduler/Scheduler.h"
#include <vector>

#define shortMin 14
#define medMin 40
#define largeMax 64
#define gpuNodes 10
#define totalNodes 128

class Queue {
private:
    std::vector <Job*> jobsInQueue;
    int numJobsProcessed;
    double totalWaitTime;
public:
    Queue();
    void insertJob(Job* job);
    Job* nextJob();
    void removeJob(int n);
    std::vector <Job*> getJobsInQueue();
    void incrNumJobsProcessed();
    void addWaitTime(double time);


};

