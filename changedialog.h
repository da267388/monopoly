#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

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
class changeDialog;
}

class changeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent = nullptr);
    ~changeDialog();

private:
    Ui::changeDialog *ui;
    Player **m_player;
    landSpace **m_land_rsc;
    Game **m_land;
    QPushButton *confirmButton;
    QRadioButton *btn[28];

};

#endif // CHANGEDIALOG_H
