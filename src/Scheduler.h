#pragma once

#include "Job.h"
#include "Queue.h"
#include <vector>

#define WEEKENDCUTOFF 104
#define WEEKDAYCUTOFF 168 //end of week
#define MAX_DOUBLE 9999.99


class Scheduler {
public:
	Scheduler() {}
	//virtual ~Scheduler() = 0;
	virtual std::vector<Job*> getJobs(int state, std::array <int,5> &running, int &runningTotal, double currentTime)=0;
	void addQueues(std::array<Queue *, 5> queues);
    std::array<Queue *, 5> getQueues();
	
protected:
	std::vector <Job*> nextUp;
    std::array <Queue*,5> queues;
};
