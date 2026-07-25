#include "Map.h"

Map::Map() {
    fill_map();
}

const Map::GameMapType& Map::get_game_map() const {
    return game_map_;
}

void Map::set_tile(int x, int y, char tile) {
    game_map_[y][x] = tile;
}

void Map::set_tile(const Vec2 &pos, char tile) {
    game_map_[pos.y][pos.x] = tile;
}

char Map::get_tile(int x, int y) const {
    return game_map_[y][x];
}

char Map::get_tile(const Vec2 &pos) const {
    return game_map_[pos.y][pos.x];
}

void Map::fill_map() {
    for(auto& row: game_map_) {
        row.fill('#');
    }
}

bool Map::is_walkable(const Vec2& vec2) const{
    if(vec2.x < 1 || vec2.x > WIDTH-2 || vec2.y < 1 || vec2.y > HEIGHT-2)
        return false;

    char tile = get_tile(vec2.x,vec2.y);

    if(tile == '#')
        return false;
    else
        return true;
}


