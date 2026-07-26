#include "Combat.h"


Combat::Combat() {
    current_state_ = GameState::PLAYER_TURN;
}

void Combat::combat_loop(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map, bool& is_running) {
    switch (current_state_) {
        case GameState::PLAYER_TURN: {
            player_turn(player, enemies, game_map);
            break;
        }
        case GameState::ENEMY_TURN: {
            for (auto& enemy: enemies) {
                enemy_turn(*enemy, player, game_map);
            }
            break;
        }
        case GameState::GAME_OVER: {
            is_running = false;
            break;
        }
        case GameState::VICTORY: {

            break;
        }
    }
}

void Combat::player_turn(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map) {
    Vec2 new_pos  = player.move_player(game_map);

    for (auto& enemy: enemies) {
        if (new_pos == enemy->get_entity_pos() && enemy->isAlive()) {
            enemy->modify_health(-player.get_damage());
        }
    }
    player.get_entity_pos() = new_pos;
}

void Combat::enemy_turn(Enemy& enemy, Player& player, Map& game_map) {
    Vec2 new_pos = enemy.find_path_to_player(player.get_entity_pos(), game_map);

    if(new_pos == player.get_entity_pos()) {
        player.modify_health(-enemy.get_damage());
    }
    else {
        enemy.get_entity_pos()=new_pos;
    }
}


