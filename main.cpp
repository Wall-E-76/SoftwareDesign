#include "src/Simulation.h"
#include <iostream>

int main(int argc, char *argv[]) {
    int totalNode=128;
    int weeks;
    std::cout << "How many weeks is this simulation?";
    std::cin >> weeks;
    Simulation s(totalNode, weeks);
    if (argc > 1){
        s.run(argv[1]);
    }
    else
    {
        s.run("./src/inputSA.txt");
    }
    return 0;
}