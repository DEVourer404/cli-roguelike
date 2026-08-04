#include "JsonLoader.h"
#include "../items/Weapon.h"
#include "../items/Armor.h"
#include "../items/Consumable.h"

std::vector<Enemy> JsonLoader::load_enemies() {
    std::ifstream file("../resources/enemies.json");

    std::vector<Enemy> loaded_enemies;

    if (!file.is_open()) {
        std::cerr << "Can't open the enemies file!" << std::endl;
        return loaded_enemies;
    }

    json data = json::parse(file);
    for (const auto& enemy: data) {
        auto name = enemy.at("name").get<std::string>();
        int health = enemy.at("health").get<int>();
        int damage = enemy.at("damage").get<int>();
        char symbol = enemy.at("symbol").get<std::string>()[0];
        int given_xp = enemy.at("given_xp").get<int>();

        loaded_enemies.emplace_back(name, health, damage, symbol, given_xp);
    }

    return loaded_enemies;
}

std::vector<std::unique_ptr<Item>> JsonLoader::load_items() {
    std::ifstream file("../resources/items.json");

    std::vector<std::unique_ptr<Item>> loaded_items;

    if (!file.is_open()) {
        std::cerr << "Can't open the items file!" << std::endl;
        return loaded_items;
    }

    json data = json::parse(file);
    for (const auto& item: data) {
        auto id = item.at("id").get<std::string>();
        auto name = item.at("name").get<std::string>();
        auto type = item.at("type").get<std::string>();

        if (type == "weapon") {
            int damage = item.at("damage").get<int>();
            loaded_items.push_back(std::make_unique<Weapon>(id, name, damage));
        } else if (type == "armor") {
            int armor_rate = item.at("armor_rate").get<int>();
            loaded_items.push_back(std::make_unique<Armor>(id, name, armor_rate));
        } else if (type == "consumable") {
            int amount = item.at("amount").get<int>();
            loaded_items.push_back(std::make_unique<Consumable>(id, name, amount));
        }
    }

    return loaded_items;
}
