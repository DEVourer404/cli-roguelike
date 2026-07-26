#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <string>
#include <queue>
#include "Entity.h"
#include "../utils/Vec2.h"
#include "../core/Map.h"

class Enemy: public Entity {
private:

public:
    Enemy(const std::string& name, int health, int damage, char enemy_symbol);

    void take_turn(Entity& player, const const Map& game_map);

    Vec2 find_path_to_player(const Vec2& player_pos, const Map& game_map);
};



#endif //ENEMY_H
