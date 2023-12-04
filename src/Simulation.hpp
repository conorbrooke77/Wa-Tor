#include <vector>
#include "SeaCreature.hpp"
#include "SimulationDisplay.cpp"
#include "Fish.hpp"
#include "Shark.hpp"

class Simulation {
private:

    int totalShark;
    int totalFish;
    int fishBreedTime;
    int sharkStarve;
    int sharkBreedTime;

    int gridSize;
    
    vector<SeaCreature*> seaCreatures;
    vector<SeaCreature*> allCreaturesToDelete;
    SimulationDisplay* displayGrid;

    bool isGridInitialized;
    vector<vector<SeaCreature*>> creaturesInGrid;
    mt19937 randEngine;

    void addCreature(SeaCreature* creature);
    void createFish(int numFish, int reproduceAge);
    void createShark(int numFish, int reproduceAge);
    void update();
    void display(int fishPopulation, int sharkPopulation);
    bool isRunning();
    void deleteCreatures();


public:

    Simulation(int NumShark, int NumFish, int FishBreed, int SharkBreed, int Starve, int gridSize, int Threads);
    ~Simulation();

    void run();
};
