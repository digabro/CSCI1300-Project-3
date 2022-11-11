#include <iostream>
#include <string>
#include "Inventory.h"
#include "Item.h"

using namespace std;

Inventory::Inventory()
{
    int num_buff_bucks = 50; // in game currency
    int num_pedialyte = 0; // health potion regenerate vitamins and minerals lost during sickness
    int num_energy_drink = 0; // speed/haste potion
    int num_muscle_milk = 0;  // strength potion
    int num_cup_of_noodles = 0; // food
} 
Inventory::Inventory(int in_buff_bucks, int in_pedialyte, int in_energy_drink, int in_muscle_milk, int in_cup_of_noodles)
{
    num_buff_bucks = in_buff_bucks; 
    num_pedialyte = in_pedialyte; 
    num_energy_drink = in_energy_drink;
    num_muscle_milk = in_muscle_milk;  
    num_cup_of_noodles = in_cup_of_noodles;
}
int Inventory::getBuffBucks()
{
    return num_buff_bucks;
}
int Inventory::getPedialyte()
{
    return num_pedialyte;
}
int Inventory::getEnergyDrink()
{
    return num_energy_drink;
}
int Inventory::getMuscleMilk()
{
    return num_muscle_milk;
}
int Inventory::getCupOfNoodles()
{
    return num_cup_of_noodles;
}

//mutators
int Inventory::setBuffBucks(int in_buff_bucks)
{
    if(in_buff_bucks > max_buff_bucks)
    {
        cout << max_buff_bucks <<" is the maximum amount of Buff Bucks that can be stored in your inventory." << endl;
        return max_buff_bucks;
    }
    return in_buff_bucks;
}
int Inventory::setPedialyte(int in_pedialyte)
{
    if(iin_pedialyte > max_pedialyte)
    {
        cout << max_pedialyte <<" is the maximum amount of pedialyte that can be stored in your inventory." << endl;
        return max_pedialyte;
    }
    return in_pedialyte;

}
int Inventory::setEnergyDrink(int in_energy_drink)
{
    if(in_energy_drink >max_energy_drink)//energy drink is the same thing as redbull
    {
        cout << max_energy_drink <<" is the maximum amount of Redbull that can be stored in your inventory." << endl;
        return max_energy_drink;
    }
    return in_energy_drink;

}
int Inventory::setMuscleMilk(int in_muscle_milk)
{
    if(in_muscle_milk > max_muscle_milk)
    {
        cout << max_muscle_milk << " is the maximum amount of muscle milk that can be stored in your inventory." << endl;
        return  max_muscle_milk;
    }
    return in_muscle_milk;

}
int Inventory::setCupOfNoodles(int in_cup_of_noodles)//cup of noodles is basically the same thing as ramen
{
    if(in_cup_of_noodles > max_cup_of_noodles)
    {
        cout << max_cup_of_noodles <<" is the maximum amount of Ramen Chicken Noodle soup that can be stored in your inventory." << endl;
        return max_cup_of_noodles;
    }
    return in_cup_of_noodles;

}
void Inventory::addItem(string Item){
    item_list[num_items]=Item(ItemName,ItemType,ItemCost,num_items,damage,protection,durability);
    
}

bool buyItem(Item item,int cost){
    if (num_buff_bucks>=cost&&item.getQuantity()<item.getMaxQuantity()){
        Item
    }
}
