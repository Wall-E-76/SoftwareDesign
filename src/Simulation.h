#pragma once

#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <ctgmath>
#include "Researcher.h"
#include "Student.h"
#include "fifoScheduler.h"

#define TIMESTEP 0.5



class Simulation {
private:
    int totalNode;
    double currentTime;
	int weekCounter;
	int weeksSimulated;
    Generator* generator;
    Machine machine;
	std::array<Queue*,5> queues;

public:
    explicit Simulation(int totalNode, int weeks);
	void run();
    void setup();
    void computeTimeSteps();
    void output();
    std::array<Queue*,5> getQueues();
    void addScheduler(Scheduler* s);
    void addQueues(std::array<Queue*,5> queues);
    void addGenerator(Generator* g);
};

