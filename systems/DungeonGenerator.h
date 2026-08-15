#ifndef DUNGEON_H
#define DUNGEON_H


#include "core/Map.h"
#include "utils/Rng.h"
#include "utils/Vec2.h"
#include "core/Level.h"

class DungeonGenerator {
public:
    DungeonGenerator();
    Vec2 generate(Map& game_map);
    void spawn_enemies(Level &current_level, const Vec2 &player_pos, const std::vector<Enemy> &enemies_templates);
    void place_items(Level &current_level, const Vec2 &player_pos, const std::vector<std::unique_ptr<Item>> &items_templates);
private:
    void place_exit(Map& game_map);


};



#endif //DUNGEON_H
