#include "choosedialog.h"
#include "ui_choosedialog.h"
#include <QMessageBox>


chooseDialog::chooseDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseDialog),
    m_player(player),
    m_land(land),
    m_land_rsc(land_rsc)
{
    ui->setupUi(this);

    QGroupBox *groupBox = new QGroupBox("請選擇要與哪位玩家交換位置", this);
    QVBoxLayout *layout = new QVBoxLayout(this);

    //設置單選按鈕
    for(int i = 0; i < 4; i++){
        btn[i] = new QRadioButton("", groupBox);
        btn[i]->setText(QObject::tr("玩家 %1").arg(i));
        btn[i]->setProperty("id", QVariant(i));
        layout->addWidget(btn[i]);
    }
    confirmButton = new QPushButton("確定", this);


    //禁用按鈕
    for(int i = 0; i < 4; i++){
        if(i == id){
            btn[i]->setDisabled(true);
        }
        else if(m_player[i]->isAlive() == false){
            btn[i]->setDisabled(true);
        }
    }

    confirmButton->setDisabled(true);

    //連結確認按鈕並交換位置
    connect(confirmButton, &QPushButton::clicked, this, [this,id](){
        int selectId = -1;
        foreach (QRadioButton *button, findChildren<QRadioButton *>())
        {
            if (button->isChecked())
            {
                selectId = button->property("id").toInt();
                m_player[id]->delItem(2);
                break;
            }
        }

        int currentPosition = m_player[id]->getPosition();//目前玩家位置
        int changePosition = m_player[selectId]->getPosition();//被選玩家位置

        //移除玩家原位置
        m_land[currentPosition]->removePosition(id);
        m_land_rsc[currentPosition]->setPlayers(id, false);
        m_land[m_player[selectId]->getPosition()]->removePosition(selectId);
        m_land_rsc[m_player[selectId]->getPosition()]->setPlayers(selectId, false);

        //設置玩家新位置
        m_player[id]->setPosition(changePosition);
        m_player[selectId]->setPosition(currentPosition);
        m_land[m_player[id]->getPosition()]->setPosition(id);
        m_land_rsc[m_player[id]->getPosition()]->setPlayers(id, true);
        m_land[m_player[selectId]->getPosition()]->setPosition(selectId);
        m_land_rsc[m_player[selectId]->getPosition()]->setPlayers(selectId, true);
        this->close();
    });

    //連結單選按鈕與確認按鈕
    for (int i = 0; i < 4; i++){
        //若有單選按鈕被啟用，啟用確認按鈕
        connect(btn[i], &QRadioButton::toggled, this, [this](){
            confirmButton->setDisabled(false);
        });
    }

    groupBox->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(confirmButton);
    setLayout(mainLayout);
}

chooseDialog::~chooseDialog()
{
    delete ui;
}
