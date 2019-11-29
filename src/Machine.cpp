
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
	state = -1; // added these, not sure if right
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
	int counter = 0;
	while (counter < jobsRunning.size()) {
		if (jobsRunning[counter]->doneRunning(currentTime)) {
			collector(jobsRunning[counter]);
			jobsRunning.erase(jobsRunning.begin() + counter);  //remove from vector of current jobs
		}
		else{
            counter++;
		}

	}
}
void Machine::getJobsFromScheduler(double currentTime) {
	std::vector<Job*> toRun = scheduler->getJobs(state, running, runningTotal, currentTime);
	for (auto e : toRun) {
		jobsRunning.push_back(e); 
		e->setTimeLeftQueue(currentTime); //Job has left wait queue and is now started runnning
	}
}
void Machine::setMachineState(double currentTime) {

	if (currentTime >= STATE5)
        state = 5;
	else if (currentTime >= STATE4)
		state = 4;
	else if (currentTime >= STATE3)
		state = 3;
	else if (currentTime >= STATE2)
		state = 2;
	else
		state = 1;
}

void Machine::collector(Job* job) {

	running[job->getCategory()] -= job->getNodes();
    (*this).runningTotal -= job->getNodes();

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
    std::cout << std::endl;
    std::cout<< "Weekly report: "<<std::endl;
	int totalJobsProcessed = 0;

	for (int i = 0; i < 5; i++) {
        std::cout << "Total jobs processed in queue "<<i<<": " << processedByQueue[i]<< std::endl;
		totalJobsProcessed += processedByQueue[i];
	}

	double machineCost = WEEKENDCUTOFF * (totalNodes - gpuNodes) * MACHINE_COST;
	machineCost+= WEEKENDCUTOFF * (gpuNodes) * MACHINE_COST_GPU;
	machineCost += (WEEKDAYCUTOFF - WEEKENDCUTOFF) * totalNodes * MACHINE_COST;

	double utilizationRatio = machineHoursConsumed / (double(WEEKDAYCUTOFF) * totalNodes);

	double averageTurnaroundRatio = turnaroundRatiosSummed / totalJobsProcessed;

	std::cout << "Utilization Ratio: " << utilizationRatio<< std::endl;
    std::cout << "Machine cost: " << machineCost<< std::endl;
    std::cout << "Price paid: "<< (*this).pricesPaid<< std::endl;
    std::cout << "Machine Hours consumed: "<< machineHoursConsumed << std::endl;

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

int Machine::getMachineState() {
    return (*this).state;
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






