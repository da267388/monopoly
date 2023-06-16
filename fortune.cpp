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
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <QIcon>
#include "other.h"
#include "dart.h"

void fortune(QWidget *widget, Game **land_img,landSpace ** land ,Player** player, int id, QLabel **playerStatus, dart *Dart){

    //31選1
    int n;
    srand( time(NULL) );
    n = rand() % 31 + 1;
    QMessageBox *msg = new QMessageBox(widget);
    msg->setText("");

    switch (n) {

    case 1: case 2:{
        msg->setText("恭喜你入獄了！吃牢飯囉");
        setJail(player[id], land_img, land);
        msg->exec();
    }
        break;
    case 3: case 4:
        msg->setText("恭喜你獲得出獄卡！");
        player[id]->newCard(1);
        msg->exec();
        break;
    case 5: case 6:
        msg->setText("你太調皮，被禁止行動一回合了");
        player[id]->setStop(true);
        msg->exec();
        break;

    case 7:{
        int p;
        int alive[4];//紀錄活著的人
        int num = 0;//活人人數
        for(int i = 0; i < 4; i++){
            if(player[i]->isAlive()){
                alive[num++] = player[i]->getId();
            }
        }
        if (num == 1){
            setJail(player[id], land_img, land);
            p = id;
        }
        else{
            srand( time(NULL) );
            p = alive[rand()%num];//哪位玩家被抽到了
            setJail(player[p], land_img, land);
        }
        msg->setText(QObject::tr("緊張刺激，隨機入獄時間\n恭喜玩家 %1入獄哈哈哈").arg(p));
        msg->exec();
    }
        break;
    case 8:
    {
        player[id]->increaseDiceMaximum(1);
        int dice = player[id]->getDiceMaximum();
        msg->setText(QObject::tr("骰子點數+1\n目前骰子點數為 ：%1").arg(dice));
        msg->exec();

    }
        break;
    case 9:{
        msg->setText("貧民最喜歡的快樂均富時間");
        msg->exec();
        int money = 0;
        int alive = 0;
        for(int i = 0; i < 4; i++){
            if (player[i]->isAlive()){
                money += player[i]->getMoneyAmount();
                alive++;
            }

        }
        money = money / alive;
        for(int i = 0; i < 4; i++){
            if(player[i]->isAlive()){
                player[i]->setMoneyAmount(money);
                setStatus(player[i],playerStatus);
            }
        }


    }
        break;
    case 10:
        msg->setText("飛鏢-100卡");
        player[id]->newCard(3);
        msg->exec();
        break;

    case 11: case 12:
        msg->setText("飛鏢+100卡");
        player[id]->newCard(2);
        msg->exec();
        break;

    case 13: {
        msg->setText("前進5格");
        msg->exec();
        move(widget,player[id], land_img, land, 5, playerStatus, Dart);

    }
        break;

    case 14:
        msg->setText("後退5格");
        msg->exec();
        move(widget,player[id], land_img, land, -5, playerStatus, Dart);

        break;
    case 15:
        msg->setText("前進2格");
        msg->exec();
        move(widget,player[id], land_img, land, 2, playerStatus, Dart);

        break;


    case 16:
        msg->setText("後退2格");
        msg->exec();
        move(widget,player[id], land_img, land, -2, playerStatus, Dart);

        break;

    case 17: case 18:
    {
        msg->setText("+500元");
        msg->exec();
        TakeMoney(player[id], 500, playerStatus);

    }
        break;
    case 19: case 20:
    {
        msg->setText("你媽媽沒有教過你不能闖紅燈嗎，請你繳罰金500元");
         msg->exec();
        GiveMoney(widget, player[id], 500, playerStatus, land_img, land);

    }
        break;
    case 21: case 22:
    {
        msg->setText("+1000元");
        TakeMoney(player[id], 1000, playerStatus);
        msg->exec();
    }
        break;
    case 23: case 24:
    {
        msg->setText("我想不到了，總之給我把1000元拿來");
        msg->exec();
        GiveMoney(widget, player[id], 1000, playerStatus, land_img, land);

    }
        break;
    case 25: case 26:
    {
        msg->setText("哈囉，給你1500元");
        TakeMoney(player[id] , 1500, playerStatus);
        msg->exec();
    }
        break;
    case 27: case 28:
    {
        msg->setText("恭喜！你被突然出現的CCU開拓者聯盟勒索了1500元");
        msg->exec();
        GiveMoney(widget, player[id], 1500, playerStatus, land_img, land);

    }
        break;
    case 29: case 30:
    {
        msg->setText("你家失火了，恭喜你獲得賠償2000元");
        TakeMoney(player[id], 2000, playerStatus);
        msg->exec();
    }
        break;
    case 31:
    {
        msg->setText("你家狗死了，你花了2000元幫狗勾辦喪事");
        msg->exec();
        GiveMoney(widget, player[id], 2000, playerStatus, land_img, land);

    }
        break;


    }



}





