#ifndef DUNGEON_H
#define DUNGEON_H


#include "../core/Map.h"
#include "../utils/Rng.h"
#include "../utils/Vec2.h"

class DungeonGenerator {
public:
    DungeonGenerator();
    Vec2 generate(Map& game_map);
private:
    void place_exit(Map& game_map);
};



#endif //DUNGEON_H
