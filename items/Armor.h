#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor: public Item{
private:
    int armor_rate_;
public:
    Armor(std::string id, std::string name, int armor_rate, int price = 0);

    std::unique_ptr<Item> clone() const override;
    void use(Player& player) override;

    int get_armor_rate() const;
};



#endif //ARMOR_H
