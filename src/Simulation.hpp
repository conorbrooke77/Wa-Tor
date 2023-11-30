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
    
    std::vector<SeaCreature*> seaCreatures;
    SimulationDisplay* displayGrid;


public:
    Simulation(int gridSize);
    Simulation(int NumShark, int NumFish, int FishBreed, int SharkBreed, int Starve, int gridSize, int Threads);

    ~Simulation();

    void addCreature(SeaCreature* creature);
    void createFish(int numFish);
    void createSharks(int numSharks);
    void update();
    void display();
    void displaySeaCreatures();

};
