#include <gtest/gtest.h>
#include "core/Level.h"
#include "entities/Enemy.h"
#include "items/Weapon.h"

TEST(LevelTest, InitialProperties) {
    Level level("Cave Floor", 3, RoomType::Shop);

    EXPECT_EQ(level.get_level_name(), "Cave Floor");
    EXPECT_EQ(level.get_level_num(), 3);
    EXPECT_EQ(level.get_room_type(), RoomType::Shop);
    EXPECT_TRUE(level.get_enemies().empty());
    EXPECT_TRUE(level.get_items().empty());
}

TEST(LevelTest, AddEnemyAndEnemyAtLookup) {
    Level level("Dungeon", 1, RoomType::Normal);

    Enemy goblin("Goblin", 20, 5, 'g', 10);
    goblin.get_entity_pos() = Vec2(3, 4);
    level.add_enemy(goblin);

    EXPECT_EQ(level.get_enemies().size(), 1);

    Enemy* found = level.enemy_at(Vec2(3, 4));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->get_name(), "Goblin");

    Enemy* not_found = level.enemy_at(Vec2(0, 0));
    EXPECT_EQ(not_found, nullptr);
}

TEST(LevelTest, RemoveDeadEnemiesLeavesOnlyLivingEnemies) {
    Level level("Dungeon", 1);

    Enemy alive_enemy("Orc", 50, 10, 'o', 25);
    alive_enemy.get_entity_pos() = Vec2(2, 2);

    Enemy dead_enemy("Zombie", 30, 8, 'z', 15);
    dead_enemy.get_entity_pos() = Vec2(4, 4);
    dead_enemy.modify_health(-30); // 0 HP (dead)

    level.add_enemy(alive_enemy);
    level.add_enemy(dead_enemy);
    ASSERT_EQ(level.get_enemies().size(), 2);

    level.remove_dead_enemies();

    EXPECT_EQ(level.get_enemies().size(), 1);
    EXPECT_EQ(level.get_enemies()[0].get_name(), "Orc");
}

TEST(LevelTest, AddItemAndTakeItemAtTransfersOwnership) {
    Level level("Dungeon", 1);

    auto sword = std::make_unique<Weapon>("iron_sword", "Iron Sword", 10, 30);
    sword->get_item_pos() = Vec2(5, 5);
    level.add_item(std::move(sword));

    ASSERT_EQ(level.get_items().size(), 1);

    Item* item_ptr = level.item_at(Vec2(5, 5));
    ASSERT_NE(item_ptr, nullptr);
    EXPECT_EQ(item_ptr->get_name(), "Iron Sword");

    // Take item from the level
    std::unique_ptr<Item> taken = level.take_item_at(Vec2(5, 5));
    ASSERT_NE(taken, nullptr);
    EXPECT_EQ(taken->get_name(), "Iron Sword");

    // Ensure item was removed from level
    EXPECT_TRUE(level.get_items().empty());
    EXPECT_EQ(level.item_at(Vec2(5, 5)), nullptr);

    // Taking from empty tile returns nullptr
    EXPECT_EQ(level.take_item_at(Vec2(5, 5)), nullptr);
}
