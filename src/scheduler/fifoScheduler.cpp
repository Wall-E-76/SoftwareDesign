
#include "fifoScheduler.h"


FIFOScheduler::FIFOScheduler(std::vector<Queue*> queues) {
	this->queues = queues;
}

std::vector<Job*> FIFOScheduler::getJobs(int status, std::array <int, 5>& running, int& runningTotal, double currentTime) {

	std::vector<Job*> nextJobs;

	//have only done case 1 so far,
	//will have it so there is a case for state 5, weekend mode, and then the other case for weekdays but
	//need to have if statements each time to check to see what state it is and if it needsto check time and look at next one in queue..

	switch (status) {

	case 5:           //case for state 5, weekend opeteration

		if (running[4] < totalNodes) {
			int n = 0;
			while (running[4] < totalNodes) {
				Job* temp = queues[4]->nextJob();
				if (temp->getReservedTime() + currentTime > WEEKENDCUTOFF) {
					n = queues[4]->nextJobT(WEEKENDCUTOFF - currentTime);
					if (n > 0) {
						temp = queues[4]->getJobAt(n);
					}
					else
						break; //means no more jobs in the queue can be run at this time
				}
				if (temp->getNodes() + running[4] <= totalNodes) {
					nextJobs.push_back(temp);
					running[4] += temp->getNodes();
					runningTotal += temp->getNodes(); //redundant but keeping it in for consistency 
					queues[4]->removeJob(n, currentTime);
				}
				else
					break; //because next job in queue will go over resource max, so stop checking for more jobs to run
			}
		}
		return nextJobs;

	default:       //case for states 1-4, weekday opertaion
		if (running[0] < shortMin) {
			int n = 0;
			while (running[0] < shortMin) {
				Job* temp = queues[0]->nextJob();
				if (temp == nullptr) break;
				if (status == 4) {
					if (temp->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						n = queues[0]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (n > 0) {
							temp = queues[0]->getJobAt(n);
						}
						else
							break; //else, we break out because no more jobs can be run in time
					}
				}
				if (temp->getNodes() + running[0] <= shortMin) {
					nextJobs.push_back(temp);
					running[0] += temp->getNodes();
					runningTotal += temp->getNodes();
					queues[0]->removeJob(n, currentTime);
				}
				else
					break; //because next job will go over, so leave while loop and continue on
			}
		}
		if (running[1] < medMin) {
			int n = 0;
			while (running[1] < medMin) {
				Job* temp = queues[1]->nextJob();
				if (temp == nullptr) break;
				if (status == 3) {
					if (temp->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						n = queues[1]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (n > 0) {
							temp = queues[1]->getJobAt(n);
						}
						else
							break;
					}
				}
				if (temp->getNodes() + running[1] <= medMin) {
					nextJobs.push_back(temp);
					running[1] += temp->getNodes();
					runningTotal += temp->getNodes();
					queues[1]->removeJob(n, currentTime);
				}
				else
					break;
			}
		}
		if (running[3] < gpuNodes) {
			int n = 0; //position in queue of job being looked at, default 0 but might change for time constraint case
			while (running[3] < gpuNodes) {
				Job* temp = queues[3]->nextJob();
				if (temp == nullptr) break; //means there are no more jobs in this queue, so we break out
				if (status == 3) {
					//if its status 3, we need to check times of jobs
					//so, we check if the first job in the gpu queue goes will go over our cutoff 
					if (temp->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						// if it, does, we will check to see if any other jobs in the GPU queue can run in time
						n = queues[3]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (n > 0) {
							//if we find one, we make it the new temp
							temp = queues[3]->getJobAt(n);
						}
						else
							break; //else, we break out because no more jobs can be run in time
					}
				}
				if (temp->getNodes() + running[3] <= gpuNodes) {
					nextJobs.push_back(temp);
					running[3] += temp->getNodes();
					runningTotal += temp->getNodes();
					queues[3]->removeJob(n, currentTime);
				}
				else
					break;
			}
		}

		Job* temp0 = queues[0]->nextJob(); //short
		Job* temp1 = queues[1]->nextJob(); //medium
		Job* temp2 = queues[2]->nextJob(); //large jobs

		while (runningTotal - running[3] < totalNodes - gpuNodes) {

			double oldestTime = MAX_DOUBLE; //oldest time of next jobs in line, initialized to unreachable value
			int oldest = 3; //queues index of oldest job, initialized to unreachable value
			int nShort = 0; int nMedium = 0; int nLarge = 0;

			if (temp0 != nullptr) {
				bool flag = false;
				if (status == 4) {
					if (temp0->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						//next job in this queue can't be run, so lets check for others
						nShort = queues[0]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (nShort > 0) {
							temp0 = queues[0]->getJobAt(nShort);
						}
						else
							flag = true;//no jobs in this queue can be run at this time, so make it so it dosent check the times below
					}
				}
				if (temp0->getTimeEnteredQueue() < oldestTime && flag == false) {
					oldestTime = temp0->getTimeEnteredQueue();
					oldest = 0;
				}
			}
			if (temp1 != nullptr) {
				bool flag = false;
				if (status == 3) {
					if (temp1->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						nMedium = queues[1]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (nMedium > 0) {
							temp1 = queues[1]->getJobAt(nMedium);
						}
						else
							flag = true;
					}
				}
				if (temp1->getTimeEnteredQueue() < oldestTime && flag == false) {
					oldestTime = temp1->getTimeEnteredQueue();
					oldest = 1;
				}
			}

			if (temp2 != nullptr) {
				bool flag = false;
				if (status == 2) {
					if (temp2->getReservedTime() + currentTime > WEEKENDCUTOFF) {
						nLarge = queues[2]->nextJobT(WEEKENDCUTOFF - currentTime);
						if (nLarge > 0) {
							temp2 = queues[2]->getJobAt(nLarge);
						}
						else
							flag = true;
					}
				}
				if (temp2->getTimeEnteredQueue() < oldestTime && flag == false) {
					oldestTime = temp2->getTimeEnteredQueue();
					oldest = 2;
				} //finds the oldest job in the three main queues
			}

			if (temp0 == nullptr && temp1 == nullptr && temp2 == nullptr)
				break; //if there are no more jobs that can be run next, break out from scheduler


			if (oldest == 0) {
				if (temp0->getNodes() + running[0] + running[2] + gpuNodes + std::max(medMin, running[1]) <=
					totalNodes) {
					nextJobs.push_back(temp0);
					running[0] += temp0->getNodes();
					runningTotal += temp0->getNodes();
					queues[0]->removeJob(nShort, currentTime);
					temp0 = queues[0]->nextJob();
				}
				else
					break;
			}
			else if (oldest == 1) {
				if (temp1->getNodes() + running[1] + running[2] + gpuNodes + std::max(shortMin, running[0]) <=
					totalNodes) {
					nextJobs.push_back(temp1);
					running[1] += temp1->getNodes();
					runningTotal += temp1->getNodes();
					queues[1]->removeJob(nMedium, currentTime);
					temp1 = queues[1]->nextJob();
				}
				else
					break;
			}
			else if (oldest == 2) {
				if (temp2->getNodes() + running[2] + gpuNodes + std::max(medMin, running[1]) +
					std::max(shortMin, running[0]) <= totalNodes) {
					nextJobs.push_back(temp2);
					running[2] += temp2->getNodes();
					runningTotal += temp2->getNodes();
					queues[2]->removeJob(nLarge, currentTime);
					temp2 = queues[2]->nextJob();
				}
				else
					break;
			}

		}
		return nextJobs;
	}
}