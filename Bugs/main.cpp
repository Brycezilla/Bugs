#include <iostream>
#include <ctime>    // for time
#include "World.h"
#include <Windows.h>
#include <conio.h>
using namespace std;

int main()
{


    
    World myWorld(time(0));

    myWorld.display();
    //declare variables
    char ch;
    int x = 0;
    int n = 2;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    

    
    while (x == 0)//creates start menu
    {
        
        if (n % 2 == 0)//performs animation
            cout << "\n \n \n \n           -> Press E to start <-" << endl;
        else
            cout << "\n \n \n \n            ->Press E to start<-" << endl;

        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'e' || ch == 'E')
            {
                x++;//triggers program
                
            }
        }
        n++;
        Sleep(390);
    }
    while (x == 1) {//starts program
        if (_kbhit())
        {
            ch = _getch();

            if (ch == 'b' || ch == 'B')
            {
                myWorld.createOrganisms(BOMB, 1);//adds bomb bug
            }
            else if (ch == 'v' || ch == 'V')
            {
                myWorld.createOrganisms(BUG, 1);//adds bug
            }
            else if (ch == 'p' || ch == 'P')
            {
                myWorld.createOrganisms(PANT, 1);//adds poisonous ant
            }
            else if (ch == 'a' || ch == 'A')
            {
                myWorld.createOrganisms(ANT, 1);//adds poisonous ant
            }

        }

        system("cls");
        myWorld.simulateOneStep();
        myWorld.display();
        //Sleep(575);
        Sleep(900);//slows program down

    }

    return 0;
}
