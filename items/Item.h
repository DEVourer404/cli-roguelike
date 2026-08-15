#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

#include "utils/Vec2.h"

class Player;

class Item {
protected:
    std::string id_;
    char symbol{};
    std::string name_;

    Vec2 item_pos_;
public:
    Item(std::string  id, std::string  name, char symbol);
    virtual ~Item() = default;

    virtual std::unique_ptr<Item> clone() const = 0;
    virtual void use(Player& player) = 0;

    const std::string& get_id() const;
    char get_symbol() const;
    const std::string& get_name() const;

    Vec2& get_item_pos();
    bool is_picked_;
    bool is_equipped_;
};



#endif //ITEM_H
