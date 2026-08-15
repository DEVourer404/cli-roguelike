#include "DungeonGenerator.h"


DungeonGenerator::DungeonGenerator() {}

int random_direction() {
    return (Rng::generate_random_number(1,4) - 1);
}

Vec2 DungeonGenerator::generate(Map& game_map) {
    int startX = Rng::generate_random_number(1, Map::WIDTH-2);
    int startY = Rng::generate_random_number(1, Map::HEIGHT-2);

    Vec2 start_pos{startX,startY};

    int dx[] = {0,0,1,-1};
    int dy[] = {-1,1,0,0};

    int dir = random_direction();

    int floorCount = 1;

    //game_map.set_tile(startX, startY, 'S');

    while ((floorCount*100)/(Map::WIDTH*Map::HEIGHT) < 50) {
        // momentum - 70% szans na utrzymanie tego same kierunku
        if(Rng::generate_random_number(1,100) <= 30)
            dir = random_direction();
        startX+=dx[dir];
        startY+=dy[dir];

        if(startX < 1 || startX > Map::WIDTH - 2) {
            startX-=dx[dir];
            dir = random_direction();
        }
        else if (startY < 1 || startY > Map::HEIGHT - 2) {
            startY-=dy[dir];
            dir = random_direction();
        }
        else {
            if(game_map.get_tile(startX,startY) == '#') {
                game_map.set_tile(startX, startY, '.');
                floorCount++;
            }
        }
    }

    place_exit(game_map);

    return start_pos;
}

void DungeonGenerator::place_exit(Map &game_map) {
    char exit_symbol = '>';
    int exit_X = Rng::generate_random_number(1, Map::WIDTH-2);
    int exit_Y = Rng::generate_random_number(1, Map::HEIGHT-2);

    while(true) {
        if(game_map.get_tile(exit_X, exit_Y) == '.') {
            game_map.set_tile(exit_X, exit_Y, exit_symbol);
            break;
        }
        exit_X = Rng::generate_random_number(1, Map::WIDTH-2);
        exit_Y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}


void DungeonGenerator::spawn_enemies(Level& current_level, const Vec2& player_pos, const std::vector<Enemy> &enemies_templates) {
    if (enemies_templates.empty())
      return;

    for (int i = 0; i < 3; ++i) {
        int r = Rng::generate_random_number(0, static_cast<int>(enemies_templates.size()) - 1);
        current_level.enemies.push_back(enemies_templates[r]);
    }

    Vec2 temp_pos{0,0};
    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);

    size_t enemies_counter = 0;

    while (enemies_counter < current_level.enemies.size()) {
        if (current_level.get_level_map().get_tile(temp_pos.x, temp_pos.y) == '.' && temp_pos != player_pos) {
            current_level.enemies[enemies_counter].get_entity_pos() = temp_pos;
            enemies_counter++;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}

void DungeonGenerator::place_items(Level& current_level, const Vec2 &player_pos, const std::vector<std::unique_ptr<Item>> &items_templates) {
    if (items_templates.empty())
        return;

    Vec2 temp_pos{0,0};

    for (int i = 0; i < 3; ++i) {
        int r = Rng::generate_random_number(0, static_cast<int>(items_templates.size()) - 1);
        current_level.items.push_back(items_templates[r]->clone());
    }

    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);

    size_t items_counter = 0;

    while (items_counter < current_level.items.size()) {
        if (current_level.get_level_map().get_tile(temp_pos.x, temp_pos.y) == '.' && temp_pos != player_pos) {
            current_level.items[items_counter]->get_item_pos() = temp_pos;
            items_counter++;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}


