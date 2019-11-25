
#include "Machine.h"

Machine::Machine(int shortMin, int medMin, int largeMax, int gpuNodes, int totalNodes):
    shortMin(shortMin),
    medMin(medMin),
    largeMax(largeMax),
    gpuNodes(gpuNodes),
    totalNodes(totalNodes)
{
    availableShort = shortMin;
    availableMed = medMin;
    availableLarge = largeMax;
    availableGPU = gpuNodes;
    availableHuge = 0;
    machineStatus = 0;
}

void Machine::addQueue(Queue queue, int category) {
    (*this).queues[category] = queue;
}
