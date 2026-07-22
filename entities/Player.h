#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../core/Map.h"


class Player: public Entity{
private:
public:
    Player(const std::string& name, int health, char player_symbol);

    void handle_movement( Map& game_map);
};



#endif //PLAYER_H
