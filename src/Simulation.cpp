
#include "Simulation.h"


Simulation::Simulation(int totalNode, int weeks) :
        currentTime(0),
        totalNode(totalNode),
        machine(Machine()),
		weekCounter(0),
		weeksSimulated(weeks)
{}

void Simulation::setupFile(std::string input) {
	std::cout << "Beginning of setup" << std::endl;
	std::array<Queue*, 5> queues{};
	for (int i = 0; i < 5; i++) {
		auto* q = new Queue();
		queues[i] = q;
	}
	(*this).addQueues(queues);
	auto* g = new Generator((*this).totalNode);
	(*this).addGenerator(g);
	g->addQueues(queues);
	machine.addQueues(queues);
	Scheduler* s = new FIFOScheduler();
	s->addQueues(queues);
	(*this).addScheduler(s);

	std::ifstream in(input);
	std::vector <struct Group> groups;
	std::string line;
	std::string space = " ";
	//add groups
	while (true) {
		std::getline(in, line); //first line of element/section
		if (line == "--")  break; //break if empty section
		double paramGroup;
		struct Group group {};
		std::getline(in, line); //budget line
		paramGroup = std::stod(line.substr(line.find(space) + 1, line.size() - 1));
		group.budget = paramGroup;

		std::getline(in, line); //expDistParam line
		paramGroup = std::stod(line.substr(line.find(space) + 1, line.size() - 1));
		group.expoParameter = paramGroup;

		std::getline(in, line); //permissions line
		std::string temp = line.substr(line.find(space) + 1, line.size() - 1);
		for (int i = 0; i < 5; i++) {
			char num = temp[i * 2];
			group.permission[i] = num == '1';
		}
		groups.push_back(group);
		std::getline(in, line); // '+' or '--' line
		if (line == "--") break;
	}
	std::vector <struct Curriculum> curriculums;
	//add curriculums
	while (true) {
		std::getline(in, line); //first line of element/section
		if (line == "--") break; //break if section is empty
		double paramCurriculum;
		struct Curriculum curriculum {};
		std::getline(in, line); //budget line
		paramCurriculum = std::stod(line.substr(line.find(space) + 1, line.size() - 1));
		curriculum.budget = paramCurriculum;

		std::getline(in, line); //expDistParam line
		paramCurriculum = std::stod(line.substr(line.find(space) + 1, line.size() - 1));
		curriculum.expoParameter = paramCurriculum;

		std::getline(in, line); //instCap line
		paramCurriculum = std::stod(line.substr(line.find(space) + 1, line.size() - 1));
		curriculum.instResourceCap = paramCurriculum;

		std::getline(in, line); //permissions line
		std::string temp = line.substr(line.find(space) + 1, line.size() - 1);
		for (int i = 0; i < 5; i++) {
			char num = temp[i * 2];
			curriculum.permission[i] = num == '1';
		}
		curriculums.push_back(curriculum);
		std::getline(in, line); // '+' or '--' line
		if (line == "--") break;
	}
	//create researchers by group
	int groupNumber = 0;
	while (true) {
		std::getline(in, line); //number of researchers
		if (groups.empty()) break; //no researchers
		int groupSize; //number of people in group
		int grantMembers; //number of people with grant in group
		groupSize = std::stoi(line.substr(line.find(space) + 1, line.size() - 1));
		std::getline(in, line); //number of researchers with grant
		grantMembers = std::stoi(line.substr(line.find(space) + 1, line.size() - 1));
		std::getline(in, line); //grant values
		std::string temp = line.substr(line.find(space) + 1, line.size() - 1);
		std::string delim = ",";
		size_t pos;
		//add reserachers with specified grants
		for (int i = 0; i < grantMembers; i++) {
			pos = temp.find(delim);
			Researcher* r = new Researcher(groups[groupNumber], std::stoi(temp.substr(0, pos)));
			(*this).generator->addUser(r);
			temp.erase(0, pos + delim.length());
		}
		//add regular researchers
		for (int i = 0; i < groupSize - grantMembers; i++) {
			Researcher* r = new Researcher(groups[groupNumber], 0);
			(*this).generator->addUser(r);
		}

		std::getline(in, line); //'+' or '--' line
		if (line == "--") break;
		groupNumber++;
	}

	//create students by curriculum
	int curriNumber = 0;
	while (true) {
		std::getline(in, line); //number of students
		if (curriculums.empty()) break; //no students
		int groupSize;
		groupSize = std::stoi(line.substr(line.find(space) + 1, line.size() - 1));
		for (int i = 0; i < groupSize; i++) {
			Student* s = new Student(curriculums[curriNumber]);
			(*this).generator->addUser(s);
		}
		std::getline(in, line); //'+' or '--' line
		if (line == "--") break;
		curriNumber++;
	}
}

void Simulation::computeTimeSteps() {
	while (currentTime < double(ENDTIME)) {
		machine.setMachineState(currentTime);
        generator->lookForJobs(currentTime+ (double(ENDTIME)*weekCounter));
		machine.checkJobsRunning(currentTime+ (double(ENDTIME) * weekCounter));
		machine.getJobsFromScheduler(currentTime, currentTime + (double(ENDTIME)*weekCounter));
		currentTime += TIMESTEP;
    }
    currentTime = 0;
}


void Simulation::run() {

    (*this).setupFile("../src/inputSA.txt"); // Or change to inputSA.txt
	while (weekCounter < weeksSimulated) {
		(*this).computeTimeSteps();
        (*this).machine.report();
        (*this).machine.resetMetrics();
		weekCounter++;
	}

}

std::array<Queue *, 5> Simulation::getQueues() {
    return (*this).queues;
}

void Simulation::addScheduler(Scheduler* s) {
    (*this).machine.addScheduler(s);
}

void Simulation::addQueues(std::array<Queue *, 5> queues) {
    (*this).queues = queues;
}
void Simulation::addGenerator(Generator* g){
    (*this).generator = g;
}

Scheduler* Simulation::getScheduler() {
    return (*this).machine.getScheduler();
}

Generator *Simulation::getGenerator() {
    return (*this).generator;
}

Machine Simulation::getMachine() {
    return (*this).machine;
}



