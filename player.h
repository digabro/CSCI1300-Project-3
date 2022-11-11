#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "person.h"
using namespace std;

class Player : public Person{
    private:
        int skill_level_;
        static const int max_skill_level_=100;//add in max level
    public:
        Player();
        Player(string name,int hp,int armor,int skillLevel);
        int getSkillLevel();
        int getMaxSkillLevel();

        void setSkillLevel();
        void setMaxSkillLevel();
};

#endif