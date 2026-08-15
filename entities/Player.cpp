#include "Player.h"

Player::Player(const std::string& name, char player_symbol):
Entity(name, player_symbol),
level_(1), current_xp_(0), xp_to_next_level(100), stats_{1,1,1}, gained_levels_(0) {
    current_health_ = Player::get_max_health();
}

Vec2 Player::move_player(Map& game_map, Key k) {
    Vec2 new_pos = get_entity_pos();

    if (k == Key::W || k == Key::Up) new_pos.y -= 1;
    if (k == Key::S || k == Key::Down) new_pos.y += 1;
    if (k == Key::A || k == Key::Left) new_pos.x -= 1;
    if (k == Key::D || k == Key::Right) new_pos.x += 1;

    if (game_map.is_walkable(new_pos))
        return new_pos;
    else
        return get_entity_pos();
}

int Player::get_max_health() const {
    return 50 + (stats_.constitution * 10);
}

int Player::get_damage() const {
    int base_damage = stats_.strength * 10;
    if (equipment_.weapon) {
        base_damage += equipment_.weapon->get_damage();
    }
    return base_damage;
}

int Player::get_armor_rate() const {
    if (equipment_.armor) {
        return equipment_.armor->get_armor_rate();
    }
    return 0;
}

int Player::get_dodge_chance() const {
    return std::min(stats_.dexterity * 5, 50);
}

const Equipment& Player::get_equipment() const {
    return equipment_;
}

void Player::use_item(int index) {
    if (index >= 0 && index < static_cast<int>(inventory_items_.size())) {
        inventory_items_[index]->use(*this);
    }
}

void Player::drop_item(int index) {
    if (index >= 0 && index < static_cast<int>(inventory_items_.size())) {
        remove_from_inventory(inventory_items_[index].get());
    }
}

void Player::equip_weapon(Weapon* weapon) {
    if (!weapon) return;
    if (equipment_.weapon == weapon) {
        weapon->is_equipped_ = false;
        equipment_.weapon = nullptr;
    } else {
        if (equipment_.weapon) {
            equipment_.weapon->is_equipped_ = false;
        }
        weapon->is_equipped_ = true;
        equipment_.weapon = weapon;
    }
}

void Player::equip_armor(Armor* armor) {
    if (!armor) return;
    if (equipment_.armor == armor) {
        armor->is_equipped_ = false;
        equipment_.armor = nullptr;
    } else {
        if (equipment_.armor) {
            equipment_.armor->is_equipped_ = false;
        }
        armor->is_equipped_ = true;
        equipment_.armor = armor;
    }
}

void Player::level_up(int choice) {
    switch (choice) {
        case 1:
            stats_.strength++;
        break;
        case 2:
            stats_.dexterity++;
        break;
        case 3:
            stats_.constitution++;
        break;
        default:
            break;
    }
}

Stats Player::get_stats() const { return stats_; }
int Player::get_level() const { return level_; }
int Player::get_current_xp() const { return current_xp_; }
int Player::get_xp_to_next_level() const { return xp_to_next_level; }

void Player::add_xp(int value) {
    current_xp_ += value;

    while (current_xp_ >= xp_to_next_level) {
        level_++;
        current_xp_-= xp_to_next_level;
        xp_to_next_level+=100;
        gained_levels_++;
    }
}

const std::vector<std::unique_ptr<Item>>& Player::get_inventory_items() const { return inventory_items_; }

void Player::add_to_inventory(std::unique_ptr<Item> item) {
    inventory_items_.push_back(std::move(item));
}

void Player::remove_from_inventory(Item* item_to_delete) {
    if (equipment_.weapon == item_to_delete) {
        equipment_.weapon = nullptr;
    }
    if (equipment_.armor == item_to_delete) {
        equipment_.armor = nullptr;
    }
    std::erase_if(inventory_items_, [&item_to_delete](const auto& item) {
                    return item.get()==item_to_delete; });
}

bool Player::has_pending_level_ups() const { return gained_levels_ > 0; }
void Player::consume_level_up() { if (gained_levels_ > 0) gained_levels_--; }

