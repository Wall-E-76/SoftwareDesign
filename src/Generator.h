#pragma once

#include "User.h"
#include "Job.h"
#include <vector>
#include "Machine.h"
#include "Queue.h"
#include <array>
#include <iostream>
#define TIMESTEP 0.5
#define ENDTIME 24*7
#define SHORTMAXNODES 2
#define MEDIUMMAXNODES 12
#define LARGEMAXNODES 64
#define GPUMAXNODES 10
#define HUGEMAXNODES 128

struct PropertyQueue {
    int nodeMax;
	int nodeMinExclusive;
    int timeMax;
};

class Generator {
private:
    std::vector <User*> users;
    std::array<PropertyQueue,5> property;
    std::array<Queue*,5> queues;

public:
    Generator();
    explicit Generator(int totlNodes);
    std::vector <User*> getUsers();
    std::array<PropertyQueue,5> getProperty();
    std::array<Queue*,5> getQueues();  //i dont think this is used ever
    void addQueues(std::array<Queue*,5> queue);
    void addUser(User *user);
    int randomCategory(int i);
    Job* createJob(int i);
    void check(Job* job, double currentTime);
    void lookForJobs(double currentTime);
    double roundUp(double time);
};


