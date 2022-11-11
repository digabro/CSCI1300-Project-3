#include "player.h"
#include <iostream>
using namespace std;

Player::Player()
{
    Person::setName("");
    Person::setHp(0);
    Person::setArmor(0);
    skill_level_=0;
}
Player::Player(string name, int hp, int armor,int skill)
{
    Person::setName(name);
    Person::setHp(hp);
    Person::setArmor(armor);
    skill_level_=skill;
}

int Player::getSkillLevel(){ 
  return skill_level_; 
}
int Player::getMaxSkillLevel(){ 
  return max_skill_level_;
}

void Player::setSkillLevel(int skillLevel){ 
  skill_level_ = skillLevel; 
}

