#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon: public Item{
private:
    int damage_;
public:
    Weapon(std::string id, std::string name, int damage, int price = 0);

    std::unique_ptr<Item> clone() const override;
    void use(Player& player) override;

    int get_damage() const;
};



#endif //WEAPON_H
