#include "ending.h"

ending::ending(Player *player,QWidget *parent):
    QMessageBox(parent)
{
    winner = player;
    int id = winner->getId();
    this->setText(QObject::tr("恭喜玩家 %1獲勝!\n是否再玩一次?").arg(id));
    this->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
}

bool ending::run(QApplication *app){
    int x = this->exec();
    switch(x){
    case QMessageBox::Yes:
        app->exit(0);
        return true;
    case QMessageBox::No:
        app->exit(0);
        return false;
    }
    return false;
}
