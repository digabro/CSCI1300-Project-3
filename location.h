//Lachlan Kotarski and Diego Olin 

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
        int coords[2];//(row,col)
    public:
        Location();
        Location(string name,int difficulty);
        string getName();
        int getDifficulty();
        int getRow();
        int getCol();

        void setName(string name);
        void setDifficulty(int difficulty);
        void setLocation(int row,int col);
};

#endif