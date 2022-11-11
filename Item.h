#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
//added this so all items can be under one class for the item vector in the inventory class
class Item{
private:
    string ItemType_; //what type of item ex: Weapon,Armor,Food,Random
    string ItemName_; //name of item ex: Slingshot, Cup of Noodles
    int ItemCost_; //how much an item costs in a shop
    int ItemIndex_; //index of item in inventory vector
    int damage_; //if the item does damage, how much damage is done
    int durability_; //how much usage the item can have ----can be removed if we want to
    int protection_; //how much protection a piece of armor has
    int quantity_;
    int max_quantity_;

public:
    //default constructor
    Item();
    //parameterized constructor
    Item(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int damage_,int protection_,int durability_,int max_quantity_,int quantity_);
    //getters
    string getItemName();
    string getItemType();
    int getProtection();
    int getDamage();
    int getDurability();
    int getQuantity();
    int getMaxQuantity();
    //setters 
    void setItemName(string ItemName_);
    void setItemCost(int ItemCost_);
    void setDamage(int damage_);
    void setDurability(int durability_);
    void setProtection(int damage_);
    void setQuantity(int quantity);
    void setMaxQuantity(int maxQuantity);
};

/*We can change this if needed, the idea for this is to have each specific item like weapons armor or other random stuff be used
and then we can have a Item vector in the inventory class to store all inventory items in one vector.*/


#endif