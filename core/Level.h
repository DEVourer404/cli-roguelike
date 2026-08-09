#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "Map.h"
#include <vector>
#include "../entities/Enemy.h"
#include <memory>

#include "../items/Item.h"

class Level {
public:
    Level(const std::string& level_name, const std::vector<Enemy> &enemies_templates, const std::vector<std::unique_ptr<Item>> &items_templates, int level_num = 0);

    Map& get_level_map();
    int get_level_num() const { return level_num_;}
    const std::string& get_level_name() const { return level_name_;}

    const Map::GameMapType& get_map_grid() const;

    void set_tile(int x, int y, char tile);
    void set_tile(const Vec2& pos, char tile);
    char get_tile(int x, int y) const;
    char get_tile(const Vec2& pos) const;
    bool is_walkable(const Vec2& vec2) const;

    void spawn_enemies(const Vec2& player_pos);
    void place_items(const Vec2& player_pos);

    std::vector<Enemy> enemies;
    std::vector<std::unique_ptr<Item>> items;
private:
    std::string level_name_;
    int level_num_;
    Map level_map_;
};



#endif //LEVEL_H
