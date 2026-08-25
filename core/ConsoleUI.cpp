#include "ConsoleUI.h"
#include "utils/Input.h"

namespace Renderer {

    void print_game(const Level& current_level, Player& player) {
        auto temp_map = current_level.get_map_grid();

        temp_map[player.get_entity_pos().y][player.get_entity_pos().x] = player.get_entity_symbol();

        // render enemies
        for (const auto& enemy: current_level.enemies) {
            if (enemy.isAlive())
                temp_map[enemy.get_entity_pos().y][enemy.get_entity_pos().x] = enemy.get_entity_symbol();
        }

        // render items
        for (const auto& item: current_level.items) {
            if (!item->is_picked_)
                temp_map[item->get_item_pos().y][item->get_item_pos().x] = item->get_symbol();
        }

        std::cout << current_level.get_level_name() << ": " << current_level.get_level_num() << std::endl;
        for (int y = 0; y < Map::HEIGHT; y++) {
            for (int x = 0; x < Map::WIDTH; x++) {
                std::cout << temp_map[y][x];
            }
            std::cout << "\n";
        }
        print_player_stats(player);
    }

    void print_player_stats(Player& player) {
        std::cout << "\n";
        std::cout << "HP: " << player.get_current_health() << "/" << player.get_max_health() << " | ";
        std::cout << "DMG: " << player.get_damage() << " | ";
        std::cout << "Lvl: " << player.get_level() << " XP: " << player.get_current_xp() << "/" << player.get_xp_to_next_level() << " | ";
        std::cout << "Gold: " << player.get_gold() << "\n";
    }

    void print_current_text(const std::string& current_turn_text) {
        std::cout << current_turn_text << "\n";
    }

    void clear_screen() {
        std::cout << "\033[2J\033[H";
    }

}

namespace UI {
    static int key_to_item_index(Key key) {
        switch (key) {
            case Key::Num1: return 0;
            case Key::Num2: return 1;
            case Key::Num3: return 2;
            case Key::Num4: return 3;
            case Key::Num5: return 4;
            case Key::Num6: return 5;
            case Key::Num7: return 6;
            case Key::Num8: return 7;
            case Key::Num9: return 8;
            default: return -1;
        }
    }

    int show_level_up(const Player& player) {
        Renderer::clear_screen();

        std::cout << "You have gained another level! \n";
        std::cout << "Choose which stats you want to upgrade! \n";
        std::cout << "Current stats: STR: " << player.get_stats().strength << " | DEX: " << player.get_stats().dexterity << " | CON: " << player.get_stats().constitution << "\n\n";

        std::cout << "[1]. Strength (increase your damage) \n"
                     "[2]. Dexterity (increase dodge chance) \n"
                     "[3]. Constitution (increase your health) \n";
        std::cout << "Your choice: ";

        while (true) {
            Key key = Terminal::getKey();
            if (key == Key::Num1) return 1;
            if (key == Key::Num2) return 2;
            if (key == Key::Num3) return 3;
        }
    }

    bool show_inventory(Player& player) {
        while (true) {
            Renderer::clear_screen();

            const auto& items = player.get_inventory_items();
            int inv_size = player.get_inventory_size();

            std::cout << "========================================\n";
            std::cout << "             YOUR INVENTORY             \n";
            std::cout << "========================================\n";

            if (inv_size == 0) {
                std::cout << "  (Inventory is empty)\n";
            } else {
                for (int i = 0; i < inv_size; ++i) {
                    if (items[i]) {
                        std::cout << "  [" << i + 1 << "] " << items[i]->get_name();
                        if (items[i]->is_equipped_) {
                            std::cout << " [EQUIPPED]";
                        }
                        std::cout << "\n";
                    }
                }
            }

            std::cout << "========================================\n";
            if (inv_size > 0) {
                std::cout << " [1-" << inv_size << "] Select item | [Q / ESC] Return to game\n";
            } else {
                std::cout << " [Q / ESC] Return to game\n";
            }
            std::cout << "Choose option: ";

            Key key = Terminal::getKey();

            if (key == Key::Q || key == Key::Escape) {
                return false;
            }

            int selected_index = key_to_item_index(key);

            if (inv_size > 0 && selected_index >= 0 && selected_index < inv_size) {
                while (true) {
                    Renderer::clear_screen();

                    const auto& current_items = player.get_inventory_items();
                    int current_size = player.get_inventory_size();
                    if (selected_index >= current_size || !current_items[selected_index]) {
                        break;
                    }

                    Item* selected_item = current_items[selected_index].get();

                    std::cout << "========================================\n";
                    std::cout << " Selected: " << selected_item->get_name();
                    if (selected_item->is_equipped_) {
                        std::cout << " [EQUIPPED]";
                    }
                    std::cout << "\n========================================\n";
                    std::cout << "  [1] Use / Equip / Unequip\n";
                    std::cout << "  [2] Drop (Remove item)\n";
                    std::cout << "  [Q / ESC] Back to inventory\n";
                    std::cout << "========================================\n";
                    std::cout << "Choose action: ";

                    Key action_key = Terminal::getKey();

                    if (action_key == Key::Q || action_key == Key::Escape) {
                        break;
                    }
                    if (action_key == Key::Num1) {
                        player.use_item(selected_index);
                        return true;
                    }
                    if (action_key == Key::Num2) {
                        player.remove_from_inventory(selected_index);
                        break;
                    }
                }
            }
        }
    }

