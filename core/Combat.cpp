#include "Combat.h"


Combat::Combat() {
    current_phase_ = TurnPhase::PLAYER;
    current_enemy_index_ = 0;
    current_entity_turn_text_ = "=== YOUR TURN ===";
}

CombatResult Combat::combat_loop(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map) {
    switch (current_phase_) {
        case TurnPhase::PLAYER: {
            player_turn(player, enemies, game_map);

            if (!enemies.empty()) {
                current_phase_ = TurnPhase::ENEMY;
                current_enemy_index_ = 0;
                current_entity_turn_text_ = "=== Enemy " + std::to_string(current_enemy_index_  + 1) + " " + enemies[current_enemy_index_]->get_name() + " ===";
                return CombatResult::WAIT_INPUT;
            }
            return CombatResult::CONTINUE;
        }
        case TurnPhase::ENEMY: {
            enemy_turn(*enemies[current_enemy_index_], player, game_map);

            if (!player.isAlive())
                return CombatResult::GAME_OVER;

            current_enemy_index_++;
            if (current_enemy_index_ >= enemies.size()) {
                current_phase_ = TurnPhase::PLAYER;
                current_entity_turn_text_ = "=== YOUR TURN ===";
                current_enemy_index_ = 0;
            }
            else {
                current_entity_turn_text_ = "=== Enemy " + std::to_string(current_enemy_index_  + 1) + " " + enemies[current_enemy_index_]->get_name() + " ===";

            }
            return CombatResult::WAIT_INPUT;
        }
    }
    return CombatResult::CONTINUE;
}

void Combat::player_turn(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map) {
    Vec2 new_pos  = player.move_player(game_map);

    bool attacked_enemy = false;

    for (auto& enemy: enemies) {
        if (new_pos == enemy->get_entity_pos() && enemy->isAlive()) {
            enemy->modify_health(-player.get_damage());
            attacked_enemy = true;
        }
    }

    if (attacked_enemy) {
        std::erase_if(enemies, [&player](auto& enemy) {
            if(!enemy->isAlive()) {
                player.add_xp(enemy->get_given_xp());
                return true;
            }

            return false;
        });
    }
    else {
        player.get_entity_pos() = new_pos;
    }
}

void Combat::enemy_turn(Enemy& enemy, Player& player, Map& game_map) {
    Vec2 new_pos = enemy.find_path_to_player(player.get_entity_pos(), game_map);

    if(new_pos == player.get_entity_pos()) {
        player.modify_health(-enemy.get_damage());
    }
    else {
        enemy.get_entity_pos() = new_pos;
    }
}


