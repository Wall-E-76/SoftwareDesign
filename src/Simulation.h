#pragma once

#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <ctgmath>
#include "Researcher.h"
#include "Student.h"

#define TIMESTEP 0.5
#define ENDTIME 24*7


class Simulation {
private:
    int totalNode;
    double currentTime;
	int weeks;
    Generator generator;
    Machine machine;
	std::array<Queue*,5> queues;

public:
    explicit Simulation(int totalNode);
	void mainProgram();
    void setup();
    void computeTimeSteps();
    void output();
};

