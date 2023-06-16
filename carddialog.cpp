#include "carddialog.h"
#include "ui_carddialog.h"
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include "other.h"

CardDialog::CardDialog(Player **player, landSpace **land_rsc, Game **land, dart *Dart, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardDialog),
    m_player(player),
    m_land_rsc(land_rsc),
    m_land(land),
    m_Dart(Dart)
{
    ui->setupUi(this);
    label0 = new QLabel("玩家 0 :");
    label0->setFixedSize(50, 50);
    QLabel *label1 = new QLabel("出獄卡");
    QLabel *label2 = new QLabel("飛鏢格 +100");
    QLabel *label3 = new QLabel("飛鏢格 -100");
    QGridLayout *Layout = new QGridLayout(this);
    Layout->addWidget (label0, 0, 0);
    Layout->addWidget (label1, 1, 0);
    Layout->addWidget (label2, 2, 0);
    Layout->addWidget (label3, 3, 0);

    for(int i = 1; i < 4; i++){
        //顯示卡片個數
        num[i] = new QLabel("");
        num[i]->setText("            0");
        Layout->addWidget (num[i], i, 1);

        //顯示按鈕
        btn[i] = new QPushButton("使用");
        btn[i]->setFixedSize(50, 20);
        btn[i]->setDisabled(true);
        Layout->addWidget(btn[i], i, 2);
    }
    setLayout (Layout);


}

CardDialog::~CardDialog()
{
    delete ui;
}

void CardDialog::setID(int nextId){
    id = nextId;
    //更改目前玩家
    label0->setText(QObject::tr("玩家 %1 :").arg(id));

    //玩家是否暫停回合
    stop = m_player[this->id]->getJailTurn();

    //顯示卡片個數
    int *card;
    card = m_player[id]->getHoldCards();
    for(int i=0;i<3;i++){
        if(card[i]!=0){
            this->index[card[i]] = i;
        }
    }

    for(int i = 1; i < 4; i++)
    {
        if((i == card[0]) || (i == card[1]) || (i == card[2]))
            num[i]->setText("            1");
        else
            num[i]->setText("            0");
    }

    //卡片使用
    QObject::connect(btn[1], &QPushButton::clicked, [&](){
        QMessageBox::information(this, "jail", "恭喜出獄!");
        m_player[this->id]->delCard(this->index[1]);
        num[1]->setText("            0");
        outJail(m_player[this->id]);
        btn[1]->disconnect();
        btn[1]->setDisabled(true);
    });

    QObject::connect(btn[2], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用卡片");
        }
        else{
            m_player[this->id]->delCard(this->index[2]);
            num[2]->setText("            0");
            m_Dart->addDart(100);
            btn[2]->setDisabled(true);
        }
        btn[2]->disconnect();
    });

    QObject::connect(btn[3], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用卡片");
        }
        else{
            m_player[this->id]->delCard(this->index[3]);
            num[3]->setText("            0");
            m_Dart->minusDart(100);
            btn[3]->setDisabled(true);
        }
        btn[3]->disconnect();
    });

    //禁用按鈕
    for(int i = 1; i < 4; i++){
        if((i != card[0]) && (i != card[1]) && (i != card[2])){
            btn[i]->setDisabled(true);
        }
        else{
            btn[i]->setDisabled(false);
        }
    }
}
