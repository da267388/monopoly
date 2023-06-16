#ifndef JAILDIALOG_H
#define JAILDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include "itemDialog.h"
#include "player.h"
#include "GAME.h"
#include "land_space.h"

namespace Ui {
class jailDialog;
}

class jailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit jailDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent = nullptr);
    ~jailDialog();

private:
    Ui::jailDialog *ui;
    Player **m_player;
    landSpace **m_land_rsc;
    Game **m_land;
    QPushButton *confirmButton;
    QRadioButton *btn[4];
};

#endif // JAILDIALOG_H
