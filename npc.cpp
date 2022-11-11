#include "npc.h"
#include <iostream>
using namespace std;

Npc::Npc()
{
    name_ = "";
    hp_ = 0;
    armor_ = 0;
    agression_=false;
    attack1_=0;
    attack2_=0;
    attack3_=0;
}
Npc::Npc(string name, int hp, int armor,bool agression,int att1,int att2, int att3)
{
    name_ = name;
    hp_ = hp;
    armor_ = armor;
    agression_=agression;
    attack1_=att1;
    attack2_=att2;
    attack3_=att3;
}

int Npc::getAgression(){ 
  return agression_; 
}
int Npc::getAttack1(){ 
  return attack1_; 
}
int Npc::getAttack2(){ 
  return attack2_; 
}
int Npc::getAttack3(){ 
  return attack3_; 
}

void Npc::setAgression(bool agression){
  agression_=agression;
}
void Npc::setAttack1(int attack1){
  attack1_=attack1;
}
void Npc::setAttack2(int attack2){
  attack2_=attack2;
}
void Npc::setAttack3(int attack3){
  attack3_=attack3;
}