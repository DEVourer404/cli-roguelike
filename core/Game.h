#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Renderer.h"
#include "Level.h"
#include "../entities/Player.h"
#include "../systems/DungeonGenerator.h"
#include "Combat.h"

class Game {
public:
    Game();
    void main_menu();

private:
    void run();
    void move_to_new_level();
    void init_level();

    Renderer renderer_;
    DungeonGenerator dungeon_generator_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Level> current_level_;
    std::unique_ptr<Combat> current_combat_;

    CombatResult combat_result_;
    bool is_running_;
};



#endif //GAME_H
