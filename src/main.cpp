#pragma once
#include "Simulation.h"
#include <iostream>

int main() {
	int totalNode=128;
	int weeks;
	std::cout << "How many weeks is this simulation?";
	std::cin >> weeks;
	Simulation s(totalNode, weeks);
	s.run();
	return 0;

}