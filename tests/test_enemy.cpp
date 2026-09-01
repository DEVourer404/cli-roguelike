#include <gtest/gtest.h>
#include "entities/Enemy.h"
#include "core/Map.h"

TEST(EnemyTest, EnemyInitialProperties) {
    Enemy enemy("Goblin", 30, 8, 'g', 45);

    EXPECT_EQ(enemy.get_name(), "Goblin");
    EXPECT_EQ(enemy.get_max_health(), 30);
    EXPECT_EQ(enemy.get_current_health(), 30);
    EXPECT_EQ(enemy.get_damage(), 8);
    EXPECT_EQ(enemy.get_given_xp(), 45);
    EXPECT_EQ(enemy.get_entity_symbol(), 'g');
}

TEST(EnemyTest, BfsPathfindingOnOpenFloorMovesTowardsPlayer) {
    Map map;
    for (int y = 0; y < Map::HEIGHT; ++y) {
        for (int x = 0; x < Map::WIDTH; ++x) {
            map.set_tile(x, y, '.');
        }
    }

    Enemy enemy("Orc", 40, 10, 'o', 50);
    enemy.get_entity_pos() = Vec2(5, 5);
    Vec2 player_pos(5, 2);

    Vec2 next_step = enemy.find_path_to_player(player_pos, map);

    EXPECT_EQ(next_step, Vec2(5, 4));
}

TEST(EnemyTest, BfsPathfindingNavigatesAroundWall) {
    Map map;
    for (int y = 0; y < Map::HEIGHT; ++y) {
        for (int x = 0; x < Map::WIDTH; ++x) {
            map.set_tile(x, y, '.');
        }
    }

    Enemy enemy("Goblin", 20, 5, 'g', 20);
    enemy.get_entity_pos() = Vec2(5, 5);
    Vec2 player_pos(5, 3);

    // Place wall blocking direct path at (5, 4)
    map.set_tile(5, 4, '#');

    Vec2 next_step = enemy.find_path_to_player(player_pos, map);

    bool is_valid_detour = (next_step == Vec2(4, 5) || next_step == Vec2(6, 5));
    EXPECT_TRUE(is_valid_detour);
}

TEST(EnemyTest, BfsPathfindingReturnsCurrentPositionWhenPlayerIsUnreachable) {
    Map map;
    for (int y = 0; y < Map::HEIGHT; ++y) {
        for (int x = 0; x < Map::WIDTH; ++x) {
            map.set_tile(x, y, '.');
        }
    }

    Enemy enemy("Skeleton", 25, 6, 's', 30);
    enemy.get_entity_pos() = Vec2(10, 10);
    Vec2 player_pos(2, 2);

    // Completely surround player with walls
    map.set_tile(1, 2, '#');
    map.set_tile(3, 2, '#');
    map.set_tile(2, 1, '#');
    map.set_tile(2, 3, '#');

    Vec2 next_step = enemy.find_path_to_player(player_pos, map);

    EXPECT_EQ(next_step, Vec2(10, 10));
}

TEST(EnemyTest, BfsPathfindingTargetIsAdjacentStepDirectlyIntoPlayer) {
    Map map;
    for (int y = 0; y < Map::HEIGHT; ++y) {
        for (int x = 0; x < Map::WIDTH; ++x) {
            map.set_tile(x, y, '.');
        }
    }

    Enemy enemy("Bat", 10, 3, 'b', 10);
    enemy.get_entity_pos() = Vec2(5, 5);
    Vec2 player_pos(6, 5);

    Vec2 next_step = enemy.find_path_to_player(player_pos, map);

    EXPECT_EQ(next_step, Vec2(6, 5));
}
