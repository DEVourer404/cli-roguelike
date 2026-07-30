#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../core/Map.h"
#include <vector>
#include <memory>

class Enemy;

class Player: public Entity{
private:
public:
    Player(const std::string& name, int health, char player_symbol);
    Vec2 move_player(Map& game_map);
};



#endif //PLAYER_H
