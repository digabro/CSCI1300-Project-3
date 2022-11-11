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
        Person(string name, int hp, int armor);
        string getName();
        int getHp();
        int getArmor();

        void setName(string name);
        void setHp(int hp);
        void setArmor(int armor);
};

#endif