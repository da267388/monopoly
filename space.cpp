#include "space.h"

Space::Space(int id, QString name, int mode){
    spaceId = id;
    spaceName = name;
    actionMode = mode;
    for (int i = 0; i < 4; i++){
        players[i] = false;
    }
}

void Space::setId(int id){
    spaceId = id;
}

void Space::setSpaceName(QString name){
    spaceName = name;
}

void Space::setPlayers(int playerId, bool isHere){
    players[playerId] = isHere;
}

int Space::getId(){
    return spaceId;
}

QString Space::getSpaceName(){
    return spaceName;
}

bool* Space::getPlayers(){
    return players;
}
