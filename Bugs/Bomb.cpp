//
//  Bomb.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Bryce Curson on 09/02/20
//
#include "Bomb.h"
#include "Organism.h"

using namespace std;

Bomb::Bomb(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    //set timer to 0
    death_tik = 0;
    timer = 3;
}

void Bomb::move()
{
    breedTicks++;
    death_tik++; //timer counts down
    timer--;
    if (death_tik >= STARVE_BUGS) {//checks timer (I used STARVE_BUGS as the timer)
        if (world->getAt(x, y + 1) != NULL)//blows up
        {
            if ((world->getAt(x, y + 1)->getType() == ANT) || (world->getAt(x, y + 1)->getType() == BUG))
            {
                death_tik = 0;
                delete world->getAt(x, y + 1);
                movesTo(x, y + 1);
                //return;
            }
        }

        if (world->getAt(x, y - 1) != NULL)
        {
            if ((world->getAt(x, y - 1)->getType() == ANT) || (world->getAt(x, y - 1)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x, y - 1);
                movesTo(x, y - 1);
                //return;
            }
        }

        if (world->getAt(x - 1, y) != NULL)
        {
            if ((world->getAt(x - 1, y)->getType() == ANT) || (world->getAt(x - 1, y)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x - 1, y);
                movesTo(x - 1, y);
                //return;
            }
        }
        if (world->getAt(x + 1, y) != NULL)
        {
            if ((world->getAt(x + 1, y)->getType() == ANT) || (world->getAt(x + 1, y)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x + 1, y);
                movesTo(x + 1, y);
                //return;
            }
        }
        if (world->getAt(x - 1, y - 1) != NULL)
        {
            if ((world->getAt(x - 1, y - 1)->getType() == ANT) || (world->getAt(x - 1, y - 1)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x - 1, y - 1);
                movesTo(x - 1, y - 1);
                //return;
            }
        }

        if (world->getAt(x + 1, y + 1) != NULL)
        {
            if ((world->getAt(x + 1, y + 1)->getType() == ANT) || (world->getAt(x + 1, y + 1)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x + 1, y + 1);
                movesTo(x + 1, y + 1);
                //return;
            }
        }
        if (world->getAt(x + 1, y - 1) != NULL)
        {
            if ((world->getAt(x + 1, y - 1)->getType() == ANT) || (world->getAt(x + 1, y - 1)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x + 1, y - 1);
                movesTo(x + 1, y - 1);
                //return;
            }
        }

        if (world->getAt(x - 1, y + 1) != NULL)
        {
            if ((world->getAt(x - 1, y + 1)->getType() == ANT) || (world->getAt(x - 1, y + 1)->getType() == ANT))
            {
                death_tik = 0;
                delete world->getAt(x - 1, y + 1);
                movesTo(x - 1, y + 1);
                //return;
            }
        }
    }
    Move mover = world->randomMove();//moves bomb bug
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

void Bomb::generateOffspring(int whereX, int whereY)
{
    new Bomb(this->world, whereX, whereY);
    breedTicks = 0;
}

void Bomb::breed()
{
    if (breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }

}

bool Bomb::isDead() const//kill off bomb bugs that have detonated
{
    if (timer == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

OrganismType Bomb::getType() const
{
    return BOMB;
}


char Bomb::representation()const
{
    return char(153); //sets bomb bug symbol
}

int Bomb::size() const
{
    return 30;
}

bool Bomb::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
