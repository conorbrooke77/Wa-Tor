#include "Fish.hpp"

Fish::Fish(int xPosition, int yPosition, int age) 
    : SeaCreature(xPosition, yPosition, age) {
        type = "FISH";
}

void Fish::move()
{
    xPosition++;
    yPosition++;
}