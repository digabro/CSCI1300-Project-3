#ifndef FOOD_H
#define FOOD_H
#include<iostream>
#include "inventory.h"
#using namespace std;

class Food : public Inventory{
private:
    string Effect_;
public:
    string getEffect(int ItemIndex_);
    void setEffect(int ItemIndex_);

};