#include "land_event.h"
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
#include "itemDialog.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include "carddialog.h"
#include "ruledialog.h"
#include <QIcon>
#include "other.h"


void land_event(Player * player, QLabel **playerStatus, landSpace **land, Game **land_img, QWidget *widget){
    int pos = player->getPosition();
    if(land[pos]->getOwner() == nullptr){
        QMessageBox *msg = new QMessageBox(widget);
        msg->setText(QObject::tr("土地名 : %1\n土地價錢 : %2\n請問您是否要購買這塊土地?").arg(land[pos]->getSpaceName()).arg(land[pos]->getPrice()));
        QPushButton *buyBtn = msg->addButton("購買",QMessageBox::AcceptRole);
        QPushButton *close = msg->addButton("不購買", QMessageBox::RejectRole);

        msg->exec();
        if (msg->clickedButton() == (QAbstractButton*)buyBtn) {
            //購買土地
            if(player->getMoneyAmount() >= land[pos]->getPrice()){
            land[pos]->buyLand(player);
            setStatus(player, playerStatus);
            land_img[pos]->MarkLand(player->getId());
            land_img[pos]->getPriceLabel()->setText(QObject::tr("過路費: $ %1  房子: %2").arg(land[pos]->getPrice()/5).arg(land[pos]->getHouseAmount()));
            }
            else{
                QMessageBox *msg2 = new QMessageBox(widget);
                msg2->setText("你的錢不足以購買這塊土地");
                msg2->exec();
            }
        }
        //不購買
        else if(msg->clickedButton() == (QAbstractButton*)close){
            msg->reject();
        }
    }
    //加蓋
    else if (land[pos]->getOwner() == player){

        QMessageBox *msg = new QMessageBox(widget);
        msg->setText(QObject::tr("土地名 : %1\n加蓋價錢 : %2\n房子數量 : %3\n請問您是否要加蓋?").arg(land[pos]->getSpaceName()).arg(land[pos]->getPrice()/2).arg(land[pos]->getHouseAmount()));
        QPushButton *buyBtn = msg->addButton("加蓋",QMessageBox::AcceptRole);
        QPushButton *close = msg->addButton("不加蓋", QMessageBox::RejectRole);
        msg->exec();
        if (msg->clickedButton() == (QAbstractButton*)buyBtn) {
            if(player->getMoneyAmount() < (land[pos]->getPrice())/2){
                QMessageBox *msg2 = new QMessageBox(widget);
                msg2->setText("你的錢不足以加蓋");
                msg2->exec();
            }
            else if(land[pos]->getHouseAmount() == 3){
                QMessageBox *msg2 = new QMessageBox(widget);
                msg2->setText("加蓋數量已達上限");
                msg2->exec();
            }
            else{
                land[pos]->buildHouse(player);
                setStatus(player, playerStatus);

                int rent = 0;
                int houseAmount = land[pos]->getHouseAmount();
                int landPrice = land[pos]->getPrice();
                if (houseAmount == 0){
                    rent = landPrice / 5;
                }
                else if(houseAmount == 1){
                    rent = landPrice / 2;
                }
                else if(houseAmount == 2){
                    rent = landPrice;
                }
                else if(houseAmount == 3){
                    rent = landPrice * 2;
                }
                land_img[pos]->getPriceLabel()->setText(QObject::tr("過路費: $ %1  房子: %2").arg(rent).arg(houseAmount));
            }
        }
        else if(msg->clickedButton() == (QAbstractButton*)close){
            msg->reject();
        }
    }
    else{
        //收過路費
        QMessageBox *msg = new QMessageBox(widget);
        int rent = 0;
        int houseAmount = land[pos]->getHouseAmount();
        int landPrice = land[pos]->getPrice();
        int moneyAmount = player->getMoneyAmount();
        //算過路費
        if (houseAmount == 0){
            rent = landPrice / 5;
        }
        else if(houseAmount == 1){
            rent = landPrice / 2;
        }
        else if(houseAmount == 2){
            rent = landPrice;
        }
        else if(houseAmount == 3){
            rent = landPrice * 2;
        }

        if (player->getMoneyAmount() < rent){
            msg->setText(QObject::tr("你踩到玩家 %1的土地\n您的錢不足以支付過路費 %2元").arg(land[pos]->getOwner()->getId()).arg(rent));
            msg->exec();
            land[pos]->getOwner()->takeMoney(moneyAmount);//若玩家錢不足以支付過路費，則其剩餘的錢會通通給土地擁有者
            knockOut(player, land_img, land);//淘汰
        }
        else{
            msg->setText(QObject::tr("你踩到玩家 %1的土地\n支付過路費 %2元").arg(land[pos]->getOwner()->getId()).arg(rent));
            msg->exec();
            land[pos]->payRent(player);
        }

        setStatus(player, playerStatus);
        setStatus(land[pos]->getOwner(), playerStatus);
    }
}
