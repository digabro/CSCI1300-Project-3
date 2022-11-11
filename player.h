#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "person.h"
using namespace std;

class Player : public Person{
    private:
        int skill_level_;
        int max_skill_level_;
    public:
        int getSkillLevel();
        int getMaxSkillLevel();

        void setSkillLevel();
        void setMaxSkillLevel();
};

#endif