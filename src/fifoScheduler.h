/*! \file

\class FIFOScheduler

\brief Inherited from Scheduler Interface.

  Will look at the #queues, the available resources on the Machine, the currentTime, and will compile a list of Jobs
  to be sent to the Machine to be run at this time. e
  
  Uses an intelligent first in first out algorithm for job selection, meaning the jobs waiting the longest in the queue will be served first but
  it will make a special consideration if the first job in a queue can not be run before a cut off time but other jobs behind it possibly can. 
  \sa Scheduler
*/

#pragma once
#include "Scheduler.h"

class FIFOScheduler : public Scheduler{
public:
	/**\brief Constructor method.

	 Creates an instance of the scheduler object */
	FIFOScheduler();
	/** \brief Method that returns list of Jobs to be run next on machine.

		\param state current state of the Machine (states 1-5)
		\param running array of values that specify the number of nodes being used on Machine by each type of Job (i.e [0] for short, [3] for GPU).
		\param runningTotal total nodes currently occupied on Machine.
		\param currentTime value of current time of the week, in hours.
		\return vector of Job pointers that will sent to Machine to be run.

		Designed with an intelligent "First In, First Out" algorithm. 

		On weekday mode (state = 1-4), it first fills up the minimum reserved space for short, medium, and GPU accelerated jobs.
		Then by default will simply take the jobs that have been waiting the longest, one at a time, by comparing the wait times of the first Job in
		each Queue (only the short, medium, and large jobs, since GPU is different hardware and has specially reserved nodes).
 
		Depending on Machine::state however, which indicates that certain queues may not be able to run certain jobs before cut 
		off times (i.e. large jobs can reserve to 16 hours but the machine needs to have no jobs running by the weekend cutoff time of 0500pm Friday,
		so the reserved time of the jobs in the large queue need to be checked after 0100 am friday), the algorithm will instead check the specified 
		Queue for the next Job in the list that can run in the time left before cut off, if it exists, using method Queue::nextJobT. 
		It will then consider this job as first in its queue.
		Jobs that can't run before cut off will have to wait until the next week in any case, so this system prevents the freezing of a whole Queue
		by potentially considering shorter jobs in line that are behind it. 

		On weekend mode (state 5), the Scheduler only looks the the huge Queue and will use all 128 nodes of the Machine to run these Jobs. 
		Since these jobs can potentially take up to 64 hours (the whole weekend), the scheduler will consider the time of each job to see if it 
		can be run before the weekday cut off time and will once again possibly leave the front jobs in the Queue if they can't be run and will 
		instead try to run jobs behind them in line.  

		Once we find the Job with the oldest Job::timeEnteredQueue value that can be run in time before a cuttoff peroid, the Scheduler will then see if 
		the resources are available to run the job. This means that we can't run jobs that will cause us to go over the totalNodes, we can't run jobs
		that will infrgine on reserved portions of the machine, we can't run large jobs that will cause more than 50% of nodes to be used by large jobs. 
		If there are no such issues, it is added to the vector of jobs that will be returned by this method. Otherwise job stays in its Queue.
		
		The vector of Job pointers is repeatedly added to until no more jobs can currently be run, due either to time or node constraints. Each time
		a Job is added it increases Machine::runningTotal and Machine::running at the appropriate index by the amount stored in Job::nodes. 
		Then the method returns the vector. 
	*/
	std::vector<Job*> getJobs(int state, std::array <int, 5>& running, int& runningTotal, double currentTime, double systemTime);

private:

	/** \brief Private method used by ::getJobs() to fill reserved portions of machine.

		 \param running the number of nodes running on the Machine serving Jobs that came from this Queue, passed by reference because 
			it is increased when a Job is chosen to be run from this Queue
		\param runningTotal total nodes being used currently on Machine, passed by reference because it is increased when a Job is 
			chosen to be run.
		\param queue pointer to a specific queue, passed by reference because it will be modified when a Job is chosen to be run from it
		\param state machine state (ranging from 1-5).
		\param stateCheck machine state that will affect this queue's selection of jobs.
		\param cutoffTime value of the time at which all jobs from this queue need to be done running on machine.
		\param currentTime value of current time of the week, in hours.
		\param limitNodes maximum nodes reserved for this job type.
		\return vector of Job pointers to be sent to Machine to run.

		This function is used internally by ::getJobs() and takes care of filling the reserved portion of the machine at the beginning of each turn.
		Will ensure that the first jobs from the queue get as close to meeting but not exceeding the limitNodes value.
		Will also intelligently check the first job's reserved time in the case that state equals or exeeds stateCheck value, and might look instead
		for the first job in the queue that has a reserved time short enough to be run before cutoffTime.
   */
	std::vector<Job*> fillReserved(int& running, int& runningTotal, Queue*& queue, int state, int stateCheck,
		double cutoffTime, double currentTime, int limitNodes, double systemTime);

	/** \brief Private method used by getJobs() to find the oldest job that can be run from a certain queue, returns that job's pointer.

	 \param oldest passed by reference which will be set to the "queue" index of the oldest runnable job in this queue has been 
		in the queue longer than the "oldestTime" given.
	 \param oldestTime passed by reference which will be set to the time this queue's oldest runnable job entered the queue if it is
		less than the oldestTime passed in the method call.
	 \param n the index of the oldest runnable job in the specified queue.
	 \param state machine state (ranging from 1-5).
	 \param stateCheck machine state that will affect this queue's selection of jobs.
	 \param cutoffTime value of the time at which all jobs from this queue need to be done running on machine.
	 \param queue index in vector of queues of queue we are looking at
	 \param currentTime value of current time of the week, in hours.
	 \return pointer to oldest Job currently able to run from this Queue.
	FIFOScheduler();
	std::vector<Job*> getJobs(int status, std::array <int, 5>& running, int& runningTotal, double currentTime) override;
	std::vector<Job*> fillReserved(int& running, int& runningTotal, Queue*& queue, int status, int statusCheck,
		int cutoffTime, double currentTime, int limitNodes);
	 
*/
	Job* oldestCheck(int& oldest, double& oldestTime, int& n, int state,int stateCheck, 
		double cutoffTime, int queue, double currentTime);

};

