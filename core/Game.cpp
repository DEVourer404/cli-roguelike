#include "Game.h"
#include <limits>

Game::Game(): is_running_(true) {
    player_ = std::make_unique<Player>("player", 'P');

    JsonLoader json_loader;
    enemy_templates_ = json_loader.load_enemies();
    item_templates_ = json_loader.load_items();

    combat_result_ = CombatResult::CONTINUE;
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
                in_menu = false;
                Renderer::clear_screen();

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
                std::cout << "    [P]   - Player        [#] - Wall\n";
                std::cout << "    [g/o/s]- Enemies      [.] - Floor\n";
                std::cout << "    [/]   - Weapon        [[] - Armor\n";
                std::cout << "    [!]   - Potion        [>] - Floor Exit\n\n";
                std::cout << "  Game Goal:\n";
                std::cout << "    1. Move into enemies to attack them.\n";
                std::cout << "    2. Step on items to collect them.\n";
                std::cout << "    3. Defeat all enemies on the floor.\n";
                std::cout << "    4. Reach the stairs [>] to level up\n";
                std::cout << "       and proceed to the next dungeon floor!\n";
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
        Renderer::clear_screen();

        Renderer::print_game(*current_level_, *player_);
        Renderer::print_current_text(current_combat_->current_entity_turn_text_);

        combat_result_ = current_combat_->combat_loop(*player_, *current_level_);
        switch (combat_result_) {
            case CombatResult::CONTINUE: {
                move_to_new_level();
                break;
            }
            case CombatResult::GAME_OVER:
                is_running_ = false;
                break;
            case CombatResult::WAIT_INPUT: {
                UI::show_wait_for_enter();

                break;
            }
        }

    }
}

void Game::move_to_new_level() {
    if(current_level_->get_level_map().get_tile(player_->get_entity_pos().x, player_->get_entity_pos().y) == '>' && current_level_->enemies.empty()) {
        if(UI::show_move_to_new_level()) {
            while (player_->has_pending_level_ups()) {
                player_->modify_health(player_->get_max_health());
                int choice = UI::show_level_up(*player_);
                player_->level_up(choice);
                player_->consume_level_up();
            }
            init_level();
        }
    }
}

void Game::init_level() {
    int level_num = current_level_ ? current_level_->get_level_num()+1 : 1;
    RoomType current_room = (level_num % 3 == 0) ? RoomType::Shop : RoomType::Normal;
    current_level_ = std::make_unique<Level>("Dungeon floor", level_num, current_room);
    level_generator_.generate(*current_level_, *player_, enemy_templates_, item_templates_);
    current_combat_ = std::make_unique<Combat>();
}

