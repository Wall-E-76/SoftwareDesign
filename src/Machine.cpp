
#include <iostream>
#include "Machine.h"

//comments: might not need to be linked to queue?
// also, make sure that Job->category refers to short, med, large, gpu, and huge, in that order
Machine::Machine() {

	for (int i = 0; i < 5; i++) {
		running[i] = 0;
		processedByQueue[i] = 0;
		waitTimeByQueue[i] = 0.0;
	}
	turnaroundRatiosSummed = 0.0;
	machineHoursConsumed = 0.0;
	pricesPaid = 0.0;
    runningTotal = 0;
	status = -1; // added these, not sure if right
	scheduler = nullptr; //^^
}


Scheduler *Machine::getScheduler() {
    return (*this).scheduler;
}


void Machine::addScheduler(Scheduler* schedulerArg){
    (*this).scheduler = schedulerArg;
}

void Machine::addQueues(std::array<Queue*,5> queues){
    (*this).queues = queues;
}

std::array<Queue *, 5> Machine::getQueues() {
    return (*this).queues;
}

std::vector<Job *> Machine::getJobsRunning() {
    return (*this).jobsRunning;
}

void Machine::checkJobsRunning(double currentTime) {
	int n = jobsRunning.size();
	for (int i = 0; i < n; i++) {
		if (jobsRunning[i]->doneRunning(currentTime)) {
			collector(jobsRunning[i]);  
			jobsRunning.erase(jobsRunning.begin() + i);  //remove from vector of current jobs
		}
	}
}
void Machine::getJobsFromScheduler(double currentTime) {
	std::vector<Job*> toRun = scheduler->getJobs(status, running, runningTotal, currentTime);
	for (Job* e : toRun) {
		jobsRunning.push_back(e); 
		e->setTimeLeftQueue(currentTime); //Job has left wait queue and is now started runnning
	}
}
void Machine::setMachineStatus(double currentTime) {

	if (currentTime >= STATE5)
        status = 5;
	else if (currentTime >= STATE4)
		status = 4;
	else if (currentTime >= STATE3)
		status = 3;
	else if (currentTime >= STATE2)
		status = 2;
	else
		status = 1;
}

void Machine::collector(Job* job) {

	running[job->getCategory()] -= job->getNodes();
	std::cout << "Running Total1 : "<< runningTotal << std::endl;
    (*this).runningTotal -= job->getNodes();
    std::cout << "Running Total2 : "<< runningTotal << std::endl;

	//do metric stuff, still needs to be done
	
	processedByQueue[job->getCategory()]++;
		
	waitTimeByQueue[job->getCategory()] += job->getWaitTime();

	turnaroundRatiosSummed += (job->getWaitTime() + job->getRuntime()) / job->getRuntime();

	double temp = job->getNodes() * job->getRuntime();

	machineHoursConsumed += temp;

	if (job->needsGPU())
		pricesPaid += temp * MACHINE_COST_GPU;
	else 
		pricesPaid += temp * MACHINE_COST;

	delete job;
}

void Machine::report() {

	int totalJobsProcessed = 0;

	for (int i = 0; i < 5; i++) {
		totalJobsProcessed += processedByQueue[i];
	}

	double machineCost = WEEKENDCUTOFF * (totalNodes - gpuNodes) * MACHINE_COST;
	machineCost+= WEEKENDCUTOFF * (gpuNodes) * MACHINE_COST_GPU;
	machineCost += (WEEKDAYCUTOFF - WEEKENDCUTOFF) * totalNodes * MACHINE_COST;

	double utilizationRatio = machineHoursConsumed / (double(WEEKDAYCUTOFF) * totalNodes);

	double averageTurnaroundRatio = turnaroundRatiosSummed / totalJobsProcessed;

	//here will fill in code to output info to a file of a certain name...
	//probably "weekX_runtime_metrics.txt"

}


void Machine::resetMetrics() {

	for (int i = 0; i < 5; i++) {
		processedByQueue[i] = 0;
		waitTimeByQueue[i] = 0.0;
	}
	turnaroundRatiosSummed = 0.0;
	machineHoursConsumed = 0.0;
	pricesPaid = 0.0;
}

int Machine::getRunningTotal() {
	return runningTotal;
}

int Machine::getMachineStatus() {
    return (*this).status;
}

std::array<double, 5> Machine::getWaitTimeByQueue() {
    return (*this).waitTimeByQueue;
}

std::array<int, 5> Machine::getRunning() {
    return (*this).running;
}

std::array<int, 5> Machine::getProcessedByQueue() {
    return (*this).processedByQueue;
}

double Machine::getTurnaroundRatioSummed() {
    return (*this).turnaroundRatiosSummed;
}

double Machine::getPricePaid() {
    return (*this).pricesPaid;
}

double Machine::getMachineHoursConsumed() {
    return (*this).machineHoursConsumed;
}






