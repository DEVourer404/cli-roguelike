#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "ConsoleUI.h"
#include "Level.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "items/Item.h"
#include "systems/LevelGenerator.h"
#include "TurnManager.h"
#include "data/JsonLoader.h"
#include <limits>

class Game {
public:
    Game();
    void main_menu();

private:
    void run();
    void move_to_new_level();
    void init_level();

    LevelGenerator level_generator_;
    std::vector<Enemy> enemy_templates_;
    std::vector<std::unique_ptr<Item>> item_templates_;

    std::unique_ptr<Player> player_;
    std::unique_ptr<Level> current_level_;
    std::unique_ptr<TurnManager> turn_manager_;

    bool is_running_;

    enum class Difficulty
    {
        Easy = 5,
        Medium = 10,
        Hard = 20,
        Endless = std::numeric_limits<int>::max()
    };

    Difficulty difficulty_{Difficulty::Easy};

    static std::string_view difficulty_name(Difficulty difficulty);
};



#endif //GAME_H
