#include "ConsoleUI.h"

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
        std::cout << "Lvl: " << player.get_level() << " XP: " << player.get_current_xp() << "/" << player.get_xp_to_next_level() << "\n";
    }

    void print_current_text(const std::string& current_turn_text) {
        std::cout << current_turn_text << "\n";
    }

}

namespace UI {
    static char read_key_upper() {
        int key = _getch();
        if (key == 224 || key == 0) {
            _getch();
            return 0;
        }
        return static_cast<char>(std::toupper(key));
    }

    int show_level_up(const Player& player) {
        system("CLS");
        std::cout << "You have gained another level! \n";
        std::cout << "Choose which stats you want to upgrade! \n";
        std::cout << "Current stats: STR: " << player.get_stats().strength << " | DEX: " << player.get_stats().dexterity << " | CON: " << player.get_stats().constitution << "\n\n";

        std::cout << "[1]. Strength (increase your damage) \n"
                     "[2]. Dexterity (increase dodge chance) \n"
                     "[3]. Constitution (increase your health) \n";
        std::cout << "Your choice: ";

        while (true) {
            char key = read_key_upper();
            if (key == '1') return 1;
            if (key == '2') return 2;
            if (key == '3') return 3;
        }
    }



    bool show_inventory(Player& player) {
        while (true) {
            system("cls");
            const auto& items = player.get_inventory_items();

            std::cout << "========================================\n";
            std::cout << "             YOUR INVENTORY             \n";
            std::cout << "========================================\n";

            if (items.empty()) {
                std::cout << "  (Inventory is empty)\n";
            } else {
                for (size_t i = 0; i < items.size(); ++i) {
                    std::cout << "  [" << i + 1 << "] " << items[i]->get_name();
                    if (items[i]->is_equipped_) {
                        std::cout << " [EQUIPPED]";
                    }
                    std::cout << "\n";
                }
            }

            std::cout << "========================================\n";
            std::cout << " [1-" << items.size() << "] Select item | [Q / ESC] Return to game\n";
            std::cout << "Choose option: ";

            char key = read_key_upper();

            if (key == 'Q' || key == 27) {
                return false;
            }

            if (!items.empty() && key >= '1' && key <= '0' + static_cast<char>(items.size())) {
                int selected_index = key - '1';

                while (true) {
                    system("cls");
                    const auto& current_items = player.get_inventory_items();
                    if (selected_index >= static_cast<int>(current_items.size())) {
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

                    char action_key = read_key_upper();

                    if (action_key == 'Q' || action_key == 27) {
                        break;
                    }
                    if (action_key == '1') {
                        player.use_item(selected_index);
                        return true;
                    }
                    if (action_key == '2') {
                        player.drop_item(selected_index);
                        break;
                    }
                }
            }
        }
    }

    void show_wait_for_enter() {
        std::cout << "Press ENTER...";
        int key = _getch();
        if (key == 224 || key == 0) {
            _getch();
        }
    }

}
