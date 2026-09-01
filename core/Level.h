#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <memory>
#include "Map.h"
#include "entities/Enemy.h"
#include "items/Item.h"

enum class RoomType {
    Normal,
    Shop,
    Boss
};

class Level {
private:
    std::string level_name_;
    int level_num_;
    Map level_map_;
    RoomType room_type_;

    std::vector<Enemy> enemies_;
    std::vector<std::unique_ptr<Item>> items_;

public:
    Level(const std::string& level_name, int level_num = 0, RoomType room_type = RoomType::Normal);

    Map& get_level_map();
    const Map& get_level_map() const;
    int get_level_num() const;
    const std::string& get_level_name() const;
    const Map::GameMapType& get_map_grid() const;
    RoomType get_room_type() const;

    const std::vector<Enemy>& get_enemies() const;
    std::vector<Enemy>& get_enemies();
    const std::vector<std::unique_ptr<Item>>& get_items() const;
    std::vector<std::unique_ptr<Item>>& get_items();

    void add_enemy(const Enemy& enemy);
    void add_item(std::unique_ptr<Item> item);
    void remove_dead_enemies();

    Enemy* enemy_at(const Vec2& player_pos);
    Item* item_at(const Vec2& player_pos);
    std::unique_ptr<Item> take_item_at(const Vec2& pos);

    void reset();
};

#endif //LEVEL_H
