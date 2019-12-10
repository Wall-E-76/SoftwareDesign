/*! \file

\class Scheduler

\brief Scheduler interface.

Virtual class that serves as a an interface for a Scheduling algorithm.
*/
#pragma once
#include "Job.h"
#include "Queue.h"
#include <vector>

/// \brief cutoff time for weekday Jobs (Queue 1-4). Corresponds to 0500pm Friday.
#define WEEKENDCUTOFF 104
/// \brief cutoff time for weekend Jobs (Queue 5). Corresponds to 0900am Monday.
#define WEEKDAYCUTOFF 168 //end of week
/// \brief used to compare Jobs to see which enetered it's wait Queue the longet ago.
#define MAX_DOUBLE 9999.99


class Scheduler {
public:
	Scheduler() {}
	//virtual ~Scheduler() = 0;
	/// \brief virtual function that takes in Machine running information, the time, the state, and searches the Queues for Jobs to be run at this time. Returns a vector of Job pointers.
	virtual std::vector<Job*> getJobs(int state, std::array <int,5> &running, int &runningTotal, double currentTime, double systemTime)=0;
	/// \brief adds an array of Queue pointers to the Scheduler for referencing. 
	void addQueues(std::array<Queue *, 5> queues);
	/// \brief getter used in Unit testing - returns Scheduler's array of Queue pointers 
    std::array<Queue *, 5> getQueues();
	
protected:
	/// \brief array of Queue pointers for the Scheduler's reference.
    std::array <Queue*,5> queues;
};
