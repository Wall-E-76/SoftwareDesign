
#include "Queue.h"

Queue::Queue():
    numJobsProcessed(0),
    totalWaitTime(0),
    jobsInQueue({})
{
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

void Queue::removeJob(int n, double currentTime) {
    if (jobsInQueue[n]){
		jobsInQueue[n]->setTimeLeftQueue(currentTime);
        jobsInQueue.erase(jobsInQueue.begin()+n);
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

Job* Queue::getJobAt(int n) {

	if (n > jobsInQueue.size() - 1)
		return nullptr;
	else
		return jobsInQueue[n];
}

int Queue::nextJobT(double time) {
	int i = 1; //start looking at jobs after the first job

	for (i; i< jobsInQueue.size(); i++) {
		if (jobsInQueue[i]->getReservedTime() <= time) {
			return i;
		}
	}
	return -1;
}




