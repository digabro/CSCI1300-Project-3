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
  string attack1_Name_;
  string attack2_Name_;
  string attack3_Name_;

public:
  Npc();
  Npc(string name, int hp, int armor,bool agression,int att1,int att2, int att3,string att1_N,string att2_N,string att3_N);
  bool getAgression();
  int getAttack(int num);
  string getAttackName(int num);

  void setAgression(bool agression);
  void setAttack1(int attack1);
  void setAttack2(int attack2);
  void setAttack3(int attack3);
  void setAttack1Name(string attack1Name);
  void setAttack2Name(string attack2Name);
  void setAttack3Name(string attack3Name);
};
#endif