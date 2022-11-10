#include "armor.h"
#include "inventory.h"
#include <iostream>
#using namespace std;

addArmor(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int damage_,int durability,int protection){
    protection_ = protection;
    durability_ = durability;
    item_name_ = ItemName_;
    item_type_ = ItemType_;
    item_cost_ = ItemCost_;

}
int getProtection(){
    return protection_;
}
int getDurability(){
    return durability_;
}
void setProtection(int protection){
    protection_=protection;
}
void setDurability(int durability){
    durability_=durability;
}
