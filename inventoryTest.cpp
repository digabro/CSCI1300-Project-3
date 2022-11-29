//Lachlan Kotarski and Diego Olin 

#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "Inventory.h"
#include "Item.h"
#include "location.h"
#include "person.h"
#include "npc.h"
#include "player.h"
//compile command for ease of use:
//g++ -std=c++17 Inventory.cpp Item.cpp location.cpp person.cpp npc.cpp player.cpp inventoryTest.cpp
using namespace std;

/*
 * Algorithm: prints inventory based on item type given
 * Prints item type to display
 * loop i from 0 to num_items
 *      Checks if item is given type
 * prints the item and number of items   
 * if type is food
 *      prints food and amounts of food 
 */
void printInventory(Inventory inv,string type){
    cout<<type<<" items in your inventory:"<<endl;
    for (int i=0;i<inv.getNumItems();i++){
        if (inv.getItem(i).getItemType()==type){
            cout<<inv.getItem(i).getItemName()<<" - "<<inv.getItem(i).getQuantity()<<"/"<<inv.getItem(i).getMaxQuantity()<<endl;
        }
    }
    if (type=="Food"){
        cout<<"Pedialyte - "<<inv.getPedialyte()<<"/4"<<endl;
        cout<<"Energy Drink - "<<inv.getEnergyDrink()<<"/2"<<endl;
        cout<<"Muscle Milk - "<<inv.getMuscleMilk()<<"/1"<<endl;
        cout<<"Cup of Noodles - "<<inv.getCupOfNoodles()<<"/5"<<endl;
    }
}

/*
 * Displays the Farrand market location
 * Algorithm: Gets item index and checks if player is able to purchase the item
 * Welcomes player to the market and displays avaliable items 
 * checks if the player has enough money
 *      if not prints they dont have enough money 
 * if they havent purchased the max amount of items allows them to purchase one
 * and then repeats back to the top until the player exits 
*/
void farrandMarket(Inventory inv){
    int item;
    int num;
    bool farrMark=true;
    while (farrMark){
        bool validInput=true;
        cout<<"Welcome to Farrand Market\nCurrent money: "<<inv.getBuffBucks()<<"\n\nItems to buy:"<<endl;
        cout<<"1.Pedialyte - $3\n2.Energy Drink - $3\n3.Muscle Milk - $3";
        cout<<"\n4.Cup of Noodles - $3\n5.Exit\nSelect an item: ";
        while(validInput){
            cin>>item;
            if (inv.getBuffBucks()<3&&item<=4&&item>=1){
                system("clear");
                cout<<"You do not have enough Buff Bucks to purchase this.\n"<<endl;
                break;
            }
            switch(item){
                case 1:{
                        system("clear");
                    if (inv.setPedialyte(inv.getPedialyte()+1)){
                        inv.setBuffBucks(inv.getBuffBucks()-3);
                        cout<<"Successfully Purchased 1 Pedialyte\n"<<endl;
                    }
                    validInput=false;
                }break;
                case 2:{
                        system("clear");
                    if (inv.setEnergyDrink(inv.getEnergyDrink()+1)){
                        inv.setBuffBucks(inv.getBuffBucks()-3);
                        cout<<"Successfully Purchased 1 Energy Drink\n"<<endl;
                    }
                    validInput=false;
                }break;
                case 3:{
                        system("clear");
                    if (inv.setMuscleMilk(inv.getMuscleMilk()+1)){
                        inv.setBuffBucks(inv.getBuffBucks()-3);
                        cout<<"Successfully Purchased 1 Muscle Milk\n"<<endl;
                    }
                    validInput=false;
                }break;
                case 4:{
                    system("clear");
                    if (inv.setCupOfNoodles(inv.getCupOfNoodles()+1)){
                        inv.setBuffBucks(inv.getBuffBucks()-3);
                        cout<<"Successfully Purchased 1 Cup Of Noodles\n"<<endl;
                    }
                    validInput=false;
                }break;
                case 5:{
                    cout<<"Thank you for visiting Farrand Market\n"<<endl;
                    farrMark=false;
                    validInput=false;
                }break;
                default:{
                    cout<<"Invalid Input"<<endl;
                }
            } 
        }
    }
}


int main(){
    string name;
    cout<<"Please enter your name: ";
    cin>>name;
    Player player=Player(name,20,0,0);//defining player object
    Inventory inv =Inventory(50,0,0,0,0); //defining player inventory 
    //adding armor items to inventory array with quantity of 0
    Item csChestplate =Item("CS Chestplate","Armor",0,inv.getNumItems(),0,6,60,1,0);
    Item englishHelm =Item("English Helmet","Armor",0,inv.getNumItems(),0,4,40,1,0);
    Item historyHelm =Item("History Helmet","Armor",0,inv.getNumItems(),0,4,40,1,0);
    Item cowboyHat =Item("Cowboy Hat","Armor",0,inv.getNumItems(),0,4,40,1,0);
    Item hoodie =Item("Hoodie","Armor",9,inv.getNumItems(),0,3,30,1,0);
    Item sweatpants =Item("Sweatpants","Armor",6,inv.getNumItems(),0,2,20,1,0);
    Item sandals =Item("Sandals","Armor",3,inv.getNumItems(),0,1,10,1,0);
    Item sunglasses =Item("Sunglasses","Armor",3,inv.getNumItems(),0,1,10,1,0);
    //adding weapon items to inventory array with quantity of 0
    Item pencils =Item("Pencils","Weapon",0,inv.getNumItems(),2,0,-1,1,0);
    Item scissors =Item("Scissors","Weapon",0,inv.getNumItems(),3,0,-1,1,0);
    Item bottle =Item("Broken Bottle","Weapon",0,inv.getNumItems(),1,0,-1,1,0);
    Item paddle =Item("Abandoned Paddle","Weapon",0,inv.getNumItems(),1,0,-1,1,0);
    inv.addItem(csChestplate);
    inv.addItem(englishHelm);
    inv.addItem(historyHelm);
    inv.addItem(cowboyHat);
    inv.addItem(hoodie);
    inv.addItem(sweatpants);
    inv.addItem(sandals);
    inv.addItem(sunglasses);
    inv.addItem(pencils);
    inv.addItem(scissors);
    inv.addItem(bottle);
    inv.addItem(paddle);
    inv.setBuffBucks(20);
    
    // printInventory(inv,"Weapon");
    farrandMarket(inv);
    return 0;
}