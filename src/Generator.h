/*! \file

\class Generator

\brief Generator class

Generates the Users and therefor the Job submissions in the Simulation.
*/

#pragma once

#include "User.h"
#include "Job.h"
#include <vector>
#include "Machine.h"
#include "Queue.h"
#include <iostream>

/// \brief the increment of time in hours of each loop in the Simulation.
#define TIMESTEP 0.5
/// \brief defines the length of the week, equivalent to 168 hours.
#define ENDTIME 24*7
/// \brief maximum nodes a Job submitted to the short Queue can reserve.
#define SHORTMAXNODES 2
/// \brief maximum nodes a Job submitted to the medium Queue can reserve.
#define MEDIUMMAXNODES 12
/// \brief maximum nodes a Job submitted to the large Queue can reserve.
#define LARGEMAXNODES 64
/// \brief maximum nodes a Job submitted to the gpu Queue can reserve.
#define GPUMAXNODES 10
/// \brief maximum nodes a Job submitted to the huge Queue can reserve.
#define HUGEMAXNODES 128

struct PropertyQueue {
	int nodeMax;
	int nodeMinExclusive;
	int timeMax;
};

class Generator {
private:
	/// \brief vector of pointers to User objects in the Simulation.
	std::vector <User*> users;
	/// \brief ???
	std::array<PropertyQueue, 5> property;
	/// \brief array of pointers to Queue objects used in Simulation.
	std::array<Queue*, 5> queues;

public:
	Generator();
	explicit Generator(int totlNodes);
	/// \brief returns users attribute.
	std::vector <User*> getUsers();
	/// \brief returns property attribute.
	std::array<PropertyQueue, 5> getProperty();
	/// \brief returns queues attribute.
	std::array<Queue*, 5> getQueues();
	/// \brief sets the queues attribute for the object.
	void addQueues(std::array<Queue*, 5> queue);
	/// \brief adds user passed in method to users vector attribute.
	void addUser(User* user);
	/// \brief choses a random category of Job for User at position "i" in users vector, based on permissions.
	int randomCategory(int i);
	/// \brief creates a random Job linked to User at position "i" in users vector.
	Job* createJob(int i);
	/// \brief checks that a User that owns "job" can afford to run it. If so, it sends it over to the appropriate Queue.
	void check(Job* job, double systemTime);
	/// \brief iterates through users vector to see if any User has a nextJobTime equal or less to systemTime.
	void lookForJobs(double systemTime);
	/// \brief function used to round up a random time to the nearest timeStep for Simulation purposes.
	double roundUp(double time);
};


