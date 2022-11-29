#include "Inventory.h"
#include "Item.h"
#include "location.h"
#include "map.h"
#include "npc.h"
#include "person.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

bool printInventory(Inventory inv,string type){
    int count=0;
    cout<<endl<<type<<" items in your inventory:"<<endl;
    for (int i=0;i<inv.getNumItems();i++){
        if (inv.getItem(i).getItemType()==type){
            if (inv.getItem(i).getQuantity()>0){
                count++;
                cout<<count<<". "<<inv.getItem(i).getItemName()<<" - "<<inv.getItem(i).getQuantity()<<"/"<<inv.getItem(i).getMaxQuantity()<<endl;
            }
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

bool isNearEnemy(int row,int col,Map map){
    if (map.isBanditCampLocation(map.getPlayerRow(),(map.getPlayerCol()+1))||map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()+1))){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()+1),map.getPlayerCol())||map.isCultistLocation((map.getPlayerRow()+1),map.getPlayerCol())){
        return true;
    }
    else if (map.isBanditCampLocation(map.getPlayerRow(),(map.getPlayerCol()-1))||map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()-1))){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()-1),map.getPlayerCol())||map.isCultistLocation((map.getPlayerRow()-1),map.getPlayerCol())){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()+1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()+1),(map.getPlayerCol()+1))){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()-1),(map.getPlayerCol()-1))||map.isCultistLocation((map.getPlayerRow()-1),map.getPlayerCol()-1)){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()-1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()-1),(map.getPlayerCol()+1))){
        return true;
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()+1),(map.getPlayerCol()-1))||map.isBanditCampLocation((map.getPlayerRow()+1),(map.getPlayerCol()-1))){
        return true;
    }
    return false;
}

void randomChances(Map map,Inventory inv,Item bottle){//use the bottle item when calling, needs it as an input to add it to the inventory as its not a global variable
    string animalList[4]={" Black Bear"," Mountain Lion"," Coyote","n Elk"};//supposed to have space before and "n elk"
    if(!map.isExplored(map.getPlayerRow(),map.getPlayerCol())){
        int randNum = rand() % 100;//rand num from 0 to 99
        if (randNum>=0&&randNum<5){//found money
            int randmoney=(rand()%9)+1;//1 to 10 bucks --can be changed if you want
            system("clear");
            cout<<"While investigating, you found $"<<randmoney<<".00"<<endl;
            inv.setBuffBucks(inv.getBuffBucks()+randmoney);
        }
        else if (randNum>=5&&randNum<25){//found broken bottle
            system("clear");
            if (bottle.getQuantity()< bottle.getMaxQuantity()){
                inv.buyItem(bottle);
                cout<<"While investigating, you found a broken bottle"<<endl;
            }
        }
        else if (randNum>=25&&randNum<45){//found raccoon
            system("clear");
            cout<<"While investigating, you encountered a raccoon"<<endl;
            //add in raccoon code
        }
        else if (randNum>=45&&randNum<55){//found broken bottle
            system("clear");
            string animal = animalList[(rand()%4)];
            cout<<"While investigating, you encountered a"<<animal<<endl;
            //add in animal code
        }
    }
}

