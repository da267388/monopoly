#ifndef DICE_H
#define DICE_H


class Dice
{
    private:
        int diceMaximum;
        int diceMinimum;
        bool isset; //是否被道具設定過
    public:
        Dice();
        int rollDice();
        void set_diceMaximum(int max);
        void set_diceMinimum(int min);
        bool getIsset();
        void setIsset(bool);
};

#endif // DICE_H
