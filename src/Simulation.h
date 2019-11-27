#pragma once

#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <ctgmath>
#include "Researcher.h"
#include "Student.h"
#include "scheduler/fifoScheduler.h"

#define TIMESTEP 0.5
#define ENDTIME 24*7


class Simulation {
private:
    int totalNode;
    double currentTime;
	int weekCounter;
	int weeksSimulated;
    Generator generator;
    Machine machine;
	std::array<Queue*,5> queues;

public:
    explicit Simulation(int totalNode, int weeks);
	void mainProgram();
    void setup();
    void computeTimeSteps();
    void output();
};

