#include "Queue.h"

Queue::Queue():jobsInQueue({})
{}

void Queue::insertJob(Job *job, double systemTime) {
    (*this).jobsInQueue.push_back(job);
	job->setTimeEnteredQueue(systemTime);
}

Job* Queue::nextJob() {
    if (!(*this).jobsInQueue.empty()){
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