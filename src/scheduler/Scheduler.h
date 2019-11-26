#pragma once

#include "../Queue.h"


class Scheduler {
public:
	Scheduler() {} //is this necessary?
	virtual ~Scheduler() = 0;
	virtual std::vector<Job*> getJobs()=0;
protected:

	std::vector<Queue*> queues;
	std::vector<Job*> nextUp;
};
