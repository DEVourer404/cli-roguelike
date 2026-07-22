#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Entity.h"

class Enemy: public Entity {
private:

public:
    Enemy(const std::string& name, int health, int damage, char enemy_symbol);
};



#endif //ENEMY_H
