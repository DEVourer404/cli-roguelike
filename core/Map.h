#ifndef MAP_H
#define MAP_H

#include <array>
#include "utils/Vec2.h"

class Map {
public:
    static constexpr int WIDTH = 20;
    static constexpr int HEIGHT = 15;

    Map();

    using GameMapType = std::array<std::array<char, WIDTH>, HEIGHT>;
    const GameMapType& get_game_map() const;

    void set_tile(int x, int y, char tile);
    void set_tile(const Vec2& pos, char tile);
    char get_tile(int x, int y) const;
    char get_tile(const Vec2& pos) const;


    void fill_map();

    bool is_walkable(const Vec2& vec2) const;

private:
    std::array<std::array<char, WIDTH>, HEIGHT> game_map_{};
};



#endif //MAP_H
