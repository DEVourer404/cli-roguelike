#ifndef COMBAT_H
#define COMBAT_H

#include "Renderer.h"
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

    void player_turn(Player& player, Level& current_level, Renderer& renderer);
    void enemy_turn(Enemy& enemy, Player& player, Map& game_map);

    bool resolve_attack(Entity& attacker, Entity& target);
public:
    std::string current_entity_turn_text_;
    Combat();
    CombatResult combat_loop(Player& player, Level& current_level, Renderer& renderer);
};



#endif //COMBAT_H
