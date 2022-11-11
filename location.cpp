#include <iostream>
#include <string>
#include "location.h"
using namespace std;

Location::Location(){
  name_="";
  difficulty_=0;
  symbol_= ' ';
}
Location::Location(string name,int difficulty,char symbol){
  name_=name;
  difficulty_=difficulty;
  symbol_=symbol;
}
string Location::getName(){
  return name_;
}
int Location::getDifficulty(){
  return difficulty_;
}
char Location::getSymbol(){
  return symbol_;
}

void Location::setName(string name){
  name_=name;
}
void Location::setDifficulty(int difficulty){
  difficulty_=difficulty;
}
void Location::setSymbol(char symbol){
  symbol_=symbol;
}