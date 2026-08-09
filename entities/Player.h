#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../core/Map.h"
#include <vector>
#include <memory>

#include "../items/Item.h"

//class Enemy;

struct Stats {
    int strength;
    int dexterity;
    int constitution;
};

class Player: public Entity{
private:
    int level_;
    int current_xp_;
    int xp_to_next_level;

    std::vector<std::unique_ptr<Item>> inventory_items_;

public:
    Player(const std::string& name, char player_symbol);
    Vec2 move_player(Map& game_map, char k);

    Stats stats_;

    int gained_levels;

    char get_key();
    int get_level() const;
    void level_up(int choice);
    int get_current_xp() const;
    int get_xp_to_next_level() const;

    void add_xp(int value);

    int get_max_health() const override;
    int get_damage() const override;

    //void add_to_inventory(const Item* item);
    void add_to_inventory(std::unique_ptr<Item> item);

    void remove_from_inventory();
    const std::vector<std::unique_ptr<Item>>& get_inventory_items() const;
};



#endif //PLAYER_H
