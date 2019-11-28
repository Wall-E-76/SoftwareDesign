#pragma once
#include <vector>
#include <array>
#include "Job.h"
#include "Queue.h"
#include "Scheduler.h"
#define MACHINE_COST 5
#define MACHINE_COST_GPU 6
#define STATE1 0 //start time for state 1, so 0900 am monday
#define STATE2 88 //start time for state 2, so 0100 am friday
#define STATE3 96 //start time for state 3, so 0900 am friday //GPU JOBS AND MEDIUM JOBS... SO GPU WILL HAVE MAX 8 HOURS
#define STATE4 103 //start time for state 4, so 0400 pm friday
#define STATE5 104 //start time for state 5, so 0500 pm friday
// I imagine that the time will reset every week...and we will count the time incrementally from 1200am monday to 1159pm sunday? 


class Machine {
private:

	std::array <int, 5> running;
	int runningTotal;
	//running refers to Nodes occupied by jobs
	int status;

	std::array<int, 5> processedByQueue;
	//^ num of jobs processed from each queue
	std::array<double, 5> waitTimeByQueue;
	//^total time Jobs spent waiting in each queue, avg will be this div by processedByQueue 
	double turnaroundRatiosSummed;
	double machineHoursConsumed;
	//^ just add up nodes*runTime from each job
	double pricesPaid;
	//^ similar to machineHoursConsumed but taking into consideration user budgets spent, so GPU factor consideration
    std::vector <Job*> jobsRunning;
    std::array <Queue*,5> queues;
	Scheduler* scheduler; //have it here as a reference, will need to test this and see if its right
public:
    Machine();
	void addScheduler(Scheduler* schedulerArg);
	Scheduler* getScheduler();
	void addQueues(std::array<Queue*,5> queues);
    std::array<Queue*,5> getQueues();
    std::vector <Job*> getJobsRunning();
    std::array <int, 5> getRunning();
    int getRunningTotal();
    std::array <int, 5> getProcessedByQueue();
    std::array<double, 5> getWaitTimeByQueue();
    double getTurnaroundRatioSummed();
    double getMachineHoursConsumed();
    double getPricePaid();
    void checkJobsRunning(double currentTime);
    void getJobsFromScheduler(double currentTime);
    int getMachineStatus();
    void setMachineStatus(double currentTime);
	void collector(Job* job);
	void report(); //will return or print or send to file all the info gathered and processed in collector during the course of week
	void resetMetrics(); //resets @ beginning of new week, which starts 0900am mondays
};


