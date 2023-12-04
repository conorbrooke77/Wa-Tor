#ifndef FISH_HPP
#define FISH_HPP

#include "SeaCreature.hpp"

using namespace std;

class Fish : public SeaCreature {

private:
    bool beenEaten;  // Flag to indicate if the fish has been eaten by a shark

public:
   
    Fish(int xPosition, int yPosition, int reproduceAge);

    void move(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) override;

    // Adds a cell to the list of free cells if it's unoccupied
    void addIfFreeCell(std::vector<std::pair<int, int>>& neighbourhoodCells, 
                       int xPosition, int yPosition, 
                       std::vector<std::vector<SeaCreature*>>& creaturesInGrid);

    // Reproduction logic for fish
    SeaCreature* reproduce(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) override;

    // Checks if the fish has been eaten
    bool isEaten() override;

    // Marks the fish as eaten
    void getEaten() override;

    // Destructor
    ~Fish();
};

#endif