    void show_merchant_dialogue(Player& player) {
        while (true) {
            Renderer::clear_screen();
            std::cout << "================================================\n";
            std::cout << "           *  DUNGEON MERCHANT  *               \n";
            std::cout << "================================================\n";
            std::cout << "  \"Greetings, traveler! Welcome to my shop.\n";
            std::cout << "   Take a look at the goods on the floor,\n";
            std::cout << "   or let me tend to your wounds for a fee.\"\n";
            std::cout << "================================================\n";
            std::cout << "  Your Gold: " << player.get_gold() << " G | HP: " 
                      << player.get_current_health() << "/" << player.get_max_health() << "\n";
            std::cout << "================================================\n";
            std::cout << "  [1] \"Tell me some advice about this dungeon.\"\n";
            std::cout << "  [2] Rest & Heal to full (Cost: 20 Gold)\n";
            std::cout << "  [Q / ESC] Leave merchant\n";
            std::cout << "================================================\n";
            std::cout << "Choose option: ";

            Key key = Terminal::getKey();

            if (key == Key::Q || key == Key::Escape) {
                break;
            }

            if (key == Key::Num1) {
                Renderer::clear_screen();
                std::cout << "================================================\n";
                std::cout << "             * MERCHANT'S ADVICE *              \n";
                std::cout << "================================================\n";
                std::cout << "  \"Monsters hit hard in the lower depths.\n";
                std::cout << "   Always keep a health potion in your bag!\n";
                std::cout << "   And don't forget to equip new weapons and\n";
                std::cout << "   armor from your inventory [I].\"\n";
                std::cout << "================================================\n";
                std::cout << "Press ENTER to return...";
                while (true) {
                    Key k = Terminal::getKey();
                    if (k == Key::Enter || k == Key::Space || k == Key::Escape) break;
                }
            }
            else if (key == Key::Num2) {
                Renderer::clear_screen();

                const int heal_cost = 20;

                std::cout << "================================================\n";
                std::cout << "             * HEALING SERVICE *                \n";
                std::cout << "================================================\n";

                if (player.get_current_health() >= player.get_max_health()) {
                    std::cout << "  \"You are already at full health!\"\n";
                } else if (player.get_gold() < heal_cost) {
                    std::cout << "  \"You don't have enough gold! (Need " << heal_cost << " Gold)\"\n";
                } else {
                    player.modify_gold(-heal_cost);
                    player.modify_health(player.get_max_health());
                    std::cout << "  \"There you go! Your wounds are fully healed.\"\n";
                    std::cout << "  HP restored to " << player.get_max_health() << "/" << player.get_max_health() << "!\n";
                }
                std::cout << "================================================\n";
                std::cout << "Press ENTER to continue...";

                while (true) {
                    Key k = Terminal::getKey();
                    if (k == Key::Enter || k == Key::Space || k == Key::Escape) break;
                }
            }
        }
    }

    bool show_buy_item_prompt(const Item& item, int player_gold) {
        std::cout << "\n========================================\n";
        std::cout << " Item for sale: " << item.get_name() << "\n";
        std::cout << " Price: " << item.get_price() << " Gold | Your Gold: " << player_gold << " Gold\n";
        std::cout << "========================================\n";
        std::cout << " [ENTER] Buy item | [Any other key] Cancel\n";
        std::cout << "Choose option: ";

        Key key = Terminal::getKey();
        return (key == Key::Enter);
    }

    void show_wait_for_enter() {
        std::cout << "Press ENTER...";
        while (true) {
            Key key = Terminal::getKey();
            if (key == Key::Enter || key == Key::Space) {
                break;
            }
        }
    }

    bool show_move_to_new_level() {
        std::cout << "Press Enter to move to a new level\n";
        Key key = Terminal::getKey();
        if (key == Key::Enter)
            return true;
        else
            return false;
    }

}
