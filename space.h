#ifndef SPACE_H
#define SPACE_H

#include <string>
#include <QString>
#include "player.h"

using namespace std;

class Space {
    private:
        int spaceId;
        QString spaceName;
        bool players[4];
        int actionMode;
    

    public:
        Space(int id, QString name, int mode);


        void setId(int id);
        void setSpaceName(QString name);
        void setPlayers(int playerId, bool isHere);


        int getId();
        QString getSpaceName();
        bool* getPlayers();
};

#endif
