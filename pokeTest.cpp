// driver program for poke
#include <iostream>
#include <string>
#include <cstdlib> // for random numbers
#include "trainer.h"
#include "pokemon.h"
#include "move.h"
#include "game.h"
using namespace std;



void interact()
{
   cout << "Welcome to Pokemon HAHAHAHAHAHA!\n";
   Game game;
   Trainer p;
   Trainer c;
   char option = 'z';
   do 
   { 
      cout << "\nWhat would you like to do? ";
      cin >> option;
      option = tolower(option); // convert to lower case
      switch (option)
      {
         case 'b':
            game.battle(p, c);
            break;
         case 'n':
            cout << "Ok, no battle\n";
            break;
         case 'q':
            cout << "Thanks for playing\n";
            break;
         default:
            cout << "unknown option\n";
            break;
      }
   } while (option != 'q');
}

int main(int argc, char ** argv)
{
   // prepare random 
   srand(time(NULL));
   interact();  
   return 0;
}
