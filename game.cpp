#include <iostream>
#include <string>
#include <cstdlib> // for random numbers
#include "trainer.h"
#include "pokemon.h"
#include "move.h"
#include "game.h"
#include "attack.h"
#include "server.h"
using namespace std;

float Game::getTypeMult(const Pokemon & target, Move * move)
{
   int dType1 = target.getType1();
   int dType2 = target.getType2();
   int aType = move->type;
   
   // array containing effectivness NONE is num of types,
   // so each row should end with 1 for NONE TYPE
   const float eff[NONE][NONE + 1] =
      {1,1,1,1,1,.5,1,0,.5,1,1,1,1,1,1,1,1,1,1,//norm
       2,1,.5,.5,1,2,.5,0,2,1,1,1,1,.5,2,1,2,.5,1,//fight
       1,2,1,1,1,.5,2,1,.5,1,1,2,.5,1,1,1,1,1,1,//flying
       1,1,1,.5,.5,.5,1,.5,0,1,1,2,1,1,1,1,1,2,1,//poison
       1,1,0,2,1,2,.5,1,2,2,1,.5,2,1,1,1,1,1,1,//ground
       1,.5,2,1,.5,1,2,1,.5,2,1,1,1,1,2,1,1,1,1,//rock
       1,.5,.5,.5,1,1,1,.5,.5,.5,1,2,1,2,1,1,2,.5,1,//bug
       0,1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,.5,1,1,//ghost
       1,1,1,1,1,2,1,1,.5,.5,.5,1,.5,1,2,1,1,2,1,//steel
       1,1,1,1,1,.5,2,1,2,.5,.5,2,1,1,2,.5,1,1,1,//fire
       1,1,1,1,2,2,1,1,1,2,.5,.5,1,1,1,.5,1,1,1,//water
       1,1,.5,.5,2,2,.5,1,.5,.5,2,.5,1,1,1,.5,1,1,1,//grass
       1,1,2,1,0,1,1,1,1,1,2,.5,.5,1,1,.5,1,1,1,//electr
       1,2,1,2,1,1,1,1,.5,1,1,1,1,.5,1,1,0,1,1,//psychc
       1,1,2,1,2,1,1,1,.5,.5,.5,2,1,1,.5,2,1,1,1,//ice
       1,1,1,1,1,1,1,1,.5,1,1,1,1,1,1,2,1,0,1,//dragon
       1,.5,1,1,1,1,1,2,1,1,1,1,1,2,1,1,.5,.5,1,//dark
       1,2,1,.5,1,1,1,1,.5,.5,1,1,1,1,1,2,2,1,1};//fairy
   
   float mult = eff[aType][dType1] * eff[aType][dType2];
 
   if (!mult)
   {
      cout << target.getName() << " immune to " << move->name
           << endl;   
   }
   else if (mult < 1)
   {
      cout << "It's not very effective\n";
   }
   else if (mult > 1)
   {
      cout << "It's super effective\n";
   }
   
   return mult;
}

