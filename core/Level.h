#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "Map.h"
#include <vector>
#include "entities/Enemy.h"
#include <memory>

#include "items/Item.h"

class Level {
public:
    Level(const std::string& level_name, int level_num = 0);

    Map& get_level_map();
    int get_level_num() const { return level_num_;}
    const std::string& get_level_name() const { return level_name_;}

    const Map::GameMapType& get_map_grid() const;

    std::vector<Enemy> enemies;
    std::vector<std::unique_ptr<Item>> items;

    Enemy* enemy_at(const Vec2& player_pos);
    Item* item_at(const Vec2& player_pos);
private:
    std::string level_name_;
    int level_num_;
    Map level_map_;
};



#endif //LEVEL_H
