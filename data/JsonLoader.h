#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "../utils/json.hpp"
#include <fstream>
#include <iostream>

#include "../entities/Enemy.h"
#include "../items/Item.h"

using json = nlohmann::json;

class JsonLoader {
private:
public:
    std::vector<Enemy> load_enemies();
    std::vector<std::unique_ptr<Item>> load_items();
};



#endif //JSONLOADER_H
