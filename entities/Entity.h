#ifndef ENTITY_H
#define ENTITY_H

#include "../utils/Vec2.h"
#include <string>

class Entity {
private:
    std::string name_;
    char entity_symbol_;
    int max_health_;
    int current_health_;
    int damage_;

    Vec2 entity_pos;
public:
    Entity(const std::string& name, int health, int damage, char entity_symbol);

    const Vec2& get_entity_pos() const;
    Vec2& get_entity_pos();
    char get_entity_symbol() const;

    bool isAlive() const;

    int get_max_health() const;
    int get_current_health() const;
    int get_damage() const;

    void modify_health(int value);

    void set_damage(int value);
    void set_max_health(int value);

};



#endif //ENTITY_H
