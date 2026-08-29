#include "Level.h"
#include "entities/Enemy.h"
#include "utils/Vec2.h"

Level::Level(const std::string& level_name, int level_num, RoomType room_type):
level_name_(level_name), level_num_(level_num), room_type_(room_type) {}

Map& Level::get_level_map() {
    return level_map_;
}

Enemy* Level::enemy_at(const Vec2 &player_pos) {
    for (auto& enemy: enemies) {
        if (player_pos == enemy.get_entity_pos() && enemy.isAlive()) {
            return &enemy;
        }
    }
    return nullptr;
}

Item* Level::item_at(const Vec2 &player_pos) {
    for (auto& item: items) {
        if (player_pos == item->get_item_pos() && !item->is_picked()) {
            return item.get();
        }
    }
    return nullptr;
}

const Map::GameMapType& Level::get_map_grid() const { return level_map_.get_game_map(); }
void Level::reset() { level_num_ = 1; }

