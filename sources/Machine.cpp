
#include "Machine.h"

Machine::Machine(int shortMin, int medMin, int largeMax, int gpuNodes, int totalNodes){

}

void Machine::addQueue(std::array<Queue, 5> &queues) {
    (*this).queues = queues;
}
