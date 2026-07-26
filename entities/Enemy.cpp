#include "Enemy.h"

Enemy::Enemy(const std::string &name, int health, int damage, char enemy_symbol): Entity(name, health, damage, enemy_symbol) {}

void Enemy::take_turn(Entity& player, const Map& game_map) {
    Vec2 new_pos = find_path_to_player(player.get_entity_pos(), game_map);

    if(new_pos == player.get_entity_pos()) {
        player.modify_health(-get_damage());
    }
    else {
        get_entity_pos()=new_pos;
    }
}

Vec2 Enemy::find_path_to_player(const Vec2 &player_pos, const Map& game_map) {
    std::array<std::array<bool, Map::WIDTH>, Map::HEIGHT> visited{};
    std::queue<Vec2> queue;

    Vec2 direction[4] {
        {0,-1},
        {0,1},
        {1,0},
        {-1,0}
    };

    std::array<std::array<Vec2, Map::WIDTH>, Map::HEIGHT> came_from{};

    visited[get_entity_pos().y][get_entity_pos().x] = true;
    queue.emplace(get_entity_pos());

    bool player_is_found = false;

    while(!queue.empty() && !player_is_found) {
        Vec2 temp = queue.front();
        queue.pop();

        for(const auto & i : direction) {
            Vec2 neighbour = temp + i;

            if(neighbour == player_pos) {
                player_is_found = true;
                came_from[neighbour.y][neighbour.x] = temp;
                break;
            }

            if(game_map.is_walkable(neighbour) && visited[neighbour.y][neighbour.x] == false) {
                queue.emplace(neighbour);
                visited[neighbour.y][neighbour.x] = true;
                came_from[neighbour.y][neighbour.x] = temp;
            }
        }
    }

    if (!player_is_found) {
        return get_entity_pos();
    }

    Vec2 current = player_pos;

    while (came_from[current.y][current.x] != get_entity_pos()) {
        current = came_from[current.y][current.x];
    }

    return current;
}
