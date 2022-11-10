#ifndef ARMOR_H
#define ARMOR_H
#include<iostream>
#include "inventory.h"
#using namespace std;

class Armor : public Inventory{
    private:
        int protection_;
        int durability_;
        string item_name_;
        string item_type_;
        int item_cost_;
        
    public:
        Armor(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int protection_,int durability_,);//add a armor item
        int getProtection();
        int getDurability();
        void setProtection(int damage_);
        void setDurability(int durability_);

};
