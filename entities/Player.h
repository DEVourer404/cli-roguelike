#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../core/Map.h"
#include "Enemy.h"
#include <vector>
#include <memory>

class Player: public Entity{
private:
public:
    Player(const std::string& name, int health, char player_symbol);

    void handle_movement( Map& game_map, const std::vector<std::unique_ptr<Enemy>>& enemies);
};



#endif //PLAYER_H
