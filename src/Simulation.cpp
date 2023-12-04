#include "Simulation.hpp"
#include <time.h>
#include <thread> // Include this for std::this_thread
#include <chrono>
#include <omp.h>

Simulation::Simulation(int NumShark, int NumFish, int FishBreed, int SharkBreed, int Starve, int gridSize, int Threads) {
    omp_set_num_threads(Threads);
    std::srand(time(nullptr)); // Seed the random number generator once
    this->gridSize = gridSize;

    createFish(NumFish, FishBreed);
    createShark(NumShark, SharkBreed);

    displayGrid = new SimulationDisplay(gridSize);
    displayGrid->initializeRenderWindow();

    isGridInitialized = false;
}

// Add a creature to the simulation
void Simulation::addCreature(SeaCreature* creature) {
    seaCreatures.push_back(creature);
}

void Simulation::createFish(int numFish, int reproduceAge) {

    for (int i = 0; i < numFish; ++i) {
        int xPosition = rand() % gridSize;
        int yPosition = rand() % gridSize; 

        Fish* fish = new Fish(xPosition, yPosition, reproduceAge);
        addCreature(fish);
    }
}

void Simulation::createShark(int numSharks, int reproduceAge) {

    for (int i = 0; i < numSharks; ++i) {
        int xPosition = rand() % gridSize;
        int yPosition = rand() % gridSize;

        Shark* shark = new Shark(xPosition, yPosition, reproduceAge);
        addCreature(shark);
    }
}

void Simulation::update() {

    // Check if the grid has been initialized, if not, initialize it
    if (!isGridInitialized) {
        creaturesInGrid = vector<vector<SeaCreature*>>(gridSize, vector<SeaCreature*>(gridSize, nullptr));
        isGridInitialized = true;

        // Initialize the grid with current creature positions
        #pragma omp parallel for
        for (SeaCreature* creature : seaCreatures) {
            int x = creature->getXPosition();
            int y = creature->getYPosition();
            creaturesInGrid[x][y] = creature;
        }
    }
    // Update Simulation
    #pragma omp parallel
    {
        std::vector<SeaCreature*> potentialNewCreatures;
        std::vector<SeaCreature*> creaturesToDelete;

        #pragma omp for nowait
        for (SeaCreature* creature : seaCreatures) {

            if (creature->getType() == "SHARK") {
                creature->depleteEnergy();
                if (creature->isStarved())
                    creaturesToDelete.push_back(creature);
            } else {
                if (creature->isEaten()) {
                    creaturesToDelete.push_back(creature);
                }
            }

            creature->updateAge();
            creature->move(creaturesInGrid); // Assuming square grid
            
            if (creature->getType() == "FISH") {
                if (creature->isEaten()) {
                    creaturesToDelete.push_back(creature);
                }
            }

            SeaCreature* newCreature = creature->reproduce(creaturesInGrid);
            if (newCreature != nullptr) {
                potentialNewCreatures.push_back(newCreature);
            }
        }
        #pragma omp critical
        {
            seaCreatures.insert(seaCreatures.end(), potentialNewCreatures.begin(), potentialNewCreatures.end());
            allCreaturesToDelete.insert(allCreaturesToDelete.end(), creaturesToDelete.begin(), creaturesToDelete.end());

        }
    }

    displayGrid->updateGrid(creaturesInGrid);

}

void Simulation::deleteCreatures() {
    // Remove dead sea creatures from the vector and delete them
    for (SeaCreature* creature : allCreaturesToDelete) {
        auto it = std::find(seaCreatures.begin(), seaCreatures.end(), creature);
        if (it != seaCreatures.end()) {
            int x = (*it)->getXPosition();
            int y = (*it)->getYPosition();
            
            delete *it;  // Free the memory
            creaturesInGrid[x][y] = nullptr;  // Set the grid cell to nullptr after deletion
            it = seaCreatures.erase(it);  // Remove the pointer from the vector
        }
    }

    // Remove all nullptrs from the vector
    seaCreatures.erase(std::remove(seaCreatures.begin(), seaCreatures.end(), nullptr), seaCreatures.end());
    allCreaturesToDelete.clear();
}

void Simulation::display(int fishPopulation, int sharkPopulation) {
    displayGrid->renderWindow(creaturesInGrid, fishPopulation, sharkPopulation);
}

bool Simulation::isRunning() {
    return displayGrid->isWindowOpen();
}

void Simulation::run() {
    int count = 0;
    double totalElapsed = 0; // Changed to double for precision
    while (count < 500) { 
        count++;
        auto start = std::chrono::high_resolution_clock::now();
        update();
        display(SeaCreature::getFishCount(), SeaCreature::getSharkCount());
        deleteCreatures();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        totalElapsed += elapsed.count();
        std::cout << "Simulation took " << elapsed.count() << " milliseconds.\n";
        // Delay for a specified duration, e.g., 100 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

        if (count > 0) { // To avoid division by zero
        std::cout << "Average Runtime: " << (totalElapsed / count) << " milliseconds\n";
    } else {
        std::cout << "No iterations were run.\n";
    }
}

// Destructor
Simulation::~Simulation() {
    for (SeaCreature* creature : seaCreatures) {
        delete creature;
    }
}
