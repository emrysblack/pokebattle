// contains moves

#ifndef MOVE_H
#define MOVE_H
class Move
{  
   public:
      Move(std::string n = "Unknown", int p = 0, int ac = 100,
           int s = 0, int aType = NORMAL, bool special = false)
         :name(n), power(p), acc(ac), priority(s), type(aType),
          spec(special) {}
      std::string name;
      int power;
      int acc; // accuracy
      int priority;
      int type;
      bool spec; // physical or special attack
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
         std::cout << cValue;
      }
      virtual void effect(Pokemon * target) {}
};

class Tackle : public Move
{
   public:
  Tackle() : Move("Tackle", 35){}
};

class Growl : public Move
{
   public:
      Growl() : Move("Growl"){}
       void effect(Pokemon * target)
       {
          changeStat(target, ATTACK, -1);
       }
};

class FeatherDance : public Move
{
   public:
      FeatherDance() : Move("Feather Dance"){}
       void effect(Pokemon * target)
       {
          changeStat(target, ATTACK, -2);
       }
};

class TailWhip : public Move
{
   public:
      TailWhip() : Move("TailWhip"){}
      void effect(Pokemon * target)
      {
         changeStat(target, DEFENSE, -1);
      }
};

class Scratch : public Move
{
   public:
  Scratch() : Move("Scratch", 40){}
};

class HeadButt : public Move
{
   public:
       HeadButt() : Move("HeadButt", 35){}
};

class QuickAttack : public Move
{
   public:
  QuickAttack() : Move ("Quick Attack", 40, 100, 1){}
};

class Bubble : public Move
{
   public:
  Bubble() : Move ("Bubble", 20, 100, 0, WATER, true){}
};

class SandAttack : public Move
{
  public:
  SandAttack() : Move("Sand Attack"){}
   void effect(Pokemon * target)
   {
      changeStat(target, ACC, -1);
   }
};

#endif
