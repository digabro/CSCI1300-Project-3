#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#using namespace std;

class Inventory{
private:
    string ItemType_;
    int ItemCost_;
    int ItemIndex_
public:
    Inventory();
    getItem(int ItemIndex_);
    getItemType(int ItemIndex_);

};