#include "Game.h"
#include <limits>

#include "Logger.h"

Game::Game(): is_running_(true) {
    JsonLoader json_loader;
    enemy_templates_ = json_loader.load_enemies();
    item_templates_ = json_loader.load_items();
}

void Game::main_menu() {
    bool in_menu = true;
    while (in_menu) {
        Renderer::clear_screen();

        std::cout << "================================================\n";
        std::cout << "         *  CLI ROGUELIKE DUNGEON  *            \n";
        std::cout << "================================================\n";
        std::cout << "  [1] PLAY GAME\n";
        std::cout << "  [2] CONTROLS & HELP\n";
        std::cout << "  [3] EXIT\n";
        std::cout << "================================================\n";
        std::cout << "Select option: ";

        Key key = Terminal::getKey();

        switch (key) {
            case Key::Num1: {
                Renderer::clear_screen();
                is_running_ = true;
                player_ = std::make_unique<Player>("player", 'P');
                current_level_.reset();
                init_level();
                run();
                break;
            }
            case Key::Num2: {
                Renderer::clear_screen();

                std::cout << "================================================\n";
                std::cout << "              CONTROLS & HELP                   \n";
                std::cout << "================================================\n";
                std::cout << "  Movement:\n";
                std::cout << "    [W] / [Up Arrow]    - Move Up\n";
                std::cout << "    [S] / [Down Arrow]  - Move Down\n";
                std::cout << "    [A] / [Left Arrow]  - Move Left\n";
                std::cout << "    [D] / [Right Arrow] - Move Right\n\n";
                std::cout << "  Actions:\n";
                std::cout << "    [I]                 - Open Inventory\n";
                std::cout << "    [SPACE]             - Wait / Skip Turn\n";
                std::cout << "    [Q] / [ESC]         - Back / Close Menu\n\n";
                std::cout << "  Map Legend:\n";
                std::cout << "    [P]    - Player        [#] - Wall\n";
                std::cout << "    [g/o/s]- Enemies       [.] - Floor\n";
                std::cout << "    [M]    - Merchant      [>] - Floor Exit\n";
                std::cout << "    [/]    - Weapon        [[] - Armor\n";
                std::cout << "    [!]    - Potion\n\n";
                std::cout << "  Game Goal & Mechanics:\n";
                std::cout << "    1. Move into enemies to attack them.\n";
                std::cout << "    2. Defeat enemies to earn XP, level ups, and Gold.\n";
                std::cout << "    3. Step on items to pick them up (or buy in Shops).\n";
                std::cout << "    4. Walk into Merchant [M] to chat or buy healing.\n";
                std::cout << "    5. Clear all enemies and reach [>] to advance!\n";
                std::cout << "================================================\n";
                std::cout << "Press ENTER or ESC to return to main menu...";

                while (true) {
                    Key k = Terminal::getKey();
                    if (k == Key::Enter || k == Key::Escape || k == Key::Space) {
                        break;
                    }
                }
                break;
            }
            case Key::Num3: {
                std::cout << "Thank you for playing!\n";
                in_menu = false;
                break;
            }
            default:
                break;
        }
    }
}

void Game::run() {
    while (is_running_) {
        turn_manager_->process_turn(*player_, *current_level_);

        if (!player_->isAlive())
            is_running_ = false;
        else if (current_level_->get_enemies().empty())
            move_to_new_level();
    }

    Renderer::clear_screen();
    Renderer::print_death_score(*player_, *current_level_);
}

void Game::move_to_new_level() {
    if(current_level_->get_level_map().get_tile(player_->get_entity_pos().x, player_->get_entity_pos().y) == '>' && current_level_->get_enemies().empty()) {
        if(UI::show_move_to_new_level()) {
            while (player_->has_pending_level_ups()) {
                int choice = UI::show_level_up(*player_);
                player_->modify_health(player_->get_max_health());
                player_->level_up(choice);
                player_->consume_level_up();
            }
            Logger::clear();
            init_level();
        }
    }
}

void Game::init_level() {
    int level_num = current_level_ ? current_level_->get_level_num()+1 : 1;
    RoomType current_room = (level_num % 3 == 0) ? RoomType::Shop : RoomType::Normal;
    current_level_ = std::make_unique<Level>("Dungeon floor", level_num, current_room);
    level_generator_.generate(*current_level_, *player_, enemy_templates_, item_templates_);
    turn_manager_ = std::make_unique<TurnManager>();
}

