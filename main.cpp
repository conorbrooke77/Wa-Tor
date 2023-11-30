
#include "src/Simulation.hpp"
#include <iostream>

using namespace std;

int main() {

    Simulation simulation(10, 5, 0, 0, 0, 800, 1);

    simulation.displaySeaCreatures();

    simulation.display();
    
    return 0; // Indicate successful completion
}