#ifndef SHARK_HPP
#define SHARK_HPP

#include "SeaCreature.hpp"
using namespace std;


class Shark : public SeaCreature {
public:

    Shark(int xPosition, int yPosition, int age);

    void move() override;};

#endif
