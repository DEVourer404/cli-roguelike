#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"


class Consumable: public Item{
private:
    int amount_;
public:
    Consumable(std::string id, std::string name, int amount);

    std::unique_ptr<Item> clone() const override;
    void use(Player& player) override;

    int get_amount() const;
};



#endif //CONSUMABLE_H
