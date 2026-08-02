#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon: public Item{
private:
    int damage_;
public:
    Weapon(std::string id, std::string name, int damage);

    int get_damage() const;
};



#endif //WEAPON_H
