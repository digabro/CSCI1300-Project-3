//Lachlan Kotarski and Diego Olin 

#include "npc.h"
#include <iostream>
using namespace std;

Npc::Npc()
{
    Person::setName("");
    Person::setHp(0);
    Person::setArmor(0);
    agression_=false;
    attack1_=0;
    attack1_Name_="";
    attack2_=0;
    attack2_Name_="";
    attack3_=0;
    attack3_Name_="";
}
Npc::Npc(string name, int hp, int armor,bool agression,int att1,int att2, int att3,string att1_N,string att2_N,string att3_N)
{
    Person::setName(name);
    Person::setHp(hp);
    Person::setArmor(armor);
    agression_=agression;
    attack1_=att1;
    attack1_Name_=att1_N;
    attack2_=att2;
    attack2_Name_=att2_N;
    attack3_=att3;
    attack3_Name_=att3_N;
}

bool Npc::getAgression(){ 
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
string Npc::getAttack1Name(){
  return attack1_Name_;
}
string Npc::getAttack2Name(){
  return attack2_Name_;
}
string Npc::getAttack3Name(){
  return attack3_Name_;
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
void Npc::setAttack1Name(string attack1Name){
  attack1_Name_=attack1Name;
}
void Npc::setAttack2Name(string attack2Name){
  attack2_Name_=attack2Name;
}
void Npc::setAttack3Name(string attack3Name){
  attack3_Name_=attack3Name;
}