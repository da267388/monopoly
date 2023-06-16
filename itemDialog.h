#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include "player.h"
#include "mainwindow.h"
#include "GAME.h"
#include "chooseDialog.h"
#include "land_space.h"
#include "dice.h"

namespace Ui {
class ItemDialog;
}

class ItemDialog : public QDialog
{
    Q_OBJECT


public:
    explicit ItemDialog(Player **player, landSpace **land_rsc, Game **land, Dice *dice, QWidget *parent = nullptr);
    ~ItemDialog();
    void setID(int id);


private:
    Ui::ItemDialog *ui;
    Player **m_player;
    landSpace **m_land_rsc;
    Game **m_land;
    Dice *m_dice;
    int id;
    QLabel *label0;
    QLabel *num[6];
    int *item;
    QDialog *choose;
    QPushButton *btn[6];
    QDialog *jail;
    int stop;
    QDialog *change;
    int index[6];

};

#endif // ITEMDIALOG_H
