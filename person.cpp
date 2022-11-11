#include <iostream>
#include "person.h"
using namespace std;

Person::Person()
{
    name_ = "";
    hp_ = 0;
    armor_ = 0;
}
Person::Person(string name, int hp, int armor)
{
    name_ = name;
    hp_ = hp;
    armor_ = armor;
}
string Person::getName()
{
    return name_;
}
int Person::getHp()
{
    return hp_;
}
int Person::getArmor()
{
    return armor_;    
}

void Person::setName(string name)
{
    name_ = name;
    return;
}
void Person::setHp(int hp)
{
    hp_ = hp;
    return;
}
void Person::setArmor(int armor)
{
    armor_ = armor;
    return;
}