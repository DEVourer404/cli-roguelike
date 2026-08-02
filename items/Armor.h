#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor: public Item{
private:
    int armor_rate_;
public:
    Armor(std::string id, std::string name, int armor_rate);

    int get_armor_rate() const;
};



#endif //ARMOR_H
