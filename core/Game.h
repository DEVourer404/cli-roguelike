#ifndef GAME_H
#define GAME_H

#include <thread>
#include <chrono>
#include "Map.h"
#include "Renderer.h"
#include "../entities/Player.h"
#include "../systems/DungeonGenerator.h"
#include "Level.h"

enum class GameState {
    PLAYER_TURN,
    ENEMY_TURN,
    GAME_OVER,
    VICTORY
};

class Game {
public:
    Game();
    void main_menu();

private:
    void run();
    GameState move_to_new_level();

    Renderer renderer_;
    DungeonGenerator dungeon_generator_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Level> current_level_;

    bool is_running_;
};



#endif //GAME_H
