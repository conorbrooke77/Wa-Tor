#ifndef FISH_HPP
#define FISH_HPP

#include "SeaCreature.hpp"

using namespace std;

class Fish : public SeaCreature {

public:
    // Constructor
    Fish(int xPosition, int yPosition, int age);

    // Override the move method from AquaticCreature
    void move() override;
};

#endif