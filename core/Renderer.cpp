#include "Renderer.h"

Renderer::Renderer() {}

void Renderer::print(const Level& current_level, Player& player,  const std::vector<std::unique_ptr<Enemy>>& enemies) const {
    auto temp_map = current_level.get_map_grid();

    temp_map[player.get_entity_pos().y][player.get_entity_pos().x] = player.get_entity_symbol();

    for (const auto& enemy: enemies) {
        if (enemy->isAlive())
            temp_map[enemy->get_entity_pos().y][enemy->get_entity_pos().x] = enemy->get_entity_symbol();
    }

    std::cout << current_level.get_level_name() << ": " << current_level.get_level_num() << std::endl;
    for (int y = 0; y < Map::HEIGHT; y++) {
        for (int x = 0; x < Map::WIDTH; x++) {
            std::cout << temp_map[y][x];
        }
        std::cout << "\n";
    }
}
