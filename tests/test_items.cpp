#include <gtest/gtest.h>
#include "items/Weapon.h"
#include "items/Armor.h"
#include "items/Consumable.h"
#include "entities/Player.h"

TEST(ItemTest, WeaponPropertiesAndCloning) {
    Weapon sword("iron_sword", "Iron Sword", 8, 45);

    std::unique_ptr<Item> cloned = sword.clone();
    auto* cloned_weapon = dynamic_cast<Weapon*>(cloned.get());

    EXPECT_EQ(sword.get_id(), "iron_sword");
    EXPECT_EQ(sword.get_name(), "Iron Sword");
    EXPECT_EQ(sword.get_damage(), 8);
    EXPECT_EQ(sword.get_price(), 45);
    EXPECT_EQ(sword.get_symbol(), '/');

    ASSERT_NE(cloned_weapon, nullptr);
    EXPECT_EQ(cloned_weapon->get_id(), "iron_sword");
    EXPECT_EQ(cloned_weapon->get_name(), "Iron Sword");
    EXPECT_EQ(cloned_weapon->get_damage(), 8);
    EXPECT_EQ(cloned_weapon->get_price(), 45);
    EXPECT_NE(cloned_weapon, &sword);
}

TEST(ItemTest, ArmorPropertiesAndCloning) {
    Armor shield("wood_shield", "Wooden Shield", 4, 25);

    std::unique_ptr<Item> cloned = shield.clone();
    auto* cloned_armor = dynamic_cast<Armor*>(cloned.get());

    EXPECT_EQ(shield.get_id(), "wood_shield");
    EXPECT_EQ(shield.get_name(), "Wooden Shield");
    EXPECT_EQ(shield.get_armor_rate(), 4);
    EXPECT_EQ(shield.get_price(), 25);
    EXPECT_EQ(shield.get_symbol(), '[');

    ASSERT_NE(cloned_armor, nullptr);
    EXPECT_EQ(cloned_armor->get_id(), "wood_shield");
    EXPECT_EQ(cloned_armor->get_name(), "Wooden Shield");
    EXPECT_EQ(cloned_armor->get_armor_rate(), 4);
    EXPECT_EQ(cloned_armor->get_price(), 25);
    EXPECT_NE(cloned_armor, &shield);
}

TEST(ItemTest, ConsumablePropertiesAndCloning) {
    Consumable potion("health_pot", "Small Health Potion", 20, 15);

    std::unique_ptr<Item> cloned = potion.clone();
    auto* cloned_potion = dynamic_cast<Consumable*>(cloned.get());

    EXPECT_EQ(potion.get_id(), "health_pot");
    EXPECT_EQ(potion.get_name(), "Small Health Potion");
    EXPECT_EQ(potion.get_amount(), 20);
    EXPECT_EQ(potion.get_price(), 15);
    EXPECT_EQ(potion.get_symbol(), '!');

    ASSERT_NE(cloned_potion, nullptr);
    EXPECT_EQ(cloned_potion->get_amount(), 20);
    EXPECT_NE(cloned_potion, &potion);
}

TEST(ItemTest, UsingPotionHealsDamagedPlayerAndRemovesFromInventory) {
    Player player("Hero", 'P'); // 60 Max HP
    player.modify_health(-40);  // Health reduced to 20
    ASSERT_EQ(player.get_current_health(), 20);

    player.add_to_inventory(std::make_unique<Consumable>("pot_1", "Health Potion", 25, 10));
    ASSERT_EQ(player.get_inventory_size(), 1);

    player.use_item(0);

    EXPECT_EQ(player.get_current_health(), 45);
    EXPECT_EQ(player.get_inventory_size(), 0);
}

TEST(ItemTest, UsingPotionCannotExceedMaxHealth) {
    Player player("Hero", 'P'); // 60 Max HP
    player.modify_health(-10);  // Health reduced to 50
    ASSERT_EQ(player.get_current_health(), 50);

    player.add_to_inventory(std::make_unique<Consumable>("pot_big", "Greater Potion", 50, 50));

    player.use_item(0);

    EXPECT_EQ(player.get_current_health(), 60);
    EXPECT_EQ(player.get_inventory_size(), 0);
}