int main(){
std::srand(time(NULL));//without the std:: this line was calling an error, not too sure why std:: fixed it

// cout << "  _________  __              _____  _____          _                                 _   _              ____  ____                 _    __        " << endl; 
// cout << " |  _   _  |[  |            |_   _||_   _|        (_)                               (_) / |_           |_   ||   _|               / |_ [  |       " << endl;
// cout << " |_/ | | \_||  |--.  .---.    | |    | |  _ .--.   __  _   __  .---.  _ .--.  .--.   __ `| |-' _   __    | |__| |   __   _   .--.`| |-'| | .---. " << endl;
// cout << "     | |     | .-. |/ /__\\   | '    ' | [ `.-. | [  |[ \ [  ]/ /__\\[ `/'`\]( (`\] [  | | |  [ \ [  ]   |  __  |  [  | | | ( (`\]| |  | |/ /__\\"  << endl;
// cout << "    _| |_    | | | || \__.,    \ \__/ /  | |  | |  | | \ \/ / | \__., | |     `'.'.  | | | |,  \ '/ /   _| |  | |_ | \_/  |, `'.'.| |, | || \__.,"  << endl;
// cout << "   |_____|  [___]|__]'.__.'     `.__.'  [___| |__][___] \__/   '.__.'[___]   [\__) )[___]\__/[\_:__/   |____||____|'.__.'_/[\__) )\__/[___]'.__.'"  << endl;

char option;
Map mapObject=Map();
Inventory inventory =Inventory(50,0,0,0,0);
//adding armor items to inventory array with quantity of 0
Item csChestplate =Item("CS Chestplate","Armor",0,inventory.getNumItems(),0,6,60,1,0);
Item englishHelm =Item("English Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
Item historyHelm =Item("History Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
Item cowboyHat =Item("Cowboy Hat","Armor",0,inventory.getNumItems(),0,4,40,1,0);
Item hoodie =Item("Hoodie","Armor",9,inventory.getNumItems(),0,3,30,1,0);
Item sweatpants =Item("Sweatpants","Armor",6,inventory.getNumItems(),0,2,20,1,0);
Item sandals =Item("Sandals","Armor",3,inventory.getNumItems(),0,1,10,1,0);
Item sunglasses =Item("Sunglasses","Armor",3,inventory.getNumItems(),0,1,10,1,0);
//adding weapon items to inventory array with quantity of 0
Item pencils =Item("Pencils","Weapon",0,inventory.getNumItems(),2,0,-1,1,0);
Item scissors =Item("Scissors","Weapon",0,inventory.getNumItems(),3,0,-1,1,0);
Item bottle =Item("Broken Bottle","Weapon",0,inventory.getNumItems(),1,0,-1,1,0);
Item paddle =Item("Abandoned Paddle","Weapon",0,inventory.getNumItems(),1,0,-1,1,0);
inventory.addItem(csChestplate);
inventory.addItem(englishHelm);
inventory.addItem(historyHelm);
inventory.addItem(cowboyHat);
inventory.addItem(hoodie);
inventory.addItem(sweatpants);
inventory.addItem(sandals);
inventory.addItem(sunglasses);
inventory.addItem(pencils);
inventory.addItem(scissors);
inventory.addItem(bottle);
inventory.addItem(paddle);


mapObject.addMarket(6,15);//farrand market

//adding bandit camps
int bRow,bCol;
for (int i=0;i<(rand()%2)+1;i++){//can be changed to i<2 so its not a random amount of bandit camps
    bRow = (rand()%11);
    bCol = (rand()%29);
    mapObject.addBanditCamp(bRow,bCol);
}
//adding cultist camps
for (int i=0;i<(rand()%4)+1;i++){//can be changed to i<5 so its not a random amount of cultists
    bRow = (rand()%11);
    bCol = (rand()%29);
    mapObject.addCultist(bRow,bCol);
}
//adding schools
for (int i=0;i<4;i++){
    bRow = (rand()%5)+6;
    bCol = (rand()%14)+15;
    mapObject.addSchool(bRow,bCol);
}


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
            cout<<"Buff Bucks: $"<<inventory.getBuffBucks()<<".00"<<endl;
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
            if(mapObject.isMarketLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())&&mapObject.getPlayerRow()==6&&mapObject.getPlayerCol()==15){
                int item;
                int num;
                bool farrMark=true;
                while (farrMark){
                    bool validInput=true;
                    cout<<"Welcome to Farrand Market\nCurrent money: "<<inventory.getBuffBucks()<<"\n\nItems to buy:"<<endl;
                    cout<<"1.Pedialyte - $3\n2.Energy Drink - $3\n3.Muscle Milk - $3";
                    cout<<"\n4.Cup of Noodles - $3\n5.Exit\nSelect an item: ";
                    while(validInput){
                        cin>>item;
                        if (inventory.getBuffBucks()<3&&item<=4&&item>=1){
                            system("clear");
                            cout<<"You do not have enough Buff Bucks to purchase this.\n"<<endl;
                            break;
                        }
                        switch(item){
                            case 1:{
                                    system("clear");
                                if (inventory.setPedialyte(inventory.getPedialyte()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Pedialyte\n"<<endl;
                                }
                                validInput=false;
                            }break;
                            case 2:{
                                    system("clear");
                                if (inventory.setEnergyDrink(inventory.getEnergyDrink()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Energy Drink\n"<<endl;
                                }
                                validInput=false;
                            }break;
                            case 3:{
                                    system("clear");
                                if (inventory.setMuscleMilk(inventory.getMuscleMilk()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Muscle Milk\n"<<endl;
                                }
                                validInput=false;
                            }break;
                            case 4:{
                                system("clear");
                                if (inventory.setCupOfNoodles(inventory.getCupOfNoodles()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
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
            mapObject.exploreSpace(mapObject.getPlayerRow(),mapObject.getPlayerCol());
            randomChances(mapObject,inventory,bottle);

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
    if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)){
        //insert either bandit or cultist code here
    }
    if(!mapObject.isFreeSpace(mapObject.getPlayerRow(),mapObject.getDungeonExitCol())&&!mapObject.isMarketLocation(mapObject.getPlayerRow(),mapObject.getDungeonExitCol())){

    }

}
return 0;
}