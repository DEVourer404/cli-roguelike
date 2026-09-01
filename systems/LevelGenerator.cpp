#include "LevelGenerator.h"
#include "entities/Player.h"


LevelGenerator::LevelGenerator() = default;

int random_direction() {
    return (Rng::generate_random_number(1,4) - 1);
}

void LevelGenerator::generate(Level& current_level, Player& player,
    const std::vector<Enemy>& enemies_templates, const std::vector<std::unique_ptr<Item>>& items_templates) {

    switch (current_level.get_room_type()) {
        case RoomType::Normal:
            generate_normal_level(current_level.get_level_map());
            spawn_player(current_level, player);
            spawn_enemies(current_level, player.get_entity_pos(), enemies_templates);
            place_items(current_level, player.get_entity_pos(), items_templates);
            break;
        case RoomType::Shop:
            generate_shop_level(current_level.get_level_map());
            spawn_player(current_level, player);
            place_items(current_level, player.get_entity_pos(), items_templates);
            for (auto& item : current_level.get_items()) {
                item->set_sellable(true);
            }
            break;
        case RoomType::Boss:
            break;
        default:
            break;
    }
}

void LevelGenerator::generate_normal_level(Map& game_map, int direction_change_probability) {
    int startX = Rng::generate_random_number(1, Map::WIDTH-2);
    int startY = Rng::generate_random_number(1, Map::HEIGHT-2);

    int dx[] = {0,0,1,-1};
    int dy[] = {-1,1,0,0};

    int dir = random_direction();
    int floorCount = 1;

    while ((floorCount*100)/(Map::WIDTH*Map::HEIGHT) < 50) {
        // momentum - szansa na zmiane kierunku
        if (Rng::check_chance(direction_change_probability))
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
}

void LevelGenerator::generate_shop_level(Map& game_map) {
    for (int y = 1; y <= Map::HEIGHT - 2; y++) {
        for (int x = 1; x <= Map::WIDTH - 2; x++) {
            game_map.set_tile(x,y, '.');
        }
    }
    // placing merchant
    game_map.set_tile(Map::WIDTH / 2, Map::HEIGHT / 2, 'M');

    place_exit(game_map);
}

void LevelGenerator::place_exit(Map &game_map) {
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

void LevelGenerator::spawn_player(Level &current_level, Player &player) {
    Vec2 temp_pos{0,0};
    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);


    while (true) {
        if(current_level.get_level_map().get_tile(temp_pos.x, temp_pos.y) == '.') {
            player.get_entity_pos() = temp_pos;
            break;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}

void LevelGenerator::spawn_enemies(Level& current_level, const Vec2& player_pos, const std::vector<Enemy> &enemies_templates) {
    if (enemies_templates.empty())
      return;

    for (int i = 0; i < 3; ++i) {
        int r = Rng::generate_random_number(0, static_cast<int>(enemies_templates.size()) - 1);
        current_level.add_enemy(enemies_templates[r]);
    }

    Vec2 temp_pos{0,0};
    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);

    size_t enemies_counter = 0;

    while (enemies_counter < current_level.get_enemies().size()) {
        if (current_level.get_level_map().get_tile(temp_pos.x, temp_pos.y) == '.' && temp_pos != player_pos) {
            current_level.get_enemies()[enemies_counter].get_entity_pos() = temp_pos;
            enemies_counter++;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}

void LevelGenerator::place_items(Level& current_level, const Vec2 &player_pos, const std::vector<std::unique_ptr<Item>> &items_templates) {
    if (items_templates.empty())
        return;

    Vec2 temp_pos{0,0};

    for (int i = 0; i < 3; ++i) {
        int r = Rng::generate_random_number(0, static_cast<int>(items_templates.size()) - 1);
        current_level.add_item(items_templates[r]->clone());
    }

    temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
    temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);

    size_t items_counter = 0;

    while (items_counter < current_level.get_items().size()) {
        if (current_level.get_level_map().get_tile(temp_pos.x, temp_pos.y) == '.' && temp_pos != player_pos) {
            current_level.get_items()[items_counter]->get_item_pos() = temp_pos;
            items_counter++;
        }
        temp_pos.x = Rng::generate_random_number(1, Map::WIDTH-2);
        temp_pos.y = Rng::generate_random_number(1, Map::HEIGHT-2);
    }
}


