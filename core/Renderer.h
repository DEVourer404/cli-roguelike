#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "Level.h"
#include "../entities/Player.h"

class Renderer {
public:
    Renderer();

    void print(const Level& current_level, Player& player,  const std::vector<std::unique_ptr<Enemy>>& enemies) const;
private:
};



#endif //RENDERER_H
