// team class

#ifndef TRAINER_H
#define TRAINER_H
#include "pokemon.h"

class Trainer
{
   public:
   int numTeam;
   Pokemon * getNext();
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
