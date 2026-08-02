#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
protected:
    std::string id_;
    char symbol{};
    std::string name_;

public:
    Item(std::string  id, std::string  name, char symbol);
    virtual ~Item() = default;

    const std::string& get_id() const;
    char get_symbol() const;
    const std::string& get_name() const;
};



#endif //ITEM_H
