#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>
#include <vector>
#include <string>
#using namespace std;

class Location{
    private:
        string name_;
        int difficulty_;
        char symbol_;
    public:
        Location();
        Location(string name,int difficulty,char symbol);
        getName();
        getDifficulty();
        getSymbol();
};

#endif