
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

Machine::Machine(std::vector<Queue*> queues, Scheduler* schedulerArg): scheduler(schedulerArg) {

	for (int i = 0; i < 5; i++) {
		running[i] = 0;
		processedByQueue[i] = 0;
		waitTimeByQueue[i] = 0;
	}
	turnaroundRatiosSummed = 0.0;
	machineHoursConsumed = 0.0;
	pricesPaid = 0.0;
	runningTotal = 0;
	status = -1;
	this->queues = queues;
}

void Machine::addScheduler(Scheduler* schedulerArg){
    (*this).scheduler = schedulerArg;
}

void Machine::addQueues(std::vector<Queue*> queues){
    (*this).queues = queues;
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
	for (auto e : toRun) {
		jobsRunning.push_back(e); 
		e->setTimeLeftQueue(currentTime); //Job has left wait queue and is now started runnning
		//running[e->getCategory()] += e->getNodes();  // add to the running nodes value for the job category
		//runningTotal += e->getNodes();   //commented out b/c they are being modi
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
	runningTotal -= job->getNodes();

	//do metric stuff, still needs to be done
	
	processedByQueue[job->getCategory()]++;
		
	waitTimeByQueue[job->getCategory()] += job->getWaitTime();

	turnaroundRatiosSummed += (job->getWaitTime() + job->getRuntime()) / job->getRuntime();

	int temp = job->getNodes() * job->getRuntime();

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

	double utilizationRatio = machineHoursConsumed / (WEEKDAYCUTOFF * totalNodes);

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

	return jobsRunning.size();

}