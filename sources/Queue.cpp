
#include "Queue.h"

Queue::Queue() {
    (*this).jobsInQueue ={};
    (*this).numJobsProcessed = 0;
    (*this).totalWaitTime = 0;
}

void Queue::insertJob(Job *job) {
    (*this).jobsInQueue.push_back(job);
}

Job* Queue::nextJob() {
    if ((*this).jobsInQueue.empty()){
        return (*this).jobsInQueue.front();
    }
    else {
        return nullptr;
    }
}

void Queue::removeJob() {
    if (!(*this).jobsInQueue.empty()){
        (*this).jobsInQueue.erase((*this).jobsInQueue.begin());;
    }
}

std::vector<Job *> Queue::getJobsInQueue() {
    return (*this).jobsInQueue;
}

void Queue::incrNumJobsProcessed() {
    (*this).numJobsProcessed++;
}

void Queue::addWaitTime(double time) {
    (*this).addWaitTime(time);
}
