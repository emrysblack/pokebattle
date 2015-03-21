// team class
#include <iostream>
#include <string>
#include "attack.h"
#include "pokemon.h"
#include "move.h"
using namespace std;

Attack & Attack::operator =(const Attack & rhs)
{
   accRole = rhs.accRole;
   dRole = rhs.dRole;
   critRole = rhs.critRole;
   moveNum = rhs.moveNum;
   pokeNum = rhs.pokeNum;
}

bool Attack::execute(Pokemon & src, Pokemon & target, Move * move)
{
   
   float acMod = src.getMod(ACC);
   (acMod < 0)? acMod = 2/(acMod * -1 + 2) : acMod = (acMod + 2) / 2;
   float evMod = target.getMod(EVADE);
   (evMod < 0)? evMod = 2/(evMod * -1 + 2) : evMod = (evMod + 2) / 2;
   int accuracy = move->acc * (100 * acMod)/(100 * evMod);
   //cout << accuracy << endl;
   bool hit = accRole < accuracy;
   
   if (!hit)
   {
      return false;
   }
   float str = src.getStrength();
   float def = target.getDefense();
   float sMod = src.getMod(ATTACK);
   float dMod = target.getMod(DEFENSE);
   if (move->spec)
   {
      //std::cout << "special!\n";
      sMod = src.getMod(SATTACK);
      dMod = target.getMod(SDEFENSE);
      str = src.getSPStrength();
      def = target.getSPDefense();
   }
   // set up modifiers
   (sMod < 0)? sMod = 2/(sMod * -1 + 2) : sMod = (sMod + 2) / 2;
   (dMod < 0)? dMod = 2/(dMod * -1 + 2) : dMod = (dMod + 2) / 2;

   //cout << endl << sMod << " " << dMod << endl;
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
   float p = ((dRole + 85)/100.0); // 81 - 100 % dam
   int damage = percent * mod * p; 
   //cout << "damage value: " << damage << endl << "percent: " << p << endl;
   
   
   
   // only display if damage dealt
   if (damage)
   {
      // critcal hit?
   
      // normal value, other stages are 1/8, 1/4, 1/3, 1/2
      float cChance = 100/16;
   
      //cout << "crit chance - " << critRole << endl;
      bool crit = (critRole <= cChance);
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
   return true;
}

float Attack::getTypeMult(const Pokemon & target, Move * move)
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
