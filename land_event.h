#ifndef LAND_EVENT_H
#define LAND_EVENT_H
#include "fortune.h"

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
#include "itemdialog.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include "carddialog.h"
#include "ruledialog.h"
#include <QIcon>


#include "other.h"

void land_event(Player * player, QLabel **playerStatus, landSpace **land, Game **land_ima, QWidget *widget);

#endif // LAND_EVENT_H
