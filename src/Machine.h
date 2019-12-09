/*! \file

\class Machine

\brief Machine class.

The class that will represent the opertaion of the HPC. It holds a vector of running Job pointers and contains methods needed to manage the set of 
Jobs running and the state of the Machine attributes. 
*/

#pragma once
#include <vector>
#include <array>
#include <iostream>
#include "Job.h"
#include "Queue.h"
#include "Scheduler.h"

/** \brief price paid by user for 1 machine hour, non GPU accelerated nodes. */
#define MACHINE_COST 5
/** \brief price paid by user for 1 machine hour, for GPU accelerated nodes. */
#define MACHINE_COST_GPU 6
/** \brief start time for state 0, which is equivalent to 0900am monday. No queues are affected. */
#define STATE1 0 
/** \brief start time for state 2, which is equivalent to 0100am friday. Large job queue is affected.*/
#define STATE2 88 
/** \brief start time for state 3, which is equivalent to 0900am friday. Medium and GPU job queues are affected. */
#define STATE3 96 
/** \brief start time for state 4, which is equivalent to 0400pm friday. Small job queue is affected.*/
#define STATE4 103 //start time for state 4, so 0400 pm friday
/** \brief start time for state 5, which is equivalent to 0500pm friday. Only huge job queue is accessed at this point.*/
#define STATE5 104 //start time for state 5, so 0500 pm friday


class Machine {
private:

	/// \brief array of nodes occupied on Machine, indexed by Job::category.
	std::array <int, 5> running;
	/// \brief total nodes occupied accross whole Machine.
	int runningTotal;
	/// \brief current satate of Machine.
	int state;
	/// \brief set by collector for system metrics - number of Jobs processed by Machine, indexed by Job::category.
	std::array<int, 5> processedByQueue;
	/// \brief set by collector for system metrics - sum of times spent waiting in Queue, indexed by Job::category.
	std::array<double, 5> waitTimeByQueue;
	/// \brief set by collector for system metrics - sum of all Jobs turnaround ratios. 
	double turnaroundRatiosSummed;
	/// \brief set by collector for system metrics - sum of all machine hours consumed by Users.
	double machineHoursConsumed;
	/// \brief set by collector for system metrics - sum of all User::budget spent during simulation.
	double pricesPaid;
	/// \brief vecotr of pointers for Jobs currently "running" on system. 
    std::vector <Job*> jobsRunning;
	/// \brief array of pointers to the Queues acessed by Machine. 
    std::array <Queue*,5> queues;
	/// \brief instance of Scheduler algorithm being used by Machine to run Jobs.
	Scheduler* scheduler; 
public:
    Machine();
	Scheduler* getScheduler();
    std::array<Queue*,5> getQueues();
    std::vector <Job*> getJobsRunning();
    std::array <int, 5> getRunning();
    std::array <int, 5> getProcessedByQueue();
    std::array<double, 5> getWaitTimeByQueue();
    double getTurnaroundRatioSummed();
    double getMachineHoursConsumed();
    double getPricePaid();
	/// \brief method to add a Scheduler to this Machine. 
	void addScheduler(Scheduler* schedulerArg);
	/// \brief method to set array of Queue pointers to this Machine.
	void addQueues(std::array<Queue*,5> queues);
	/** \brief checks for Jobs that have finished running on Machine.

	cycles through jobsRunning checking Job::doneRunning for each. If a Job is done running, it sends it to collector and removes 
	it from jobsRunning vector.
	*/
    void checkJobsRunning(double currentTime);
	/** \brief will call Sheduler::getJobs and add the returned Jobs to jobsRunning. 
		Will also set the Job::timeLeftQueue to the currentTime. 
	*/
    void getJobsFromScheduler(double currentTime, double systemTime);
	/// \brief will set the state based on the currentTime.
    void setMachineState(double currentTime);
	/// \brief will get the current state.
	int getMachineState();
	/// \brief returns the number of Jobs currently running on Machine.
	int getRunningTotal();
	/** \brief where Jobs are sent once they are done running on Machine.

	decreases the running and runningTotal of the machine, based on Job::nodes and Job::category. 
	Uses information from Job to update system metrics attributes.
	*/
	void collector(Job* job);
	/// \brief called at the end of the week, outputs all the processed metric data for the week to a text file. 
	void report(); 
	/// \brief resets all the metric attributes on the Machine if it is being run for another week.
	void resetMetrics(); 
};


