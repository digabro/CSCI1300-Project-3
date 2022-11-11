#ifndef NPC_H
#define NPC_H
#include <iostream>
#include "person.h"
using namespace std;

class Npc : public Person{
    private:
        int agression;
        int attack1;
        int attack2;
        int attack3;
    public:
        int getAgression();
        int getAttack1();
        int getAttack2();
        int getAttack3();

        void setAgression();
        void setAttack1();
        void setAttack2();
        void setAttack3();
};
 #endif