#ifndef WEAPON_H
#define WEAPON_H
#include<iostream>
#include "inventory.h"
#using namespace std;

class Weapon : public Inventory{
    private:
        int damage_;
        int durability_;
    public:
        Weapon(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int damage_,int durability_,);//add a weapon item
        int getDamage();
        int getDurability();
        void setDamage(int damage_);
        void setDurability(int durability_);
};


#endif