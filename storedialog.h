#ifndef STOREDIALOG_H
#define STOREDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include "player.h"
#include "mainwindow.h"
#include "GAME.h"
#include "itemDialog.h"
#include "other.h"


namespace Ui {
class StoreDialog;
}

class StoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StoreDialog(QLabel **PlayerStatus, Player **player, QWidget *parent = nullptr);
    void setID(int id);

    ~StoreDialog();

private:
    Ui::StoreDialog *ui;
    Player **m_player;
    QLabel **m_PlayerStatus;
    int id;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    int money;
    int *item;


};

#endif // STOREDIALOG_H
