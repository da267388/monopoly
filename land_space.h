#ifndef LAND_SPACE_H
#define LAND_SPACE_H

#include "space.h"

class landSpace : public Space{
    private:
        int landPrice;
        Player* landOwner;
        int houseAmount;


    public:
        landSpace(int id, QString name, int mode,  int price, Player* owner);

        void setPrice(int price);
        void setOwner(Player* owner);
        void setHouseAmount(int amount);


        int getPrice();
        Player* getOwner();
        int getHouseAmount();


        void buyLand(Player* player);
        void buildHouse(Player* player);
        void payRent(Player* player);
};

#endif
