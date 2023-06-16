#include "land_space.h"

landSpace::landSpace(int id, QString name, int mode, int price, Player* owner) : Space(id, name, mode){
    landPrice = price;
    landOwner = owner;//NULL == noboby
    houseAmount = 0;
}


void landSpace::setPrice(int price){
    landPrice = price;
}

void landSpace::setOwner(Player* owner){
    landOwner = owner;
}

void landSpace::setHouseAmount(int amount){
    houseAmount = amount;
}

int landSpace::getPrice(){
    return landPrice;
}

Player* landSpace::getOwner(){
    return landOwner;
}

int landSpace::getHouseAmount(){
    return houseAmount;
}

void landSpace::buyLand(Player* player){
    player->giveMoney(landPrice);
    landOwner = player;
}

void landSpace::buildHouse(Player* player){
    player->giveMoney(landPrice / 2);
    houseAmount++;
}

void landSpace::payRent(Player* player){
    int rent = 0;
    if (houseAmount == 0){
        rent = landPrice / 5;
    }
    else if(houseAmount == 1){
        rent = landPrice / 2;
    }
    else if(houseAmount == 2){
        rent = landPrice;
    }
    else if(houseAmount == 3){
        rent = landPrice * 2;
    }
    player->giveMoney(rent);
    landOwner->takeMoney(rent);
}
