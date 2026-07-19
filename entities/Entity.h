#ifndef ENTITY_H
#define ENTITY_H

#include "../utils/Vec2.h"
#include <string>

class Entity {
private:
    std::string name_;
    char entity_symbol_;
    int health_;

    Vec2 entity_pos;
public:
    Entity(const std::string& name, int health, char entity_symbol);

    const Vec2& get_entity_pos() const;
    Vec2& get_entity_pos();

    char get_entity_symbol();
};



#endif //ENTITY_H
