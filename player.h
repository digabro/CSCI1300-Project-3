//Lachlan Kotarski and Diego Olin 

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "person.h"
using namespace std;

class Player : public Person{
    private:
        bool doesKingWookTrustThe;
        int classes_passed_;
        int fights_won_;
        int skill_level_;
        static const int max_skill_level_=100;//add in max level
    public:
        Player();
        Player(string name,int hp,int armor,int skillLevel);
        int getSkillLevel();
        int getMaxSkillLevel();
        int getClassesPasses();
        int getFightsWon();
        bool getKingWookTrust();

        void setKingWookTrust(bool trust);
        void setClassesPassed(int classes);
        void setFightsWon(int fights);
        void setSkillLevel(int skillLevel);
};

#endif