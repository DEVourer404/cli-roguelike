#include "Combat.h"
#include "../utils/Rng.h"

Combat::Combat() {
    current_phase_ = TurnPhase::PLAYER;
    current_enemy_index_ = 0;
    current_entity_turn_text_ = "=== YOUR TURN ===";
}

CombatResult Combat::combat_loop(Player& player, Level& current_level) {
    switch (current_phase_) {
        case TurnPhase::PLAYER: {
            player_turn(player, current_level);

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

void Combat::player_turn(Player& player, Level& current_level) {
    bool turn_ended = false;

    while (!turn_ended) {
        char key = player.get_key();

        if (key == 'I') {
            bool used_item = UI::show_inventory(player);
            if (used_item) {
                turn_ended = true;
            } else {
                system("cls");
                Renderer::print_game(current_level, player);
                Renderer::print_current_text(current_entity_turn_text_);
            }
        }
        else if (key == 'W' || key == 'A' || key == 'S' || key == 'D') {
            Vec2 new_pos = player.move_player(current_level.get_level_map(), key);

            if (Enemy* enemy = current_level.enemy_at(new_pos)) {
                if (resolve_attack(player, *enemy)) {
                    player.add_xp(enemy->get_given_xp());
                }
                std::erase_if(current_level.enemies, [](const auto& e) {
                    return !e.isAlive();
                });
                turn_ended = true;
            }
            else if (Item* item = current_level.item_at(new_pos)) {
                item->is_picked_ = true;
                auto it = std::find_if(current_level.items.begin(), current_level.items.end(),
                    [item](const auto& ptr) { return ptr.get() == item; });
                if (it != current_level.items.end()) {
                    player.add_to_inventory(std::move(*it));
                    current_level.items.erase(it);
                }
                player.get_entity_pos() = new_pos;
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
    int raw_damage = attacker.get_damage();

    if (auto* player = dynamic_cast<Player*>(&target)) {
        // hadnle dodge chance
        int dodge_chance = player->get_dodge_chance();
        if (dodge_chance > 0) {
            int roll = Rng::generate_random_number(1, 100);
            if (roll <= dodge_chance) {
                current_entity_turn_text_ = "Player DODGED " + attacker.get_name() + "'s attack!";
                return false;
            }
        }

        // handle armor rate
        raw_damage -= player->get_armor_rate();
        if (raw_damage < 1) raw_damage = 1;
    }

    target.modify_health(-raw_damage);
    return !target.isAlive();
}
