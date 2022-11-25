#include "Inventory.h"
#include "Item.h"
#include "location.h"
#include "map.h"
#include "npc.h"
#include "person.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

bool printInventory(Inventory inv,string type){
    int count=0;
    cout<<endl<<type<<" items in your inventory:"<<endl;
    for (int i=0;i<inv.getNumItems();i++){
        if (inv.getItem(i).getItemType()==type){
            count++;
            cout<<count<<". "<<inv.getItem(i).getItemName()<<" - "<<inv.getItem(i).getQuantity()<<"/"<<inv.getItem(i).getMaxQuantity()<<endl;
        }
    }
    if (type=="Food"){
        if (inv.getPedialyte()>0){
            cout<<"1. "<<"Pedialyte - "<<inv.getPedialyte()<<"/4"<<endl;
            count++;
        }
        if (inv.getEnergyDrink()>0){
            cout<<"2. "<<"Energy Drink - "<<inv.getEnergyDrink()<<"/2"<<endl;
            count++;
        }
        if (inv.getMuscleMilk()>0){
            cout<<"3. "<<"Muscle Milk - "<<inv.getMuscleMilk()<<"/1"<<endl;
            count++;
        }
        if (inv.getCupOfNoodles()>0){
            cout<<"4. "<<"Cup of Noodles - "<<inv.getCupOfNoodles()<<"/5"<<endl;
            count++;
        }
        
    }
    if (count>0){
        return true;
    }
    else{
        return false;
    }
}

void printFile(string file_name){
    ifstream inFile;
    inFile.open(file_name);
    string line;
    
    if(inFile.is_open()){
        while(getline(inFile, line))
        {
            cout << line << endl;
        }
    } 
    else{
        cout << "Could not open file." << endl;
        return;
    }
    inFile.close();
    return;
}

int main(){


// cout << "  _________  __              _____  _____          _                                 _   _              ____  ____                 _    __        " << endl; 
// cout << " |  _   _  |[  |            |_   _||_   _|        (_)                               (_) / |_           |_   ||   _|               / |_ [  |       " << endl;
// cout << " |_/ | | \_||  |--.  .---.    | |    | |  _ .--.   __  _   __  .---.  _ .--.  .--.   __ `| |-' _   __    | |__| |   __   _   .--.`| |-'| | .---. " << endl;
// cout << "     | |     | .-. |/ /__\\   | '    ' | [ `.-. | [  |[ \ [  ]/ /__\\[ `/'`\]( (`\] [  | | |  [ \ [  ]   |  __  |  [  | | | ( (`\]| |  | |/ /__\\"  << endl;
// cout << "    _| |_    | | | || \__.,    \ \__/ /  | |  | |  | | \ \/ / | \__., | |     `'.'.  | | | |,  \ '/ /   _| |  | |_ | \_/  |, `'.'.| |, | || \__.,"  << endl;
// cout << "   |_____|  [___]|__]'.__.'     `.__.'  [___| |__][___] \__/   '.__.'[___]   [\__) )[___]\__/[\_:__/   |____||____|'.__.'_/[\__) )\__/[___]'.__.'"  << endl;

char option;
Map mapObject=Map();
Inventory inventory =Inventory(50,0,0,0,0);
while(option != 'Q')
{
    mapObject.displayMap();

    cout << "======Main Menu======" << endl;
    cout << "W: Move Upwards" << endl; 
    cout << "A: Move Left" << endl; 
    cout << "S: Move Downwards" << endl; 
    cout << "D: Move Right" << endl; 
    cout << "E: Inventory" << endl; 
    cout << "I: Investigate" << endl;
    cout << "R: Rules and directions" << endl;
    cout << "Q: Quit game" << endl;
    cout << "Choose one of the options above." << endl;
    cin >> option;
    system("clear");
    switch(tolower(option))
    {
        case 'w':{
            mapObject.move('w');
        }
        break;
        case 'a':{
            mapObject.move('a');
        }
        break;
        case 's':{
            mapObject.move('s');
        }
        break;
        case 'd':{
            mapObject.move('d');
        }
        break;
        case 'e':{
            string temp;
            system("clear");
            cout<<"======Inventory======"<<endl;
            if(!printInventory(inventory,"Weapon")){
                cout<<"No Weapons Stored in Inventory."<<endl;
            }
            if(!printInventory(inventory,"Armor")){
                cout<<"No Armor Stored in Inventory."<<endl;
            }
            if(!printInventory(inventory,"Food")){
                cout<<"No Food Stored in Inventory."<<endl;
            }
            cout<<"\nClick any button to continue..."<<endl;
            cin>>temp;
        }
        break;
        case 'i':{
            /*
            Open investigate menu(maybe make inv)
            * search for money
            * search for wildlife
            * search for supplies 
            */
        }
        break;
        case 'r':{
            printFile("rules.txt");
        }
        break;
        case 'q':{
            cout << "Better luck next time!" << endl;
            return 0;
        }break;
        default:{
            system("clear");
            cout << "Invalid input. Please try again." << endl;
        }
    }
}
return 0;
}