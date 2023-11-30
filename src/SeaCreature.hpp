#include <string>
#ifndef SEACREATURE_HPP
#define SEACREATURE_HPP

using namespace std;

class SeaCreature {
protected:
    int xPosition, yPosition; // Coordinates in the Wa-Tor world
    int age;  // Age of the creature
    bool moved; // Flag to check if the creature has moved in the current turn
    string type;

    // Constructor
    SeaCreature(int xPosition, int yPosition, int age);

    // Virtual function for movement
    virtual void move() = 0;

public:
    string showMovement();

    int getXPosition();

    int getYPosition();

    string getType();

    // Virtual destructor
    virtual ~SeaCreature();
};


#endif