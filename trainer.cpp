// team class
#include "pokemon.h"
#include "trainer.h"
#include <iostream>
using namespace std;
Trainer::Trainer()
{
   team[0] = new Bulbasaur;
   team[1] = new Squirtle;
   team[2] = new Charmander;
   numTeam = 3;
}

Pokemon * Trainer::getNext()
{
   int num = 0; // total number of Pokemon 
   int faint = 0; // number of fainted Pokemon
   // get a list of pokemon in party
   for (int i = 0; i < numTeam; i++)
   {
      cout << ++num << " - " << team[i]->getName();
      if(team[i]->fainted())
      {
         cout << " fainted";
         ++faint;
      }
      cout << endl;
   }

   int option = 0; // 0 will run slection loop
    
   // return first if no one else
   if (!(num - faint)) // everyone fainted
      option = 1; // select first and skip selection loop
   
   while ((cin.fail() || option < 1 || option > num
           || team[option - 1]->fainted()) && (num - faint))
   {
      cout << "\nSelect Pokemon: ";
      cin >> option;
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      else if (option < 1 || option > num)
      {
         cout << "invalid pokemon\n";
      }
      else if (team[option - 1]->fainted())
      {
         cout << "Pokemon Fainted!\n";
      }
      
      
   }
   return team[option - 1];
}
