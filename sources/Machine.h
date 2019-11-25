#pragma once
#include <vector>
#include <array>
#include "Job.h"
#include "Queue.h"
#define MACHINE_COST 5
#define MACHINE_COST_GPU 6


class Machine {
private:
    int shortMin;
    int medMin;
    int largeMax;
    int gpuNodes;
    int totalNodes;
    int availableShort;
    int availableMed;
    int availableLarge;
    int availableGPU;
    int availableHuge;
    int machineStatus;
    std::vector <Job> jobsRunning;
    std::array <Queue,5> queues;
public:
    Machine(int shortMin, int medMin, int largeMax, int gpuNodes, int totalNodes);
    void addQueue(Queue queue, int category);
    void checkJobsRunning();
    void checkAvailability();
    void setMachineStatus();
};


