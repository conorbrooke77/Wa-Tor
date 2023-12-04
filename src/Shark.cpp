#include "Shark.hpp"
#include <iostream>

Shark::Shark(int xPosition, int yPosition, int reproduceAge) 
    : SeaCreature(xPosition, yPosition, reproduceAge) {
        type = "SHARK";
        SeaCreature::sharkCount++;
}

void Shark::move(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    // Store coordinates (x, y) of adjacent free cells and cells with fish
    std::vector<std::pair<int, int>> neighbourhoodCells, cellsWithFish;
    
    // Check adjacent cells for free space and fish presence
    findFish(neighbourhoodCells, cellsWithFish, xPosition, yPosition - 1, creaturesInGrid); // North
    findFish(neighbourhoodCells, cellsWithFish, xPosition, yPosition + 1, creaturesInGrid); // South
    findFish(neighbourhoodCells, cellsWithFish, xPosition + 1, yPosition, creaturesInGrid); // East
    findFish(neighbourhoodCells, cellsWithFish, xPosition - 1, yPosition, creaturesInGrid); // West

    if (!cellsWithFish.empty()) {
        std::uniform_int_distribution<int> dist(0, cellsWithFish.size() - 1);
        int choice = dist(randEngine);

        eatFish(cellsWithFish[choice].first, cellsWithFish[choice].second, creaturesInGrid);
        moveTo(cellsWithFish[choice].first, cellsWithFish[choice].second, creaturesInGrid);
    } else if (!neighbourhoodCells.empty()) {
        std::uniform_int_distribution<int> dist(0, neighbourhoodCells.size() - 1);
        int choice = dist(randEngine);

        moveTo(neighbourhoodCells[choice].first, neighbourhoodCells[choice].second, creaturesInGrid);
    }
}

void Shark::eatFish(int fishX, int fishY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    if (creaturesInGrid[fishX][fishY] != nullptr) {
        creaturesInGrid[fishX][fishY]->getEaten();
        energy += 10;
    }
}

void Shark::findFish(std::vector<std::pair<int, int>>& neighbourhoodCells, std::vector<std::pair<int, int>>& cellsWithFish, int xPosition, int yPosition, std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    // Wrap around the grid
    xPosition = wrapAround(xPosition, creaturesInGrid.size());
    yPosition = wrapAround(yPosition, creaturesInGrid[0].size());

    SeaCreature* creature = creaturesInGrid[xPosition][yPosition];

    if (creature == nullptr) {
        neighbourhoodCells.push_back({xPosition, yPosition});
    } else if (creature->getType() == "FISH") {
        cellsWithFish.push_back({xPosition, yPosition});
    }
}

SeaCreature* Shark::reproduce(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    if (getAge() == getReproduceAge() && updateState()) {
        SeaCreature* newShark = nullptr;
            #pragma omp critical
            {
                // Check if the position is already occupied by another creature
                SeaCreature*& oldShark = creaturesInGrid[oldXPosition][oldYPosition];
                if (oldShark != nullptr) {
                    delete oldShark;  // Delete the existing creature
                }

                // Create a new Shark and place it in the grid
                newShark = new Shark(oldXPosition, oldYPosition, 0);
                oldShark = newShark;

                // Reset the original fish's position or mark it as reproduced
                oldXPosition = -1;
                oldYPosition = -1;
            }

            resetAge();
            return newShark;
        }
    return nullptr;
}

void Shark::depleteEnergy() {
    energy -= 1;
}

int Shark::getEnergy() {
    return energy;
}

void Shark::setEnergy(int energy) {
    this->energy = energy;
}

bool Shark::isStarved() {
    return energy == 0;
}

Shark::~Shark() {
    SeaCreature::sharkCount--;  // Decrement shark count
}