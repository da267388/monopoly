#include "storedialog.h"
#include "ui_storedialog.h"

#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include <random>

StoreDialog::StoreDialog(QLabel **PlayerStatus, Player **player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreDialog),
    m_player(player),
    m_PlayerStatus(PlayerStatus)
{
    ui->setupUi(this);

    //顯示道具名
    QLabel *label0 = new QLabel("請選擇欲購買之道具:  (隨機產生三樣)");
    label0->setFixedHeight(50);
    QLabel *label1 = new QLabel("出獄卡");
    QLabel *label2 = new QLabel("交換位址");
    QLabel *label3 = new QLabel("更換骰子");
    QLabel *label4 = new QLabel("換房子/土地主人");
    QLabel *label5 = new QLabel("入獄卡");
    QGridLayout *Layout = new QGridLayout(this);
    Layout->addWidget (label0, 0, 0);
    Layout->addWidget (label1, 1, 0);
    Layout->addWidget (label2, 2, 0);
    Layout->addWidget (label3, 3, 0);
    Layout->addWidget (label4, 4, 0);
    Layout->addWidget (label5, 5, 0);

    //顯示道具價錢
    QLabel *price1 = new QLabel("$ 1000");
    QLabel *price2 = new QLabel("$ 1000");
    QLabel *price3 = new QLabel("$ 1000");
    QLabel *price4 = new QLabel("$ 5500");
    QLabel *price5 = new QLabel("$ 2000");
    Layout->addWidget (price1, 1, 1);
    Layout->addWidget (price2, 2, 1);
    Layout->addWidget (price3, 3, 1);
    Layout->addWidget (price4, 4, 1);
    Layout->addWidget (price5, 5, 1);


    //顯示按鈕
    btn1 = new QPushButton("購買");
    btn1->setFixedSize(50, 20);
    btn2 = new QPushButton("購買");
    btn2->setFixedSize(50, 20);
    btn3= new QPushButton("購買");
    btn3->setFixedSize(50, 20);
    btn4 = new QPushButton("購買");
    btn4->setFixedSize(50, 20);
    btn5 = new QPushButton("購買");
    btn5->setFixedSize(50, 20);
    Layout->addWidget(btn1, 1, 2);
    Layout->addWidget(btn2, 2, 2);
    Layout->addWidget(btn3, 3, 2);
    Layout->addWidget(btn4, 4, 2);
    Layout->addWidget(btn5, 5, 2);

    setLayout(Layout);

}

StoreDialog::~StoreDialog()
{
    delete ui;
}

void StoreDialog::setID(int id){
    this->id = id;

    item = m_player[this->id]->getHoldItems();
    money = m_player[this->id]->getMoneyAmount();

    //按鈕列表
    QList<QPushButton *> buttons;
    buttons << btn1 << btn2 << btn3 << btn4 << btn5;

    //按鈕預設為可使用
    for(int i = 0; i < 5; i++) {
        buttons[i]->setEnabled(true);
    }

    QObject::connect(btn1, &QPushButton::clicked, [this](){
        //餘額不足
        if(money < 1000){
            QMessageBox::warning(this, "store", "餘額不足! 無法購買");
            btn1->disconnect();
        }
        //已有相同道具
        else if((item[0] == 1) || (item[1] == 1) || (item[2] == 1)){
            QMessageBox::warning(this, "store", "已有此道具! 無法購買");
            btn1->disconnect();
        }
        else{
            m_player[this->id]->giveMoney(1000);
            m_player[this->id]->newItem(1);
            setStatus(m_player[this->id], m_PlayerStatus);
            this->close();
            btn1->disconnect();
        }
    });

    QObject::connect(btn2, &QPushButton::clicked, [&](){
        //餘額不足
        if(money < 1000){
            QMessageBox::warning(this, "store", "餘額不足! 無法購買");
            btn2->disconnect();
        }
        //已有相同道具
        else if((item[0] == 2) || (item[1] == 2) || (item[2] == 2)){
            QMessageBox::warning(this, "store", "已有此道具! 無法購買");
            btn2->disconnect();
        }
        else{
            m_player[this->id]->giveMoney(1000);
            m_player[this->id]->newItem(2);
            setStatus(m_player[this->id], m_PlayerStatus);
            close();
            btn2->disconnect();
        }
    });

    QObject::connect(btn3, &QPushButton::clicked, [&](){
        //餘額不足
        if(money < 1000){
            QMessageBox::warning(this, "store", "餘額不足! 無法購買");
            btn3->disconnect();
        }
        //已有相同道具
        else if((item[0] == 3) || (item[1] == 3) || (item[2] == 3)){
            QMessageBox::warning(this, "store", "已有此道具! 無法購買");
            btn3->disconnect();
        }
        else{
            m_player[this->id]->giveMoney(1000);
            m_player[this->id]->newItem(3);
            setStatus(m_player[this->id], m_PlayerStatus);
            close();
            btn3->disconnect();
        }
    });

    QObject::connect(btn4, &QPushButton::clicked, [&](){
        //餘額不足
        if(money < 5500){
            QMessageBox::warning(this, "store", "餘額不足! 無法購買");
            btn4->disconnect();
        }
        //已有相同道具
        else if((item[0] == 4) || (item[1] == 4) || (item[2] == 4)){
            QMessageBox::warning(this, "store", "已有此道具! 無法購買");
            btn4->disconnect();
        }
        else{
            m_player[this->id]->giveMoney(5500);
            m_player[this->id]->newItem(4);
            setStatus(m_player[this->id], m_PlayerStatus);
            close();
            btn4->disconnect();
        }
    });

    QObject::connect(btn5, &QPushButton::clicked, [&]() {
        //餘額不足
        if(money < 2000){
            QMessageBox::warning(this, "store", "餘額不足! 無法購買");
            btn5->disconnect();
        }
        //已有相同道具
        else if((item[0] == 5) || (item[1] == 5) || (item[2] == 5)){
            QMessageBox::warning(this, "store", "已有此道具! 無法購買");
            btn5->disconnect();
        }
        else{
            m_player[this->id]->giveMoney(2000);
            m_player[this->id]->newItem(5);
            setStatus(m_player[this->id], m_PlayerStatus);
            close();
            btn5->disconnect();
        }
    });


    //隨機禁用兩個按鈕 (三個可用)
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(buttons.begin(), buttons.end(), rng);

    for(int i = 0; i < 2; i++) {
        buttons[i]->setEnabled(false);
    }

}

