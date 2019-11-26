#pragma once

#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <ctgmath>
#include <src/users/Researcher.h>
#include <src/users/Student.h>

#define TIMESTEP 0.5
#define ENDTIME 24*14


class Simulation {
private:
    int totalNode;
    double currentTime;
    int machineHours;
    int resultingPrice;
    double totalTurnAroundTimeRatio;
    Generator generator;
    Machine machine;

public:
    explicit Simulation(int totalNode);
    void setup();
    void computeTimeSteps();
    void output();
    void addMachineHours(Job job);
    void addResultingPrice(Job job);
    void addTurnAroungRatio(Job job);
};

