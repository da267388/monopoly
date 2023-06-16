#include "dice.h"
#include <cstdlib>
#include <ctime>

Dice::Dice(){
    diceMaximum = 6;
    diceMinimum = 1;
    isset = false;
}

void Dice::set_diceMaximum(int max){
    diceMaximum = max;
}

void Dice::set_diceMinimum(int min){
    diceMinimum = min;
}

int Dice::rollDice(){

    int roll = 0;
    srand( time(NULL) );
    roll = rand() % (diceMaximum - diceMinimum + 1) + diceMinimum;

    return roll;
}

bool Dice::getIsset(){
    return isset;
}

void Dice::setIsset(bool set){
    isset = set;
}
