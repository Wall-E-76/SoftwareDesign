/*! \file

\class Simulation

\brief Simulation class.

.........describe here......
*/

#pragma once
#include "Job.h"
#include "Generator.h"
#include <iostream>
#include <fstream>
#include <ctgmath>
#include "Researcher.h"
#include "Student.h"
#include "fifoScheduler.h"

/// \brief definition of time step per iteration of the Simulation, in hours.
#define TIMESTEP 0.5
/// \brief count of the hours in a week, end of simulation.
#define ENDTIME 24*7


class Simulation {
private:
	/// \brief total nodes on Machine being simulated.
    int totalNode;
	/// \brief holds the current time of the week in hours, since 0900am monday, of the Simulation.
    double currentTime;
	/// \counts the weeks passed in Simulation.
	int weekCounter;
	/// \brief number of weeks to be simulated.
	int weeksSimulated;
	/// \brief pointer to Generator object instantiated Simulation.
    Generator* generator;
	/// \brief Machine object instantiated in Simulation.
    Machine machine;
	/// \brief array of Queue pointers instantiated in Simulation.
	std::array<Queue*,5> queues;

public:
    explicit Simulation(int totalNode, int weeks);
	void run();
    void setup();
	void setupFile(std::string input);
    void computeTimeSteps();
    void output();
    std::array<Queue*,5> getQueues();
    void addScheduler(Scheduler* s);
    void addQueues(std::array<Queue*,5> queues);
    void addGenerator(Generator* g);
};

