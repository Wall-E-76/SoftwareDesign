#pragma once

#include "../Job.h"
#include "../Queue.h"
#include <vector>


class Scheduler {
public:
	Scheduler() {} //is this necessary?
	virtual ~Scheduler() = 0;
	virtual std::vector<Job*> getJobs(int status, std::array <int,5> &running, int &runningTotal, double currentTime)=0;
protected:
	std::vector <Job*> nextUp;
    std::vector <Queue*> queues;
};
