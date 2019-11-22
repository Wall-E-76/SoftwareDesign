#pragma once

#include "Job.h"


class Simulation {
private:
    int machineHours;
    int resultingPrice;
    double totalTurnAroundTimeRatio;

public:
    Simulation();
    void addMachineHours(Job job);
    void addResultingPrice(Job job);
    void addTurnAroungRatio(Job job);
};

