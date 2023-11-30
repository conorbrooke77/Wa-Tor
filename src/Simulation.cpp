#include "Simulation.hpp"
#include <time.h>

Simulation::Simulation(int gridSize) {

    this->gridSize = gridSize;
}

Simulation::Simulation(int NumShark, int NumFish, int FishBreed, int SharkBreed, int Starve, int gridSize, int Threads) {
    
    this->gridSize = gridSize;
    createFish(NumFish);
    createSharks(NumShark);

    cout << seaCreatures.size() << endl;
    displayGrid = new SimulationDisplay(20, 20, gridSize);
}

// Add a creature to the simulation
void Simulation::addCreature(SeaCreature* creature) {
    seaCreatures.push_back(creature);
}

void Simulation::createFish(int numFish) {
    std::srand(time(nullptr)); // Seed the random number generator
    for (int i = 0; i < numFish; ++i) {
        int xPosition = rand() % gridSize; // Random position within grid size
        int yPosition = xPosition+4;
        int age = rand() % 5; // Random age, for example between 0 and 9

        Fish* fish = new Fish(xPosition, yPosition, age);
        addCreature(fish);
    }
}

void Simulation::createSharks(int numSharks) {
    std::srand(time(nullptr)); // Re-seeding is generally not necessary
    for (int i = 0; i < numSharks; ++i) {
        int xPosition = std::rand() % gridSize;
        int yPosition = xPosition+4;
        int age = std::rand() % 20;

        Shark* shark = new Shark(xPosition, yPosition, age);
        addCreature(shark);
    }
}

void Simulation::update() {
    displayGrid->updateGrid(seaCreatures);
    cout << displayGrid->getWindowHeight() << endl << displayGrid->getWindowWidth();
}

void Simulation::display() {
    displayGrid->renderWindow();
}

void Simulation::displaySeaCreatures() {

    cout << "Displaying Sea Creatures" << endl;
    for (SeaCreature *creature : seaCreatures) {
        int x = creature->getXPosition();
        int y = creature->getYPosition();

        cout << creature->getType() << endl;
        cout << "X Position" << x << endl;
        cout << "Y Position" << y << endl;
    }
}

// Destructor
Simulation::~Simulation() {
    for (SeaCreature* creature : seaCreatures) {
        delete creature;
    }
}