#include "mainwindow.h"
#include <stdio.h>
#include <time.h>
#include <QApplication>
#include <QString>
#include <QtDebug>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QImage>
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
#include "fortune.h"
#include <QThread>
#include <QPicture>
#include "space.h"
#include "land_space.h"
#include "land_event.h"
#include "storedialog.h"
#include "other.h"
#include "jaildialog.h"
#include "changedialog.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "turn.h"
#include "dart.h"
#include "ending.h"
#include "initialStates.h"

int main(int argc, char *argv[])
{
    bool playAgain = false;
    QApplication app(argc, argv);
    QWidget *widget = new QWidget;

    //中間版面設計
    Player *player[4];
        for(int i = 0; i < 4; i++){
           player[i] = new Player(i, MONEY, DICE_MAX);
    }
    QVBoxLayout *center= new QVBoxLayout;//用來合併回合＋玩家狀態欄
    turnLabel *Turn = new turnLabel;
    QLabel *label = new QLabel();//放骰子最大值
    QLabel *PlayerStatus[4];
    QHBoxLayout *diceLayout = new QHBoxLayout();//排列骰子和骰子最大值
    QHBoxLayout *status = new QHBoxLayout();//玩家狀態欄
    status->setContentsMargins(2, 2, 2, 2);
    status->setSpacing(15);
    for(int i = 0; i < 4; i++){
        PlayerStatus[i] = new QLabel;//一格玩家狀態欄
        PlayerStatus[i]->setText(QObject::tr("玩家 %1\n$ %2").arg(i).arg(MONEY));
        //設底色
        switch (i) {
            case 0:
                PlayerStatus[i]->setStyleSheet("background-color: tomato; font-family: DFKai-SB;font-size:18px");
                PlayerStatus[i]->setAlignment(Qt::AlignCenter);
                break;
            case 1:
                PlayerStatus[i]->setStyleSheet("background-color: steelblue;font-family: DFKai-SB;font-size:18px");
                PlayerStatus[i]->setAlignment(Qt::AlignCenter);
                break;
            case 2:
                PlayerStatus[i]->setStyleSheet("background-color : darkseagreen;font-family: DFKai-SB;font-size:18px");
                PlayerStatus[i]->setAlignment(Qt::AlignCenter);
                break;
            case 3:
                PlayerStatus[i]->setStyleSheet("background-color : gold;font-family: DFKai-SB;font-size:18px");
                PlayerStatus[i]->setAlignment(Qt::AlignCenter);
                break;
        }
        status->addWidget(PlayerStatus[i]);
    }

    //骰子按鈕
    QPushButton *dicebtn = new QPushButton("", widget);
    dicebtn->setFixedSize(80, 50);
    QIcon icon;
    icon.addFile(":/image/pic/dice.png");
    dicebtn->setIcon(icon);
    dicebtn->setIconSize(QSize(60, 60));
    diceLayout->addWidget(dicebtn);
    diceLayout->addWidget(Turn->dicelabel(label,player));
    status->addLayout(diceLayout);
    center->addWidget(Turn);
    center->addLayout(status);
    center->setSpacing(10);


    //設定音效
    QAudioOutput *audioOutput = new QAudioOutput();
    audioOutput->setVolume(50);

    QMediaPlayer *diceSound = new QMediaPlayer();
    QUrl diceUrl("qrc:/audio/audio/dice_sound.mp3");
    diceSound->setSource(diceUrl);

    QMediaPlayer *roulette= new QMediaPlayer();
    QUrl rouletteUrl("qrc:/audio/audio/roulette.mp3");
    roulette->setSource(rouletteUrl);

    if(diceSound->hasAudio()){
        printf("dice audio was set\n");
    }
    else{
        printf("dice audio error\n");
    }

    QStringList LandName;//用來裝地名的
    LandName<<"起點 →"<<"行政大樓"<<"理學院"<<"機會"<<"早餐好樂"<<"大禮堂"<<"圖書館"<<"監獄"<<"工學院"<<"創新大樓"<<"隱客廳"<<"機會"<<"管理學院"<<"果真"<<"飛鏢"<<"中正雞場"
            <<"機會"<<"七里香"<<"共教"<<"商店"<<"文學院"<<"入獄"<<"鳳梨田"<<"機會"<<"法學院"<<"宿舍"<<"骰子點數\n+1"<<"活動中心";
    int LandPrice[28] = {0, 1000, 2000, 0, 1500, 1000, 2500, 0, 3500, 2000, 1500, 0, 4000, 3000, 0, 2500, 0, 4500, 3000, 0, 3500, 0, 4000, 0, 5000, 4500, 0, 5000};
    Game *land[28];

    landSpace *land_rsc[28];

    widget->showFullScreen();

    for(int i = 0; i < 28; i++){
        QLabel *landName = new QLabel;
        QLabel *landPrice = new QLabel;
        QLabel *P1 = new QLabel;
        QLabel *P2 = new QLabel;
        QLabel *P3 = new QLabel;
        QLabel *P4 = new QLabel;

        //開始初始化
        land[i] = new Game(landName, landPrice, P1, P2, P3, P4, widget->width(), widget->height());
        
        if( (i == 0) | (i == 14) |(i == 21)){
            land[i]->setUniqueLand();
            land[i]->getName()->setText(LandName.at(i));
            land[i]->getName()->setStyleSheet("QLabel{"
                                             "background-color : white;font-size:25px;color:black;font-family: DFKai-SB;border:1px solid black"
                                             "}");
            land[i]->getName()->setFrameStyle(QFrame::Panel + QFrame::Plain);
            land_rsc[i] = new landSpace(i, LandName.at(i), 1, 0, nullptr);
        }
        else if((i == 3) | (i == 11) | (i == 16) | (i == 23)){
            land[i]->setUniqueLand();
            land[i]->getName()->setText("?");
            land[i]->getName()->setStyleSheet("QLabel{"
                                             "background-color : #CBD6E2;font-size:40px;color:black;font-family: calibri;border:1px solid black"
                                             "}");
            //land[i]->getName()->setFrameStyle(QFrame::Panel + QFrame::Plain);
            land_rsc[i] = new landSpace(i, LandName.at(i), 1, 0, nullptr);
        }
        else if(i == 19){
            land[i]->setUniqueLand();
            land[i]->getName()->setStyleSheet("QLabel{"
                                             "border-image:url(:/image/pic/store.png) ;"
                                              "background-color :#CBD6E2;font-size:20px; color:black"
                                              "}" );
            land_rsc[i] = new landSpace(i, LandName.at(i), 1, 0, nullptr);
        }
        else if(i == 26){
            land[i]->setUniqueLand();
            land[i]->getName()->setStyleSheet("QLabel{"
                                               "border-image:url(:/image/pic/dice.png) 450 1 ;"
                                              "background-color :#CBD6E2;font-size:20px; color:black"
                                             "}");
            land_rsc[i] = new landSpace(i, LandName.at(i),1, 0, nullptr);
        }
        else if(i == 7){
            land[i]->setUniqueLand();
            land[i]->getName()->setStyleSheet("QLabel{"
                                             "border-image:url(:/image/pic/jail.png)  ;"
                                              "background-color :#CBD6E2;font-size:20px; color:black"
                                              "}");
           land_rsc[i] = new landSpace(i, LandName.at(i), 1, 0, nullptr);
        }
        else{
            land_rsc[i] = new landSpace(i, LandName.at(i), 0, LandPrice[i], nullptr);
            land[i]->setLand(LandName.at(i), LandPrice[i]);
        }
    }

    for(int i = 0; i < 4; i++){
        land[0]->setPosition(i);
        land_rsc[0]->setPlayers(i, true);
    }

    //初始化飛鏢
    dart* Dart = new dart(DART, land[14]->getName());

    //排地圖，相當於我把整個畫面切成8*8，依序把地塞進去
    QGridLayout *grid = new QGridLayout(widget);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setGeometry(QRect(0, 0, 10, 100));
    int l = 1;
    int m = 6;
    int n = 7;
    for (int i = 0; i < 28; i++) {
        if(i < 8)
            grid->addLayout(land[i]->grid, 0, i);
        else if(i < 14)
            grid->addLayout(land[i]->grid, l++, 7);
        else if(i < 22)
            grid->addLayout(land[i]->grid, 7, n--);
        else
            grid->addLayout(land[i]->grid, m--, 0);
    }
    grid->addLayout(center, 1, 2, 1, 4);


    Player *winner = nullptr;
    Dice *dice = new Dice;
    StoreDialog storedialog(PlayerStatus, player, widget);
    storedialog.setWindowTitle("Store");
    storedialog.setModal(true);
    ItemDialog itemDialog(player, land_rsc, land, dice, widget);
    itemDialog.setWindowTitle("Items");
    itemDialog.setModal(true);
    CardDialog cardDialog(player, land_rsc, land, Dart, widget);
    cardDialog.setWindowTitle("Cards");
    cardDialog.setModal(true);
    RuleDialog ruleDialog(widget);
    ruleDialog.setWindowTitle("Rules");
    ruleDialog.setFixedSize(850, 600);
    ruleDialog.move((widget->width() - 850)/2, (widget->height() - 600)/2);
    ruleDialog.setModal(true);
    //道具按鈕
    QPushButton *btn1 = new QPushButton("道具", widget);
    btn1->setStyleSheet("font-family: DFKai-SB;font-size:15px");
    btn1->setFixedSize(100, 50);
    btn1->move(200, 350);
    btn1->show();
    QObject::connect(btn1, &QPushButton::clicked, [&](){
        itemDialog.setWindowTitle("Items");
        itemDialog.show();
    });

    //卡片按鈕
    QPushButton *btn2 = new QPushButton("卡片", widget);
    btn2->setStyleSheet("font-family: DFKai-SB;font-size:15px");
    btn2->setFixedSize(100, 50);
    btn2->move(200, 430);
    btn2->show();
    QObject::connect(btn2, &QPushButton::clicked, [&](){
        cardDialog.setWindowTitle("Cards");
        cardDialog.show();
    });

    //規則按鈕
    QPushButton *btn3 = new QPushButton("遊戲規則", widget);
    btn3->setStyleSheet("font-family: DFKai-SB;font-size:15px");
    btn3->setFixedSize(100, 50);
    btn3->move(200, 510);
    btn3->show();
    QObject::connect(btn3, &QPushButton::clicked, [&](){
        ruleDialog.setWindowTitle("Rules");
        ruleDialog.show();
    });

    QObject::connect(dicebtn, &QPushButton::clicked, [&](){
        //int turn = Turn->getTurn();
        int id = Turn->getId();
        int diceroll = 0;

        //如果在監獄擲骰子看是否可以出去
        if(player[id]->getJailTurn()){
            diceroll = dice->rollDice();
            diceSound->setAudioOutput(audioOutput);
            diceSound->play();
            QMessageBox msg(QMessageBox::Information, "dice", QObject::tr("玩家 %1\n點數 : %2").arg(id).arg(diceroll));
            msg.exec();
            if(diceroll == 1){
                outJail(player[id]);//出獄
                QMessageBox::information(widget, "jail", "骰到1點\n恭喜出獄!");
                //dice->setIsset(false)  //道具只作用在骰出獄的骰子
                //dice->setIsset(true)   //道具作用在出獄與移動的骰子(預設)
            }
            else{
                player[id]->passJailTurn();
                int jail = player[id]->getJailTurn();
                if(jail != 0){
                QMessageBox msg(QMessageBox::Information, "jail", QObject::tr("Player %1\n 還須服刑%2回合").arg(id).arg(jail));
                msg.exec();
                }
                else{
                QMessageBox msg(QMessageBox::Information, "jail", QObject::tr("Player %1\n 恭喜出獄!").arg(id));
                msg.exec();
                }
                dice->setIsset(false);
                //結束回合
                Turn->endTurn(player);
                if( (winner = Turn->getWinner(player) ) != nullptr ){
                ending end(winner, widget);
                playAgain = end.run(&app);
                return;
                }
                itemDialog.setID(id);
                cardDialog.setID(id);
            }
            return ;
            //是否滿三回合，若否減少回合
        }

        //set dice
        if(!dice->getIsset()){
            dice->set_diceMaximum(player[id]->getDiceMaximum());
            dice->set_diceMinimum(player[id]->getDiceMinimum());
        }

        int newPos;

        //擲骰子
        diceroll = dice->rollDice();
        diceSound->setAudioOutput(audioOutput);
        diceSound->play();
        dice->setIsset(false);

        //顯示擲出的點數
        QMessageBox msg(QMessageBox::Information, "dice", QObject::tr("玩家 %1\n點數 : %2 ").arg(id).arg(diceroll));
        msg.exec();

        //玩家移動
        move(widget, player[id], land, land_rsc, diceroll, PlayerStatus, Dart);

        //獲勝
        if(Dart->getDart() == 0){
            winner = player[id];
            ending end(winner, widget);
            playAgain = end.run(&app);
            return;
        }

        //land event
        newPos = player[id]->getPosition();
        if(newPos == 3 || newPos == 11 || newPos == 16 || newPos == 23){
            roulette->setAudioOutput(audioOutput);
            roulette->play();
            QMessageBox msg2(widget);
            msg2.setText("命運的輪盤正在轉動");
            msg2.exec();
            fortune(widget, land, land_rsc, player, id, PlayerStatus, Dart);
        }
        else if(newPos == 19){
            storedialog.setID(id);
            storedialog.show();
            setStatus(player[id], PlayerStatus);
        }
        else if(newPos == 0 || newPos == 7 || newPos == 14){
            //jail不觸發任何事件
            //起點飛鏢在移動時就已經觸發了
        }
        else if(newPos == 21){
            msg.setText(QObject::tr("你入獄囉!"));
            msg.exec();
            setJail(player[id], land, land_rsc);
        }
        else if(newPos == 26){
            QMessageBox msg(widget);
            player[id]->increaseDiceMaximum(1);
            int dice = player[id]->getDiceMaximum();
            msg.setText(QObject::tr("骰子點數+1\n目前骰子點數為 ： %1").arg(dice));
            msg.exec();

        }
        else{
            land_event(player[id],PlayerStatus, land_rsc, land, widget);
        }

        //結束回合
        Turn->endTurn(player);
        id = Turn->getId();
        if( (winner = Turn->getWinner(player) ) != nullptr ){
            ending end(winner,widget);
            playAgain = end.run(&app);
            return;
        }
        //連結新id給按鈕
        itemDialog.setID(id);
        cardDialog.setID(id);
        return;
    });

    widget->show();
    app.exec();
    
    while(playAgain == true){   //再玩一次
        playAgain = false;
        printf("play again\n");
        fflush(stdout);

        //初始化
        winner = nullptr;
        Turn->setTurn(0);
        for(int i = 0; i < 28; i++){
            if( (i == 0) | (i == 14) | (i == 21) | (i == 3) | (i == 11) | (i == 16) | (i == 23) | (i == 19) | (i == 26) | (i == 7)){

            }
            else{
                land_rsc[i] = new landSpace(i, LandName.at(i), 0, LandPrice[i], nullptr);
                land_rsc[i]->setHouseAmount(0);
                land_rsc[i]->setOwner(nullptr);
                land[i]->setLand(LandName.at(i), LandPrice[i]);
                land[i]->del_LandMark();
            }
            for(int j = 0; j < 4; j++){
                land[i]->removePosition(j);
            }
        }
        for(int i = 0; i < 4; i++){
            land[0]->setPosition(i);
            land_rsc[0]->setPlayers(i, true);
        }
        for(int i = 0; i < 4; i++){
            player[i]->setAlive(true);
            player[i]->setJailTurn(0);
            player[i]->setMaximum(DICE_MAX);
            player[i]->setPosition(0);
            player[i]->setStop(false);
            player[i]->setMoneyAmount(MONEY);
            for(int j = 0; j < 3; j++){
                player[i]->delCard(j);
                player[i]->delItem(j);
            }
        }
        for(int i = 0; i < 4; i++){
            setStatus(player[i],PlayerStatus);
        }
        Dart->setDart(DART);
        widget->show();
        app.exec();
    }

    return 0;
}

