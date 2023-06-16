#ifndef TURN_H
#define TURN_H
#include <QLabel>
#include "player.h"
#include "itemDialog.h"
#include "carddialog.h"
#include <QPushButton>
#include "initialStates.h"
class turnLabel :public QLabel{
public:
    void changeLabel();
    void endTurn(Player **player);
    int getTurn();
    int getId();
    turnLabel();
    QLabel *dicelabel(QLabel *label,Player **player);
    Player* getWinner(Player**);
    void setTurn(int n);
private:
    int turn;
    int id;
    QLabel *dice;
signals:
    void turnChange(Player**);
};

#endif // TURN_H
