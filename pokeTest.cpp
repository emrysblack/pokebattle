// driver program for poke
#include <iostream>
#include <string>
#include <cstdlib> // for random numbers
#include "trainer.h"
#include "pokemon.h"
#include "move.h"
#include "server.h"
#include "game.h"
using namespace std;



void mSetUp()
{
   //Server connection;
   //connection.findClient();
   Server::findClient();
}

void interact()
{
   cout << "Welcome to Pokemon !\n";
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
         case 'm':
              mSetUp();
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
