#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

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
class chooseDialog;
}

class chooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chooseDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent = nullptr);
    ~chooseDialog();


private:
    Ui::chooseDialog *ui;
    Player **m_player;
    Game **m_land;
    landSpace **m_land_rsc;
    QPushButton *confirmButton;
    QRadioButton *btn[4];

};

#endif // CHOOSEDIALOG_H
