#include <stdio.h>
#include <time.h>
#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QObject>
#include <QApplication>
#include <QString>
#include <QtDebug>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "player.h"

class Game : public QObject {
    Q_OBJECT
    public:

    Game(QLabel * Name, QLabel *price, QLabel *p1, QLabel *p2, QLabel *p3, QLabel *p4, int w, int h){
        landName = Name;
        landPrice = price;
        Player[0] = p1;
        Player[1] = p2;
        Player[2] = p3;
        Player[3] = p4;
        this->w = w;
        this->h = h;
        //設置label中文本的對齊方式
        //置中對齊，底色都為白色，字體為黑色，LandName字體大小為20px
        landName->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
        //landName->setFrameStyle(QFrame::Panel + QFrame::Plain);
        landName->setStyleSheet("background-color :white;font-family: DFKai-SB;font-size:20px; color:black;border:1px solid black");
        landName->setFixedSize(w/8,h/8);
        landPrice->setAlignment(Qt::AlignHCenter| Qt::AlignCenter);
        //landPrice->setFrameStyle(QFrame::Panel + QFrame::Plain);
        landPrice->setStyleSheet("background-color :white; color:black;font-family: DFKai-SB;border:1px solid black");
        for(int i = 0; i < 4; i++){
            Player[i]->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
            Player[i]->setFrameStyle(QFrame::Panel + QFrame::Plain);
            Player[i]->setFixedWidth(landName->width()/4);
            Player[i]->setStyleSheet("background-color :white; border:1px solid black");
            Player[i]->setText("");
        }

    }

    //標記土地
    void MarkLand(int id){
        switch (id) {
            case 0:
                this->landName->setStyleSheet("background-color : tomato;font-family: DFKai-SB;font-size:20px; color:black");
                break;
            case 1:
                this->landName->setStyleSheet("background-color :steelblue;font-family: DFKai-SB;font-size:20px; color:black");
                break;
            case 2:
                this->landName->setStyleSheet("background-color :darkseagreen;font-family: DFKai-SB;font-size:20px; color:black");
                break;
            case 3:
               this->landName->setStyleSheet("background-color :gold;font-family: DFKai-SB;font-size:20px; color:black");
                break;
        }
    }
    //移除土地標記
    void del_LandMark(){
        landName->setStyleSheet("background-color : white;font-family: DFKai-SB;font-size:20px; color:black;border:1px solid black");
    }

    //設置玩家標記
    void setPosition(int id)
    {
        switch (id) {
            case 0:
                this->Player[0]->setText("<b><font color = tomato><size = 20px>●</font></b>");
                break;
            case 1:
                this->Player[1]->setText("<b><font color = steelblue>< size = 20px>●</font></b>");
                break;
            case 2:
                this->Player[2]->setText("<b><font color = darkseagreen><size = 20px>●</font></b>");
                break;
            case 3:
                this->Player[3]->setText("<b><font color = gold><size = 20px>●</font></b>");
                break;

        }
    }
    //移除玩家標記
    void removePosition(int id){
        switch (id) {
            case 0:
                this->Player[0]->setText("");
                break;
            case 1:
                this->Player[1]->setText("");
                break;
            case 2:
                this->Player[2]->setText("");
                break;
            case 3:
                this->Player[3]->setText("");
                break;

        }
    }

    //這個QVBoxLayout等於一格土地，照理來說應該要設在private然後用函數提出來，但我好懶ㄛ
    QVBoxLayout *grid = new QVBoxLayout;

    //初始化土地
    void setLand(QString name, int price){
        //開始設置地名和價錢（特殊土地我先不顯示價錢）
        landName->setText(name);
        landPrice->setText(QObject::tr("$ %1").arg(price));
        //下面都是在排列，我先把顯示玩家的四個小格裝在一個HLayout再跟地名價錢的label做排列
        landName->setFixedSize(w/8, h/8*0.6);
        landPrice->setFixedSize(w/8, h/8*0.2);
        QHBoxLayout *Hgrid = new QHBoxLayout;
        Hgrid->setAlignment(Qt::AlignHCenter);
        for(int i = 0 ; i < 4; i++){
            Hgrid->addWidget(Player[i]);
            Player[i]->setFixedSize(w/32, h/8*0.2);
        }
        grid->setSpacing(0);
        grid->setContentsMargins(0, 0, 0, 0);
        grid->addWidget(landPrice, 2);
        grid->addWidget(landName, 4);
        grid->addLayout(Hgrid);
    }

    QLabel* getPriceLabel(){
        return landPrice;
    }


    //初始化土地
    void setUniqueLand(){
        landName->setText(" ");
        landName->setFixedSize(w/8, h/8*0.8);

        QHBoxLayout *Hgrid = new QHBoxLayout;
        Hgrid->setAlignment(Qt::AlignHCenter);
        for(int i = 0 ; i < 4; i++){
            Hgrid->addWidget(Player[i]);
            Player[i]->setFixedSize(w/32, h/8*0.2);
        }
        grid->setSpacing(0);
        grid->setContentsMargins(0, 0, 0, 0);
        grid->addWidget(landName, 4);
        grid->addLayout(Hgrid);
    }
    QLabel **getplayer(){
        return &Player[0];
    }

    QLabel* getName(){
        return landName;
    }

   
    private:
    //下面用於土地
    QLabel *landName ;
    QLabel *landPrice;
    QLabel *Player[4] ;
    int w;
    int h;

};


#endif // GAME_H
