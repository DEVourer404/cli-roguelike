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
        system("CLS");
        std::cout << "================================================\n";
        std::cout << "         *  CLI ROGUELIKE DUNGEON  *            \n";
        std::cout << "================================================\n";
        std::cout << "  [1] PLAY GAME\n";
        std::cout << "  [2] CONTROLS & HELP\n";
        std::cout << "  [3] EXIT\n";
        std::cout << "================================================\n";
        std::cout << "Select option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                in_menu = false;
                system("CLS");
                init_level();
                run();
                break;
            }
            case 2: {
                system("CLS");
                std::cout << "================================================\n";
                std::cout << "              CONTROLS & HELP                   \n";
                std::cout << "================================================\n";
                std::cout << "  Movement keys:\n";
                std::cout << "    [W] - Move Up\n";
                std::cout << "    [S] - Move Down\n";
                std::cout << "    [A] - Move Left\n";
                std::cout << "    [D] - Move Right\n";
                std::cout << "  Game Goal:\n";
                std::cout << "    Explore the dungeon and avoid obstacles.\n";
                std::cout << "================================================\n";
                std::cout << "Press ENTER to return to main menu...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 3: {
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
        system("CLS");
        renderer_.print(*current_level_, *player_, current_level_->enemies);
        renderer_.print_current_text(current_combat_->current_entity_turn_text_);

        combat_result_ = current_combat_->combat_loop(*player_, current_level_->enemies, *current_level_, renderer_);
        switch (combat_result_) {
            case CombatResult::CONTINUE: {
                move_to_new_level(*player_);
                break;
            }
            case CombatResult::GAME_OVER:
                is_running_ = false;
                break;
            case CombatResult::WAIT_INPUT: {
                renderer_.wait_for_enter();
                break;
            }
        }
    }
}

void Game::move_to_new_level(const Player& player) {
    if(current_level_->get_level_map().get_tile(player_->get_entity_pos().x, player_->get_entity_pos().y) == '>' && current_level_->enemies.empty()) {
        renderer_.print_player_level_up(*player_);

        while (player.gained_levels > 0) {
            int choice = renderer_.print_player_level_up(player);
            player_->level_up(choice);
            player_->gained_levels--;
        }

        init_level();
    }
}

void Game::init_level() {
    int level_num = current_level_ ? current_level_->get_level_num()+1 : 1;

    current_level_ = std::make_unique<Level>("Dungeon floor", enemy_templates_, level_num);
    player_->get_entity_pos() = dungeon_generator_.generate(current_level_->get_level_map());
    current_level_->spawn_enemies(player_->get_entity_pos());
    current_combat_ = std::make_unique<Combat>();
}

