#include "changedialog.h"
#include "ui_changedialog.h"

changeDialog::changeDialog(int id, Player **player, landSpace **land_rsc, Game **land, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeDialog),
    m_player(player),
    m_land_rsc(land_rsc),
    m_land(land)
{
    ui->setupUi(this);

    QGroupBox *groupBox = new QGroupBox("請選擇要哪塊土地", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QGridLayout *gridLayout = new QGridLayout;
    layout->addLayout(gridLayout);

    //設置單選按鈕
    for(int i = 0; i < 28; i++){
        btn[i] = new QRadioButton("", groupBox);
        //btn[i]->setText(QObject::tr("land %1").arg(i));
        btn[i]->setProperty("id", QVariant(i));
        btn[i]->setDisabled(true);
        gridLayout->addWidget(btn[i], i / 4, i % 4);
    }

    btn[0]->setText("起點");
    btn[1]->setText("行政大樓");
    btn[2]->setText("理學館");
    btn[3]->setText("機會");
    btn[4]->setText("早餐好樂");
    btn[5]->setText("大禮堂");
    btn[6]->setText("圖書館");
    btn[7]->setText("監獄");
    btn[8]->setText("工學院");
    btn[9]->setText("創新大樓");
    btn[10]->setText("隱客廳");
    btn[11]->setText("機會");
    btn[12]->setText("管理學院");
    btn[13]->setText("果真");
    btn[14]->setText("飛鏢");
    btn[15]->setText("中正雞場");
    btn[16]->setText("機會");
    btn[17]->setText("七里香");
    btn[18]->setText("共教");
    btn[19]->setText("商店");
    btn[20]->setText("文學院");
    btn[21]->setText("入獄");
    btn[22]->setText("鳳梨田");
    btn[23]->setText("機會");
    btn[24]->setText("法學院");
    btn[25]->setText("宿舍");
    btn[26]->setText("骰子+1");
    btn[27]->setText("活動中心");

    confirmButton = new QPushButton("確定", this);
    groupBox->setLayout(layout);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(confirmButton);
    setLayout(mainLayout);
    confirmButton->setDisabled(true);


    //禁用按鈕
    for(int i = 0; i < 28; i++){
        Player* owner = m_land_rsc[i]->getOwner();
        if(owner != NULL && owner != m_player[id]){
            btn[i]->setDisabled(false);
        }
    }

    //連結確認按鈕並交換位置
    connect(confirmButton, &QPushButton::clicked, this, [this,id](){
        int select = -1;
        foreach (QRadioButton *button, findChildren<QRadioButton *>())
        {
            if (button->isChecked())
            {
                select = button->property("id").toInt();
                break;
            }
        }
        if(select != -1){
            m_land_rsc[select]->setOwner(m_player[id]);
            m_land[select]->MarkLand(id);
        }
        this->close();
    });

    //連結單選按鈕與確認按鈕
    for (int i; i < 28; i++){
        //若有單選按鈕被啟用，啟用確認按鈕
        connect(btn[i], &QRadioButton::toggled, this, [this](){
            confirmButton->setDisabled(false);
        });
    }
}


changeDialog::~changeDialog()
{
    delete ui;
}
