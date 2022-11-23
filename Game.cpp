// #include "Inventory.h"
#include "Item.h"
#include "location.h"
// #include "map.h"
#include "npc.h"
#include "person.h"
#include "player.h"
#include <iostream>
#include <fstream>
using namespace std;

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
while(option != 'Q')
{
    //display map

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
    switch(option)
    {
        case 'W':
        case 'w':{
            /*
            mapObject.move(w);
            if(isOnMap() == true)
            if player location matches certain event locations then continue to that event
            if not check random likely event   
            */
        }
        break;
        case 'A':
        case 'a':{
            /*
            mapObject.move(a);
            if(isOnamp() == true)
            continue
            */
        }
        break;
        case 'S': 
        case 's':{
            /*
            mapObject.move(s);
            if(isOnmap() == true)
            continue
            */
        }
        break;
        case 'D':
        case 'd':{
            /*
            mapObject.move(d);
            if(isOnmap() == true)
            continue
            */
        }
        break;
        case 'E': 
        case 'e':{
            /*
            Inventory display 
            print out how much of each item and each item's maxes
            Would you like to use something?
            pick item you would like to use
            */
        }
        break;
        case 'I':
        case 'i':{
            /*
            Open investigate menu(maybe make inv)
            * search for money
            * search for wildlife
            * search for supplies 
            */
        }
        break;
        case 'R': 
        case 'r':{
            printFile("rules.txt");
        }
        break;
        case 'Q':
        case 'q':{
            cout << "Better luck next time!" << endl;
            return 0;
        }
        case default:{
            cout << "Invalid input. Please try again." << endl;
        }
    }
}
return 0;
}