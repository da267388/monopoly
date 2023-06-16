#include "jaildialog.h"
#include "ui_jaildialog.h"

#include "other.h"

jailDialog::jailDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent) :
    QDialog(parent),
    //ui(new Ui::jailDialog),
    m_player(player),
    m_land_rsc(land_rsc),
    m_land(land)
{
    QGroupBox *groupBox = new QGroupBox("請選擇哪位玩家入獄", this);
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

    //連結確認按鈕
    connect(confirmButton, &QPushButton::clicked, this, [this,id](){
        int selectId = -1;
        foreach (QRadioButton *button, findChildren<QRadioButton *>())
        {
            if (button->isChecked())
            {
                selectId = button->property("id").toInt();
                break;
            }
        }
        if(selectId != -1){
            setJail(m_player[selectId], m_land, m_land_rsc);
        }
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

jailDialog::~jailDialog()
{
    //delete ui;
}
