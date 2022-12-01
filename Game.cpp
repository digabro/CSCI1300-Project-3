//Lachlan Kotarski and Diego Olin 
//compile command:
//g++ Inventory.cpp Item.cpp location.cpp person.cpp npc.cpp player.cpp map.cpp Game.cpp -std=c++17 -o universityHustle


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

void sendScore(string file_name,Player player, Inventory inv){
    ofstream outFile;
    outFile.open(file_name,ios_base::app);
    outFile<<player.getName()<<","<<player.getHp()<<","<<player.getSkillLevel()<<","<<inv.getBuffBucks()<<","<<player.getClassesPasses()<<","<<player.getFightsWon()<<endl;//player aspects
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
    string splitArr[6];
    string line;
    ifstream inFile;
    inFile.open("playerLogs");
    vector<vector<string>> logLines;
    vector<string> tempLog;
    while(!inFile.eof()){
        getline(inFile,line);
        split(line,',',splitArr,6);
        for (int i=0;i<6;i++){
            tempLog.push_back(splitArr[i]);
        }
        double health=(stod(tempLog[1])/20.0)*0.3;//base 0.3
        double armor=(stod(tempLog[2])/10)*0.3;//base 0
        double money=(stod(tempLog[3])/50.0)*0.4;//base 0.4
        double classes=stod(tempLog[4])*5;//base 0
        double fights=stod(tempLog[5])*5;//base 0
        tempLog.push_back(to_string(((health+armor+money+classes+fights))));//remaining hp 20% skill 30% buffbucks 50% 
        logLines.push_back(tempLog);
        tempLog.clear();
    }
    for (int i=0;i<(logLines.size()-1);i++){
        for (int j=1;j<(logLines.size()-1);j++){
            if (stod(logLines[j][6])>=stod(logLines[j-1][6])){
                tempLog=logLines[j-1];
                logLines[j-1]=logLines[j];
                logLines[j]=tempLog;
            }
        }
    }
    inFile.close();
    ofstream outFile;
    outFile.open("scoreboard.txt");
    int numRep=5;
    if(logLines.size()<5){
        numRep=logLines.size()-1;
    }
    for (int i=0;i<numRep;i++){
        outFile<<(i+1)<<". "<<logLines[i][0]<<" | Total: "<<stoi(logLines[i][6])<<" | Health: "<<logLines[i][1]<<" | Skill: "<<logLines[i][2]<<" | BuffBucks: "<<logLines[i][3]<<" | Classes Passed: "<<logLines[i][4]<<" | Fights Won: "<<logLines[i][5]<<endl;
    }
    outFile.close();
}

bool isValidAnswer(string answer){
    if(answer == "a"||answer == "b"||answer == "c"||answer == "d"){
        return true;
    }
    else{
        return false;
    }
}

bool isAnswerRight(string answer, int i, int j, string array[6][6]){

    if(answer == array[i][j]){
        return true;
    }
    else{
        return false;
    }
}

