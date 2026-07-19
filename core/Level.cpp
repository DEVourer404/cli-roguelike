#include "Level.h"


Level::Level(const std::string& level_name, int level_num):
level_name_(level_name), level_num_(level_num)  {}


Map& Level::get_level_map() {
    return level_map_;
}

const Map::GameMapType& Level::get_map_grid() const {
    return level_map_.get_game_map();
}

char Level::get_tile(int x, int y) const { return level_map_.get_tile(x,y);}
void Level::set_tile(int x, int y, char tile) { level_map_.set_tile(x,y, tile); }
bool Level::is_walkable(const Vec2 &vec2) const { return level_map_.is_walkable(vec2); }


