
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
	Scheduler* fifo = new FIFOScheduler();
	fifo->addQueues(queues);
	(*this).addScheduler(fifo);

	std::ifstream in(input);
	std::vector <struct Group> groups;
	std::string line;
	std::string space = " ";
	//add groups
	while (true) {
		double paramGroup;
		struct Group group {};
		std::getline(in, line); //group # line
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
		double paramCurriculum;
		struct Curriculum curriculum {};
		std::getline(in, line); //curriculum # line
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
		int groupSize; //number of people in group
		int grantMembers; //number of people with grant in group
		std::getline(in, line); //number of researchers
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
		int groupSize;
		std::getline(in, line); //number of students
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

void Simulation::setup() {
    std::cout << "Beginning of setup"<< std::endl;
    std::array<Queue*,5> queues{};
    for (int i =0; i<5;i++){
        auto* q = new Queue();
        queues[i] = q;
    }
    (*this).addQueues(queues);
    auto* g = new Generator((*this).totalNode);
    (*this).addGenerator(g);
    g->addQueues(queues);
	machine.addQueues(queues);
    Scheduler* fifo = new FIFOScheduler();
    fifo->addQueues(queues);
    (*this).addScheduler(fifo);

	std::vector <struct Group> groups;
    std::string answer;
    std::array <std::string,5> arrayCategory = {"short","medium", "large", "GPU", "huge"};
    do {
        double paramGroup;
        std::cout << "Registering group " << groups.size() << ": "<< std::endl;
        struct Group group{};
        std::cout << "Budget: ";
        std::cin >> paramGroup;
        group.budget = paramGroup;
        std::cout << "Parameter for the exponential distribution: ";
        std::cin >> paramGroup;
        group.expoParameter = paramGroup;
        std::string yesOrNo;
        for (int i = 0; i<5;i++){
            std::cout<<"Is this group allowed to submit "<< arrayCategory[i]<<" jobs? [y/n]";
            std::cin >> yesOrNo;
            group.permission[i] = yesOrNo[0] == 'y' || yesOrNo[0] == 'Y';
        }
        groups.push_back(group);
        std::cout << "Do you want to keep registering groups? [y/n]";
        std::cin >> answer;
    } while (answer[0]=='y'|| answer[0]=='Y');
    std::vector <struct Curriculum> curriculums;

    do {
        double paramCurriculum;
        std::cout << "Registering curriculum " << curriculums.size() << ": "<< std::endl;
        struct Curriculum curriculum{};
        std::cout << "Budget: ";
        std::cin >> paramCurriculum;
        curriculum.budget = paramCurriculum;
        std::cout << "Parameter for the exponential distribution: ";
        std::cin >> paramCurriculum;
        curriculum.expoParameter = paramCurriculum;
        std::cout << "Instantaneous cap: ";
        std::cin >> paramCurriculum;
        curriculum.instResourceCap = paramCurriculum;
        std::string yesOrNo;
        for (int i = 0; i<5;i++){
            std::cout<<"Is this curriculum allowed to submit "<< arrayCategory[i]<<" jobs? [y/n]";
            std::cin >> yesOrNo;
            curriculum.permission[i] = yesOrNo[0] == 'y' || yesOrNo[0] == 'Y';
        }
        curriculums.push_back(curriculum);
        std::cout << "Do you want to keep registering curriculums? [y/n]";
        std::cin >> answer;
    } while (answer[0]=='y'|| answer[0]=='Y');
    std::cout << "Let's register researchers" << std::endl;
    do {
        int groupNumber;
        do{
            std::cout <<"Of which group is this researcher part of? (0-"<<groups.size()-1<<")";
            std::cin >> groupNumber;
        } while (groupNumber>=groups.size() || groupNumber<0);
        double grant;
        std::cout <<"How much personal grant does this reasearcher have?";
        std::cin >> grant;
        Researcher* r = new Researcher(groups[groupNumber], grant);
        (*this).generator->addUser(r);
        std::cout << "Researcher registered. Do you want to register another? [y/n]";
        std::cin >> answer;
    } while (answer[0]=='y'|| answer[0]=='Y');
    std::cout << "Let's register students" << std::endl;
    do {
        int curriNumber;
        do{
            std::cout <<"Of which curriculum is this student a part of? (0-"<<curriculums.size()-1<<")";
            std::cin >> curriNumber;
        } while (curriNumber>=curriculums.size() || curriNumber<0);
        Student* s = new Student(curriculums[curriNumber]);
        (*this).generator->addUser(s);
        std::cout << "Student registered. Do you want to register another? [y/n]";
        std::cin >> answer;
    } while (answer[0]=='y'|| answer[0]=='Y');
}

void Simulation::computeTimeSteps() {
   // while (currentTime < double(ENDTIME)*(weekCounter+1)){
	while (currentTime < double(ENDTIME)) {  //changed  -Callum
        //machine.setMachineState(currentTime-floor(currentTime/ENDTIME)*(ENDTIME-1));
		machine.setMachineState(currentTime); //changed - Callum
        generator->lookForJobs(currentTime);
		machine.checkJobsRunning(currentTime);
		//machine.getJobsFromScheduler(currentTime-floor(currentTime/ENDTIME)*(ENDTIME-1));
		machine.getJobsFromScheduler(currentTime); //changed - Callum
		//I think that's all?
		currentTime += TIMESTEP;
    }
    currentTime = 0; //changed - Callum
}

void Simulation::output() {
	(*this).machine.report();
}

void Simulation::run() {

	char ans;
	std::cout << "File setup or manual setup? y=file, n=manual.";
	std::cin >> ans;
	if (ans == 'y') (*this).setupFile("inputSA.txt");
	else (*this).setup();
	while (weekCounter < weeksSimulated) {
		(*this).computeTimeSteps();
		(*this).output();
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



