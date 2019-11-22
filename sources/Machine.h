#pragma once
#include <vector>
#include "Job.h"


class Machine {
private:
    static int shortMin;
    static int medMin;
    static int largeMax;
    static int gpuNodes;
    static int totalNodes;
    int availableShort;
    int availableMed;
    int availableLarge;
    int availableGPU;
    int availableHuge;
    int machineStatus;
    std::vector <Job> jobsRunning;

public:
    Machine(int shortMin, int medMin, int largeMax, int gpuNodes, int totalNodes);
    void checkJobsRunning();
    void checkAvailability();
    void setMachineStatus();
};


