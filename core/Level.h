#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "Map.h"
#include <vector>
#include "../entities/Enemy.h"
#include <memory>

class Level {
public:
    Level(const std::string& level_name, int level_num);

    Map& get_level_map();
    int get_level_num() const { return level_num_;}
    const std::string& get_level_name() const { return level_name_;}

    const Map::GameMapType& get_map_grid() const;

    void set_tile(int x, int y, char tile);
    char get_tile(int x, int y) const;

    bool is_walkable(const Vec2& vec2) const;

    std::vector<std::unique_ptr<Enemy>> enemies;
private:
    std::string level_name_;
    int level_num_;
    Map level_map_;
};



#endif //LEVEL_H
