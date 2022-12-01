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
#include <climits>
#include <fstream>
#include <vector>
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
    else if (map.isBanditCampLocation(map.getPlayerRow(),map.getPlayerCol())){
        return 'B';//camp itself
    }
    else if (map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()+1),map.getPlayerCol())||map.isCultistLocation(map.getPlayerRow(),(map.getPlayerCol()-1))||map.isCultistLocation((map.getPlayerRow()-1),map.getPlayerCol())){
        return 'C';//cardinal directions
    }
    else if (map.isCultistLocation((map.getPlayerRow()+1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()+1),(map.getPlayerCol()-1))||map.isCultistLocation((map.getPlayerRow()-1),(map.getPlayerCol()+1))||map.isCultistLocation((map.getPlayerRow()-1),(map.getPlayerCol()-1))){
        return 'C';//diagnal directions
    }
    else if (map.isCultistLocation(map.getPlayerRow(),map.getPlayerCol())){
        return 'C';//camp itself
    }
    return 'N';
}

void randomChances(Map map,Inventory inv,Item bottle){//use the bottle item when calling, needs it as an input to add it to the inventory as its not a global variable
    string animalList[4]={" Black Bear"," Mountain Lion"," Coyote","n Elk"};//supposed to have space before and "n elk"
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
        tempLog.push_back(to_string((((stod(tempLog[1])/20.0)*0.3)+((stod(tempLog[2])/10.0)*0.3)+(stod(tempLog[3])/20.0)*0.4)*14.3));//remaining hp 20% skill 30% buffbucks 50% 
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
    vector<Item> weaponArr;//making a vector for weapons -- used in the fights
    vector<Item> foodArr; //making food vector for fights
    //adding armor items to inventory array with quantity of 0
    Item csChestplate =Item("CS Chestplate","Armor",0,inventory.getNumItems(),0,6,60,1,0);
    Item biologyHelm =Item("Biology Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
    Item historyHelm =Item("History Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
    Item cowboyHat =Item("Cowboy Hat","Armor",0,inventory.getNumItems(),0,4,40,1,0);
    Item hoodie =Item("Hoodie","Armor",18,inventory.getNumItems(),0,3,30,1,0);
    Item sweatpants =Item("Sweatpants","Armor",12,inventory.getNumItems(),0,2,20,1,0);
    Item sandals =Item("Sandals","Armor",6,inventory.getNumItems(),0,1,10,1,0);
    Item sunglasses =Item("Sunglasses","Armor",6,inventory.getNumItems(),0,1,10,1,0);
    //adding weapon items to inventory array with quantity of 0
    Item pencils =Item("Pencils","Weapon",2,inventory.getNumItems(),4,0,-1,4,0);
    Item scissors =Item("Scissors","Weapon",2,inventory.getNumItems(),6,0,-1,4,0);
    Item bottle =Item("Broken Bottle","Weapon",0,inventory.getNumItems(),3,0,-1,1,0);
    
    Item pedialyte =Item("Pedialyte","Food",6,inventory.getNumItems(),0,0,-1,4,0);
    Item cupOfNoodles =Item("Cup Of Noodles","Food",6,inventory.getNumItems(),0,0,-1,5,0);
    Item muscleMilk =Item("Muscle Milk","Food",6,inventory.getNumItems(),0,0,-1,1,0);
    Item energyDrink =Item("Energy Drink","Food",6,inventory.getNumItems(),0,0,-1,2,0);

    Item paddle =Item("Abandoned Paddle","Weapon",0,inventory.getNumItems(),2,0,-1,1,0);
    Item fist =Item("Fist","Weapon",0,inventory.getNumItems(),1,0,-1,1,1);//for the fight if theres no weapon default to this
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
    inventory.addItem(pedialyte);
    inventory.addItem(cupOfNoodles);
    inventory.addItem(muscleMilk);
    inventory.addItem(energyDrink);

    mapObject.addMarket(6,15);//farrand market
    mapObject.addMarket(1,5);//wallgreens market

    //adding bandit camps
    int bRow,bCol;
    for (int i=0;i<(rand()%4)+1;i++){//can be changed to i<2 so its not a random amount of bandit camps
        bRow = (rand()%11);
        bCol = (rand()%14);
        mapObject.addBanditCamp(bRow,bCol);
    }
    //adding cultist camps
    for (int i=0;i<(rand()%2)+1;i++){//can be changed to i<5 so its not a random amount of cultists
        bRow = (rand()%11);
        bCol = (rand()%14);
        mapObject.addCultist(bRow,bCol);
    }
    //adding schools
    for (int i=0;i<4;i++){
        bRow = (rand()%11);
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
        cout << "C: Consumables" << endl;
        cout << "R: Rules and directions" << endl;
        cout << "F: Scoreboard" << endl;
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
                cout<<inventory.getEnergyDrink()<<endl;
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
            case 'c':{
                vector<Item> foodArr;
                bool consume =true;
                while(consume){
                    foodArr.clear();
                    for (int i=0;i<inventory.getNumItems();i++){
                        if(inventory.getItem(i).getItemType()=="Food"){
                            if(inventory.getItem(i).getQuantity()>0){
                                foodArr.push_back(inventory.getItem(i));
                            }
                        }
                    }
                    int option;
                    cout<<"\nConsume a food item:"<<endl;
                    if (foodArr.size()==0){
                        cout<<"Nothing to consume"<<endl;
                    }
                    for (int i=0;i<(foodArr.size());i++){
                        cout<<(i+1)<<". "<<foodArr[i].getItemName()<<"("<<foodArr[i].getQuantity()<<")"<<endl;
                    }
                    cout<<(foodArr.size()+1)<<". Exit"<<endl;
                    cout<<"Choose an item: ";
                    if(!(cin>>option)){
                        system("clear");
                        cout<<"Invalid Input"<<endl;
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                    }
                    option--;

                    if(option<foodArr.size()){
                        inventory.activateFood(foodArr[option].getItemName());
                        system("clear");
                        cout<<"You consumed 1 "<<foodArr[option].getItemName()<<endl;
                        for (int i=0;i<inventory.getNumItems();i++){//remove one from inventory
                            if (inventory.getItem(i).getItemName()==foodArr[option].getItemName()){
                                inventory.getItem(i).setQuantity(inventory.getItem(i).getQuantity()-1);
                                foodArr[option].setQuantity(foodArr[option].getQuantity()-1);
                            }
                        }
                    }
                    else if(option==foodArr.size()){
                        consume=false;
                        system("clear");
                    }
                    if (inventory.isActive("Pedialyte")){
                        system("clear");
                        cout<<"You heal for 10 hp"<<endl;
                        player.setHp(player.getHp()+10);
                        inventory.deactivateFood("Pedialyte");
                    }
                    if (inventory.isActive("Cup Of Noodles")){
                        system("clear");
                        cout<<"You heal for 5 hp"<<endl;
                        player.setHp(player.getHp()+5);
                        inventory.deactivateFood("Cup Of Noodles");
                    }
                    
                }
            }break;
            case 'i':{
                //farrand market
                if(mapObject.isMarketLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())&&mapObject.getPlayerRow()==6&&mapObject.getPlayerCol()==15){
                    int item=0;
                    int num;
                    bool farrMark=true;
                    while (farrMark){
                        cout<<"Welcome to Farrand Market\nCurrent money: "<<inventory.getBuffBucks()<<"\n\nItems to buy:"<<endl;
                        cout<<"1.Pedialyte - $6\n2.Energy Drink - $6\n3.Muscle Milk - $6";
                        cout<<"\n4.Cup of Noodles - $6\n5.Exit\nSelect an item: ";
                        if(!(cin>>item)){
                            system("clear");
                            cout<<"Invalid Input"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');//https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer – error with clearing cin buffer
                        }
                        if (inventory.getBuffBucks()<6&&item<=4&&item>=1){
                            system("clear");
                            cout<<"You do not have enough Buff Bucks to purchase this.\n"<<endl;
                            break;
                        }
                        switch(item){
                            case 1:{
                                system("clear");
                                inventory.buyItem(pedialyte);
                            }break;
                            case 2:{
                                system("clear");
                                inventory.buyItem(energyDrink);
                            }break;
                            case 3:{
                                system("clear");
                                inventory.buyItem(muscleMilk);
                            }break;
                            case 4:{
                                system("clear");
                                inventory.buyItem(cupOfNoodles);
                            }break;
                            case 5:{
                                system("clear");
                                cout<<"Thank you for visiting Farrand Market\n"<<endl;
                                farrMark=false;
                            }break;
                        } 
                    }
                }
                //wallgreens
                if(mapObject.isMarketLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())&&mapObject.getPlayerRow()==1&&mapObject.getPlayerCol()==5){
                    int item=0;
                    int num;
                    bool wallgreens=true;
                    while (wallgreens){
                        cout<<"Welcome to Wallgreens\nCurrent money: "<<inventory.getBuffBucks()<<"\n\nItems to buy:"<<endl;
                        cout<<"1.Hoodie - $18\n2.Sweatpants - $12\n3.Sandals - $6";
                        cout<<"\n4.Sunglasses - $6\n5.Pencil - $2\n6.Scissors - $2\n7.Exit\nSelect an item: ";
                        if(!(cin>>item)){
                            system("clear");
                            cout<<"Invalid Input"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');//https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer – error with clearing cin buffer
                        }
                        switch(item){
                            case 1:{
                                    system("clear");
                                    inventory.buyItem(hoodie);
                            }break;
                            case 2:{
                                    system("clear");
                                    inventory.buyItem(sweatpants);
                            }break;
                            case 3:{
                                    system("clear");
                                    inventory.buyItem(sandals);
                            }break;
                            case 4:{
                                system("clear");
                                inventory.buyItem(sunglasses);
                            }break;
                            case 5:{
                                system("clear");
                                inventory.buyItem(pencils);
                            }break;
                            case 6:{
                                system("clear");
                                inventory.buyItem(scissors);
                            }break;
                            case 7:{
                                system("clear");
                                cout<<"Thank you for visiting Wallgreens\n"<<endl;
                                wallgreens=false;
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
            case 'f':{
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
        //updating armor after every move
        player.setArmor(0);
        for (int i=0;i<inventory.getNumItems();i++){
            if(inventory.getItem(i).getItemType()=="Armor"){
                if(inventory.getItem(i).getQuantity()>0){
                    player.setArmor(player.getArmor()+inventory.getItem(i).getProtection());
                }
            }
        }
        //updating the food array after every move incase they pickup a new food item
        foodArr.clear();
        for (int i=0;i<inventory.getNumItems();i++){
            if(inventory.getItem(i).getItemType()=="Food"){
                if(inventory.getItem(i).getQuantity()>0){
                    foodArr.push_back(inventory.getItem(i));
                }
            }
        }
        //updating the weapon array after every move incase they pickup a new weapon
        weaponArr.clear();
        weaponArr.push_back(fist);
        for (int i=0;i<inventory.getNumItems();i++){
            if(inventory.getItem(i).getItemType()=="Weapon"){
                if(inventory.getItem(i).getQuantity()>0){
                    weaponArr.push_back(inventory.getItem(i));
                }
            }
        }
        //if the input was any movement key, check if the space that was moved onto is an enemy space
        int encounterChance=rand()%100;
        bool battle=true;
        if(mapObject.isBanditCampLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())||mapObject.isCultistLocation(mapObject.getPlayerRow(),mapObject.getPlayerCol())){
            encounterChance=0;//if the space is the camp itself, 100% chance for fighting leader
        }
        if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)=='B'){
            if(encounterChance>=0&&encounterChance<10){//bandit leader attacks
                system("clear");
                cout<< "Oh no, you walked to close to the Bandit Camp!!"<<endl;
                cout<< "Bandit Leader:\"You're gonna get it adventurer!\""<<endl;
                cout<< player.getName()<<": \"Yeah right, haha!\"\n"<<endl;
                Npc banditLeader =Npc("Bandit",25,10,true,10,4,8,"Brute Charge","Fist Fight","Body Slam"); 
                while(battle){
                    cout << "\n======Status======" << endl;
                    cout << "Health Pts: "<<player.getHp()<<" | Armor: "<<player.getArmor()<<endl<<"Buff Bucks: "<<inventory.getBuffBucks();
                    cout << " | Skill: "<< player.getSkillLevel()<<endl<<endl; 
                    cout<<"Choose what to do:"<<endl;
                    cout<<"Attack:"<<endl;
                    for (int i=0;i<weaponArr.size();i++){
                        cout<<(i+1)<<". "<<weaponArr[i].getItemName()<<" - "<<weaponArr[i].getDamage()<<" damage"<<endl;
                    }
                    //option for food or fleeing
                    if(foodArr.size()>0){
                        cout<<"\nConsume a food item:"<<endl;
                        for (int i=0;i<(foodArr.size());i++){
                            cout<<(i+weaponArr.size()+1)<<". "<<foodArr[i].getItemName()<<"("<<foodArr[i].getQuantity()<<")"<<endl;
                        }
                    }
                    cout<<endl<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    int option;
                    cin>>option;
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            banditLeader.setHp(banditLeader.getHp()-weaponArr[option].getDamage());
                        }
                        banditLeader.setHp(banditLeader.getHp()-weaponArr[option].getDamage());
                        if(banditLeader.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Bandit Leader"<<endl;
                            battle=false;
                            cout<<"The bandit camp is now in disarray, and the have bandits fled in terror"<<endl;
                            int scavengedmoney=(rand()%10)+10;
                            cout<<"When scavenging the camp, you find "<<scavengedmoney<<" Buffbucks\n"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            for (int i=-1;i<=1;i++){
                                for (int j=-1;j<=1;j++){
                                    mapObject.removeBanditCamp((mapObject.getPlayerRow()+i),(mapObject.getPlayerCol()+j));
                                }
                            }
                            player.setFightsWon(player.getFightsWon()+1);
                            break;
                        }
                    }
                    else if(option>=weaponArr.size()&&option<(weaponArr.size()+foodArr.size())){
                        option-=weaponArr.size();
                        if (inventory.activateFood(foodArr[option].getItemName())){
                            cout<<"You consumed 1 "<<foodArr[option].getItemName()<<endl;
                            for (int i=0;i<inventory.getNumItems();i++){
                                if (inventory.getItem(i).getItemName()==foodArr[option].getItemName()){
                                    inventory.getItem(i).setQuantity(inventory.getItem(i).getQuantity()-1);
                                    foodArr[option].setQuantity(foodArr[option].getQuantity()-1);
                                }
                            }
                            if (inventory.isActive("Pedialyte")){
                                cout<<"You heal for 10 hp"<<endl;
                                player.setHp(player.getHp()+10);
                                inventory.deactivateFood("Pedialyte");
                            }
                            if (inventory.isActive("Cup Of Noodles")){
                                cout<<"You heal for 5 hp"<<endl;
                                player.setHp(player.getHp()+5);
                                inventory.deactivateFood("Cup Of Noodles");
                            }
                        }
                        
                    }
                    else if(option==(weaponArr.size()+foodArr.size())){
                        cout<<"You attempted to flee\nIn youre attempt, the Bandit Leader makes one last attack"<<endl;
                        if(inventory.isActive("Energy Drink")){
                            cout<<"Using your energy drink, you outran the Bandit Leaders final attack"<<endl;
                            break;
                        }
                        battle=false;
                    }



                    int attackNum=(rand()%3)+1;
                    int damageNum=banditLeader.getAttack(attackNum);
                    cout << "Bandit Leader used " <<banditLeader.getAttackName(attackNum)<<" to deal "<<damageNum<<" damage"<<endl;
                    if(player.getArmor()>=banditLeader.getAttack(attackNum)){
                        damageNum=0;
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    else if(player.getArmor()<=banditLeader.getAttack(attackNum)&&player.getArmor()>0){
                        damageNum-=player.getArmor();
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    player.setHp(player.getHp()-damageNum);
                    if(player.getHp()<=0){
                        cout << "You Died\nBetter luck next time!" << endl;
                        sendScore("playerLogs",player,inventory);
                        return 0;
                    }
                }
            }
            else if(encounterChance>=10&&encounterChance<40){//normal bandit attacks
                system("clear");
                cout<< "Oh no, you walked to close to the Bandit Camp!!"<<endl;
                cout<< "Bandit:\"You're gonna get it adventurer!\""<<endl;
                cout<< player.getName()<<": \"Yeah right, haha!\""<<endl;
                Npc bandit =Npc("Bandit",25,0,true,6,4,8,"Brute Charge","Fist Fight","Body Slam");
                while(battle){
                    cout << "\n======Status======" << endl;
                    cout << "Health Pts: "<<player.getHp()<<" | Armor: "<<player.getArmor()<<endl<<"Buff Bucks: "<<inventory.getBuffBucks();
                    cout << " | Skill: "<< player.getSkillLevel()<<endl<<endl; 
                    cout<<"Choose what to do:"<<endl;
                    cout<<"Attack:"<<endl;
                    for (int i=0;i<weaponArr.size();i++){
                        cout<<(i+1)<<". "<<weaponArr[i].getItemName()<<" - "<<weaponArr[i].getDamage()<<" damage"<<endl;
                    }
                    //option for food or fleeing
                    if(foodArr.size()>0){
                        cout<<"\nConsume a food item:"<<endl;
                        for (int i=0;i<(foodArr.size());i++){
                            cout<<(i+weaponArr.size()+1)<<". "<<foodArr[i].getItemName()<<"("<<foodArr[i].getQuantity()<<")"<<endl;
                        }
                    }
                    cout<<endl<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    int option;
                    cin>>option;
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            bandit.setHp(bandit.getHp()-weaponArr[option].getDamage());
                        }
                        bandit.setHp(bandit.getHp()-weaponArr[option].getDamage());
                        if(bandit.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Bandit "<<endl;
                            battle=false;
                            int scavengedmoney=(rand()%10);
                            cout<<"When searching the bandits pockets, you find "<<scavengedmoney<<" Buffbucks"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            player.setFightsWon(player.getFightsWon()+1);
                        }
                    }
                    else if(option>=weaponArr.size()&&option<(weaponArr.size()+foodArr.size())){
                        option-=weaponArr.size();
                        if (inventory.activateFood(foodArr[option].getItemName())){
                            cout<<"You consumed 1 "<<foodArr[option].getItemName()<<endl;
                            for (int i=0;i<inventory.getNumItems();i++){
                                if (inventory.getItem(i).getItemName()==foodArr[option].getItemName()){
                                    inventory.getItem(i).setQuantity(inventory.getItem(i).getQuantity()-1);
                                    foodArr[option].setQuantity(foodArr[option].getQuantity()-1);
                                }
                            }
                            if (inventory.isActive("Pedialyte")){
                                cout<<"You heal for 10 hp"<<endl;
                                player.setHp(player.getHp()+10);
                                inventory.deactivateFood("Pedialyte");
                            }
                            if (inventory.isActive("Cup Of Noodles")){
                                cout<<"You heal for 5 hp"<<endl;
                                player.setHp(player.getHp()+5);
                                inventory.deactivateFood("Cup Of Noodles");
                            }
                        }
                        
                    }
                    else if(option==(weaponArr.size()+foodArr.size())){
                        cout<<"You attempted to flee\nIn youre attempt, the Bandit makes one last attack"<<endl;
                        if(inventory.isActive("Energy Drink")){
                            cout<<"Using your energy drink, you outran the Bandits final attack"<<endl;
                            break;
                        }
                        battle=false;
                    }



                    int attackNum=(rand()%3)+1;
                    int damageNum=bandit.getAttack(attackNum);
                    cout << "Bandit used " <<bandit.getAttackName(attackNum)<<" to deal "<<damageNum<<" damage"<<endl;
                    if(player.getArmor()>=bandit.getAttack(attackNum)){
                        damageNum=0;
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    else if(player.getArmor()<=bandit.getAttack(attackNum)&&player.getArmor()>0){
                        damageNum-=player.getArmor();
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    player.setHp(player.getHp()-damageNum);
                    if(player.getHp()<=0){
                        cout << "You Died\nBetter luck next time!" << endl;
                        sendScore("playerLogs",player,inventory);
                        return 0;
                    }
                }
            }
        
        }
        //again for cult
        if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)=='C'){
            if(encounterChance>=0&&encounterChance<10){//cultist leader attacks
                system("clear");
                cout<< "Oh no, you walked to close to the Cultist Church!!"<<endl;
                cout<< "Cultist Leader:\"You're gonna get it adventurer!\""<<endl;
                cout<< player.getName()<<": \"Yeah right, haha!\"\n"<<endl;
                Npc cultistLeader =Npc("Cultist",20,15,true,7,9,12,"Holy Water","Torch","Crucifix"); 
                while(battle){
                    cout << "\n======Status======" << endl;
                    cout << "Health Pts: "<<player.getHp()<<" | Armor: "<<player.getArmor()<<endl<<"Buff Bucks: "<<inventory.getBuffBucks();
                    cout << " | Skill: "<< player.getSkillLevel()<<endl<<endl; 
                    cout<<"Choose what to do:"<<endl;
                    cout<<"Attack:"<<endl;
                    for (int i=0;i<weaponArr.size();i++){
                        cout<<(i+1)<<". "<<weaponArr[i].getItemName()<<" - "<<weaponArr[i].getDamage()<<" damage"<<endl;
                    }
                    //option for food or fleeing
                    if(foodArr.size()>0){
                        cout<<"\nConsume a food item:"<<endl;
                        for (int i=0;i<(foodArr.size());i++){
                            cout<<(i+weaponArr.size()+1)<<". "<<foodArr[i].getItemName()<<"("<<foodArr[i].getQuantity()<<")"<<endl;
                        }
                    }
                    cout<<endl<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    int option;
                    cin>>option;
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            cultistLeader.setHp(cultistLeader.getHp()-weaponArr[option].getDamage());
                        }
                        cultistLeader.setHp(cultistLeader.getHp()-weaponArr[option].getDamage());
                        if(cultistLeader.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Cultist Leader"<<endl;
                            battle=false;
                            cout<<"The Cultist church is now in disarray, and the Cultist have fled in terror"<<endl;
                            int scavengedmoney=(rand()%10)+10;
                            cout<<"When scavenging the church, you find "<<scavengedmoney<<" Buffbucks\n"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            for (int i=-1;i<=1;i++){
                                for (int j=-1;j<=1;j++){
                                    mapObject.removeBanditCamp((mapObject.getPlayerRow()+i),(mapObject.getPlayerCol()+j));
                                }
                            }
                            player.setFightsWon(player.getFightsWon()+1);
                            break;
                        }
                    }
                    else if(option>=weaponArr.size()&&option<(weaponArr.size()+foodArr.size())){
                        option-=weaponArr.size();
                        if (inventory.activateFood(foodArr[option].getItemName())){
                            cout<<"You consumed 1 "<<foodArr[option].getItemName()<<endl;
                            for (int i=0;i<inventory.getNumItems();i++){
                                if (inventory.getItem(i).getItemName()==foodArr[option].getItemName()){
                                    inventory.getItem(i).setQuantity(inventory.getItem(i).getQuantity()-1);
                                    foodArr[option].setQuantity(foodArr[option].getQuantity()-1);
                                }
                            }
                            if (inventory.isActive("Pedialyte")){
                                cout<<"You heal for 10 hp"<<endl;
                                player.setHp(player.getHp()+10);
                                inventory.deactivateFood("Pedialyte");
                            }
                            if (inventory.isActive("Cup Of Noodles")){
                                cout<<"You heal for 5 hp"<<endl;
                                player.setHp(player.getHp()+5);
                                inventory.deactivateFood("Cup Of Noodles");
                            }
                        }
                        
                    }
                    else if(option==(weaponArr.size()+foodArr.size())){
                        cout<<"You attempted to flee\nIn youre attempt, the Cultist Leader makes one last attack"<<endl;
                        if(inventory.isActive("Energy Drink")){
                            cout<<"Using your energy drink, you outran the Cultist Leaders final attack"<<endl;
                            break;
                        }
                        battle=false;
                    }



                    int attackNum=(rand()%3)+1;
                    int damageNum=cultistLeader.getAttack(attackNum);
                    cout << "Cultist Leader used " <<cultistLeader.getAttackName(attackNum)<<" to deal "<<damageNum<<" damage"<<endl;
                    if(player.getArmor()>=cultistLeader.getAttack(attackNum)){
                        damageNum=0;
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    else if(player.getArmor()<=cultistLeader.getAttack(attackNum)&&player.getArmor()>0){
                        damageNum-=player.getArmor();
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    player.setHp(player.getHp()-damageNum);
                    if(player.getHp()<=0){
                        cout << "You Died\nBetter luck next time!" << endl;
                        sendScore("playerLogs",player,inventory);
                        return 0;
                    }
                }
            }
            else if(encounterChance>=10&&encounterChance<40){//normal cultist attacks
                system("clear");
                cout<< "Oh no, you walked to close to the Cultist Church!!"<<endl;
                cout<< "Cultist:\"You're gonna get it adventurer!\""<<endl;
                cout<< player.getName()<<": \"Yeah right, haha!\""<<endl;
                Npc cultist =Npc("Cultist",20,0,true,3,5,8,"Holy Water","Torch","Crucifix");
                while(battle){
                    cout << "\n======Status======" << endl;
                    cout << "Health Pts: "<<player.getHp()<<" | Armor: "<<player.getArmor()<<endl<<"Buff Bucks: "<<inventory.getBuffBucks();
                    cout << " | Skill: "<< player.getSkillLevel()<<endl<<endl; 
                    cout<<"Choose what to do:"<<endl;
                    cout<<"Attack:"<<endl;
                    for (int i=0;i<weaponArr.size();i++){
                        cout<<(i+1)<<". "<<weaponArr[i].getItemName()<<" - "<<weaponArr[i].getDamage()<<" damage"<<endl;
                    }
                    //option for food or fleeing
                    if(foodArr.size()>0){
                        cout<<"\nConsume a food item:"<<endl;
                        for (int i=0;i<(foodArr.size());i++){
                            cout<<(i+weaponArr.size()+1)<<". "<<foodArr[i].getItemName()<<"("<<foodArr[i].getQuantity()<<")"<<endl;
                        }
                    }
                    cout<<endl<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    int option;
                    cin>>option;
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            cultist.setHp(cultist.getHp()-weaponArr[option].getDamage());
                        }
                        cultist.setHp(cultist.getHp()-weaponArr[option].getDamage());
                        if(cultist.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Cultist "<<endl;
                            battle=false;
                            int scavengedmoney=(rand()%10);
                            cout<<"When searching the cultists pockets, you find "<<scavengedmoney<<" Buffbucks"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            player.setFightsWon(player.getFightsWon()+1);
                        }
                    }
                    else if(option>=weaponArr.size()&&option<(weaponArr.size()+foodArr.size())){
                        option-=weaponArr.size();
                        if (inventory.activateFood(foodArr[option].getItemName())){
                            cout<<"You consumed 1 "<<foodArr[option].getItemName()<<endl;
                            for (int i=0;i<inventory.getNumItems();i++){
                                if (inventory.getItem(i).getItemName()==foodArr[option].getItemName()){
                                    inventory.getItem(i).setQuantity(inventory.getItem(i).getQuantity()-1);
                                    foodArr[option].setQuantity(foodArr[option].getQuantity()-1);
                                }
                            }
                            if (inventory.isActive("Pedialyte")){
                                cout<<"You heal for 10 hp"<<endl;
                                player.setHp(player.getHp()+10);
                                inventory.deactivateFood("Pedialyte");
                            }
                            if (inventory.isActive("Cup Of Noodles")){
                                cout<<"You heal for 5 hp"<<endl;
                                player.setHp(player.getHp()+5);
                                inventory.deactivateFood("Cup Of Noodles");
                            }
                        }
                        
                    }
                    else if(option==(weaponArr.size()+foodArr.size())){
                        cout<<"You attempted to flee\nIn youre attempt, the Bandit makes one last attack"<<endl;
                        if(inventory.isActive("Energy Drink")){
                            cout<<"Using your energy drink, you outran the Bandits final attack"<<endl;
                            break;
                        }
                        battle=false;
                    }



                    int attackNum=(rand()%3)+1;
                    int damageNum=cultist.getAttack(attackNum);
                    cout << "Bandit used " <<cultist.getAttackName(attackNum)<<" to deal "<<damageNum<<" damage"<<endl;
                    if(player.getArmor()>=cultist.getAttack(attackNum)){
                        damageNum=0;
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    else if(player.getArmor()<=cultist.getAttack(attackNum)&&player.getArmor()>0){
                        damageNum-=player.getArmor();
                        cout<<"You blocked "<<player.getArmor()<<" damage with your armor"<<endl;
                    }
                    player.setHp(player.getHp()-damageNum);
                    if(player.getHp()<=0){
                        cout << "You Died\nBetter luck next time!" << endl;
                        sendScore("playerLogs",player,inventory);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}