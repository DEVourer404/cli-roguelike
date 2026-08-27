#include "TurnManager.h"

#include "utils/Rng.h"
#include "utils/Input.h"

TurnManager::TurnManager() {
    current_entity_turn_text_ = "=== YOUR TURN ===";
}

void TurnManager::process_turn(Player &player, Level &current_level) {
    Renderer::print_current_text("=== Your turn ===");
    player_turn(player, current_level);

    if (!current_level.enemies.empty())
        UI::show_wait_for_enter();

    for (auto &enemy: current_level.enemies) {
        Renderer::clear_screen();
        Renderer::print_game(current_level, player);
        Renderer::print_current_text("=== Enemy " + enemy.get_name() + "'s turn ===");
        UI::show_wait_for_enter();

        enemy_turn(enemy, player, current_level.get_level_map());
        if (!player.isAlive()) return;
    }
}

void TurnManager::player_turn(Player &player, Level &current_level) {
    bool turn_ended = false;

    while (!turn_ended) {
        Key key = Terminal::getKey();

        if (key == Key::I) {
            bool used_item = UI::show_inventory(player);
            if (used_item) {
                turn_ended = true;
            } else {
                Renderer::clear_screen();

                Renderer::print_game(current_level, player);
                Renderer::print_current_text(current_entity_turn_text_);
            }
        } else if (key == Key::W || key == Key::A || key == Key::S || key == Key::D ||
                   key == Key::Up || key == Key::Left || key == Key::Down || key == Key::Right) {
            Vec2 new_pos = player.move_player(current_level.get_level_map(), key);

            if (handle_player_attack(player, current_level, new_pos)) {
                turn_ended = true;
            } else if (handle_merchant(player, current_level, new_pos)) {
            } else if (handle_item_pickup(player, current_level, new_pos)) {
                turn_ended = true;
            } else if (new_pos != player.get_entity_pos()) {
                player.get_entity_pos() = new_pos;
                turn_ended = true;
            }
        } else if (key == Key::Space) {
            current_entity_turn_text_ = "You waited a turn.";
            turn_ended = true; // spacebar - skip turn
        }
    }
}

void TurnManager::enemy_turn(Enemy &enemy, Player &player, Map &game_map) {
    Vec2 new_pos = enemy.find_path_to_player(player.get_entity_pos(), game_map);

    if (new_pos == player.get_entity_pos()) {
        resolve_attack(enemy, player);
    } else {
        enemy.get_entity_pos() = new_pos;
    }
}

bool TurnManager::handle_player_attack(Player &player, Level &current_level, Vec2 new_pos) {
    if (Enemy *enemy = current_level.enemy_at(new_pos)) {
        if (resolve_attack(player, *enemy)) {
            player.add_xp(enemy->get_given_xp());
        }

        current_entity_turn_text_ = "You attacked a " + enemy->get_name();

        std::erase_if(current_level.enemies, [&](const auto &e) {
            if (!e.isAlive()) {
                player.modify_gold(10);
                current_entity_turn_text_ = "You killed a " + e.get_name();
                return true;
            }
            return false;
        });

        Renderer::clear_screen();
        Renderer::print_game(current_level, player);
        Renderer::print_current_text(current_entity_turn_text_);

        return true;
    }
    return false;
}

bool TurnManager::handle_merchant(Player &player, Level &current_level, Vec2 new_pos) {
    if (current_level.get_level_map().get_tile(new_pos) == 'M') {
        UI::show_merchant_dialogue(player);
        Renderer::clear_screen();
        Renderer::print_game(current_level, player);
        Renderer::print_current_text("Merchant: Safe travels, stranger!");

        return true;
    }
    return false;
}

bool TurnManager::handle_item_pickup(Player &player, Level &current_level, Vec2 new_pos) {
    Item *item = current_level.item_at(new_pos);
    if (!item) return false;
    bool can_take = true;

    if (item->is_sellable_) {
        if (UI::show_buy_item_prompt(*item, player.get_gold())) {
            if (player.get_gold() >= item->get_price()) {
                if (!player.is_inventory_full()) {
                    player.modify_gold(-item->get_price());
                    current_entity_turn_text_ = "Bought " + item->get_name() + " for " + std::to_string(
                                                    item->get_price()) + "G!";
                } else {
                    current_entity_turn_text_ = "Inventory is full!";
                    can_take = false;
                }
            } else {
                current_entity_turn_text_ = "Not enough gold!";
                can_take = false;
            }
        } else {
            can_take = false;
        }
    } else {
        if (player.is_inventory_full()) {
            current_entity_turn_text_ = "Inventory is full!";
            can_take = false;
        } else {
            current_entity_turn_text_ = "You picked up " + item->get_name();
        }
    }

    if (can_take) {
        item->is_picked_ = true;
        auto it = std::find_if(current_level.items.begin(), current_level.items.end(),
                               [item](const auto &ptr) { return ptr.get() == item; });
        if (it != current_level.items.end()) {
            player.add_to_inventory(std::move(*it));
            current_level.items.erase(it);
        }
        player.get_entity_pos() = new_pos;
    }
    Renderer::clear_screen();
    Renderer::print_game(current_level, player);
    Renderer::print_current_text(current_entity_turn_text_);
    return can_take;
}

bool TurnManager::resolve_attack(Entity &attacker, Entity &target) {
    int raw_damage = attacker.get_damage();

    // handle dodge chance
    int dodge_chance = target.get_dodge_chance();
    if (dodge_chance > 0) {
        int roll = Rng::generate_random_number(1, 100);
        if (roll <= dodge_chance) {
            current_entity_turn_text_ = target.get_name() + " DODGED " + attacker.get_name() + "'s attack!";
            return false;
        }
    }

    // handle armor rate
    raw_damage -= target.get_armor_rate();
    if (raw_damage < 1) raw_damage = 1;

    target.modify_health(-raw_damage);
    return !target.isAlive();
}
