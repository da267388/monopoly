#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {
private:
    int playerId;
    string playerName;
    int moneyAmount;
    int position;
    int diceMaximum;
    int diceMinimum;
    bool alive;
    int jailTurn;
    bool stop;
    int holdItems[3];
    int holdCards[3];


public:
    //constructors
    //Player();
    Player(int playerId, int moneyAmount, int diceMaximum);

    //setting functions
    void setId(int playerId);
    void setPlayerName(string name);
    void setMoneyAmount(int amoumt);
    void setPosition(int pos);
    void setMaximum(int amount);
    void setAlive(bool status);
    void setJailTurn(int turn);
    void setStop(bool status);

    //functions to get values
    int getId();
    int getPosition();
    string getPlayerName();
    int getMoneyAmount();
    int getDiceMaximum();
    int getDiceMinimum();
    bool isAlive();
    int getJailTurn();
    bool isStop();
    int* getHoldItems();
    int* getHoldCards();

    //other
    void passStop(int n);
    void giveMoney(int amount);
    void takeMoney(int amount);
    void move(int amount);
    void increaseDiceMaximum(int amount);
    void passJailTurn();
    void newItem(int item);
    void newCard(int card);
    void delItem(int num);
    void delCard(int num);
};

#endif // PLAYER_H
