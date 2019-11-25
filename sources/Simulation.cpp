
#include "Simulation.h"
#include <iostream>
#include <ctgmath>
#include <sources/users/Researcher.h>

Simulation::Simulation(int totalNode) :
        currentTime(0),
        totalNode(totalNode),
        machine(Machine(floor(totalNode*0.1), floor(totalNode*0.3), totalNode - floor(totalNode*0.1)- floor(totalNode*0.3), 8, totalNode))
{
}

void Simulation::setup() {
    Generator((*this).totalNode);
    std::vector <struct Group> groups;
    double paramGroup;
    std::string answer;
    do {
        std::cout << "Registering group " << groups.size() << ": "<< std::endl;
        struct Group group{};
        std::cout << "Budget: ";
        std::cin >> paramGroup;
        group.budget = paramGroup;
        std::cout << "Parameter for the exponential distribution: ";
        std::cin >> paramGroup;
        group.expoParameter = paramGroup;
        std::string arrayCategory = {"short","medium", "large", "GPU", "huge"};
        for (int i = 0; i<5;i++){
            std::cout<<"Is this group allowed to submit "<< arrayCategory[i]<<" jobs? [y/n]";
            std::cin >> answer;
            group.permission[i] = answer[0] == 'y' || answer[0] == 'Y';
        }

        std::cout << "Do you want to keep registering groups? [y/n]";
        std::cin >> paramGroup;
    } while (answer[0]=='y'|| answer[0]=='Y');
}

void Simulation::computeTimeSteps() {
    while ((*this).currentTime < ENDTIME){
        (*this).generator.lookForJobs((*this).currentTime);
        (*this).machine.setMachineStatus();
        (*this).machine.checkJobsRunning();
        (*this).machine.checkAvailability();
    }
}



