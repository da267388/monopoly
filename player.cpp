#include "player.h"

Player::Player(int id, int money, int initDice){
    playerId = id;
    playerName = "***";
    moneyAmount = money;
    position = 0;
    diceMaximum = initDice;
    diceMinimum = 1;
    alive = true;
    jailTurn = 0;
    stop = false;
    for (int i = 0; i < 3; i++){
        holdItems[i] = 0;
        holdCards[i] = 0;
    }
}


void Player::setId(int id){
    playerId = id;
}

void Player::setPlayerName(string name){
    playerName = name;
}

void Player::setMoneyAmount(int amount){
    moneyAmount = amount;
}

void Player::setPosition(int pos){
    position = pos;
}

void Player::setMaximum(int amount){
    diceMaximum = amount;
}

void Player::setAlive(bool status){
    alive = status;
}

void Player::setJailTurn(int turn){
    jailTurn = turn;
}

void Player::setStop(bool status){
    stop = status;
}

int Player::getId(){
    return playerId;
}

int Player::getPosition(){
    return position;
}

string Player::getPlayerName(){
    return playerName;
}

int Player::getMoneyAmount(){
    return moneyAmount;
}

int Player::getDiceMaximum(){
    return diceMaximum;
}

int Player::getDiceMinimum(){
    return  diceMinimum;
}

bool Player::isAlive(){
    return alive;
}

int Player::getJailTurn(){
    return jailTurn;
}

bool Player::isStop(){
    return stop;
}

int* Player::getHoldItems(){
    return holdItems;
}

int* Player::getHoldCards(){
    return holdCards;
}


void Player::giveMoney(int amount){
    moneyAmount = moneyAmount - amount;
}

void Player::takeMoney(int amount){
    moneyAmount = moneyAmount + amount;
}

void Player::move(int amount){
    position = (position + amount) % 28;
}

void Player::increaseDiceMaximum(int amount){
    diceMaximum = diceMaximum + amount;
}

void Player::passJailTurn(){
    jailTurn--;
}

void Player::newItem(int item){
    bool flag = true;
    for (int i = 0; i < 3; i++){
        if (holdItems[i] == 0){
            holdItems[i] = item;
            flag = false;
            break;
        }
    }
    if (flag){//if holdcard is full replace first card
        holdItems[0] = item;
    }
}

void Player::newCard(int card){
    bool flag = true;
    for (int i = 0; i < 3; i++){
        if (holdCards[i] == 0){
            holdCards[i] = card;
            flag = false;
            break;
        }
    }
    if (flag){//if holdcard is full replace first card
        holdCards[0] = card;
    }
}

void Player::delItem(int num){
    holdItems[num] = 0;
}

void Player::delCard(int num){
    holdCards[num] = 0;
}