bool doesKingWookTrustThee()
{
    string answer;
    string wook_riddles[5][2] = 
    {{"What has keys but no locks space but no room you can enter but you can't exit?","keyboard"},
    {"What gets wet while drying?","towel"},
    {"What has a tongue but can't talk?","shoe"},
    {"What bus could cross the ocean?","columbus"},
    {"What disappears as soon as you say its name?","silence"}};
    srand(time(NULL));
    int randNum = rand() % 100; 
    cout << "Grettings traveler! I am King Wook, the sorcerer of Boulder who lives under the Broadway Bridge. I am able to protect you if you solve my riddle." << endl;
    if(randNum <= 0 && randNum <=20){
        cout << wook_riddles[0][0] << endl;
        cin >> answer;
        system("clear");
        if(answer == wook_riddles[0][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 21 && randNum <=40){
        cout << wook_riddles[1][0] << endl;
        cin >> answer;
        system("clear");
        if(answer == wook_riddles[1][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 41 && randNum <=60){
        cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
        cout << wook_riddles[2][0] << endl;
        cin >> answer;
        system("clear");
        if(answer == wook_riddles[2][1]){
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 61 && randNum <=80){
        cout << wook_riddles[3][0] << endl;
        cin >> answer;
        system("clear");
        if(answer == wook_riddles[3][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 81 && randNum <=100){
        cout << wook_riddles[4][0] << endl;
        cin >> answer;
        system("clear");
        if(answer == wook_riddles[4][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    return false;
}

bool printHistoryQuestions()
{

    int num_history_qs = 6;
    int num_history_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // history college:     Q#&Q  a   b   c   d   A
    string history[7][6] =
   {{"1. When was the town of Bolder built?","a. 1878","b. 1865","c. 1892","d. 1871","d"}, 
    {"2. What year was the University of Colorado-Boulder founded?","a. 1876","b. 1870","c. 1895","d. 1909","b"},
    {"3. When was the first Ralphie Buffalo introduced to the university?","a. 1919","b. 1957","c. 1892","d. 1909","b"},
    {"4. Why are the flat irons named the flat irons?","a. The pioneers saw that it was flat and filled with with iron.","b. The pioneers thought that it looked flat like an iron used to iron clothes.","c. The pioneers thought they were magnetic and thought their magnetic field would protect them from the sun.","d. When Boulder was founded, there was a large iron deposit found in the mountains.","b"},
    {"5. Who was Alfred Packer?","a. He was a settler on an expedition and became a cannibal after the trip went sour.","b. Famous rooster.","c. Famous Boulderite.","d. none of the above.","a"},
    {"6. Which musician referenced Boulder in one of his songs?","a. Johnny Cash.","b. The Highway Men.","c. Both a & b.","d. None of the above.","c"}};
for(int i = 0; i < num_history_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of History. Today we will be learning the history of this school and Boulder, Colorado." << endl;
        cout << endl;
    }
    for(int j = 0; j < 5; j++){// doesn't print answer
        cout << history[i][j] << endl; 
        if(j==0)
        {
            cout << endl;
        }
        if(j==4)
        {
            cout << endl;
        }
    }
    cin >> answer;
    while(isValidAnswer(answer) == 0){
        cout << "Invalid Input. Please try again." << endl;
        cin >> answer;
    }
    if(isAnswerRight(answer, i, 5, history) == 1){
        score = score + 1;
    }
    if(i == num_history_qs - 1)
    {
        cout << "You scored " << score << "/6 on the history quiz. Which means you ";
        if(score >= 5){
            system("clear");
            cout << "passed the quiz!" << endl;
            return true;  
        }
        else{
            system("clear");
            cout << "didn't pass the quiz, please try again." << endl;
            return false;
        }
    }  
}
return false;
}

bool printBusinessQuestions()
{

    const static int num_business_qs = 3;
    const static int num_business_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string business[num_business_qs][num_business_cols] =
   {{"1. When should you invest?","a. When the stock starts high.","b. When the stock starts low","c. When the stock is green which means go.","d. When the stock is unhappy.","b"}, 
    {"2. Is 1 greater than 0?","a. Yes","b. No","c. Maybe","d. Is this test curved?","a"},
    {"3. What letter does Blue start with?","a. B","b. g","c. z","d. 3","a"}};
for(int i = 0; i < num_business_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Business. Here's a quiz if you really know your stuff.(Select the answer that makes the most sense.)" << endl;
        cout << endl;
    }
    for(int j = 0; j < num_business_cols - 1; j++){// doesn't print answer
        cout << business[i][j] << endl; 
        if(j==0)
        {
            cout << endl;
        }
        if(j==4)
        {
            cout << endl;
        }
    }
    cin >> answer;
    while(isValidAnswer(answer) == 0){
        cout << "Invalid Input. Please try again." << endl;
        cin >> answer;
    }
    if(isAnswerRight(answer, i, num_business_cols - 1, business) == 1){
        score = score + 1;
    }
    if(i == num_business_qs - 1)
    {
        cout << "You scored " << score << "/3 on the Business quiz. Which means you ";
        if(score >= 2){
            system("clear");
            cout << "passed the quiz!" << endl;
            return true;  
        }
        else{
            system("clear");
            cout << "didn't pass the quiz, please try again." << endl;
            return false;
        }
    }  
}
return false;
}

bool printBiologyQuestions()
{
    const static int num_biology_qs = 4;
    const static int num_biology_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string biology[num_biology_qs][num_biology_cols] =
   {{"1. ___________ is the powerhouse of the cell.","a. Mitochondria","b. Nucleus","c. DNA","d. ATP","a"}, 
    {"2. Is it okay to shake a baby?","a. Hell yeah.","b. NO.","c. I mean don't knock it unitl you try it...","d. None of the above.","b"},
    {"3. What is the thigh bone called?","a. phlanges","b. fibula","c. tibia","d. femur","d"},
    {"4. What does the frontal lobe do?","a. Motor function","b. controls the eyes","c. controls the mouth ","d. main computing","a"}};
for(int i = 0; i < num_biology_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Pre-Med. Let's see what medical knowledge you have." << endl;
        cout << endl;
    }
    for(int j = 0; j < num_biology_cols - 1; j++){// doesn't print answer
        cout << biology[i][j] << endl; 
        if(j==0)
        {
            cout << endl;
        }
        if(j==4)
        {
            cout << endl;
        }
    }
    cin >> answer;
    while(isValidAnswer(answer) == 0){
        cout << "Invalid Input. Please try again." << endl;
        cin >> answer;
    }
    if(isAnswerRight(answer, i, num_biology_cols - 1, biology) == 1){
        score = score + 1;
    }
    if(i == num_biology_qs - 1)
    {
        cout << "You scored " << score << "/4 on the Biology quiz. Which means you ";
        if(score >= 3){
            system("clear");
            cout << "passed the quiz!" << endl;
            return true;  
        }
        else{
            system("clear");
            cout << "didn't pass the quiz, please try again." << endl;
            return false;
        }
    }  
}
return false;
}

bool printMathQuestions()
{
    const static int num_math_qs = 10;
    const static int num_math_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string math[num_math_qs][num_math_cols] =
   {{"1. Solve 4 x 4.","a. 1","b. 4","c. 16","d. 20","c"}, 
    {"2. Solve 9 x 9.","a. 63","b. 72","c. 81","d. 90","c"},
    {"3. Solve 6 x 6.","a. 36","b. 33","c. 27","d. 39","a"},
    {"4. If f(x) = 4x^5 + 7x^3 - 2x, solve f`(x). Pick one of the answers below.","a. f`(x) = 20x + 22x^2 - 4.","b. F(x) = x^5 + (7/4)x^4 -x^2 + c.","c. f`(x) = 20x^4 + 21x^2 - 2. ","d. f`(x) = x^5 + (7/4)x^4 -x^2 + c.","c"},
    {"5. Solve 2 + 2. ","a. 1","b. 2","c. 4","d. 5","c"},
    {"6. Solve 2 - 2. ","a. -1","b. 0","c. 1.99","d. 2.01","b"},
    {"7. Solve 7 x 0. ","a. 7","b. 0","c. 1","d. none of the above","b"},
    {"8. Solve 7 x 1. ","a. 7","b. 1","c. 0 ","d. none of the above.","a"},
    {"9. Solve 7 x 0.001.","a. 0.07","b. 1","c. 0.7","d. 0.007","d"},
    {"10. Solve 100 - 4(7-5)^2.","a. 4","b. 36","c. 84","d. 0","c"}};
for(int i = 0; i < num_math_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Mathematics. Here's a quiz if you really know your stuff. (Select the answer that makes the most sense)" << endl;
        cout << endl;
    }
    for(int j = 0; j < num_math_cols - 1; j++){// doesn't print answer
        cout << math[i][j] << endl; 
        if(j==0)
        {
            cout << endl;
        }
        if(j==4)
        {
            cout << endl;
        }
    }
    cin >> answer;
    while(isValidAnswer(answer) == 0){
        cout << "Invalid Input. Please try again." << endl;
        cin >> answer;
    }
    if(isAnswerRight(answer, i, num_math_cols - 1, math) == 1){
        score = score + 1;
    }
    if(i == num_math_qs - 1)
    {
        cout << "You scored " << score << "/10 on the Math quiz. Which means you ";
        if(score >= 7){
            system("clear");
            cout << "passed the quiz!" << endl;
            return true;  
        }
        else{
            system("clear");
            cout << "didn't pass the quiz, please try again." << endl;
            return false;
        }
    }  
}
return false;
}

int isValidInput(int lastValidInput){
    int input;
    while((!(cin>>input))){
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }
    return input;
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
    cout<<"                                                               |____|\n\n"<<endl;
    printFile("rules.txt");
    char option;
    Map mapObject=Map();

    cout<<"\n\nPlease enter your name: ";
    string name;
    getline(cin,name);
    system("clear");
    Player player=Player(name,20,0,0);
    Npc kingWook =Npc("King Wook",25,10,true,10,5,8,"Truth Bomb","Magic Projectile","Body Slam");
    Inventory inventory =Inventory(50,0,0,0,0);
    vector<Item> weaponArr;//making a vector for weapons -- used in the fights
    vector<Item> foodArr; //making food vector for fights
    //adding armor items to inventory array with quantity of 0
    Item buisnessSuit =Item("Buisness Suit","Armor",0,inventory.getNumItems(),0,6,60,1,0);
    Item biologyHelm =Item("Biology Helmet","Armor",0,inventory.getNumItems(),0,4,40,1,0);
    Item fractalLeggings =Item("Fractal Leggings","Armor",0,inventory.getNumItems(),0,4,40,1,0);
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
    inventory.addItem(buisnessSuit);
    inventory.addItem(biologyHelm);
    inventory.addItem(fractalLeggings);
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
        bCol = (rand()%14)+14;
        mapObject.addSchool(bRow,bCol, i); 
    }
    //add King Wook
    mapObject.addKingWook(2,6);

    while(option != 'Q')
    {
        cout << "========Map of Boulder========" << endl;
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
                /*
                * check if the space is either of the two markets
                * if not, set as explored and
                * search for money,wildlife, or supplies 
                */
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
                
                //checking random chances each time the player investigates
                string animalList[4]={" Black Bear"," Mountain Lion"," Coyote","n Elk"};//supposed to have space before and "n elk"
                int randNum = rand() % 100;//rand num from 0 to 99
                if (randNum>=0&&randNum<5){//found money
                    int randmoney=(rand()%9)+1;//1 to 10 bucks --can be changed if you want
                    system("clear");
                    cout<<"While investigating, you found $"<<randmoney<<".00"<<endl;
                    inventory.setBuffBucks(inventory.getBuffBucks()+randmoney);
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
            break;
            case 'r':{//pull rules from text file and keep it on screen until player navigates off
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
                // system("clear");
                string temp;
                organizeLogs();
                cout<<"======Scoreboard======"<<endl;
                printFile("scoreboard.txt");
                cout<<"\nClick any button to continue..."<<endl;
                cin>>temp;
                system("clear");
            }break;
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
        weaponArr.push_back(fist);//adding fist as a default weapon
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
        //battling bandits
        if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)=='B'){//check if the player if near a bandit
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
                    cout<<endl<<"Flee the Battle:\n"<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    cout<<"Enter a number: ";                    cout<<"Enter a number: ";
                    int option=isValidInput(weaponArr.size()+foodArr.size()+1);
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            banditLeader.setHp(banditLeader.getHp()-weaponArr[option].getDamage());
                        }
                        banditLeader.setHp(banditLeader.getHp()-weaponArr[option].getDamage());
                        //king wook attack
                        if(player.getKingWookTrust()){
                            int WookAttack=(rand()%3)+1;
                            int WookDamageNum=kingWook.getAttack(WookAttack);
                            cout << "King Wook used " <<kingWook.getAttackName(WookAttack)<<" to deal "<<WookDamageNum<<" damage"<<endl;
                            banditLeader.setHp(banditLeader.getHp()-WookDamageNum);
                        }   
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
                            player.setHp(20);
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
                    //enemy attacking

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
                    cout<<endl<<"Flee the Battle:\n"<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    cout<<"Enter a number: ";
                    int option=isValidInput(weaponArr.size()+foodArr.size()+1);
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            bandit.setHp(bandit.getHp()-weaponArr[option].getDamage());
                        }
                        bandit.setHp(bandit.getHp()-weaponArr[option].getDamage());
                        //king wook attack
                        if(player.getKingWookTrust()){
                            int WookAttack=(rand()%3)+1;
                            int WookDamageNum=kingWook.getAttack(WookAttack);
                            cout << "King Wook used " <<kingWook.getAttackName(WookAttack)<<" to deal "<<WookDamageNum<<" damage"<<endl;
                            bandit.setHp(bandit.getHp()-WookDamageNum);
                        } 
                        if(bandit.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Bandit "<<endl;
                            battle=false;
                            int scavengedmoney=(rand()%10);
                            cout<<"When searching the bandits pockets, you find "<<scavengedmoney<<" Buffbucks"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            player.setHp(20);
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
        if(isNearEnemy(mapObject.getPlayerRow(),mapObject.getPlayerCol(),mapObject)=='C'){//check is player is near a cultist
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
                    cout<<endl<<"Flee the Battle:\n"<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    cout<<"Enter a number: ";
                    int option=isValidInput(weaponArr.size()+foodArr.size()+1);
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            cultistLeader.setHp(cultistLeader.getHp()-weaponArr[option].getDamage());
                        }
                        cultistLeader.setHp(cultistLeader.getHp()-weaponArr[option].getDamage());
                        //king wook attack
                        if(player.getKingWookTrust()){
                            int WookAttack=(rand()%3)+1;
                            int WookDamageNum=kingWook.getAttack(WookAttack);
                            cout << "King Wook used " <<kingWook.getAttackName(WookAttack)<<" to deal "<<WookDamageNum<<" damage"<<endl;
                            cultistLeader.setHp(cultistLeader.getHp()-WookDamageNum);
                        } 
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
                                    mapObject.removeCultistCamp((mapObject.getPlayerRow()+i),(mapObject.getPlayerCol()+j));
                                }
                            }
                            player.setFightsWon(player.getFightsWon()+1);
                            player.setHp(20);
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
                    cout<<endl<<"Flee the Battle:\n"<<(weaponArr.size()+foodArr.size()+1)<<". Flee"<<endl;
                    cout<<"Enter a number: ";
                    int option=isValidInput(weaponArr.size()+foodArr.size()+1);
                    option--;
                    system("clear");
                    if (option>=0&&option<weaponArr.size()){
                        cout<<player.getName()<<" attacks with "<<weaponArr[option].getItemName()<<" for "<<weaponArr[option].getDamage()<<" damage"<<endl;
                        if (inventory.isActive("Muscle Milk")){
                            cout<<"The muscle milk strengthened your attack dealing "<<weaponArr[option].getDamage()<<" more damage"<<endl;
                            cultist.setHp(cultist.getHp()-weaponArr[option].getDamage());
                        }
                        cultist.setHp(cultist.getHp()-weaponArr[option].getDamage());
                        //king wook attack
                        if(player.getKingWookTrust()){
                            int WookAttack=(rand()%3)+1;
                            int WookDamageNum=kingWook.getAttack(WookAttack);
                            cout << "King Wook used " <<kingWook.getAttackName(WookAttack)<<" to deal "<<WookDamageNum<<" damage"<<endl;
                            cultist.setHp(cultist.getHp()-WookDamageNum);
                        } 
                        if(cultist.getHp()<=0){
                            system("clear");
                            cout<<"You defeated the Cultist "<<endl;
                            battle=false;
                            int scavengedmoney=(rand()%10);
                            cout<<"When searching the cultists pockets, you find "<<scavengedmoney<<" Buffbucks"<<endl;
                            inventory.setBuffBucks(inventory.getBuffBucks()+scavengedmoney);
                            player.setHp(20);
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
        if(mapObject.isSchoolLocation(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 1){
            if(mapObject.getSchoolType(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 0){
                if(printHistoryQuestions()==1){
                    player.setClassesPassed(player.getClassesPasses()+1);
                    // give player good armor piece biotech 
                    cout << endl;
                    cout << "Because you passed this class you won a piece of armor! " << endl;
                    cout << "You got: History Cowboy Hat"<< endl; // we'll print name here and then store in inventory in next line.
                    inventory.buyItem(cowboyHat);
                    mapObject.removeSchool(mapObject.getPlayerRow(), mapObject.getPlayerCol());
                }
            }
            if(mapObject.getSchoolType(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 1){
                if(printBusinessQuestions()==1){
                    player.setClassesPassed(player.getClassesPasses()+1);
                    // give player good armor piece biotech 
                    cout << endl;
                    cout << "Because you passed this class you won a piece of armor! " << endl;
                    cout << "You got: Buisness Suit"<< endl; // we'll print name here and then store in inventory in next line.
                    inventory.buyItem(buisnessSuit);
                    mapObject.removeSchool(mapObject.getPlayerRow(), mapObject.getPlayerCol());
                }
            }
            if(mapObject.getSchoolType(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 2){
                if(printMathQuestions()==1){
                    player.setClassesPassed(player.getClassesPasses()+1);
                    // give player good armor piece biotech 
                    cout << endl;
                    cout << "Because you passed this class you won a piece of armor! " << endl;
                    cout << "You got: Fractal Leggings"<< endl; // we'll print name here and then store in inventory in next line.
                    inventory.buyItem(fractalLeggings);
                    mapObject.removeSchool(mapObject.getPlayerRow(), mapObject.getPlayerCol());
                }
            }
            if(mapObject.getSchoolType(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 3){
                
                if(printBiologyQuestions()==1){
                    player.setClassesPassed(player.getClassesPasses()+1);
                    // give player good armor piece biotech 
                    cout << endl;
                    cout << "Because you passed this class you won a piece of armor! " << endl;
                    cout << "You got: Biology Helmet" << endl; // we'll print name here and then store in inventory in next line.
                    inventory.buyItem(biologyHelm);
                    mapObject.removeSchool(mapObject.getPlayerRow(), mapObject.getPlayerCol());
                }
            }
        }
        if(mapObject.isKingWookLocation(mapObject.getPlayerRow(), mapObject.getPlayerCol()) == 1)
        {
            if(doesKingWookTrustThee()==1){
                player.setKingWookTrust(1);
                mapObject.removeKingWook(mapObject.getPlayerRow(),mapObject.getPlayerCol());
            }
            else{
                player.setKingWookTrust(0);
            }
        }
        //checking if the class/fight requirement has been passed
        if(player.getClassesPasses()==4&&player.getFightsWon()>=1){
            system("clear");
            cout<<"You have now passed enough classes and defeated enough enemies to graduate"<<endl;
            cout<<"Make your way to the exit to graduate"<<endl;
            mapObject.addCollegeExit();
        }
        if(mapObject.isDungeonExit(mapObject.getPlayerRow(),mapObject.getPlayerCol())){
            option='Q';//quitting out of the while loop
        }
    }

    system("clear");
    cout<<"Congrats, you have graduated from CU Boulder!"<<endl;
    cout<<"Have a good day and thank you for playing!"<<endl;
    return 0;
}