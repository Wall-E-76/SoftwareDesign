#pragma once

#include "users/User.h"
#include "Job.h"
#include <vector>
#include "Machine.h"
#include "Queue.h"
#define TIMESTEP 0.5
#define ENDTIME 24*14

struct PropertyQueue {
    int coreMax;
    int timeMax;
};

class Generator {
private:
    std::vector <User*> users;
    std::array<PropertyQueue,5> property;
    std::array<Queue,5> queues;

public:
    Generator();
    explicit Generator(int totlNodes);
    void addUser(User *user);
    int randomCategory(int i);
    Job createJob(int i);
    void check(Job* job);
    void lookForJobs(double currentTime);
    double roundUp(double time);
};


