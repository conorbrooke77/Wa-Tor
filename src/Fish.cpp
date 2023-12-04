#include "Fish.hpp"

Fish::Fish(int xPosition, int yPosition, int reproduceAge) 
    : SeaCreature(xPosition, yPosition, reproduceAge) {
        type = "FISH";
        beenEaten = false;
        SeaCreature::fishCount++;
}

void Fish::move(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    //Store coordinates (x, y) of adjacent free cells
    std::vector<std::pair<int, int>> neighbourhoodCells;

    // Check adjacent cells for free space (North, South, East, West)
    addIfFreeCell(neighbourhoodCells, xPosition, yPosition - 1, creaturesInGrid); // North
    addIfFreeCell(neighbourhoodCells, xPosition, yPosition + 1, creaturesInGrid); // South
    addIfFreeCell(neighbourhoodCells, xPosition + 1, yPosition, creaturesInGrid); // East
    addIfFreeCell(neighbourhoodCells, xPosition - 1, yPosition, creaturesInGrid); // West

    if (!neighbourhoodCells.empty()) {

        // Using the random engine and distribution
        std::uniform_int_distribution<int> dist(0, neighbourhoodCells.size() - 1);
        int choice = dist(randEngine);

        moveTo(neighbourhoodCells[choice].first, neighbourhoodCells[choice].second, creaturesInGrid);
    }
}

SeaCreature* Fish::reproduce(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    if (getAge() == getReproduceAge() && updateState()) {
        SeaCreature* newFish = nullptr;
            #pragma omp critical
            {
                // Check if the position is already occupied by another creature
                SeaCreature*& oldFish = creaturesInGrid[oldXPosition][oldYPosition];
                if (oldFish != nullptr) {
                    delete oldFish;  // Delete the existing creature
                }

                // Create a new fish and place it in the grid
                newFish = new Fish(oldXPosition, oldYPosition, 0);
                oldFish = newFish;

                // Reset the original fish's position or mark it as reproduced
                oldXPosition = -1;
                oldYPosition = -1;
            }

            resetAge();
            return newFish;
        }
    return nullptr;
}

void Fish::addIfFreeCell(std::vector<std::pair<int, int>>& neighbourhoodCells, int xPosition, int yPosition, std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {

    // Wrap around the grid, so no out of bounds plus it being a round world;
    xPosition = wrapAround(xPosition, creaturesInGrid.size());
    yPosition = wrapAround(yPosition, creaturesInGrid[0].size());

    if (creaturesInGrid[xPosition][yPosition] == nullptr) {
        neighbourhoodCells.push_back({xPosition, yPosition});
    }
}

bool Fish::isEaten() {
    return beenEaten;
}

void Fish::getEaten() {
    beenEaten = true;
}

Fish::~Fish() {
    SeaCreature::fishCount--;  // Decrement fish count
}