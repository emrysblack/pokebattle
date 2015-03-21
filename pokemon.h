// New Pokemon battle system test

#ifndef POKEMON_H
#define POKEMON_H
#include <string>
//#include "move.h"

// MOVESET has to be the last entry since it contains the number of moves
enum moves{TACKLE, GROWL, TAILWHIP, SCRATCH, HEADBUTT, BUBBLE, QUICKATTACK,
           SANDATTACK, FEATHERDANCE, MOVESET};

enum types{NORMAL, FIGHT, FLYING, POISON, GROUND, ROCK, BUG, GHOST, STEEL,
           FIRE, WATER, GRASS, ELECTRIC, PSYCHIC, ICE, DRAGON, DARK, FAIRY,
           NONE};
           
enum stat{ATTACK, DEFENSE, SATTACK, SDEFENSE, SPEED, ACC, EVADE, MODSET};
// abstract type
class Pokemon
{
   protected:
   std::string name; // name
   int type1; // 1st type
   int type2; // 2nd type
   int hpT; // total HP
   int hpC; // current HP
   int strength;
   int defense;
   int spStrength; // special attack
   int spDefense; // special defense
   int speed;
   float sMod; // strength multiplier for battles
   float dMod; // defense multiplier for battles
   float spSMod; // special strength multiplier for battles
   float spDMod; // special defense multiplier for battles
   float acMod; // accuracy multiplier for battles
   float speMod; // speed multiplier for battles
   float evMod; // evasion multiplier for battles 
   virtual void setMoves() = 0;
   public:
   Pokemon()
   {
      for(int i = 0; i < MOVESET; i++)
      {
         moveSet[i] = -1;
      }
   }
   ~Pokemon(){}
   // getters
   std::string getName() const{return name;}
   int getType1() const{return type1;}
   int getType2() const{return type2;}
   int getHPC() const{return hpC;}
   int getHPT() const{return hpT;}
   int getStrength() const{return strength;}
   int getDefense() const{return defense;}
   int getSPStrength() const{return spStrength;}
   int getSPDefense() const{return spDefense;}
   int getSpeed() const{return speed;}
   
   int getMod(const int type) const
   {
      int mod;
      switch (type)
      {
         case ATTACK:
            mod = sMod;
            break;
         case DEFENSE:
            mod = dMod;
            break;
         case SATTACK:
            mod = spSMod;
            break;
         case SDEFENSE:
            mod = spDMod;
            break;
         case SPEED:
            mod = speMod;
            break;
         case ACC:
            mod = acMod;
            break;
         case EVADE:
            mod = evMod;
            break;
         default: // should never happen
            mod = 0;
            break;
      }
      return mod;
   }
   /* int getSMod() const{return sMod;} */
   /* int getDMod() const{return dMod;} */
   /* int getSPSMod() const{return spSMod;} */
   /* int getSPDMod() const{return spDMod;} */
   /* int getACMod() const{return acMod;} */
   /* int getEVMod() const{return evMod;} */
   
   // setters
   void setName(const std::string & nickName) {name = nickName;}
   void setHPC(const int & hp) {hpC = hp;}
   void setHPT(const int & hpTotal) {hpT = hpTotal;}
   void setStrength(const int & str) {strength = str;}
   void setDefense(const int & def) {defense = def;}
   void setSPStrength(const int & str) {spStrength = str;}
   void setSPDefense(const int & def) {spDefense = def;}
   void setSpeed(const int & spd) {speed = spd;}
   
   void setMod(const int type, const int mod)
   {
      switch (type)
      {
         case ATTACK:
            sMod = mod;
            break;
         case DEFENSE:
            dMod = mod;
            break;
         case SATTACK:
            spSMod = mod;
            break;
         case SDEFENSE:
            spDMod = mod;
            break;
         case SPEED:
            speMod = mod;
            break;
         case ACC:
            acMod = mod;
            break;
         case EVADE:
            evMod = mod;
            break;
         default: // should never happen
            break;
      }
   }
   /* void setSMod(const int & mod) {sMod = mod;} */
   /* void setDMod(const int & mod) {dMod = mod;} */
   /* void setSPSMod(const int & mod) {spSMod = mod;} */
   /* void setSPDMod(const int & mod) {spDMod = mod;} */
   /* void setACMod(const int & mod) {acMod = mod;} */
   /* void setEVMod(const int & mod) {evMod = mod;} */
   
   bool fainted() {return hpC <= 0;}
   int moveSet[MOVESET]; // known moves
};

class Bulbasaur : public Pokemon
{
   public:
   Bulbasaur(std::string n = "Bulbasaur", int hpTotal = 20)
   {
      name = n;
      type1 = GRASS;
      type2 = NONE;
      hpT = hpTotal;
      hpC = hpTotal;
      strength = 10;
      defense = 10;
      spStrength = 10;
      spDefense = 10;
      speed = 10;
      setMoves();
   }
   void setMoves()
   {
      moveSet[TACKLE] = 4;
      moveSet[GROWL] = 1;
      moveSet[FEATHERDANCE] = 1;
   }
};

class Squirtle : public Pokemon
{
   public:
   Squirtle(std::string n = "Squirtle", int hpTotal = 20)
   {
      name = n;
      type1 = WATER;
      type2 = NONE;
      hpT = hpTotal;
      hpC = hpTotal;
      strength = 8;
      defense = 12;
      spStrength = 8;
      spDefense = 12;
      speed = 8;
      setMoves();
   }
   void setMoves()
   {
      moveSet[TACKLE] = 3;
      moveSet[TAILWHIP] = 1;
      moveSet[BUBBLE] = 1;
      moveSet[QUICKATTACK] = 1;
   }
};

class Charmander : public Pokemon
{
   public:
   Charmander(std::string n = "Charmander", int hpTotal = 20)
   {
      name = n;
      type1 = FIRE;
      type2 = NONE;
      hpT = hpTotal;
      hpC = hpTotal;
      strength = 12;
      defense = 8;
      speed = 12;
      spStrength = 12;
      spDefense = 8;
      setMoves();
   }
   void setMoves()
   {
      moveSet[SCRATCH] = 4;
      moveSet[GROWL] = 1;
      moveSet[SANDATTACK] = 1;
   }
};

#endif





