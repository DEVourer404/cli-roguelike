#ifndef COMBAT_H
#define COMBAT_H

#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../utils/Vec2.h"


enum class CombatResult {
    CONTINUE,
    GAME_OVER,
    WAIT_INPUT
};

enum class TurnPhase {
    PLAYER,
    ENEMY
};

class Combat {
private:
    TurnPhase current_phase_;
    int current_enemy_index_;

    void player_turn(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map);
    void enemy_turn(Enemy& enemy, Player& player, Map& game_map);
public:
    std::string current_entity_turn_text_;
    Combat();
    CombatResult combat_loop(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, Map& game_map);
};



#endif //COMBAT_H
