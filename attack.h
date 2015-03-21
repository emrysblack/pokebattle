// team class

#ifndef ATTACK_H
#define ATTACK_H

#include "pokemon.h"
#include "move.h"

class Attack
{
  public:
   Attack() : accRole(0), dRole(0), critRole(0), moveNum(0), pokeNum(0){};
   Attack(int a, int d, int c, int m, int p)
   {
      accRole = a;
      dRole = d;
      critRole = c;
      moveNum = m;
      pokeNum = p;
   }
   
   Attack(const Attack & rhs)
   {
      *this = rhs;
   }
   Attack & operator =(const Attack & rhs);
   /* { */
   /*    accRole = rhs.accRole; */
   /*    dRole = rhs.dRole; */
   /*    critRole = rhs.critRole; */
   /*    moveNum = rhs.moveNum; */
   /*    pokeNum = rhs.pokeNum; */
   /* } */
   
   bool execute(Pokemon & src, Pokemon & target, Move * move);
   float getTypeMult(const Pokemon & target, Move * move);
   int accRole;
   int dRole;
   int critRole;
   int moveNum;
   int pokeNum;
  private:
};

#endif
