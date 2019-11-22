#pragma once

#include "users/User.h"
#include "Job.h"
#include <vector>
#include "Machine.h"
#include "Queue.h"

struct PropertyQueue {
    int nodeMax;
    int timeMax;
};

class Generator {
private:
    std::vector <User> users;
    std::array<PropertyQueue,5> property;
    std::array<Queue,5> queues;

public:
    Generator();
    void addQueue(std::array<Queue,5> &queues);
    int randomCategory(int i);
    Job createJob(int i);
    void check(Job* job);
    void lookForJobs(int currentTime);
};


