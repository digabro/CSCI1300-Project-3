#ifndef FOOD_H
#define FOOD_H
#include <iostream>
#include <string>
#include "inventory.h"
#using namespace std;

class Food : public Inventory{
    private:
        string Effect_;
        int EffectTime_;
    public:
        Food(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,string Effect_,int EffectTime_,);//add a food item
        string getEffect();
        int getEffectTime();
        void setEffect(string Effect_);
        void setEffectTime(int EffectTime_);
    
};

#endif
