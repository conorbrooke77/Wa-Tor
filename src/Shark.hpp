#ifndef SHARK_HPP
#define SHARK_HPP

#include "SeaCreature.hpp"
using namespace std;

class Shark : public SeaCreature {
private:
    int energy = 100;  // Initial energy for the shark

public:
    Shark(int xPosition, int yPosition, int reproduceAge);

    void move(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) override;

    // Scans for nearby fish and free cells
    void findFish(std::vector<std::pair<int, int>>& neighbourhoodCells, 
                  std::vector<std::pair<int, int>>& cellsWithFish, 
                  int xPosition, int yPosition, 
                  std::vector<std::vector<SeaCreature*>>& creaturesInGrid);

    // Reproduction logic for sharks
    SeaCreature* reproduce(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) override;

    // Decreases the shark's energy
    void depleteEnergy() override;

    int getEnergy() override;
    void setEnergy(int energy);

    // Shark eats a fish at the given position
    void eatFish(int fishX, int fishY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid);

    // Checks if the shark has starved
    bool isStarved() override;

    ~Shark();
};
#endif
