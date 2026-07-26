#include "Player.h"
#include <conio.h>
#include "../entities/Enemy.h"

#include "../systems/DungeonGenerator.h"

Player::Player(const std::string& name, int health, char player_symbol):
Entity(name, health, 10, player_symbol) {}

char get_key() {
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

void Player::take_turn(Map& game_map, const std::vector<std::unique_ptr<Enemy>>& enemies) {
    char k = get_key();
    Vec2 new_pos = get_entity_pos();

    if (k == 'W') new_pos.y-=1;
    if (k == 'S') new_pos.y+=1;
    if (k == 'A') new_pos.x-=1;
    if (k == 'D') new_pos.x+=1;

    if(game_map.is_walkable(new_pos)) {
        for (auto& enemy: enemies) {
            if (new_pos == enemy->get_entity_pos() && enemy->isAlive()) {
                enemy->modify_health(-get_damage());
                return;
            }
        }
        get_entity_pos() = new_pos;
    }
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
