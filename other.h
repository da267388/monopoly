#ifndef OTHER_H
#define OTHER_H
#include <stdio.h>
#include <time.h>
#include <QApplication>
#include <QString>
#include <QtDebug>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include "GAME.h"
#include <QPalette>
#include "dice.h"
#include <QPushButton>
#include <QMessageBox>
#include "itemDialog.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include "carddialog.h"
#include "ruledialog.h"
#include <QIcon>
#include "space.h"
#include "land_space.h"
#include "dart.h"

void setStatus(Player * player, QLabel** playerStatus);

void move(QWidget *widget,Player *player, Game **land_img, landSpace **land, int dice, QLabel **playerStatus, dart *Dart);

//專門用來入獄的函數
void setJail(Player *player, Game **land_img, landSpace **land);
void outJail(Player *player);
void TakeMoney(Player *player, int money, QLabel **playerStatus);

void GiveMoney(QWidget *widget,Player *player ,int money, QLabel **playerStatus, Game **land_img, landSpace **land);
void knockOut(Player *player, Game **land_img, landSpace **land);

#endif // OTHER_H
