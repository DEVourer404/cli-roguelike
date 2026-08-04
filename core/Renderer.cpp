#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::print(const Level& current_level, Player& player,  const std::vector<Enemy>& enemies) const {
    auto temp_map = current_level.get_map_grid();

    temp_map[player.get_entity_pos().y][player.get_entity_pos().x] = player.get_entity_symbol();

    for (const auto& enemy: enemies) {
        if (enemy.isAlive())
            temp_map[enemy.get_entity_pos().y][enemy.get_entity_pos().x] = enemy.get_entity_symbol();
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

void Renderer::print_player_stats(Player &player) const {
    std::cout << "\n";
    std::cout << "HP: " << player.get_current_health() << "/" << player.get_max_health() << " | ";
    std::cout << "DMG: " << player.get_damage() << " | ";
    std::cout << "Lvl: " << player.get_level() << " XP: " << player.get_current_xp() << "/" << player.get_xp_to_next_level() << "\n";
}

void Renderer::wait_for_enter() const {
    std::cout << "Nacisnij Enter...";
    int key = _getch();
    if (key == 224 || key == 0) {
        _getch();
    }
}

void Renderer::print_current_text(const std::string& current_turn_text) {
    std::cout << current_turn_text << "\n";

}

void Renderer::print_player_level_up(Player& player) {
    if(player.gained_levels > 0 ) {
        while (player.gained_levels > 0) {
            system("CLS");
            std::cout << "You have gained another level! \n";
            std::cout << "Choose which stats you want to upgrade! \n";

            std::cout << "1. Strength (increase your damage) \n"
                         "2. Dexterity (increase dodge chance) \n"
                         "3. Constitution (increase your health) \n" ;

            std::cout << "Your choice: ";
            int choice;
            std::cin >> choice;

            player.level_up(choice);
            player.gained_levels--;
        }
    }

}

