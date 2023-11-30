#include "SeaCreature.hpp"
#include <vector>

SeaCreature::SeaCreature(int xPosition, int yPosition, int age) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->age = age;
    moved = false;
}

string SeaCreature::showMovement() {
    return "X Position:" + to_string(xPosition) + "\n" + "Y Position:" + to_string(yPosition); 
}

SeaCreature::~SeaCreature() {
    // Implementation can be empty if there's nothing specific to destroy
}

int SeaCreature::getXPosition() {
    return xPosition;
}

int SeaCreature::getYPosition() {
    return yPosition;
}

string SeaCreature::getType() {
    return type;
}