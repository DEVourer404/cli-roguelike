#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

#include "utils/Vec2.h"

class Player;

class Item {
private:
    std::string id_;
    std::string name_;
    char symbol{};

    Vec2 item_pos_;

    int price_;

    bool is_picked_;
    bool is_sellable_;
public:
    Item(std::string  id, std::string  name, char symbol, int price = 0);
    virtual ~Item() = default;

    virtual std::unique_ptr<Item> clone() const = 0;
    virtual void use(Player& player) = 0;

    const std::string& get_id() const;
    char get_symbol() const;
    const std::string& get_name() const;
    int get_price() const;

    Vec2& get_item_pos();

    bool is_picked() const;
    bool is_sellable() const;
    void set_picked(bool value);
    void set_sellable(bool value);

    // // dodać do pól prywatnych, gettery i setery
    //
    // bool is_equipped_; // do usunięcia, w Player dodałem nową metodę do sprawdzania na bazie Equipment

};



#endif //ITEM_H
