#include "SeaCreature.hpp"
#include <vector>
#include <iostream>

/**
 * @brief Constructs a new Sea Creature object.
 * 
 * @param xPosition Initial x position of the creature.
 * @param yPosition Initial y position of the creature.
 * @param reproduceAge Age at which the creature can reproduce.
 */
SeaCreature::SeaCreature(int xPosition, int yPosition, int reproduceAge) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->reproduceAge = reproduceAge;
    moved = false;

    std::random_device rd;
    randEngine.seed(rd());
}

/**
 * @brief Moves the creature to a new position on the grid.

 */
void SeaCreature::moveTo(int newX, int newY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    
    // Apply wrap-around for the grid
    int newXPosition = wrapAround(newX, creaturesInGrid.size());
    int newYPosition = wrapAround(newY, creaturesInGrid[0].size());

    // Move the creature to new position
    moveCreatureOnGrid(newXPosition, newYPosition, creaturesInGrid);

    xPosition = newXPosition;
    yPosition = newYPosition;
}

/**
 * @brief Wraps around the coordinate to ensure it stays within grid bounds.
 * @return int Wrapped around coordinate.
 */
int SeaCreature::wrapAround(int coordinateOnGrid, int maxCoordinate) {
    // Applies a wrap-around for the grid using modulus;
    return (coordinateOnGrid + maxCoordinate) % maxCoordinate;
}

/**
 * @brief Moves the creature on the grid, updating the grid's state.
 */
void SeaCreature::moveCreatureOnGrid(int newX, int newY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid) {
    #pragma omp critical
    {
        // Clear the old position
        creaturesInGrid[xPosition][yPosition] = nullptr;

        oldXPosition = xPosition;
        oldYPosition = yPosition;
        // Place the creature pointer at position (x, y) on the grid
        creaturesInGrid[newX][newY] = this;

        setMoved(true);
    }
}

/**
 * @brief Increments the age of the creature.
 */
void SeaCreature::updateAge() {
    age++;
}

/**
 * @brief Resets the age of the creature to zero.
 */
void SeaCreature::resetAge() {
    age = 0;
}

int SeaCreature::getAge() {
    return age;
}

int SeaCreature::getReproduceAge() {
    return reproduceAge;
}

/**
 * @brief Sets the moved status of the creature.
 * 
 * @param move Boolean indicating whether the creature has moved.
 */
void SeaCreature::setMoved(bool move) {
    moved = move;
}

/**
 * @brief Updates and returns the movement state of the creature.
 * 
 * @return bool True if the creature has moved, false otherwise.
 */
bool SeaCreature::updateState() {
    return moved;
}

int SeaCreature::getXPosition() {
    return xPosition;
}

int SeaCreature::getYPosition() {
    return yPosition;
}

string SeaCreature::getType() {
    if (this == nullptr) {
        // Handle or report error
        std::cout << "Error: getType() called on a null SeaCreature object." << std::endl;
        return "";
    }
    return type;
}

void SeaCreature::setXPosition(int xPosition) {
    this->xPosition = xPosition;
}

void SeaCreature::setYPosition(int yPosition) {
    this->yPosition = yPosition;
}

int SeaCreature::fishCount = 0;
int SeaCreature::sharkCount = 0;

