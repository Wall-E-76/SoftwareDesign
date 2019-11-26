#pragma once
#include <vector>
#include <array>
#include "Job.h"
#include "Queue.h"
#define MACHINE_COST 5
#define MACHINE_COST_GPU 6
#define STATE1 ?? //start time for state 1, so 0900 am monday
#define STATE2 ?? //start time for state 2, so 0100 am friday 
#define STATE3 ?? //start time for state 3, so 0900 am friday //GPU JOBS AND MEDIUM JOBS... SO GPU WILL HAVE MAX 8 HOURS
#define STATE4 ?? //start time for state 4, so 0300 pm friday
#define STATE5 ?? //start time for state 5, so 0500 pm friday
//^^ dont know how to represent these time values yet...
// I imagine that the time will reset every week...and we will count the time incrementally from 1200am monday to 1159pm sunday?


class Machine {
private:

	std::array <int, 5> running;
	//int& runningShort= running[0];
	//int& runningMed = running[1];
	//int& runnningLarge = running[2];
	//int& runningGPU = running[3];
	//int& runningHuge = running[4];  //way to use these ref variables..? if not, not that important, can do without
	int runningTotal;
	int status;
    std::vector <Job*> jobsRunning;
    std::vector <Queue*> queues;
	Scheduler& scheduler; //have it here as a reference, will need to test this and see if its right
public:
	Machine(std::vector<Queue*> queues, Scheduler& schedulerArg);
    void checkJobsRunning(double currentTime);
    void getJobsFromScheduler(double currentTime);
    void setMachineStatus(double currentTime);
	void collector(Job* job);
};


