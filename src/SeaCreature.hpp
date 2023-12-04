#include <string>
#include <vector>
#include <random>

#ifndef SEACREATURE_HPP
#define SEACREATURE_HPP

using namespace std;

class SeaCreature {
protected:
    static int fishCount; // Could be a thread safety concern
    static int sharkCount; // Could be a thread safety concern

    int xPosition, yPosition; // Positions on the grid
    int age; // Creature's age
    bool moved; // Flag to indicate if the creature has moved
    string type; // Type of the creature (Fish or Shark)
    int reproduceAge; // Age at which the creature can reproduce
    std::mt19937 randEngine; // Random engine

    SeaCreature(int xPosition, int yPosition, int reproduceAge);
    
    // Wrap around logic for the grid
    int wrapAround(int coordinateOnGrid, int maxCoordinate);
    void moveCreatureOnGrid(int newX, int newY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid);
    void moveTo(int newX, int newY, std::vector<std::vector<SeaCreature*>>& creaturesInGrid);


public:
     int oldXPosition, oldYPosition; // Previous positions, used for tracking movement

    static int getFishCount() { return fishCount; }
    static int getSharkCount() { return sharkCount; }
    
    string getType();
    int getXPosition();
    int getYPosition();

    void setXPosition(int xPosition);
    void setYPosition(int yPosition);

    bool updateState(); // Moved update state
    void setMoved(bool move); // Set the moved flag

    void updateAge(); // Update the age of the creature
    int getAge(); 
    int getReproduceAge(); 
    void resetAge(); // Reset the age (typically after reproduction)

    virtual bool isEaten() { return false; } // Virtual method to check if creature is eaten
    virtual void getEaten() {} // Virtual method to mark creature as eaten

    virtual void depleteEnergy() {} // Virtual method for depleting energy (specific to Sharks)
    virtual bool isStarved() { return false; }
    virtual int getEnergy() { return 1; }

    virtual SeaCreature* reproduce(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) = 0; // Thread safety concern: modifies shared grid.

    virtual void move(std::vector<std::vector<SeaCreature*>>& creaturesInGrid) = 0; // Thread safety concern: modifies shared grid.

    // Virtual destructor
    virtual ~SeaCreature() {}

};
#endif