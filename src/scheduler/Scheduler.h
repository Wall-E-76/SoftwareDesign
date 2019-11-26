#pragma once

#include "../Queue.h"


class Scheduler {
public:
	Scheduler() {} //is this necessary?
	virtual ~Scheduler() = 0;
	virtual std::vector<Job*> getJobs(int status, std::array <int,5> &running, int &runningTotal, double currentTime)=0;
protected:

	std::vector<Queue*> queues;
	std::vector<Job*> nextUp;
};
