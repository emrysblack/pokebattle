// has other files and declarations
#ifndef GAME_H
#define GAME_H
//class Pokemon;
//class Trainer;
//class Move;
#include "trainer.h"
//#include "pokemon.h"
//#include "move.h"
class Game
{
  private:
   Move * moveList[MOVESET];
   int numMoves;
   void attack(Pokemon & src, Pokemon & target, Move * move);
   Move * selectMove(const Pokemon & src);
   Move * getMove(int moveNum);
   float getTypeMult(const Pokemon & target, Move * move);
   void displayOptions()
   {
      std::cout << "a - attack\n"
                << "d - defend\n"
                << "s - support\n"
                << "i - item\n"
                << "r - run\n";
   }
  public:
   Game()
   {
      moveList[TACKLE] = new Tackle;
      moveList[GROWL] = new Growl;
      moveList[TAILWHIP] = new TailWhip;
      moveList[SCRATCH] = new Scratch;
      moveList[HEADBUTT] = new HeadButt;
      moveList[QUICKATTACK] = new QuickAttack;
      moveList[BUBBLE] = new Bubble;
      moveList[SANDATTACK] = new SandAttack;
      moveList[FEATHERDANCE] = new FeatherDance;
   }
   ~Game()
   {
      for (int i = 0; i < MOVESET; i++)
      {
         delete moveList[i];
      }
   }
   void battlePrep(Pokemon * poke);
   bool battle(Trainer& p, Trainer& c);
   bool netBattle(Trainer& p, Trainer& c);
};
#endif
