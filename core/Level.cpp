#include "Level.h"
#include "entities/Enemy.h"
#include "utils/Vec2.h"
#include <algorithm>

Level::Level(const std::string& level_name, int level_num, RoomType room_type):
    level_name_(level_name), level_num_(level_num), room_type_(room_type) {}

Map& Level::get_level_map() { return level_map_; }
const Map& Level::get_level_map() const { return level_map_; }

const std::string& Level::get_level_name() const { return level_name_; }
int Level::get_level_num() const { return level_num_; }
RoomType Level::get_room_type() const { return room_type_; }

const std::vector<Enemy>& Level::get_enemies() const { return enemies_; }
std::vector<Enemy>& Level::get_enemies() { return enemies_; }

const std::vector<std::unique_ptr<Item>>& Level::get_items() const { return items_; }
std::vector<std::unique_ptr<Item>>& Level::get_items() { return items_; }

void Level::add_enemy(const Enemy& enemy) {
    enemies_.push_back(enemy);
}

void Level::add_item(std::unique_ptr<Item> item) {
    if (item) {
        items_.push_back(std::move(item));
    }
}

void Level::remove_dead_enemies() {
    std::erase_if(enemies_, [](const Enemy& e) { return !e.isAlive(); });
}

Enemy* Level::enemy_at(const Vec2& player_pos) {
    for (auto& enemy : enemies_) {
        if (player_pos == enemy.get_entity_pos() && enemy.isAlive()) {
            return &enemy;
        }
    }
    return nullptr;
}

Item* Level::item_at(const Vec2& player_pos) {
    for (auto& item : items_) {
        if (player_pos == item->get_item_pos() && !item->is_picked()) {
            return item.get();
        }
    }
    return nullptr;
}

std::unique_ptr<Item> Level::take_item_at(const Vec2& pos) {
    auto it = std::find_if(items_.begin(), items_.end(), [&](const auto& item_ptr) {
        return item_ptr->get_item_pos() == pos && !item_ptr->is_picked();
    });

    if (it != items_.end()) {
        auto taken_item = std::move(*it);
        items_.erase(it);
        return taken_item;
    }
    return nullptr;
}

const Map::GameMapType& Level::get_map_grid() const { return level_map_.get_game_map(); }
void Level::reset() { level_num_ = 1; }
