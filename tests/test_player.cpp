#include <gtest/gtest.h>
#include "entities/Player.h"
#include "items/Weapon.h"
#include "items/Armor.h"
#include "items/Consumable.h"

TEST(PlayerTest, InventoryStartsEmpty) {
    Player player("Hero", 'P');

    EXPECT_EQ(player.get_inventory_size(), 0);
    EXPECT_FALSE(player.is_inventory_full());
}

TEST(PlayerTest, AddItemsUpToMaximumCapacity) {
    Player player("Hero", 'P');

    for (int i = 0; i < Player::MAX_INVENTORY_SIZE; ++i) {
        player.add_to_inventory(std::make_unique<Weapon>("w" + std::to_string(i), "Sword", 5, 10));
    }

    EXPECT_EQ(player.get_inventory_size(), Player::MAX_INVENTORY_SIZE);
    EXPECT_TRUE(player.is_inventory_full());
}

TEST(PlayerTest, AddingItemWhenInventoryIsFullDoesNothing) {
    Player player("Hero", 'P');
    for (int i = 0; i < Player::MAX_INVENTORY_SIZE; ++i) {
        player.add_to_inventory(std::make_unique<Weapon>("w" + std::to_string(i), "Sword", 5, 10));
    }

    auto extra_item = std::make_unique<Armor>("extra_armor", "Shield", 5, 20);
    player.add_to_inventory(std::move(extra_item));

    EXPECT_EQ(player.get_inventory_size(), Player::MAX_INVENTORY_SIZE);
    EXPECT_TRUE(player.is_inventory_full());
}

TEST(PlayerTest, RemoveFromInventoryShiftsElementsLeft) {
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Weapon>("w1", "Iron Sword", 5, 10));
    player.add_to_inventory(std::make_unique<Weapon>("w2", "Steel Axe", 10, 20));
    player.add_to_inventory(std::make_unique<Weapon>("w3", "Wooden Bow", 3, 5));

    player.remove_from_inventory(1);

    const auto& items = player.get_inventory_items();
    EXPECT_EQ(player.get_inventory_size(), 2);
    ASSERT_NE(items[0], nullptr);
    EXPECT_EQ(items[0]->get_name(), "Iron Sword");
    ASSERT_NE(items[1], nullptr);
    EXPECT_EQ(items[1]->get_name(), "Wooden Bow");
    EXPECT_EQ(items[2], nullptr);
}

TEST(PlayerTest, RemoveEquippedItemClearsEquipmentSlot) {
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Weapon>("w1", "Excalibur", 25, 100));
    player.add_to_inventory(std::make_unique<Armor>("a1", "Dragon Armor", 15, 150));

    auto* weapon_ptr = dynamic_cast<Weapon*>(player.get_inventory_items()[0].get());
    auto* armor_ptr = dynamic_cast<Armor*>(player.get_inventory_items()[1].get());
    player.equip_weapon(weapon_ptr);
    player.equip_armor(armor_ptr);

    ASSERT_EQ(player.get_equipment().weapon, weapon_ptr);
    ASSERT_EQ(player.get_equipment().armor, armor_ptr);

    player.remove_from_inventory(0);
    EXPECT_EQ(player.get_equipment().weapon, nullptr);

    player.remove_from_inventory(0);
    EXPECT_EQ(player.get_equipment().armor, nullptr);

    EXPECT_EQ(player.get_inventory_size(), 0);
}

TEST(PlayerTest, RemoveInvalidIndexDoesNothing) {
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Weapon>("w1", "Dagger", 2, 5));

    player.remove_from_inventory(-1);
    player.remove_from_inventory(5);

    EXPECT_EQ(player.get_inventory_size(), 1);
    EXPECT_EQ(player.get_inventory_items()[0]->get_name(), "Dagger");
}

TEST(PlayerTest, InitialStatsAndCalculations) {
    Player player("Hero", 'P');
    Stats stats = player.get_stats();

    EXPECT_EQ(stats.strength, 1);
    EXPECT_EQ(stats.dexterity, 1);
    EXPECT_EQ(stats.constitution, 1);
    EXPECT_EQ(player.get_max_health(), 60);
    EXPECT_EQ(player.get_current_health(), 60);
    EXPECT_EQ(player.get_damage(), 10);
    EXPECT_EQ(player.get_dodge_chance(), 5);
    EXPECT_EQ(player.get_armor_rate(), 0);
}

TEST(PlayerTest, EquippingWeaponIncreasesDamage) {
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Weapon>("w1", "Warhammer", 12, 50));
    auto* weapon_ptr = dynamic_cast<Weapon*>(player.get_inventory_items()[0].get());

    player.equip_weapon(weapon_ptr);
    EXPECT_EQ(player.get_damage(), 22);

    player.equip_weapon(weapon_ptr);
    EXPECT_EQ(player.get_damage(), 10);
}

TEST(PlayerTest, EquippingArmorIncreasesArmorRate) {
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Armor>("a1", "Plate Armor", 8, 60));
    auto* armor_ptr = dynamic_cast<Armor*>(player.get_inventory_items()[0].get());

    player.equip_armor(armor_ptr);
    EXPECT_EQ(player.get_armor_rate(), 8);

    player.equip_armor(armor_ptr);
    EXPECT_EQ(player.get_armor_rate(), 0);
}

TEST(PlayerTest, AddXpTriggersLevelUpAndPendingPoints) {
    Player player("Hero", 'P');

    player.add_xp(150);

    EXPECT_EQ(player.get_level(), 2);
    EXPECT_EQ(player.get_current_xp(), 50);
    EXPECT_EQ(player.get_xp_to_next_level(), 200);
    EXPECT_TRUE(player.has_pending_level_ups());
}

TEST(PlayerTest, LevelUpIncreasesChosenStat) {
    Player player("Hero", 'P');
    player.add_xp(100);

    player.level_up(1); // Strength
    player.consume_level_up();

    EXPECT_EQ(player.get_stats().strength, 2);
    EXPECT_EQ(player.get_damage(), 20);
    EXPECT_FALSE(player.has_pending_level_ups());

    player.add_xp(200);
    player.level_up(2); // Dexterity
    player.consume_level_up();

    EXPECT_EQ(player.get_stats().dexterity, 2);
    EXPECT_EQ(player.get_dodge_chance(), 10);

    player.add_xp(300);
    player.level_up(3); // Constitution
    player.consume_level_up();

    EXPECT_EQ(player.get_stats().constitution, 2);
    EXPECT_EQ(player.get_max_health(), 70);
}

TEST(PlayerTest, ModifyGold) {
    Player player("Hero", 'P');

    EXPECT_EQ(player.get_gold(), 0);

    player.modify_gold(100);
    EXPECT_EQ(player.get_gold(), 100);

    player.modify_gold(-40);
    EXPECT_EQ(player.get_gold(), 60);
}
