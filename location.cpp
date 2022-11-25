#include <iostream>
#include <string>
#include "location.h"
using namespace std;

Location::Location(){
  name_="";
  difficulty_=0;
}
Location::Location(string name,int difficulty){
  name_=name;
  difficulty_=difficulty;
}
int Location::getRow(){
  return coords[0];
}
int Location::getCol(){
  return coords[1];
}
string Location::getName(){
  return name_;
}
int Location::getDifficulty(){
  return difficulty_;
}

void Location::setName(string name){
  name_=name;
}
void Location::setDifficulty(int difficulty){
  difficulty_=difficulty;
}
void Location::setLocation(int row,int col){
  coords[0]=row;
  coords[1]=col;
}
