/*! \file

\class Queue

\brief Queue class.

 A Queue contains a certain category of job as they wait to be processed. New elements will be pushed back, and elements will usually be taken out of this Queue starting from
 its head, although any element can be accessed at any time.
*/

#pragma once
#include "Job.h"
#include <vector>

/// \brief Machine nodes reserved for jobs in short Queue.
#define shortMin 14
/// \brief Machine nodes reserved for jobs in medium Queue.
#define medMin 40
/// \brief maximum Machine nodes that jobs from large Queue can occupy.
#define largeMax 64
/// \brief GPU equipped Machine nodes reserved for jobs in GPU Queue.
#define gpuNodes 10
/// \brief total nodes in Machine.
#define totalNodes 128

class Queue {
private:
	/// \brief vector of pointers to Jobs waiting in this Queue.
    std::vector <Job*> jobsInQueue;
public:
    Queue();
	/// \brief inserts Job to end of jobsInQueue.
    void insertJob(Job* job);
	/// \brief returns pointer to first Job in jobsInQueue.
    Job* nextJob();
	/// \brief returns the index of the first Job in jobsInQueue whose Job::reservedTime is less than or equal to specified 'time'.
	int nextJobT(double time);
	/// \brief removes the Job at specified position 'n' in jobsInQueue. Sets Job::timeLeftQueue to specified 'currentTime'.
    void removeJob(int n, double currentTime);
	/// \brief returns pointer to Job at specified position 'n'.
	Job* getJobAt(int n);
	/// \brief returns jobsInQueue vector of Job pointers.
    std::vector <Job*> getJobsInQueue();
};

