#ifndef ENTITY_H
#define ENTITY_H

#include "../utils/Vec2.h"
#include <string>

class Entity {
protected:
    int current_health_;
private:
    std::string name_;
    char entity_symbol_;
    Vec2 entity_pos_;
public:
    Entity(const std::string& name, char entity_symbol);

    const Vec2& get_entity_pos() const;
    Vec2& get_entity_pos();
    char get_entity_symbol() const;
    bool isAlive() const;
    virtual int get_max_health() const = 0;
    int get_current_health() const;
    virtual int get_damage() const = 0;
    const std::string& get_name() const;
    void modify_health(int value);

    virtual ~Entity() = default;
};



#endif //ENTITY_H
