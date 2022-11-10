#include <iostream>
#include <string>
#include "Inventory.h"

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
        return max_buff_bucks;
    }
    return in_buff_bucks;
}
int Inventory::setPedialyte(int in_pedialyte)
{
    if(iin_pedialyte > max_pedialyte)
    {
        return max_pedialyte;
    }
    return in_pedialyte;

}
int Inventory::setEnergyDrink(int in_energy_drink)
{
    if(in_energy_drink >max_energy_drink)
    {
        return max_energy_drink;
    }
    return in_energy_drink;

}
int Inventory::setMuscleMilk(int in_muscle_milk)
{
    if(in_muscle_milk > max_muscle_milk)
    {
        return  max_muscle_milk;
    }
    return in_muscle_milk;

}
int Inventory::setCupOfNoodles(int in_cup_of_noodles)
{
    if(in_cup_of_noodles > max_cup_of_noodles)
    {
        return max_cup_of_noodles;
    }
    return in_cup_of_noodles;

}

