#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "Level.h"
#include "../entities/Player.h"
#include <conio.h>

class Renderer {
public:
    Renderer();
    void print(const Level& current_level, Player& player) const;
    void print_player_stats(Player& player) const;
    void wait_for_enter() const;
    void print_current_text(const std::string& current_turn_text);

    int print_player_level_up(const Player& player);
    int show_inventory(const Player& player);
};

#endif //RENDERER_H
