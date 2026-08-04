#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

class Item {
protected:
    std::string id_;
    char symbol{};
    std::string name_;

public:
    Item(std::string  id, std::string  name, char symbol);
    virtual ~Item() = default;

    virtual std::unique_ptr<Item> clone() const = 0;

    const std::string& get_id() const;
    char get_symbol() const;
    const std::string& get_name() const;
};



#endif //ITEM_H
