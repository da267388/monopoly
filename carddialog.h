#ifndef CARDDIALOG_H
#define CARDDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "player.h"
#include "mainwindow.h"
#include "GAME.h"
#include "land_space.h"
#include "dart.h"

namespace Ui {
class CardDialog;
}

class CardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CardDialog(Player **player, landSpace **land_rsc, Game **land, dart *Dart, QWidget *parent = nullptr);
    ~CardDialog();
    void setID(int id);

private:
    Ui::CardDialog *ui;
    Player **m_player;
    landSpace **m_land_rsc;
    Game **m_land;
    dart *m_Dart;
    int id;
    QLabel *label0;
    QLabel *num[4];
    int *card;
    QPushButton *btn[4];
    int stop;
    int index[4];
};

#endif // CARDDIALOG_H
