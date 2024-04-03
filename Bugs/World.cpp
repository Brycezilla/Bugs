#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "bomb.h"
#include "Pant.h"
#include <Windows.h>
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 3
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 8
    createOrganisms(BUG, INITIAL_BUGS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const {
    int numAnts = 0;
    int numBugs = 0;
    int numBombs = 0;
    int numPants = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "     *****Bryce Curson*****" << endl; //Display name
    cout << endl << endl;
    for (int j = 0; j < WORLDSIZE; j++) {
        for (int i = 0; i < WORLDSIZE; i++) {
            if (grid[i][j] == NULL) {
                cout << " ";
            }
            else {
                if (grid[i][j]->getType() == ANT) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//set ant color
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//set bug color
                    numBugs++;
                }
                else if (grid[i][j]->getType() == BOMB) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);//set bug color
                    numBombs++;
                }
                else if (grid[i][j]->getType() == PANT) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);//set bug color
                    numPants++;
                }


                cout << grid[i][j]->representation();
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//change font color
    cout << "Ants: " << numAnts;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//change font color
    cout << " Bugs: " << numBugs;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);//change font color
    cout << " Bomb bugs: " << numBombs;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);//change font color
    cout << " Poisonous ants: " << numPants;
   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//change font color

    //cout << "Ants: " << numAnts << " Bugs: " << numBugs << " bombs: " << numBombs << endl;
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    //move the bomb bug
    moveOrganism(BOMB);

    // Move the poisonous ants
    moveOrganism(PANT);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == BOMB) {
                new Bomb(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == PANT) {
                new Pant(this, p.x, p.y);   // Create a Bug and put it into the world
            }
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}





// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
