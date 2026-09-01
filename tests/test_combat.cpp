#include <gtest/gtest.h>
#include "core/TurnManager.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "items/Weapon.h"
#include "items/Armor.h"
#include "utils/Rng.h"

TEST(CombatTest, RegularAttackDealsDamageAndTargetSurvives) {
    TurnManager turn_manager;
    Player player("Hero", 'P'); // 10 Base Damage
    Enemy enemy("Orc", 50, 5, 'o', 20); // 50 HP

    bool target_killed = turn_manager.resolve_attack(player, enemy);

    EXPECT_FALSE(target_killed);
    EXPECT_TRUE(enemy.isAlive());
    EXPECT_EQ(enemy.get_current_health(), 40);
}

TEST(CombatTest, FatalAttackKillsTargetAndReturnsTrue) {
    TurnManager turn_manager;
    Player player("Hero", 'P');
    player.add_to_inventory(std::make_unique<Weapon>("greatsword", "Greatsword", 40, 100));
    player.equip_weapon(dynamic_cast<Weapon*>(player.get_inventory_items()[0].get()));
    ASSERT_EQ(player.get_damage(), 50);

    Enemy goblin("Goblin", 30, 5, 'g', 15);

    bool target_killed = turn_manager.resolve_attack(player, goblin);

    EXPECT_TRUE(target_killed);
    EXPECT_FALSE(goblin.isAlive());
    EXPECT_EQ(goblin.get_current_health(), 0);
}

TEST(CombatTest, ArmorReducesIncomingDamage) {
    TurnManager turn_manager;
    Enemy attacker("Minotaur", 100, 20, 'M', 100);
    Player defender("Hero", 'P');

    defender.add_to_inventory(std::make_unique<Armor>("iron_plate", "Iron Plate", 8, 50));
    defender.equip_armor(dynamic_cast<Armor*>(defender.get_inventory_items()[0].get()));
    ASSERT_EQ(defender.get_armor_rate(), 8);

    // 20 damage - 8 armor = 12 net damage (60 - 12 = 48 HP)
    bool target_killed = turn_manager.resolve_attack(attacker, defender);

    EXPECT_FALSE(target_killed);
    EXPECT_EQ(defender.get_current_health(), 48);
}

TEST(CombatTest, MinimumDamageIsAlwaysAtLeastOne) {
    TurnManager turn_manager;
    Player attacker("Hero", 'P'); // 10 Base Damage
    Player heavily_armored("Tank", 'P');
    heavily_armored.add_to_inventory(std::make_unique<Armor>("tank_plate", "Tank Plate", 30, 200));
    heavily_armored.equip_armor(dynamic_cast<Armor*>(heavily_armored.get_inventory_items()[0].get()));
    ASSERT_EQ(heavily_armored.get_armor_rate(), 30);

    // 10 damage vs 30 armor -> clamped to 1 minimum damage
    bool target_killed = turn_manager.resolve_attack(attacker, heavily_armored);

    EXPECT_FALSE(target_killed);
    EXPECT_EQ(heavily_armored.get_current_health(), 59);
}

TEST(CombatTest, SuccessfulDodgeNegatesAllDamage) {
    TurnManager turn_manager;
    Enemy attacker("Slow Ogre", 80, 25, 'O', 50);
    Player defender("Rogue", 'P');

    // 10 DEX -> 50% max dodge
    for (int i = 0; i < 9; ++i) {
        defender.level_up(2);
    }
    ASSERT_EQ(defender.get_dodge_chance(), 50);

    // Seed RNG such that next roll triggers a dodge (roll <= 50)
    Rng::seed(1);

    bool target_killed = turn_manager.resolve_attack(attacker, defender);

    EXPECT_FALSE(target_killed);
    EXPECT_EQ(defender.get_current_health(), 60);
}
