#ifndef INVENTORY.H
#define INVENTORY
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
using namespace std;
//should it be inventory or Health_Armor
class Inventory
{
    public: 
    //default constructors
    Inventory();
    //parameterized constructor
    Inventory(int num_buff_bucks, int num_pedialyte, int num_energy_drink, int num_muscle_milk, int num_cup_of_noodles);

    //accessors
    int getBuffBucks();
    int getPedialyte();
    int getEnergyDrink();
    int getMuscleMilk(); 
    int getCupOfNoodles();

    //mutators
    void setBuffBucks(int num_buff_bucks);
    void setPedialyte(int num_pedialyte);
    void setEnergyDrink(int num_energy_drink);
    void setMuscleMilk(int num_muscle_milk); 
    void setCupOfNoodles(int num_cup_of_noodles);
    //added this for manipulating the item array
    void addItem(string ItemName_,string ItemType_,int ItemCost_,int ItemIndex_,int damage_,int protection_,int durability_);
    bool buyItem(Item item,int cost);
    // printInventory(); ------------add this in after code skelly

    private:
    // do we set these values equal to the amount of them we have in our inventory or do we set it to the amount of health/armor or damage it gives you
    int num_buff_bucks; // in game currency
    int num_pedialyte; // health potion regenerate vitamins and minerals lost during sickness
    int num_energy_drink; // speed/haste potion
    int num_muscle_milk;  // strength potion
    int num_cup_of_noodles; // food
    int num_items; //amount of items in inventory
    static const int max_buff_bucks = 25000; // max amount of money
    static const int max_pedialyte = 4;
    static const int max_energy_drink = 2;
    static const int max_muscle_milk = 1;
    static const int max_cup_of_noodles = 5; 
    static const int max_items =15; 
    Item item_list[max_items]; //added list of inventory items      
    

/*
should would stack items and make unstackable items like minecraft or should 
we make different slots for each kind of items there are in the game.
Ex:
Inventory(int num_buff_bucks, int num_pedialyte, int num_energy_drink, int num_muscle_milk, int num_cup_of_noodles);
i think we need to set a max for each item in the private part of the inventory class. 
*/

};
#endif
