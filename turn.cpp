#include "Turn.h"

turnLabel::turnLabel(){
    turn = 0;
    id = 0;
    setText(QObject::tr("<b><font face = DFKai-SB>回合 %1\n<font color = #FF6347><font face = DFKai-SB>玩家 %2</font><b>").arg(0).arg(0));
    setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    setStyleSheet("font-size:30px");
}

void turnLabel::changeLabel(){
    int round = turn / 4;
    switch (id) {
        case 0:
            setText(QObject::tr("<b><font face = DFKai-SB>回合 %1\n<font color = #FF6347><font face = DFKai-SB>玩家 %2</font><b>").arg(round).arg(id));
            break;
        case 1:
            setText(QObject::tr("<b><font face = DFKai-SB>回合 %1\n<font color = #4682B4><font face = DFKai-SB>玩家 %2</font><b>").arg(round).arg(id));
            break;
        case 2:
            setText(QObject::tr("<b><font face = DFKai-SB>回合 %1\n<font color = #8fbc8f><font face = DFKai-SB>玩家 %2</font><b>").arg(round).arg(id));
            break;
        case 3:
            setText(QObject::tr("<b><font face = DFKai-SB>回合 %1\n<font color = #FFD700><font face = DFKai-SB>玩家 %2</font><b>").arg(round).arg(id));
            break;
    }
    printf("trunLabel is changed\n");
    fflush(stdout);
}

QLabel* turnLabel:: dicelabel(QLabel *label, Player **player){
    dice = label;
    dice->setText(QObject::tr("Max : %1").arg(player[id]->getDiceMaximum()));
    dice->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    dice->setStyleSheet("font-size:15px; font-family: calibri");
    return dice;
}

void turnLabel::endTurn(Player **player){
    int round = turn / 4;
    printf("Round %d ended\n",round);
    fflush(stdout);
    turn++;
    round = turn / 4;
    id = turn % 4;
    printf("Round %d started,it's player%d turn\n",round,id);
    printf("turn:%d\n",turn);
    fflush(stdout);
    while(!player[id]->isAlive()||player[id]->isStop()){
        if(player[id]->isStop()){
            player[id]->setStop(false);
        }
        printf("pass the player%d\n",id);
        fflush(stdout);
        turn++;
        round = turn / 4;
        id = turn % 4;
        printf("Round %d started,it's player%d turn\n",round,id);
        printf("turn:%d\n",turn);
        fflush(stdout);
    }
    changeLabel();
    dice->setText(QObject::tr("Max : %1").arg(player[id]->getDiceMaximum()));
}

int turnLabel::getTurn(){
    return turn;
}

int turnLabel::getId(){
    return id;
}

Player* turnLabel::getWinner(Player** player){
    int aliveNum = 0;
    Player *winner = player[0];
    for(int i = 0; i < 4; i++){
        if(player[i]->isAlive()){
            winner = player[i];
            aliveNum++;
        }
    }
    if(this->getTurn() >= MAX_TURN){
        for(int i = 0; i < 4; i++){
            if(winner->getMoneyAmount() < player[i]->getMoneyAmount()){
                winner = player[i];
            }
        }
        return winner;
    }
    if(aliveNum == 1){
        return winner;
    }
    return nullptr;
}
void turnLabel::setTurn(int n){
    turn = n;
    id = n / 4;
    changeLabel();
}
