// contains moves

#ifndef MOVE_H
#define MOVE_H
#include "pokemon.h"

class Move
{  
   public:
      Move(int mNum = MOVESET, std::string n = "Unknown", int p = 0,
           int ac = 100, int s = 0, int aType = NORMAL, bool special = false)
         :moveNum(mNum), name(n), power(p), acc(ac), priority(s),
      type(aType), spec(special) {}

   int moveNum;
   std::string name;
   int power;
   int acc; // accuracy
   int priority;
   int type;
   bool spec; // physical or special attack
   int getMoveNum() { return moveNum; }
   void changeStat(Pokemon * target, const int statType, int stage)
      {
         std::cout << target->getName();
         int cValue;
         std::string stat[] = {"attack", "defense",
                               "special attack", "special defense",
                               "speed", "accuracy", "evasion"};
         cValue = target->getMod(statType);
       
         if (cValue <= -6 || cValue >= 6)
         {
            std::cout << "'s " << stat[statType] << " won't go any "
                      << ((cValue < 0)? "Lower!" : "Higher!");
         }
         else
         {
            if (cValue + stage <= -6)
            {
               stage = -6 - cValue;
            }
            else if (cValue + stage >= 6)
            {
               stage = 6 - cValue;
            }
            target->setMod(statType,cValue + stage);
            std::cout << "'s " << stat[statType];
            if (stage < -1 || stage > 1)
               std::cout << " sharply ";
            std::cout << ((stage < 0)? " fell!" : " rose!");
         }
      }
      virtual void effect(Pokemon * target) {}
};

class Tackle : public Move
{
   public:
  Tackle() : Move(TACKLE, "Tackle", 35){}
};

class Growl : public Move
{
   public:
  Growl() : Move(GROWL, "Growl"){}
       void effect(Pokemon * target)
       {
          changeStat(target, ATTACK, -1);
       }
};

class FeatherDance : public Move
{
   public:
  FeatherDance() : Move(FEATHERDANCE, "Feather Dance"){}
       void effect(Pokemon * target)
       {
          changeStat(target, ATTACK, -2);
       }
};

class TailWhip : public Move
{
   public:
  TailWhip() : Move(TAILWHIP, "TailWhip"){}
      void effect(Pokemon * target)
      {
         changeStat(target, DEFENSE, -1);
      }
};

class Scratch : public Move
{
   public:
  Scratch() : Move(SCRATCH, "Scratch", 40){}
};

class HeadButt : public Move
{
   public:
  HeadButt() : Move(HEADBUTT, "HeadButt", 35){}
};

class QuickAttack : public Move
{
   public:
  QuickAttack() : Move (QUICKATTACK, "Quick Attack", 40, 100, 1){}
};

class Bubble : public Move
{
   public:
  Bubble() : Move (BUBBLE, "Bubble", 20, 100, 0, WATER, true){}
};

class SandAttack : public Move
{
  public:
  SandAttack() : Move(SANDATTACK, "Sand Attack"){}
   void effect(Pokemon * target)
   {
      changeStat(target, ACC, -1);
   }
};

#endif
