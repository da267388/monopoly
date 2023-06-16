#ifndef FORTUNE_H
#define FORTUNE_H
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
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <QIcon>
#include "other.h"
#include "space.h"
#include "land_space.h"

void fortune(QWidget *widget, Game **land_img, landSpace ** land, Player** player, int id, QLabel **playerStatus, dart *Dart);


#endif // FORTUNE_H
