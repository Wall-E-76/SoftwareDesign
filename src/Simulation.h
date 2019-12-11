/*! \file

\class Simulation

\brief Simulation class.

The main driver of the whole Simulation. Creates the instances of the Machine, Scheduler, Queues, and sets up the Users of the Simulation from the details of an input file. 
Manages the time steps and cycles all the actions, keeping track of the time and the weeks passed. 
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
	/// \brief called after the setUpFile(), this is the method that runs the simulation for the entire duration of weeks specified.
	void run();
	/// \brief takes care of the setup of all the objects in the Simulation, and reads the input file to create the Users for this scenario.
	void setupFile(std::string input);
	/// \brief called by run(), this method engages all the actions in the Simulation for a single cycle, incrementing the time step until the week is done.
    void computeTimeSteps();
	/// \brief getter used in Unit testing - returns the array of Queue pointers of the Simulation.
    std::array<Queue*,5> getQueues();
	/// \brief after the Simulator instantiates a Scheduler object, this method will add pass its pointer to the Machine object.
    void addScheduler(Scheduler* s);
	/// \brief getter used in Unit testing - returns the Scheduler used in this Simulation.
    Scheduler* getScheduler();
	/// \brief adds the array of Queue pointers to itself.
    void addQueues(std::array<Queue*,5> queues);
	/// \brief adds the pointer to the Generator to itself.
    void addGenerator(Generator* g);
	/// \brief getter used in Unit testing - returns the pointer to Simulation's Generator.
    Generator* getGenerator();
	/// \brief getter used in Unit testing - returns the Simulation's Machine object.
    Machine* getMachine();
    void setWeekCounter(int week);
};

