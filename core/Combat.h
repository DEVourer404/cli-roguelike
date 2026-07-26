#ifndef COMBAT_H
#define COMBAT_H

#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../utils/Vec2.h"

enum class GameState {
    PLAYER_TURN,
    ENEMY_TURN,
    GAME_OVER,
    VICTORY
};

class Combat {
private:
    GameState current_state_;

    void player_turn(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map);
    void enemy_turn(Enemy& enemy, Player& player, Map& game_map);
public:
    Combat();
    void combat_loop(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map, bool& is_running);
};



#endif //COMBAT_H
