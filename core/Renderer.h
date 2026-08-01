#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "Level.h"
#include "../entities/Player.h"
#include <conio.h>

class Renderer {
public:
    Renderer();
    void print(const Level& current_level, Player& player,  const std::vector<std::unique_ptr<Enemy>>& enemies) const;
    void print_player_stats(Player& player) const;
    void wait_for_enter() const;
    void print_current_text(const std::string& current_turn_text);

    void print_player_level_up(Player& player);
};

#endif //RENDERER_H