void Game::attack(Pokemon & src, Pokemon & target, Move * move)
{
   float str = src.getStrength();
   float def = target.getDefense();
   float sMod = src.getMod(ATTACK);
   float dMod = target.getMod(DEFENSE);
   if (move->spec)
   {
      std::cout << "special!\n";
      sMod = src.getMod(SATTACK);
      dMod = target.getMod(SDEFENSE);
      str = src.getSPStrength();
      def = target.getSPDefense();
   }
   // set up modifiers
   (sMod < 0)? sMod = 2/(sMod * -1 + 2) : sMod = (sMod + 2) / 2;
   (dMod < 0)? dMod = 2/(dMod * -1 + 2) : dMod = (dMod + 2) / 2;

   cout << endl << sMod << " " << dMod << endl;
   int bPLevels = 2; // battle point levels
   for (int i = 0; i < MOVESET; i++)
   {
      if (src.moveSet[i] > 0)
         bPLevels += src.moveSet[i];
   }
   float level = (2.0 * bPLevels + 10) / 250;
   // original damage formula for level, need to calculate level
   // from stats due to cutting levels altogether, or make it private
   // and hidden - call it experience modifier?
   // replaced level with battle point levels - counts the total number
   // of move levels known by the current pokemon
   float percent = level * (float)(str * sMod)
      /(float)(def * dMod) * move->power + 2;
   
   // cout << "\n---\n" << percent << "\n---\n";
   
   // same type attack bonus
   float stab = (src.getType1() == move->type ||
                 src.getType2() == move->type)? 1.5 : 1.0;
   // type effectiveness
   float typeMult = getTypeMult(target, move);

   // mod and final damage
   float mod = stab * typeMult * (bool)move->power;
   float p = ((rand()  % 16 + 85)/100.0); // 81 - 100 % dam
   int damage = percent * mod * p; 
   //cout << "damage value: " << damage << endl << "percent: " << p << endl;
   
   
   
   // only display if damage dealt
   if (damage)
   {
      // critcal hit?
   
      // normal value, other stages are 1/8, 1/4, 1/3, 1/2
      float cChance = 100/16;
   
      int cc = rand() % 100;
      cout << "crit chance - " << cc << endl;
      bool crit = (cc <= cChance);
      if (crit)
      {
         damage *= 1.5;
         cout << "critcal hit!\n";
      }
      target.setHPC(target.getHPC() - damage);
      cout << damage << " damage dealt!\n";
   }
   // only run effect if target is not immune
   if (typeMult)
      move->effect(&target);
}

// handles the stat prep for a new pokemon
void Game::battlePrep(Pokemon * poke)
{
   for (int i = 0; i < MODSET; i++)
      poke->setMod(i,0);
}

