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
    Scheduler* fifo = new FIFOScheduler();
    fifo->addQueues(s.getQueues());
    s.addScheduler(fifo);
    s.run();
    return 0;
}