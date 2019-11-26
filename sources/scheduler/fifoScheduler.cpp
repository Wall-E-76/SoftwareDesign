
#include "fifoScheduler.h"


FIFOScheduler::FIFOScheduler(std::vector<Queue*> queues) {
	this->queues = queues;
}

std::vector<Job*> FIFOScheduler::getJobs(int status, std::array <int,5> &running, int &runningTotal, double currentTime) {
	
	std::vector<Job*> nextJobs;

	//have only done case 1 so far,
	//will have it so there is a case for state 5, weekend mode, and then the other case for weekdays but
	//need to have if statements each time to check to see what state it is and if it needsto check time and look at next one in queue..

	switch (status) {

	case 1 : 
		if (running[0] < shortMin) {
			while (running[0] < shortMin) {
				Job* temp = queues[0]->nextJob();
				if (temp->getNodes() + running[0] <= shortMin) {
					nextJobs.push_back(temp);
					running[0] += temp->getNodes();
					runningTotal += temp->getNodes();;
				}
				else
					break; //because next job will go over, so leave while loop and continue on
			}
		}
		if (running[1] < medMin) {
			while (running[1] < medMin) {
				Job* temp = queues[1]->nextJob();
				if (temp->getNodes() + running[1] <= medMin) {
					nextJobs.push_back(temp);
					running[1] += temp->getNodes();
					runningTotal += temp->getNodes();
				}
				else
					break; 
			}
		}
		if (running[3] < gpuNodes) {
			while (running[3] < gpuNodes) {
				Job* temp = queues[3]->nextJob();
				if (temp->getNodes() + running[3] <= gpuNodes) {
					nextJobs.push_back(temp);
					running[3] += temp->getNodes();
					runningTotal += temp->getNodes();
				}
				else
					break; 
			}
		}

		Job* temp0 = queues[0]->nextJob();
		Job* temp1 = queues[1]->nextJob();
		Job* temp2 = queues[2]->nextJob();

		while (runningTotal-running[3]< totalNodes-gpuNodes){

			double oldestTime= temp0->getTimeEnteredQueue();
			int oldest = 0;

			if (temp1->getTimeEnteredQueue() < oldestTime) {
				oldestTime = temp1->getTimeEnteredQueue();
				oldest = 1;
			}
			if (temp2->getTimeEnteredQueue() < oldestTime) {
				oldestTime = temp2->getTimeEnteredQueue();
				oldest = 2;
			} //finds the oldest job in the three main queues

			
			if (oldest == 0) {
				if (temp0->getNodes()+running[0]+ running[2] + gpuNodes+ max(medMin, running[1]) <= totalNodes) {
					nextJobs.push_back(temp0);
					running[0] += temp0->getNodes();
					runningTotal += temp0->getNodes();
					queues[0]->removeJob(0);
					temp0 = queues[0]->nextJob();
				}
				else
					break;
			}
			else if (oldest == 1) {
				if (temp1->getNodes() + running[1] + running[2] + gpuNodes + max(shortMin, running[0]) <= totalNodes) {
					nextJobs.push_back(temp1);
					running[1] += temp1->getNodes();
					runningTotal += temp1->getNodes();
					queues[1]->removeJob(0);
					temp1 = queues[1]->nextJob();
				}
				else
					break;
			}

			else {
				if (temp2->getNodes() + running[2] + gpuNodes + max(medMin, running[1]) + max(shortMin, running[0]) <= totalNodes) {
					nextJobs.push_back(temp2);
					running[2] += temp2->getNodes();
					runningTotal += temp2->getNodes();
					queues[2]->removeJob(0);
					temp2 = queues[2]->nextJob();
				}
				else
					break;
			}
	
		}

		return nextJobs;
	

}