#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

Item(){}//not really needed i dunno if itll be fine to remove this
Item(string itemName,string itemType,int itemCost,int itemIndex,int damage,int protection,int durability){
    ItemName_=itemName;
    ItemType_=itemType;
    ItemCost_=itemCost;
    ItemIndex_=itemIndex;
    damage_=damage;
    protection_=protection;
    durability_=durability;
}
string Item::getItemName(){
    return ItemName_;
}
string Item::getItemType(){
    return ItemIndex_;
}
int Item::getItemIndex(){
    return ItemIndex_;
}
int Item::getProtection(){
    return protection_;
}
int Item::getDamage(){
    return damage_;
}
int Item::getDurability(){
    return durability_;
}
int Item::getQuantity(){
    return quantity_;
}
int Item::getMaxQuantity(){
    return max_quantity_;
}



void Item::setItemName(string itemName){
    ItemName_=itemName;
}
void Item::setItemCost(int itemCost){
    ItemCost_=itemCost;
}
void Item::setDamage(int damage){
    damage_=damage;
}
void Item::setDurability(int durability){
    durability_=durability;
}
void Item::setProtection(int damage){
    damage_=damage;
}
void Item::setQuantity(int quantity){
    quantity_=quantity;
}
void Item::setMaxQuantity(int maxQuantity){
    max_quantity_=maxQuantity;
}