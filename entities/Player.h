#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../core/Map.h"
#include <vector>
#include <memory>

#include "../items/Item.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Consumable.h"

struct Stats {
    int strength;
    int dexterity;
    int constitution;
};

struct Equipment {
    Weapon* weapon = nullptr;
    Armor* armor = nullptr;
};

class Player: public Entity{
private:
    int level_;
    int current_xp_;
    int xp_to_next_level;
    Stats stats_;
    int gained_levels_;
    Equipment equipment_;
    std::vector<std::unique_ptr<Item>> inventory_items_;
public:
    Player(const std::string& name, char player_symbol);
    Vec2 move_player(Map& game_map, char k);

    bool has_pending_level_ups() const;
    void consume_level_up();

    char get_key();
    int get_level() const;
    void level_up(int choice);
    int get_current_xp() const;
    int get_xp_to_next_level() const;
    Stats get_stats() const;

    void add_xp(int value);

    int get_max_health() const override;
    int get_damage() const override;
    int get_armor_rate() const;
    int get_dodge_chance() const;

    void use_item(int index);
    void drop_item(int index);
    void equip_weapon(Weapon* weapon);
    void equip_armor(Armor* armor);
    const Equipment& get_equipment() const;

    void add_to_inventory(std::unique_ptr<Item> item);

    void remove_from_inventory(Item* item_to_delete);
    const std::vector<std::unique_ptr<Item>>& get_inventory_items() const;
};



#endif //PLAYER_H
