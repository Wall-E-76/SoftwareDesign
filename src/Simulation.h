#pragma once

#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <ctgmath>
#include "Researcher.h"
#include "Student.h"

#define TIMESTEP 0.5
#define ENDTIME 24*14


class Simulation {
private:
    int totalNode;
    double currentTime;
    Generator generator;
    Machine machine;

public:
    explicit Simulation(int totalNode);
    void setup();
    void computeTimeSteps();
    void output();
};

