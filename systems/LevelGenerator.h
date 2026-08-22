#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include <vector>
#include <memory>
#include "core/Map.h"
#include "utils/Rng.h"
#include "utils/Vec2.h"
#include "core/Level.h"

class Player;

enum class RoomType {
    Normal,
    Shop,
    Boss
};

class LevelGenerator {
public:
    LevelGenerator();
    void generate(Level& current_level, RoomType room_type, Player& player,
        const std::vector<Enemy>& enemies_templates, const std::vector<std::unique_ptr<Item>>& items_templates);

private:
    void generate_normal_level(Map& game_map, int direction_change_probability = 30);
    void generate_shop_level(Map& game_map);
    void place_exit(Map& game_map);

    void spawn_player(Level &current_level, Player& player);
    void spawn_enemies(Level &current_level, const Vec2 &player_pos, const std::vector<Enemy> &enemies_templates);
    void place_items(Level &current_level, const Vec2 &player_pos, const std::vector<std::unique_ptr<Item>> &items_templates);
};

#endif //LEVEL_GENERATOR_H
