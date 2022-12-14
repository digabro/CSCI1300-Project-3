//Lachlan Kotarski and Diego Olin 

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
    pedialyte_active_=false;
    energy_drink_active_=false;
    muscle_milk_active_=false;
    cup_of_noodles_active_=false;
} 
Inventory::Inventory(int in_buff_bucks, int in_pedialyte, int in_energy_drink, int in_muscle_milk, int in_cup_of_noodles)
{
    num_buff_bucks = in_buff_bucks; 
    num_pedialyte = in_pedialyte; 
    num_energy_drink = in_energy_drink;
    num_muscle_milk = in_muscle_milk;  
    num_cup_of_noodles = in_cup_of_noodles;
    pedialyte_active_=false;
    energy_drink_active_=false;
    muscle_milk_active_=false;
    cup_of_noodles_active_=false;
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
int Inventory::getNumItems(){
    return num_items;
}
Item Inventory::getItem(int index){
    if(index>=0&&index<=num_items){
        return item_list[index];
    }
    else if(index<0){
        return getItem(index+1); // change: added return
    }
    else{
        return getItem(index-1); // change: added return
    }
}

//mutators
void Inventory::setBuffBucks(int in_buff_bucks)
{
    if(in_buff_bucks > max_buff_bucks)
    {
        cout << max_buff_bucks <<" is the maximum amount of Buff Bucks that can be stored in your inventory.\n" << endl;
        num_buff_bucks = max_buff_bucks;
        return; 
    }
    num_buff_bucks = in_buff_bucks;
    return;
}
bool Inventory::setPedialyte(int in_pedialyte)
{
    if(in_pedialyte > max_pedialyte)
    {
        cout << max_pedialyte <<" is the maximum amount of pedialyte that can be stored in your inventory.\n" << endl;
        num_pedialyte = max_pedialyte;
        return false;
    }
    num_pedialyte = in_pedialyte;
    return true;
}
bool Inventory::setEnergyDrink(int in_energy_drink)
{
    if(in_energy_drink >max_energy_drink)//energy drink is the same thing as redbull
    {
        cout << max_energy_drink <<" is the maximum amount of Redbull that can be stored in your inventory.\n" << endl;
        int num_energy_drink = max_energy_drink;
        return false;
    }
    int num_energy_drink = in_energy_drink;
    return true;
}
bool Inventory::setMuscleMilk(int in_muscle_milk)
{
    if(in_muscle_milk > max_muscle_milk)
    {
        cout << max_muscle_milk << " is the maximum amount of muscle milk that can be stored in your inventory.\n" << endl;
        num_muscle_milk = max_muscle_milk;
        return false;
    }
    num_muscle_milk = in_muscle_milk;
    return false;
}
bool Inventory::setCupOfNoodles(int in_cup_of_noodles)//cup of noodles is basically the same thing as ramen
{
    if(in_cup_of_noodles > max_cup_of_noodles)
    {
        cout << max_cup_of_noodles <<" is the maximum amount of Ramen Chicken Noodle soup that can be stored in your inventory.\n" << endl;
        num_cup_of_noodles = max_cup_of_noodles;
        return false;
    }
    num_cup_of_noodles = in_cup_of_noodles;
    return false;

}

void Inventory::setNumItems(int items){
    num_items=items;
}
//adding a function to append item array but doesnt currently work
//is supposed to check if item is in the array and if not add it to the end 
//if it is in the array its supposed to add one to the item quantity

void Inventory::addItem(Item item){
    int index=-1;
    for (int i=0;i<num_items;i++){
        if (item_list[i].getItemName() == item.getItemName()){
            index=i;
            break;
        }
    }
    if (index!=-1){
        item_list[index].setQuantity(item_list[index].getQuantity()+ 1);
    }
    else if(index==-1){
        item_list[num_items]=item;
        num_items++;
        item.setQuantity(0);
    }
}

//this function is supposed to check if a player has enough room and buff bucks to purchace an item
//doesnt work becuase addItem() isnt currently functioning 

bool Inventory::buyItem(Item item){
    if (num_buff_bucks >= item.getItemCost()&&item.getQuantity()<item.getMaxQuantity()){
        addItem(item);
        num_buff_bucks-=item.getItemCost();
        cout<<"Successfully Purchased 1 "<<item.getItemName()<<endl<<endl;
        return true;
    }
    else if(num_buff_bucks<item.getItemCost()){
        cout<<"You dont have enough Buff Bucks to purchase "<<item.getItemName()<<"."<<endl;
    }
    else if(item.getQuantity()>=item.getMaxQuantity()){
        cout<<"You have purchased the maximum amount of"<<item.getItemName()<<" possible." <<endl;
    }
    return false;
}


bool Inventory::activateFood(string item){
    if(item=="Pedialyte"){
        pedialyte_active_=true;
    }
    else if(item=="Cup Of Noodles"){
        cup_of_noodles_active_=true;
    }
    else if(item=="Muscle Milk"){
        muscle_milk_active_=true;
    }
    else if(item=="Energy Drink"){
        energy_drink_active_=true;
    }
    else{
        return false;
    }
    return true;
}
void Inventory::deactivateFood(string item){
    if(item=="Pedialyte"){
        pedialyte_active_=false;
    }
    else if(item=="Cup Of Noodles"){
        cup_of_noodles_active_=false;
    }
    else if(item=="Muscle Milk"){
        muscle_milk_active_=false;
    }
    else if(item=="Energy Drink"){
        energy_drink_active_=false;
    }
}
bool Inventory::isActive(string item){
    if(item=="Pedialyte"){
        if(pedialyte_active_){
            return true;
        }
    }
    else if(item=="Cup Of Noodles"){
        if(cup_of_noodles_active_){
            return true;
        }
    }
    else if(item=="Muscle Milk"){
        if(muscle_milk_active_){
            return true;
        }
    }
    else if(item=="Energy Drink"){
        if(energy_drink_active_){
            return true;
        }
    } 
    return false;
}