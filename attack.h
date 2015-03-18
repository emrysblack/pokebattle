// team class

#ifndef ATTACK_H
#define ATTACK_H

class Attack
{
  public:
   Attack();
   Attack(int p, int m, int a, int e, int a1, int d, int c)
   {
      priority = p;
      moveNum = m;
      accMod = a;
      evMod = e;
      accRole = a1;
      dRole = d;
      critRole = c;
   };
   int priority;
   int moveNum;
   int accMod; //needed?
   int evMod; // needed?
   int accRole;
   int dRole;
   int critRole;
  private:
};
#endif
