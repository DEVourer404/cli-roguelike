#include "Game.h"
#include <limits>


Game::Game(): running(true) {
    player_ = std::make_unique<Player>("player", 10, 'P');

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
            case 1:
                in_menu = false;
                system("CLS");
                current_level_ = std::make_unique<Level>("Dungeon floor", 1);
                player_->get_entity_pos() =  dungeon_generator_.generate(current_level_->get_level_map());
                current_level_->spawn_enemies(player_->get_entity_pos());
                run();
                break;
            case 2:
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
            case 3:
                std::cout << "Thank you for playing!\n";
                in_menu = false;
                break;
            default:
                break;
        }
    }
}

void Game::run() {
    while (running) {
        renderer_.print(*current_level_, *player_, current_level_->enemies);
        player_->handle_movement(current_level_->get_level_map(), current_level_->enemies);
        move_to_new_level();
        system ("CLS");
    }
}

void Game::move_to_new_level() {
    if(current_level_->get_level_map().get_tile(player_->get_entity_pos().x, player_->get_entity_pos().y) == '>') {
        current_level_ = std::make_unique<Level>("Dungeon floor", current_level_->get_level_num()+1);
        player_->get_entity_pos() = dungeon_generator_.generate(current_level_->get_level_map());
        current_level_->spawn_enemies(player_->get_entity_pos());
    }
}


