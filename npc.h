//Lachlan Kotarski and Diego Olin 

#ifndef NPC_H
#define NPC_H
#include "person.h"
#include <iostream>
using namespace std;

class Npc : public Person {
private:
  bool agression_;
  int attack1_;
  int attack2_;
  int attack3_;

public:
  Npc();
  Npc(string name, int hp, int armor,bool agression,int att1,int att2, int att3);
  bool getAgression();
  int getAttack1();
  int getAttack2();
  int getAttack3();

  void setAgression(bool agression);
  void setAttack1(int attack1);
  void setAttack2(int attack2);
  void setAttack3(int attack3);
};
#endif