#include "src/Simulation.h"
#include <iostream>

int main(){
    int totalNode;
    std::cout << "How much nodes in this simulation?";
    std::cin >> totalNode;
    Simulation s = Simulation(totalNode);
    s.setup();
    return 1;
}