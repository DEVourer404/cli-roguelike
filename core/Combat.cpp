#include "Combat.h"

Combat::Combat() {
    current_phase_ = TurnPhase::PLAYER;
    current_enemy_index_ = 0;
    current_entity_turn_text_ = "=== YOUR TURN ===";
}

CombatResult Combat::combat_loop(Player& player, Level& current_level, Renderer& renderer) {
    switch (current_phase_) {
        case TurnPhase::PLAYER: {
            player_turn(player, current_level, renderer);

            if (!current_level.enemies.empty()) {
                current_phase_ = TurnPhase::ENEMY;
                current_enemy_index_ = 0;
                current_entity_turn_text_ = "=== Enemy " + std::to_string(current_enemy_index_  + 1) + " " + current_level.enemies[current_enemy_index_].get_name() + " ===";
                return CombatResult::WAIT_INPUT;
            }
            return CombatResult::CONTINUE;
        }
        case TurnPhase::ENEMY: {
            enemy_turn(current_level.enemies[current_enemy_index_], player, current_level.get_level_map());

            if (!player.isAlive())
                return CombatResult::GAME_OVER;

            current_enemy_index_++;
            if (current_enemy_index_ >= current_level.enemies.size()) {
                current_phase_ = TurnPhase::PLAYER;
                current_entity_turn_text_ = "=== YOUR TURN ===";
                current_enemy_index_ = 0;
            }
            else {
                current_entity_turn_text_ = "=== Enemy " + std::to_string(current_enemy_index_  + 1) + " " + current_level.enemies[current_enemy_index_].get_name() + " ===";

            }
            return CombatResult::WAIT_INPUT;
        }
    }
    return CombatResult::CONTINUE;
}

void Combat::player_turn(Player& player, Level& current_level, Renderer& renderer) {
    bool turn_ended = false;

    while (!turn_ended) {
        char key = player.get_key();

        if (key == 'I') {
            int item_index = renderer.show_inventory(player);
            if (item_index >= 0) {
                // player.use_item(item_index);
                turn_ended = true;
            } else {
                system("cls");
                renderer.print(current_level, player);
                renderer.print_current_text(current_entity_turn_text_);
            }
        }
        else if (key == 'W' || key == 'A' || key == 'S' || key == 'D') {
            Vec2 new_pos = player.move_player(current_level.get_level_map(), key);

            bool attacked_enemy = false;
            bool picked_item = false;

            for (auto& enemy: current_level.enemies) {
                if (new_pos == enemy.get_entity_pos() && enemy.isAlive()) {
                    if (resolve_attack(player, enemy))
                        player.add_xp(enemy.get_given_xp());
                    attacked_enemy = true;
                }
            }

            for (auto& item: current_level.items) {
                if (new_pos == item->get_item_pos() && !item->is_picked_) {
                    item->is_picked_ = true;
                    player.add_to_inventory(std::move(item));
                    //player.add_to_inventory(item.get());
                    picked_item = true;
                }
            }

            if(picked_item)
                std::erase_if(current_level.items, [](const auto& item) {
                    return item==nullptr; });

            if (attacked_enemy) {
                std::erase_if(current_level.enemies, [](const auto& enemy) {
                    return !enemy.isAlive();
                });
                turn_ended = true;
            }
            else if (new_pos != player.get_entity_pos()) {
                player.get_entity_pos() = new_pos;
                turn_ended = true;
            }
        }
        else if (key == ' ') {
            turn_ended = true; // spacebar - skip turn
        }
    }
}

void Combat::enemy_turn(Enemy& enemy, Player& player, Map& game_map) {
    Vec2 new_pos = enemy.find_path_to_player(player.get_entity_pos(), game_map);

    if(new_pos == player.get_entity_pos()) {
        resolve_attack(enemy, player);
    }
    else {
        enemy.get_entity_pos() = new_pos;
    }
}

bool Combat::resolve_attack(Entity &attacker, Entity &target) {
    target.modify_health(-attacker.get_damage());
    return !target.isAlive();
}
