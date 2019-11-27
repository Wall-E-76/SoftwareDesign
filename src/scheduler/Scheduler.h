#pragma once

#include "../Job.h"
#include "../Queue.h"
#include <vector>

#define WEEKENDCUTOFF 104
#define WEEKDAYCUTOFF 168 //end of week
#define MAX_DOUBLE 9999.99


class Scheduler {
public:
	Scheduler() {} //is this necessary?
	//virtual ~Scheduler() = 0;
	virtual std::vector<Job*> getJobs(int status, std::array <int,5> &running, int &runningTotal, double currentTime)=0;
	
protected:
	std::vector <Job*> nextUp;
    std::array <Queue*,5> queues;
};
