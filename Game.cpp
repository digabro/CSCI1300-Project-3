//Lachlan Kotarski and Diego Olin 

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

char isNearEnemy(int row,int col,Map map){//make return char
    if (map.isBanditCampLocation(map.getPlayerRow(),(map.getPlayerCol()+1))||map.isBanditCampLocation((map.getPlayerRow()+1),map.getPlayerCol())||map.isBanditCampLocation(map.getPlayerRow(),(map.getPlayerCol()-1))||map.isBanditCampLocation((map.getPlayerRow()-1),map.getPlayerCol())){
        return 'B';//cardinal directions
    }
    else if (map.isBanditCampLocation((map.getPlayerRow()+1),(map.getPlayerCol()+1))||map.isBanditCampLocation((map.getPlayerRow()+1),(map.getPlayerCol()-1))||map.isBanditCampLocation((map.getPlayerRow()-1),(map.getPlayerCol()+1))||map.isBanditCampLocation((map.getPlayerRow()-1),(map.getPlayerCol()-1))){
        return 'B';//diagnal directions
    }
    else if (map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()+1),map.getPlayerCol())||map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()-1))||map.isCultistLocation((map.getPlayerRow()-1),map.getPlayerCol())){
        return 'C';//cardinal directions
    }
    else if (map.isCultistLocation((map.getPlayerRow()+1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()+1),(map.getPlayerCol()-1))||map.isCultistLocation((map.getPlayerRow()-1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()-1),(map.getPlayerCol()-1))){
        return 'C';//diagnal directions
    }
    return 'N';
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
            cout<<"While investigating, you found a broken bottle"<<endl;
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

void sendScore(string file_name,Player player, Inventory inv){
    ofstream outFile;
    outFile.open(file_name,ios_base::app);
    outFile<<player.getName()<<","<<player.getHp()<<","<<player.getSkillLevel()<<","<<inv.getBuffBucks()<<endl;//player aspects
}

int split(string input, char sep, string arr[], int size){
    int min=0, prevIndex, index=-1, count=1;
    bool empty=true;
    for (int i=0;i<input.length();i++){//repeats for every char in the input string 
        if (input[i]==sep){//if it equals the seperation char 
            count++;//add one to count
        }
    }
    min=0;
    for(int s=0;s<size;s++){//repeats for every seperation wanted
        for (int i=min;i<=input.length();i++){
            if (i==input.length()){
                prevIndex=index;
                index=i;
            }
            if (input[i]==sep){
                prevIndex=index;
                index=i;
                empty=false;
                break;
            }
        }
        if (empty){//if the substring isnt in the string
            arr[s]=input;//set the array to the string 
            return 1;//return 1
        }
        
        arr[s]=input.substr(prevIndex+1, (index-prevIndex-1));
        min=index+1;
    }
    if (size<count){return -1;}//if the string has more values than asked to seperate, return -1
    if (input.empty()){return 0;}//if the input string is empty return 0
    return count;
}

void organizeLogs(){
    string splitArr[4];
    string line;
    ifstream inFile;
    inFile.open("playerLogs");
    vector<vector<string>> logLines;
    vector<string> tempLog;
    while(!inFile.eof()){
        getline(inFile,line);
        split(line,',',splitArr,4);
        for (int i=0;i<4;i++){
            tempLog.push_back(splitArr[i]);
        }
        tempLog.push_back(to_string((((stod(tempLog[1])/20.0)*0.3)+((stod(tempLog[2])/10.0)*0.3)+(stod(tempLog[3])/50.0)*0.4)*14.3));//remaining hp 20% skill 30% buffbucks 50% 
        logLines.push_back(tempLog);
        tempLog.clear();
    }
    for (int i=0;i<(logLines.size()-1);i++){
        for (int j=1;j<(logLines.size()-1);j++){
            if (stoi(logLines[j][4])>=stoi(logLines[j-1][4])){
                tempLog=logLines[j-1];
                logLines[j-1]=logLines[j];
                logLines[j]=tempLog;
            }
        }
    }
    inFile.close();
    ofstream outFile;
    outFile.open("scoreboard");
    int numRep=5;
    if(logLines.size()<5){
        numRep=logLines.size()-1;
    }
    for (int i=0;i<numRep;i++){
        outFile<<(i+1)<<". "<<logLines[i][0]<<" | Total: "<<stoi(logLines[i][4])<<" | Health: "<<logLines[i][1]<<" | Skill: "<<logLines[i][2]<<" | BuffBucks: "<<logLines[i][3]<<endl;
    }
    outFile.close();
}






