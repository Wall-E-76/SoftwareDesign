#pragma once
#include <vector>
#include <array>
#include "Job.h"
#include "Queue.h"
#include "scheduler/Scheduler.h"
#define MACHINE_COST 5
#define MACHINE_COST_GPU 6
#define STATE1 9 //start time for state 1, so 0900 am monday
#define STATE2 97 //start time for state 2, so 0100 am friday
#define STATE3 105 //start time for state 3, so 0900 am friday //GPU JOBS AND MEDIUM JOBS... SO GPU WILL HAVE MAX 8 HOURS
#define STATE4 111 //start time for state 4, so 0300 pm friday
#define STATE5 113 //start time for state 5, so 0500 pm friday
//^^ dont know how to represent these time values yet...
// I imagine that the time will reset every week...and we will count the time incrementally from 1200am monday to 1159pm sunday? Yes, by hour


class Machine {
private:

	std::array <int, 5> running;
	int runningTotal;
	int status;

	std::vector<int> processedByQueue;
	//^ num of jobs processed from each queue
	std::vector<double> waitTimeByQueue;
	//^total time Jobs spent waiting in each queue, avg will be this div by processedByQueue 
	std::vector<double> turnaroundByQueue;
	double machineHoursConsumed; 
	//^ just add up nodes*runTime from each job
	double pricesPaid;
	//^ similar to machineHoursConsumed but taking into consideration user budgets spent, so GPU factor consideration
    std::vector <Job*> jobsRunning;
    std::vector <Queue*> queues;
	Scheduler* scheduler; //have it here as a reference, will need to test this and see if its right
public:
    Machine();
	explicit Machine(std::vector<Queue*> queues, Scheduler* schedulerArg);
	void addScheduler(Scheduler* schedulerArg);
	void addQueues(std::vector<Queue*> queues);
    void checkJobsRunning(double currentTime);
    void getJobsFromScheduler(double currentTime);
    void setMachineStatus(double currentTime);
	void collector(Job* job);
	void report(double currentTime); //will return or print or send to file all the info gathered and processed in collector
};


