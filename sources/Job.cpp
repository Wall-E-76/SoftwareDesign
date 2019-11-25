
#include "Job.h"

Job::Job(User *owner, int category, int cores, bool GPU, double runtime):
    category(category),
    cores(cores),
    GPU(GPU),
    runtime(runtime),
    timeLeftQueue(0),
    timeEnteredQueue(0),
    owner(owner),
    endTime(0)
{
}

int Job::getCategory() {
    return (*this).category;
}

int Job::getCores() {
    return (*this).cores;
}

bool Job::needsGPU() {
    return (*this).GPU;
}

double Job::getRuntime() {
    return (*this).runtime;
}

double Job::getTimeEnteredQueue() {
    return (*this).timeEnteredQueue;
}

void Job::setTimeEnteredQueue(double time) {
    (*this).timeEnteredQueue = time;
}

double Job::getTimeLeftQueue() {
    return (*this).timeLeftQueue;
}

void Job::setTimeLeftQueue(double time) {
    (*this).timeLeftQueue = time;
}

User *Job::getOwner() {
    return (*this).owner;
}
