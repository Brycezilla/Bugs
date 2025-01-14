//
//  Pant.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Bryce Curson on 09/03/20
//

#include <iostream>
#include "Organism.h"
#include "World.h"

class Pant : public Organism
{
public:

    Pant(World* aWorld, int xcoord, int ycoord);
    // In the given world moves this organism.
    void move();

    // Makes this organism breed.
    void breed();

    // Returns the type of this organism.
    OrganismType getType() const;

    // The character representation of this organism.
    char representation() const;

    // The size of this organism.
    int size() const;

    bool in_range(int xx, int yy);

private:

    void generateOffspring(int whereX, int whereY);
};