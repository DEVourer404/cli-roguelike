#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <string>
#include "Level.h"
#include "entities/Player.h"

namespace Renderer {
    void print_game(const Level& current_level, Player& player);
    void print_player_stats(Player& player);
    void print_current_text(const std::string& current_turn_text);
    void clear_screen();
}

namespace UI {
    bool show_inventory(Player& player);
    int show_level_up(const Player& player);
    void show_wait_for_enter();
    bool show_move_to_new_level();
    void show_merchant_dialogue(Player& player);
    bool show_buy_item_prompt(const Item& item, int player_gold);
}

#endif // CONSOLE_UI_H
