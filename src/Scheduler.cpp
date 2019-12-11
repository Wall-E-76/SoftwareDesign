#include "Scheduler.h"

void Scheduler::addQueues(std::array<Queue *, 5> queues) {
    (*this).queues = queues;
}

std::array<Queue *, 5> Scheduler::getQueues() {
    return (*this).queues;
}