
#ifndef ENDING_H
#define ENDING_H
#include <QMessageBox>
#include <QApplication>
#include "player.h"

class ending : public QMessageBox{

public:
    explicit ending(Player *player,QWidget* = nullptr);
    bool run(QApplication *app);
private:
    Player *winner;
};

#endif // ENDING_H
