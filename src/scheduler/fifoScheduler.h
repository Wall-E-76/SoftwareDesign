#pragma once

#include "Scheduler.h"


class FIFOScheduler : public Scheduler{
public:
	FIFOScheduler(std::array<Queue*,5> queues);
	std::vector<Job*> getJobs(int status, std::array <int, 5>& running, int& runningTotal, double currentTime);

private:

	std::vector<Job*> fillReserved(int& running, int& runningTotal, Queue*& queue, int status, int statusCheck,
		int cutoffTime, double currentTime, int limitNodes);

	Job* oldestCheck(int& oldest, double& oldestTime, int& n, int status,int statusCheck, 
		double cutoffTime, int queue, double currentTime);

};

