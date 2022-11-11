#include "player.h"
#include <iostream>
using namespace std;

Player::Player()
{
    name_ = "";
    hp_ = 0;
    armor_ = 0;
    skill_level_=0;
}
Player::Player(string name, int hp, int armor,int skill)
{
    name_ = name;
    hp_ = hp;
    armor_ = armor;
    skill_level_=skill;
}

int Player::getSkillLevel(){ 
  return skill_level_; 
}
int Player::getMaxSkillLevel(){ 
  return max_skill_level_;
}

void Player::setSkillLevel(skillLevel){ 
  skill_level_ = skillLevel; 
}

