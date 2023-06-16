#include "itemdialog.h"
#include "ui_itemdialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QMessageBox>
#include "choosedialog.h"
#include "other.h"
#include "jaildialog.h"
#include "changedialog.h"

ItemDialog::ItemDialog(Player **player, landSpace **land_rsc, Game **land, Dice *dice, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemDialog),
    m_player(player),
    m_land_rsc(land_rsc),
    m_land(land),
    m_dice(dice)
{
    ui->setupUi(this);


    //顯示道具名
    label0 = new QLabel("玩家 0 :");
    label0->setFixedSize(50, 50);
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


    //數量初值
    for(int i = 1; i < 6; i++)
    {
        num[i] = new QLabel("");
        num[i]->setText("            0");
        Layout->addWidget (num[i], i, 1);
    }

    //顯示按鈕
    for(int i = 1; i < 6; i++)
    {
        btn[i] = new QPushButton("使用");
        btn[i]->setFixedSize(50, 20);
        btn[i]->setDisabled(true);
        Layout->addWidget (btn[i], i, 2);
    }

    setLayout(Layout);

}



ItemDialog::~ItemDialog()
{
    delete ui;
}


void ItemDialog::setID(int nextId){
    id = nextId;
    //更改目前玩家
    label0->setText(QObject::tr("玩家 %1 :").arg(id));

    //玩家是否暫停回合
    stop = m_player[this->id]->getJailTurn();

    //顯示道具個數
    int *item;
    item = m_player[id]->getHoldItems();

    for(int i=0;i<3;i++){
        if(item[i]!=0){
            this->index[item[i]] = i;
        }
    }

    for(int i = 1; i < 6; i++)
    {
        if((i == item[0]) || (i == item[1]) || (i == item[2]))
            num[i]->setText("            1");
        else
            num[i]->setText("            0");
    }

    chooseDialog *choosedialog = new chooseDialog(id, m_player, m_land_rsc, m_land);
    choosedialog->setWindowTitle("change");
    choosedialog->setModal(true);
    this->choose = choosedialog;
    jailDialog  *jaildialog = new jailDialog(id, m_player, m_land_rsc, m_land);
    jaildialog->setWindowTitle("jail");
    jaildialog->setModal(true);
    this->jail = jaildialog;
    changeDialog  *changedialog = new changeDialog(id, m_player, m_land_rsc, m_land);
    changedialog->setWindowTitle("change");
    changedialog->setModal(true);
    this->change = changedialog;

    //道具使用
    //出獄卡
    QObject::connect(btn[1], &QPushButton::clicked, [&](){
        QMessageBox::information(this, "jail", "恭喜出獄!");
        m_player[this->id]->delItem(this->index[1]);
        num[1]->setText("            0");
        outJail(m_player[this->id]);
        btn[1]->disconnect();
        btn[1]->setDisabled(true);
    });

    //交換位置
    QObject::connect(btn[2], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用道具");
        }
        else{
            m_player[this->id]->delItem(this->index[2]);
            num[2]->setText("            0");
            this->choose->show();
            btn[2]->setDisabled(true);
        }
        btn[2]->disconnect();
    });
    //交換骰子
    QObject::connect(btn[3], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用道具");
        }
        else{
            m_player[this->id]->delItem(this->index[3]);
            num[3]->setText("            0");

            m_dice->setIsset(true);
            QMessageBox *msg = new QMessageBox(this);
            msg->setText(QObject::tr("請選擇要哪種骰子"));
            /*QPushButton *small = */msg->addButton("小骰子(1~3)",QMessageBox::ActionRole);
            /*QPushButton *big = */msg->addButton("大骰子(4~6)", QMessageBox::ActionRole);
            int buttonClicked = msg->exec();
            if (buttonClicked == 0) {
                m_dice->set_diceMaximum(3);
                m_dice->set_diceMinimum(1);
            }
            else if(buttonClicked == 1){
                m_dice->set_diceMaximum(6);
                m_dice->set_diceMinimum(4);
            }
            btn[3]->setDisabled(true);
        }
        btn[3]->disconnect();
    });
    //交換房地產
    QObject::connect(btn[4], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用道具");
        }
        else{
            m_player[this->id]->delItem(this->index[4]);
            num[4]->setText("            0");
            this->change->show();
            btn[4]->setDisabled(true);
        }
        btn[4]->disconnect();
    });
    //入獄卡
    QObject::connect(btn[5], &QPushButton::clicked, [&](){
        if(stop != 0){
            QMessageBox::warning(this, "card", "目前為暫停狀態\n無法使用道具");
        }
        else{
            m_player[this->id]->delItem(this->index[5]);
            num[5]->setText("            0");
            this->jail->show();
            btn[5]->setDisabled(true);
        }
        btn[5]->disconnect();
    });

    //禁用按鈕
    for(int i = 1; i < 6; i++){
        if((i != item[0]) && (i != item[1]) && (i != item[2])){
            btn[i]->setDisabled(true);
        }
        else{
            btn[i]->setDisabled(false);
        }
    }

}
