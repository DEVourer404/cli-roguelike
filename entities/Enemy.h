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
    int max_health_;
    int given_xp_;
    int damage_;
public:
    Enemy(const std::string& name, int health, int damage, char enemy_symbol, int given_xp);
    Vec2 find_path_to_player(const Vec2& player_pos, const Map& game_map);

    int get_given_xp() const;
    int get_damage() const override;

    int get_max_health() const override;
};



#endif //ENEMY_H