int main(){
    srand(time(NULL));
    cout<<"  _______ _            _    _       _                    _ _           _    _           _   _" <<endl;     
    cout<<" |__   __| |          | |  | |     (_)                  (_) |         | |  | |         | | | |  "  <<endl; 
    cout<<"    | |  | |__   ___  | |  | |_ __  ___   _____ _ __ ___ _| |_ _   _  | |__| |_   _ ___| |_| | ___ "<<endl;
    cout<<"    | |  | \'_ \\ / _ \\ | |  | | \'_ \\| \\ \\ / / _ \\ \'__/ __| | __| | | | |  __  | | | / __| __| |/ _ \\"<<endl;
    cout<<"    | |  | | | |  __/ | |__| | | | | |\\ V /  __/ |  \\__ \\ | |_| |_| | | |  | | |_| \\__ \\ |_| |  __/"<<endl;
    cout<<"    |_|  |_| |_|\\___|  \\____/|_| |_|_| \\_/ \\___|_|  |___/_|\\__|\\__, | |_|  |_|\\__,_|___/\\__|_|\\___|" <<endl;
    cout<<"                                                                __/ |"<<endl;
    cout<<"                                                               |____|"<<endl;
    char option;
    Map mapObject=Map();
    cout<<"Please enter your name: ";
    string name;
    getline(cin,name);
    system("clear");
    Player player=Player(name,20,0,0);
    Inventory inventory =Inventory(50,0,0,0,0);
    //adding armor items to inventory array with quantity of 0
    Item csChestplate =Item("CS Chestplate","Armor",0,inventory.getNumItems(),0,6,60,1,0);
    Item biologyHelm =Item("Biology Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
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
    inventory.addItem(biologyHelm);
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
        cout << "\n======Status======" << endl;
        cout << "Health Pts: "<<player.getHp()<<" | Armor: "<<player.getArmor()<<endl<<"Buff Bucks: "<<inventory.getBuffBucks();
        cout << " | Skill: "<< player.getSkillLevel()<<endl<<endl; 
        cout << "======Main Menu======" << endl;
        cout << "W: Move Upwards" << endl; 
        cout << "A: Move Left" << endl; 
        cout << "S: Move Downwards" << endl; 
        cout << "D: Move Right" << endl; 
        cout << "E: Inventory" << endl; 
        cout << "I: Investigate" << endl;
        cout << "R: Rules and directions" << endl;
        cout << "C: Scoreboard" << endl;
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
                    int item=0;
                    int num;
                    bool farrMark=true;
                    while (farrMark){
                        cout<<"Welcome to Farrand Market\nCurrent money: "<<inventory.getBuffBucks()<<"\n\nItems to buy:"<<endl;
                        cout<<"1.Pedialyte - $3\n2.Energy Drink - $3\n3.Muscle Milk - $3";
                        cout<<"\n4.Cup of Noodles - $3\n5.Exit\nSelect an item: ";
                        if(!(cin>>item)){
                            system("clear");
                            cout<<"Invalid Input"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');//https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer – error with clearing cin buffer
                        }
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
                            }break;
                            case 2:{
                                    system("clear");
                                if (inventory.setEnergyDrink(inventory.getEnergyDrink()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Energy Drink\n"<<endl;
                                }
                            }break;
                            case 3:{
                                    system("clear");
                                if (inventory.setMuscleMilk(inventory.getMuscleMilk()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Muscle Milk\n"<<endl;
                                }
                            }break;
                            case 4:{
                                system("clear");
                                if (inventory.setCupOfNoodles(inventory.getCupOfNoodles()+1)){
                                    inventory.setBuffBucks(inventory.getBuffBucks()-3);
                                    cout<<"Successfully Purchased 1 Cup Of Noodles\n"<<endl;
                                }
                            }break;
                            case 5:{
                                system("clear");
                                cout<<"Thank you for visiting Farrand Market\n"<<endl;
                                farrMark=false;
                            }break;
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
                string temp;
                cout<<"\nClick any button to continue..."<<endl;
                cin>>temp;
                system("clear");
            }
            break;
            case 'q':{
                cout << "Better luck next time!" << endl;
                sendScore("playerLogs",player,inventory);
                return 0;
            }break;
            case 'c':{
                //system("clear");
                string temp;
                organizeLogs();
                cout<<"======Scoreboard======"<<endl;
                printFile("scoreboard");
                cout<<"\nClick any button to continue..."<<endl;
                cin>>temp;
                system("clear");
            }
            default:{
                system("clear");
                cout << "Invalid input. Please try again." << endl;
            }
        }
        //if the input was any movement key, check if the space that was moved onto is an enemy space
        if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)=='B'){
            //insert either bandit
        }
        //again for cult

    }
    return 0;
}