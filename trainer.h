// team class

#ifndef TRAINER_H
#define TRAINER_H
#include "pokemon.h"

class Trainer
{
   public:
   int numTeam;
   Pokemon * getNext(int & pos);
   Pokemon * getPoke(int pos) { return team[pos]; }
   Pokemon * team[6];
   Trainer();
   ~Trainer()
   {
      for(int i = 0; i < numTeam; i++)
      {
          delete team[i];
      }
   }
   Trainer(const Trainer & rhs);
   //void catch(Pokemon target);
};
#endif
