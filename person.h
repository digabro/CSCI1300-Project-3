#ifndef PERSON_H
#define PERSON_H
#include <iostream>
using namespace std;

class Person{
    private:
        string name_;
        int hp_;
        int armor_;
    public:
        Person();
        string getName();
        int getHp();
        int getArmor();

        void setName();
        void setHp();
        void setArmor();
};

#endif