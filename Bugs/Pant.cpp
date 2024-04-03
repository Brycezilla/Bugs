//
//  Pant.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Bryce Curson on 09/03/20
//
#include <cstdlib>

#include <iostream>
#include "Pant.h"
#include "Organism.h"
#include "World.h"
using namespace std;

Pant::Pant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{

}

void Pant::move()
{
    //breedTicks++; cause they are sterile
    Move mover = world->randomMove();
    switch (mover) {
    case UP:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
        }
        break;
    case DOWN:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
        }
        break;
    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
        }
        break;
    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
        }
        break;
    default:
        break;
    }
}

void Pant::breed()
{
    if (breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}


void Pant::generateOffspring(int whereX, int whereY)
{
    new Pant(this->world, whereX, whereY);
    breedTicks = 0;
}


OrganismType Pant::getType() const
{
    return PANT;
}

char Pant::representation() const
{
    return char(157);//sets poisonous ant symbol
}

int Pant::size() const
{
    return 10;
}

bool Pant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}