bool Game::battle(Trainer& p, Trainer& c)
{
   bool player = true;
   bool win = true; // assume the win
   Pokemon * one = p.getNext();
   Pokemon * two = c.getNext();
   Pokemon * first = one;
   Pokemon * second = two;
   // set modifiers to normal for battle
   battlePrep(one);
   battlePrep(two);
   char option;
   std::cout << "-----Battle-----\n\t" << one->getName() << std::endl
             << "VS\n\t" << two->getName()
             << "\n----------------\n";
   while (!one->fainted() && !two->fainted())
   {
      std::cout /*<< "\033[2J"*/ << "\n\t" << one->getName() << " HP: "
                  << one->getHPC()
                  << "\n\t" << two->getName() << " HP: "
                  << two->getHPC() << std::endl;
      std::cout << "\nBattle Command (? for options) ";
      std::cin >> option;
      option = tolower(option); // convert to lower case
      int priorityP = 0; // move order for player
      int priorityC = 0; // move order for computer
      Move * pMove;
      Move * cMove;

      // select action
      switch(option)
      {
         case 'a':
            cout << "attack\n";
            pMove = selectMove(*one);
            cMove = selectMove(*two);
            break;
         case 'd':
            cout << "defend\n";
            break;
         case 's':
            cout << "switch pokemon\n";
            break;
         case 'i':
            cout << "item\n";
            break;
         case 'r':
            cout << "run\n";
            break;
         case '?':
            displayOptions();
            continue; // display does not cost a turn
         default:
            cout << "unknown command\n";
            continue; // does not cost a turn
      }

      // execute actions in correct order

      // if the opponent is faster and
      // player is not using higher priority move
      // comp goes first
      if ((one->getSpeed() < two->getSpeed() ||
           pMove->priority < cMove->priority) &&
          pMove->priority <= cMove->priority)
      {
         //  cout << "Opponent Faster\n";
         first = two;
         second = one;
         // swap moves
         Move * temp = pMove;
         pMove = cMove;
         cMove = temp;
      }
      else // player moves first
      {
         // cout << "You are faster\n";
         first = one;
         second = two;
         // moves already in correct order
      }
      // faster goes first

      // display message
      std::cout << std::endl;
      if (first == two)
         cout << "Foe ";
      cout << first->getName()
             << " used " << pMove->name << "!\n";

      // execute attack if attack hits

      // accuracy will be move's accuracy times attack poke's accuracy over
      // target's evasion
      float acMod = first->getMod(ACC);
      (acMod < 0)? acMod = 2/(acMod * -1 + 2) : acMod = (acMod + 2) / 2;
      // (acMod < .25)? acMod = .25 : acMod = acMod;
      // (acMod > 4)? acMod = 4 : acMod = acMod;
      float evMod = second->getMod(EVADE);
      (evMod < 0)? evMod = 2/(evMod * -1 + 2) : evMod = (evMod + 2) / 2;
      // (evMod < .25)? evMod = .25 : evMod = evMod;
      // (evMod > 4)? evMod = 4 : evMod = evMod;
      int accuracy = pMove->acc * (100 * acMod)/(100 * evMod);
      cout << accuracy << endl;
      bool hit = (rand() % 100) < accuracy;
      if (hit)
      {
         attack(*first, *second, pMove);
      }
      else
      {
         std::cout << std::endl;
         if (first == two)
            cout << "Foe ";
         cout << first->getName();
         std::cout << "'s attack missed!\n";
      }
      // second can go if still healthy
      if (!second->fainted())
      {
         std::cout << std::endl;
         if (second == two)
            cout << "Opponent's ";
         cout << second->getName()
              << " used " << cMove->name << "!\n";
         // execute attack if attack hits

         // prepare random 
         // srand(time(NULL));

         // accuracy will be move's accuracy times attack poke's
         // accuracy over target's evasion
         acMod = second->getMod(ACC);
         (acMod < 0)? acMod = 2/(acMod * -1 + 2) : acMod = (acMod + 2) / 2;
         (acMod < .25)? acMod = .25 : acMod = acMod;
         (acMod > 4)? acMod = 4 : acMod = acMod;
         evMod = first->getMod(EVADE);
         (evMod < 0)? evMod = 2/(evMod * -1 + 2) : evMod = (evMod + 2) / 2;
         (evMod < .25)? evMod = .25 : evMod = evMod;
         (evMod > 4)? evMod = 4 : evMod = evMod;
         accuracy = cMove->acc * (100 * acMod)/(100 * evMod);
         cout << accuracy << endl;
         hit = (rand() % 100) < accuracy;
         if (hit)
         {
           attack(*second, *first, cMove);
         }
         else
         {
            cout << endl;
            if (second == two)
               cout << "Foe ";
            cout << second->getName();
            cout << "'s attack missed!\n";
         }
      }
      // run ends battle
      // if (option == 'r')
      // break;
      // opponent attack

      // test for fainting
      if (two->fainted())
      {
         cout << endl << "Opponent's " << two->getName() << " fainted!\n";
         two = c.getNext();
         
         // set modifiers to normal
         battlePrep(two);
      }
     
      if (one->fainted())
      {
         cout << endl << one->getName() << " fainted!\n";
         one = p.getNext();
         
         // set modifiers to normal
         battlePrep(one);   
      }
   }
   if (!one->fainted())
   {
      cout << "\nYou win!\n";
   }
   else
   {
      cout << "\nYou lose!\n";
      win = false;
   }
   return win;
}

Move * Game::selectMove(const Pokemon & src)
{
   int num = 0; // screen option
   for(int i = 0; i < MOVESET; i++)
   {
      if (src.moveSet[i] > 0)
      {
         cout << ++num << " - " << moveList[i]->name << endl;
      }
   }
   int option;
   cout << "\nselect Move: ";
   cin >> option;
   while (cin.fail() || option < 1 || option > num)
   {
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      cout << "invalid move\n";
      cout << "\nselect Move: ";
      cin >> option;
   }
      // select move from option
      num = 0;
      int i = 0;
      while(num != option)
      {
         if (src.moveSet[i] > 0)
         {
            ++num;
         }
         ++i;
      }
      // i - 1 due to extra i++ at bottom of loop
      return moveList[i - 1];
}
