#ifndef FOOD_H
#define FOOD_H
#include<iostream>
#include "inventory.h"
#using namespace std;

class Food : public Inventory{
private:
    string Effect_;
    int EffectTime_;
public:
    addFood(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,string Effect_,int EffectTime_,);//add a food item
    string getEffect(int ItemIndex_);
    int getEffectTime(int ItemIndex_);
    void setEffect(int ItemIndex_,string Effect_);
    void setEffectTime(int ItemIndex_,int EffectTime_);
    
};