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
        addWeapon(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int damage_,int durability_,);//add a weapon item
        int getDamage(int ItemIndex_);
        int getDurability(int ItemIndex_);
        void setDamage(int ItemIndex_,int damage_);
        void setDurability(int ItemIndex_,int durability_);
};