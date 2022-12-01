//Lachlan Kotarski and Diego Olin 

#include "player.h"
#include <iostream>
using namespace std;

Player::Player()
{
    Person::setName("");
    Person::setHp(0);
    Person::setArmor(0);
    skill_level_=0;
    classes_passed_=0;
    fights_won_=0;
}
Player::Player(string name, int hp, int armor,int skill)
{
    Person::setName(name);
    Person::setHp(hp);
    Person::setArmor(armor);
    skill_level_=skill;
    classes_passed_=0;
    fights_won_=0;
}

int Player::getSkillLevel(){ 
  return skill_level_; 
}
int Player::getMaxSkillLevel(){ 
  return max_skill_level_;
}
int Player::getClassesPasses(){
  return classes_passed_;
}
int Player::getFightsWon(){
  return fights_won_;
}
bool Player::getKingWookTrust(){
  return doesKingWookTrustThe;
}
void Player::setKingWookTrust(bool trust){
  doesKingWookTrustThe=trust;
}

void Player::setClassesPassed(int classes){
  classes_passed_=classes;
}
void Player::setFightsWon(int fights){
  fights_won_=fights;
}
void Player::setSkillLevel(int skillLevel){ 
  skill_level_ = skillLevel; 
}

