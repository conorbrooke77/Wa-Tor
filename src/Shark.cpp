#include "Shark.hpp"

Shark::Shark(int xPosition, int yPosition, int age) 
    : SeaCreature(xPosition, yPosition, age) {
        type = "SHARK";
}

void Shark::move()
{
    xPosition += 10;
    yPosition += 10;
}