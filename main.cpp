#include "src/Simulation.h"
#include <iostream>

int main(){
    int totalNode;
	int weeks;
    std::cout << "How much nodes in this simulation?";
    std::cin >> totalNode;
	std::cout << "How many weeks is this simulation?";
	std::cin >> weeks;
    Simulation s (totalNode, weeks);
    s.setup();
    return 1;
}