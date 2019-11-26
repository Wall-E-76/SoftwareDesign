#pragma once

#include "Scheduler.h"


class FIFOScheduler : public Scheduler{
public:
	FIFOScheduler(std::vector<Queue*> queues);
	std::vector<Job*> getJobs(int status, std::array <int, 5>& running, int& runningTotal, double currentTime);
};

