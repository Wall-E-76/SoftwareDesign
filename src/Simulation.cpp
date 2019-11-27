
#include "Simulation.h"


Simulation::Simulation(int totalNode) :
        currentTime(0),
        totalNode(totalNode),
        machine(Machine()),
		weeks(0)
{

	Queue* Short = new Queue();
	Queue* Medium = new Queue();
	Queue* Large = new Queue();
	Queue* GPU = new Queue();
	Queue* Huge = new Queue();

	queues[0] = Short; queues[1] = Medium; queues[2] = Large; queues[3] = GPU; queues[4] = Huge;

}

void Simulation::setup() {
    std::cout << "Beginning of setup"<< std::endl;
    Generator g = Generator((*this).totalNode);
	g.addQueues(queues);
	machine.addQueues(queues);
	Simulation* fifo = new FIFOSchdeuler
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
        Researcher r = Researcher(groups[groupNumber], grant);
        (*this).generator.addUser(&r);
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
        Student s = Student(curriculums[curriNumber]);
        (*this).generator.addUser(&s);
        std::cout << "Student registered. Do you want to register another? [y/n]";
        std::cin >> answer;
    } while (answer[0]=='y'|| answer[0]=='Y');
}

void Simulation::computeTimeSteps() {
    while (currentTime < double(ENDTIME)){
        generator.lookForJobs(currentTime);



		currentTime += TIMESTEP;
    }
}



