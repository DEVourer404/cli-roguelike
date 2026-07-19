#include "Player.h"
#include <conio.h>
#include "../systems/DungeonGenerator.h"

Player::Player(const std::string& name, int health, char entity_symbol):
Entity(name, health, entity_symbol) {}

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

void Player::handle_movement(Map& game_map) {
    char k = get_key();
    Vec2 new_pos = get_entity_pos();

    if (k == 'W') new_pos.y-=1;
    if (k == 'S') new_pos.y+=1;
    if (k == 'A') new_pos.x-=1;
    if (k == 'D') new_pos.x+=1;

    if(game_map.is_walkable(new_pos)) {
        get_entity_pos() = new_pos;
    }
}