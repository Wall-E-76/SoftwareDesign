
#include "Job.h"

Job::Job(User *owner, std::string category, int cores, bool GPU, double runtime) {
    (*this).category = category;
    (*this).cores = cores;
    (*this).GPU= GPU;
    (*this).runtime= runtime;
    (*this).timeEnteredQueue=0;
    (*this).timeLeftQueue=0;
    (*this).owner= owner;
    (*this).endTime = 0;
}

std::string Job::getCategory() {
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
