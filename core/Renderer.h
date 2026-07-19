#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "Level.h"
#include "../entities/Player.h"

class Renderer {
public:
    Renderer();

    void print(Level& current_level, Player& player) const;
private:
};



#endif //RENDERER_H
