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
                    system("clear");
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


// cout << "  _________  __              _____  _____          _                                 _   _              ____  ____                 _    __        " << endl; 
// cout << " |  _   _  |[  |            |_   _||_   _|        (_)                               (_) / |_           |_   ||   _|               / |_ [  |       " << endl;
// cout << " |_/ | | \_||  |--.  .---.    | |    | |  _ .--.   __  _   __  .---.  _ .--.  .--.   __ `| |-' _   __    | |__| |   __   _   .--.`| |-'| | .---. " << endl;
// cout << "     | |     | .-. |/ /__\\   | '    ' | [ `.-. | [  |[ \ [  ]/ /__\\[ `/'`\]( (`\] [  | | |  [ \ [  ]   |  __  |  [  | | | ( (`\]| |  | |/ /__\\"  << endl;
// cout << "    _| |_    | | | || \__.,    \ \__/ /  | |  | |  | | \ \/ / | \__., | |     `'.'.  | | | |,  \ '/ /   _| |  | |_ | \_/  |, `'.'.| |, | || \__.,"  << endl;
// cout << "   |_____|  [___]|__]'.__.'     `.__.'  [___| |__][___] \__/   '.__.'[___]   [\__) )[___]\__/[\_:__/   |____||____|'.__.'_/[\__) )\__/[___]'.__.'"  << endl;

char option;
Map mapObject=Map();
Inventory inventory =Inventory(50,0,0,0,0);

mapObject.addMarket(6,15);//farrand market


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
            system("clear");
        }
        break;
        case 'i':{
            //when the player investigates a space check if its a room to run the room code
            if(mapObject.isMarketLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())){
                farrandMarket(inventory);
            }

            //will likely move random things to a function to make it easier but gotta go for now
            int randNum = rand() % 100;//rand num from 0 to 99
            if (randNum>=0&&randNum<5){//found money
                int randmoney=rand()%10;//0 to 9 bucks --can be changed if you want
                system("clear");
                cout<<"While Investigating, you found $"<<randmoney<<".00"<<endl;
            }

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
    //if the input was any movement key, check if the space that was moved onto is an enemy space
    if(mapObject.isNPCLocation(mapObject.getPlayerRow(),mapObject.getDungeonExitCol())){

    }

}
return 0;
}