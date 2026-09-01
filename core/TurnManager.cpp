#include "TurnManager.h"

#include "utils/Rng.h"
#include "utils/Input.h"

TurnManager::TurnManager() = default;

void TurnManager::process_turn(Player &player, Level &current_level) {
    Renderer::print_current_text("=== Your turn ===");
    player_turn(player, current_level);

    if (!current_level.get_enemies().empty())
        UI::show_wait_for_enter();

    for (auto &enemy: current_level.get_enemies()) {
        Renderer::clear_screen();
        Renderer::print_game(current_level, player);
        Renderer::print_current_text("=== Enemy " + enemy.get_name() + "'s turn ===");
        UI::show_wait_for_enter();

        enemy_turn(enemy, player, current_level);
        if (!player.isAlive()) return;
    }
}

void TurnManager::player_turn(Player &player, Level &current_level) {
    bool turn_ended = false;

    while (!turn_ended) {
        Key key = Terminal::getKey();

        if (key == Key::I) {
            if (UI::show_inventory(player)) {
                turn_ended = true;
            } else {
                Renderer::clear_screen();
                Renderer::print_game(current_level, player);
                Renderer::print_current_text("=== Your turn ===");
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
            Renderer::clear_screen();
            Renderer::print_game(current_level, player);
            Renderer::print_current_text("You waited a turn.");
            turn_ended = true; // spacebar - skip turn
        }
    }
}

void TurnManager::enemy_turn(Enemy &enemy, Player &player, Level &current_level) {
    Vec2 new_pos = enemy.find_path_to_player(player.get_entity_pos(), current_level.get_level_map());

    if (new_pos == player.get_entity_pos()) {
        resolve_attack(enemy, player);
        Renderer::clear_screen();
        Renderer::print_game(current_level, player);
        Renderer::print_current_text(enemy.get_name() + " attacked you!");
    } else {
        enemy.get_entity_pos() = new_pos;
    }
}

bool TurnManager::handle_player_attack(Player &player, Level &current_level, Vec2 new_pos) {
    Enemy *enemy = current_level.enemy_at(new_pos);
    if (!enemy) return false;

    std::string attack_text;

    if (resolve_attack(player, *enemy)) {
        player.add_xp(enemy->get_given_xp());
        player.modify_gold(10);
        attack_text = "You killed a " + enemy->get_name();
        player.enemy_killed();
    } else {
        attack_text = "You attacked a " + enemy->get_name();
    }

    current_level.remove_dead_enemies();

    Renderer::clear_screen();
    Renderer::print_game(current_level, player);
    Renderer::print_current_text(attack_text);

    return true;
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
    std::string pickup_text;

    if (item->is_sellable()) {
        if (UI::show_buy_item_prompt(*item, player.get_gold())) {
            if (player.get_gold() >= item->get_price()) {
                if (!player.is_inventory_full()) {
                    player.modify_gold(-item->get_price());
                    pickup_text = "Bought " + item->get_name() + " for " + std::to_string(
                                      item->get_price()) + "G!";
                } else {
                    pickup_text = "Inventory is full!";
                    can_take = false;
                }
            } else {
                pickup_text = "Not enough gold!";
                can_take = false;
            }
        } else {
            can_take = false;
        }
    } else {
        if (player.is_inventory_full()) {
            pickup_text = "Inventory is full!";
            can_take = false;
        } else {
            pickup_text = "You picked up " + item->get_name();
        }
    }

    if (can_take) {
        auto taken_item = current_level.take_item_at(new_pos);
        if (taken_item) {
            player.add_to_inventory(std::move(taken_item));
        }
        player.get_entity_pos() = new_pos;
    }
    Renderer::clear_screen();
    Renderer::print_game(current_level, player);
    if (!pickup_text.empty()) {
        Renderer::print_current_text(pickup_text);
    }
    return can_take;
}

bool TurnManager::resolve_attack(const Entity &attacker, Entity &target) {
    int raw_damage = attacker.get_damage();

    // handle dodge chance
    if (Rng::check_chance(target.get_dodge_chance())) {
        return false;
    }

    // handle armor rate
    raw_damage -= target.get_armor_rate();
    if (raw_damage < 1) raw_damage = 1;

    target.modify_health(-raw_damage);
    return !target.isAlive();
}
