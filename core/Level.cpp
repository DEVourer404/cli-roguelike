#include "Level.h"
#include "../entities/Enemy.h"
#include "../utils/Rng.h"
#include "../utils/Vec2.h"

Level::Level(const std::string& level_name, const std::vector<Enemy> &enemies_templates, int level_num):
level_name_(level_name), level_num_(level_num) {

    if (!enemies_templates.empty()) {
        enemies.push_back(enemies_templates[0]);
        enemies.push_back(enemies_templates[0]);
        enemies.push_back(enemies_templates[0]);
    }

}

Map& Level::get_level_map() {
    return level_map_;
}

const Map::GameMapType& Level::get_map_grid() const {
    return level_map_.get_game_map();
}

void Level::spawn_enemies(const Vec2& player_pos) {
    Vec2 temp_pos{0,0};
    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);

    int enemies_counter = 0;

    while (enemies_counter < enemies.size()) {
        if (get_tile(temp_pos.x, temp_pos.y) == '.' && temp_pos != player_pos) {
            enemies[enemies_counter].get_entity_pos() = temp_pos;
            enemies_counter++;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}

char Level::get_tile(int x, int y) const { return level_map_.get_tile(x,y);}
char Level::get_tile(const Vec2 &pos) const { return level_map_.get_tile(pos);}
void Level::set_tile(int x, int y, char tile) { level_map_.set_tile(x,y, tile); }
void Level::set_tile(const Vec2 &pos, char tile) { level_map_.set_tile(pos,tile);}
bool Level::is_walkable(const Vec2 &vec2) const { return level_map_.is_walkable(vec2); }


