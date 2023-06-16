#include "other.h"
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
#include <QPushButton>
#include "GAME.h"
#include "dice.h"
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

//更新玩家狀態欄
void setStatus(Player * player, QLabel** playerStatus){
    int id = player->getId();
    if (player->isAlive())
        playerStatus[id]->setText(QObject::tr("玩家 %1\n$ %2").arg(id).arg(player->getMoneyAmount()));
    else
        playerStatus[id]->setText(QObject::tr("玩家 %1\n你破產了!").arg(id));//破產


}

void move(QWidget *widget,Player *player, Game **land_img, landSpace **land, int dice, QLabel **playerStatus, dart* Dart){//改變玩家位置

    int old = player->getPosition();//紀錄舊位置
    player->move(dice+28);//負數才不會出錯（機會命運倒退）
    int id = player->getId();
    land_img[old]->removePosition(id);
    land[old]->setPlayers(id, false);
    //land_img[player->getPosition()]->setPosition(id);
    land[player->getPosition()]->setPlayers(id, true);


    //判斷是否有“經過”起點，機會命運倒退不用算
    if(dice > 0){
        for(int i = 1; i <= dice; i++){
            if ((old + i) % 28 == 0){
                //機會命運到達起點會觸發
                QMessageBox *msg = new QMessageBox(widget);
                msg->setText("你經過起點，選擇想要的獎勵");
                QPushButton *m = msg->addButton("獲得2000元", QMessageBox::ButtonRole::ActionRole);
                msg->addButton("骰子點數+1", QMessageBox::ButtonRole::ActionRole);
                msg->setDefaultButton(m);
                auto ret = msg->exec();
                QMessageBox* msg2 = new QMessageBox(widget);
                if (ret == 0){
                    msg2->setText(QObject::tr("獲得2000元"));
                    TakeMoney(player, 2000, playerStatus);
                }
                else if(ret == 1){
                    player->increaseDiceMaximum(1);
                    int dice = player->getDiceMaximum();
                    msg2->setText(QObject::tr("骰子點數+1\n目前骰子點數為 ： %1").arg(dice));
                }
                msg2->exec();
            }
            else if((old + i) % 28 == 14){
                //機會命運到達飛鏢會觸發
                QMessageBox *msg = new QMessageBox(widget);
                QPushButton *tollBtn = msg->addButton("",QMessageBox::AcceptRole);
                QIcon icon;
                icon.addFile(":/image/pic/dice.png");
                tollBtn->setIcon(icon);
                tollBtn->setIconSize(QSize(35, 20));
                tollBtn->show();
                msg->setWindowTitle("DART");
                msg->setText("你經過飛鏢\n請投擲點數");
                msg->setWindowFlags(Qt::WindowTitleHint|Qt::Dialog|Qt::CustomizeWindowHint);
                msg->exec();
                if (msg->clickedButton() == (QAbstractButton*)tollBtn){
                    Dice dice;
                    int diceroll = 0;
                    dice.set_diceMaximum(player->getDiceMaximum());
                    diceroll = dice.rollDice();
                    QMessageBox* msg2 = new QMessageBox(widget);
                    if(Dart->getDart() - diceroll >= 0){
                        Dart->minusDart(diceroll);
                    }
                    else{
                        Dart->addDart(diceroll);
                    }
                    msg2->setText(QObject::tr("您骰到 %1 點\n目前飛鏢剩下點數 : %2").arg(diceroll).arg(Dart->getDart()));
                    msg2->exec();

                }

            }

        }
    }
    if (Dart->getDart() != 0){
        land_img[player->getPosition()]->setPosition(id);
    }

}

void outJail(Player *player){
    player->setJailTurn(0);
}

//專門用來入獄的函數
void setJail(Player *player, Game **land_img, landSpace **land){//改變玩家位置
    player->setJailTurn(3);
    int old = player->getPosition();//紀錄舊位置
    player->setPosition(7);
    int id = player->getId();
    land_img[old]->removePosition(id);
    land[old]->setPlayers(id, false);
    land_img[player->getPosition()]->setPosition(id);
    land[7]->setPlayers(id, true);
}

//機會命運賞金專用
void TakeMoney(Player *player, int money, QLabel **playerStatus){
    player-> takeMoney(money);
    setStatus(player,playerStatus);
}

//機會命運罰金專用
void GiveMoney(QWidget *widget, Player *player ,int money, QLabel **playerStatus, Game **land_img, landSpace **land){
    player-> giveMoney(money);

    if (player->getMoneyAmount() < 0){
        QMessageBox *msg = new QMessageBox(widget);
        msg->setText("您的錢不足以支付罰金，你破產了!");
        msg->exec();
        knockOut(player, land_img, land);
    }
    setStatus(player, playerStatus);

}

//淘汰
void knockOut(Player *player, Game **land_img, landSpace **land){
    player->setAlive(false);
    int id = player->getId();
    land_img[player->getPosition()]->removePosition(id);//移除地圖標記
    for(int i = 0; i < 28; i++){
        if (land[i]->getOwner() == player){
            land[i]->setOwner(nullptr);//移除土地
            land[i]->setHouseAmount(0);
            land_img[i]->del_LandMark();//移除土地標記
            land_img[i]->getPriceLabel()->setText(QObject::tr("$ %1").arg(land[i]->getPrice()));
        }
    }

}
