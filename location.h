#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Location{
    private:
        string name_;
        int difficulty_;
        char symbol_;
    public:
        Location();
        Location(string name,int difficulty,char symbol);
        string getName();
        int getDifficulty();
        char getSymbol();

        void setName(string name);
        void setDifficulty(int difficulty);
        void setSymbol(char symbol);
};

#endif