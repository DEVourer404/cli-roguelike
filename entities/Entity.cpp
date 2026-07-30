#include "Entity.h"

Entity::Entity(const std::string& name, int health, int damage, char entity_symbol):
name_(name), max_health_(health), damage_(damage), current_health_(max_health_), entity_symbol_(entity_symbol)  {}

const Vec2 &Entity::get_entity_pos() const{
    return entity_pos;
}

Vec2& Entity::get_entity_pos() {
    return entity_pos;
}

char Entity::get_entity_symbol() const {
    return entity_symbol_;
}

bool Entity::isAlive() const {
    return (current_health_ > 0);
}

int Entity::get_current_health() const {
    return current_health_;
}

int Entity::get_max_health() const {
    return max_health_;
}

int Entity::get_damage() const {
    return damage_;
}

const std::string& Entity::get_name() const {
    return name_;
}


void Entity::modify_health(int value)  {
    current_health_ += value;
    if(current_health_< 0) current_health_ = 0;
    if(current_health_ > max_health_) current_health_ = max_health_;
}

void Entity::set_max_health(int value) {
    max_health_ += value;
    current_health_ = max_health_;
}

void Entity::set_damage(int value) {
    damage_+=value;
}




