/*! \file

\class Job

\brief Job class.

Job will self-contain all of its information, and a pointer to it will be passed around throughout the program. Once the Job is done running, it will
be used to calculate the metrics of the Simulation with Machine::collector.
 
*/

#pragma once
#include <string>
#include "User.h"

class Job {
private:
	/// \brief category of Job.
    int category;
	/// \brief nodes required by Job.
    int nodes;
	/// \brief whether this is a GPU accelerated Job or not.
    bool GPU;
	/// \brief actual runtime of Job, randomly determined by Generator.
    double runtime;
	/// \brief machine time the User would manually reserve for their Job.
	double reservedTime; 
	/// \brief time the Job enters it's wait queue, considered same as time of creation.
    double timeEnteredQueue;
	/// \brief time Job leaves it's wait queue, considered same as time it begins to run on Machine.
    double timeLeftQueue;
	/// \brief pointer to the User who owns this Job.
    User* owner;
public:
    Job(User* owner, int category, int cores, bool GPU, double runtime, double reservedTime);
	/// \brief returns #category of Job.
    int getCategory();
	/// \brief returns #nodes of Job.
    int getNodes();
	/// \brief returns true if Job needs GPU acceleration, false otherwise.
    bool needsGPU();
	/// \brief returns #runtime of Job.
    double getRuntime();
	/// \brief returns #reservedTime of Job.
    double getReservedTime();
	/// \brief returns #timeEnteredQueue of Job.
    double getTimeEnteredQueue();
	/// \brief sets value of Job attribute #timeEnteredQueue.
    void setTimeEnteredQueue(double time);
	/// \brief returns #timeLeftQueue of Job.
    double getTimeLeftQueue();
	/// \brief sets value of Job attribute #timeLeftQueue.
    void setTimeLeftQueue(double time);
	/// \brief returns difference in time between #timeLeftQueue and #timeEnteredQueue of Job
	double getWaitTime();
	/** \brief checks if Job is done running by time give.

	If the timeLeftQueue + runtime is less than or equal to the time parameter, then return true. Otherwise, return false.
	*/
	bool doneRunning(double time);
	/// \brief returns pointer to User object who owns this Job.
    User* getOwner();
};


