#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Renderer.h"
#include "../entities/Player.h"
#include "../systems/DungeonGenerator.h"
#include "Level.h"

class Game {
public:
    Game();
    void main_menu();

private:
    void run();
    void move_to_new_level();

    Renderer renderer_;
    DungeonGenerator dungeon_generator_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Level> current_level_;

    bool running;
};



#endif //GAME_H
