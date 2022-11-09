#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#using namespace std;

class Inventory{
private:
    string ItemType_;
    string ItemName_;
    int ItemCost_;
    int ItemIndex_
public:
    Inventory(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_);
    string getItemName(int ItemIndex_);
    string getItemType(int ItemIndex_);
    int getItemIndex(string ItemName_);
    void setItemName(string ItemName_,int ItemIndex_);
    void setItemCost(int ItemCost_,int ItemIndex_);
};