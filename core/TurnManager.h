#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "ConsoleUI.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "utils/Vec2.h"
#include <algorithm>

class TurnManager {
private:
    void player_turn(Player& player, Level& current_level);
    void enemy_turn(Enemy &enemy, Player &player, Level &current_level);

    bool handle_player_attack(Player& player, Level& current_level, Vec2 new_pos);
    bool handle_merchant(Player& player, Level& current_level, Vec2 new_pos);
    bool handle_item_pickup(Player& player, Level& current_level, Vec2 new_pos);

    bool resolve_attack(const Entity& attacker, Entity& target);
public:
    TurnManager();
    void process_turn(Player& player, Level& current_level);
};

#endif //TURN_MANAGER_H
