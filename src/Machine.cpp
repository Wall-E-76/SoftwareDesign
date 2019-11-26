
#include "Machine.h"

//comments: might not need to be linked to queue?
// also, make sure that Job->category refers to short, med, large, gpu, and huge, in that order

Machine::Machine(std::vector<Queue*> queues, Scheduler& schedulerArg) : scheduler(schedulerArg) {

	running[0] = 0;
	running[1] = 0;
	running[2] = 0;
	running[3] = 0;
	running[4] = 0;
	runningTotal = 0;
	this->queues = queues;
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
	std::vector<Job*> toRun = scheduler.getJobs(status, running, runningTotal);
	for (auto e : toRun) {
		jobsRunning.push_back(e); 
		e->setTimeLeftQueue(currentTime); //Job has left wait queue and is now started runnning
		//running[e->getCategory()] += e->getNodes();  // add to the running nodes value for the job category
		//runningTotal += e->getNodes();   //commented out b/c they are being modi
	}
}
void Machine::setMachineStatus(double currentTime) {

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
	runningTotal -= job->getNodes();

	//do metric stuff, still needs to be done

	delete job;
}


