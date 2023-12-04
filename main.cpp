
#include "src/Simulation.hpp"
#include <iostream>
#include <omp.h>

using namespace std;

int main() {

    Simulation simulation(1200, 2600, 10, 20, 100, 900, 1);

    simulation.run();
    
    return 0;
}