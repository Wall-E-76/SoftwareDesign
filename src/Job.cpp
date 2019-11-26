
#include "Job.h"

Job::Job(User *owner, int category, int cores, bool GPU, double runtime, double reservedTime):
    category(category),
    GPU(GPU),
    runtime(runtime),
    timeLeftQueue(0),
    timeEnteredQueue(0),
    owner(owner),
	reservedTime(reservedTime)
{
	this->nodes = cores / 16;
	if (cores % 16 != 0)
		this->nodes++;
}

int Job::getCategory() {
    return (*this).category;
}

int Job::getNodes() {
    return (*this).nodes;
}

bool Job::needsGPU() {
    return (*this).GPU;
}

double Job::getRuntime() {
    return (*this).runtime;
}

double Job::getReservedTime() {
    return (*this).reservedTime;
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

bool Job::doneRunning(double time) {
    return timeLeftQueue + runtime <= time;
}

void Job::setTimeLeftQueue(double time) {
    (*this).timeLeftQueue = time;
}

User *Job::getOwner() {
    return (*this).owner;
}
