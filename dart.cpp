#include "dart.h"
#include <QLabel>

dart::dart(int n, QLabel* label)
{
    this->point = n;
    this->label = label;
    this->label->setText(QObject::tr("飛鏢  %1").arg(this->point));
    this->label->setStyleSheet("font-family: DFKai-SB;font-size:25px;background-color :#CBD6E2; color:black");
}

int dart::getDart(){
    return this->point;
}

//改變飛鏢點數
void dart::setDart(int point){
    this->point = point;
    label->setText(QObject::tr("飛鏢  %1").arg(this->point));
}

void dart::addDart(int point){
    this->point += point;
    label->setText(QObject::tr("飛鏢  %1").arg(this->point));
}

void dart::minusDart(int point){
    if (this->point - point < 0){
        this->point = 1;
    }
    else{
        this->point -= point;
    }
    label->setText(QObject::tr("飛鏢  %1").arg(this->point));
}
