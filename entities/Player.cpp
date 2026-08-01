#include "Player.h"
#include <conio.h>
#include "../entities/Enemy.h"

#include "../systems/DungeonGenerator.h"

Player::Player(const std::string& name, char player_symbol):
Entity(name, player_symbol),
level_(1), current_xp_(0), xp_to_next_level(100), stats_{1,1,1}, gained_levels(0) {
    current_health_ = Player::get_max_health();
}

char get_key() {
    while (_kbhit()) _getch();

    int key = _getch();

    if (key == 224 || key == 0) {
        key = _getch();

        switch (key) {
            case 72: return 'W';
            case 80: return 'S';
            case 75: return 'A';
            case 77: return 'D';
            default: ;
        }
    }
    return 0;
}

Vec2 Player::move_player(Map& game_map) {
    char k = get_key();
    Vec2 new_pos = get_entity_pos();

    if (k == 'W') new_pos.y-=1;
    if (k == 'S') new_pos.y+=1;
    if (k == 'A') new_pos.x-=1;
    if (k == 'D') new_pos.x+=1;

    if(game_map.is_walkable(new_pos))
        return new_pos;
    else
        return get_entity_pos();
}

int Player::get_max_health() const {
    return 50 + (stats_.constitution * 10);
}

int Player::get_damage() const {
    return stats_.strength * 10;
}

void Player::level_up(int choice) {
    switch (choice) {
        case 1:
            stats_.strength++;
        break;;
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

int Player::get_level() const { return level_; }
int Player::get_current_xp() const { return current_xp_; }
int Player::get_xp_to_next_level() const { return xp_to_next_level; }

void Player::add_xp(int value) {
    current_xp_ += value;

    while (current_xp_ >= xp_to_next_level) {
        level_++;
        current_xp_-= xp_to_next_level;
        xp_to_next_level+=100;
        gained_levels++;
    }
}


