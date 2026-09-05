#include <gtest/gtest.h>
#include "utils/Vec2.h"
#include "utils/Rng.h"
#include "core/Logger.h"
#include <vector>

TEST(Vec2Test, DefaultConstructorInitializesToZero) {
    Vec2 v;

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
}

TEST(Vec2Test, CustomConstructorInitializesCoordinates) {
    Vec2 v(7, -4);

    EXPECT_EQ(v.x, 7);
    EXPECT_EQ(v.y, -4);
}

TEST(Vec2Test, EqualityOperator) {
    Vec2 a(3, 8);
    Vec2 b(3, 8);
    Vec2 c(3, 9);
    Vec2 d(4, 8);

    EXPECT_EQ(a, b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
}

TEST(Vec2Test, AdditionOperator) {
    Vec2 a(2, 5);
    Vec2 b(4, -2);

    Vec2 result = a + b;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(a.x, 2);
    EXPECT_EQ(a.y, 5);
}

TEST(Vec2Test, CompoundAdditionOperator) {
    Vec2 a(10, 15);
    Vec2 b(-3, 5);

    a += b;

    EXPECT_EQ(a.x, 7);
    EXPECT_EQ(a.y, 20);
}

TEST(RngTest, SeedGuaranteesDeterministicSequence) {
    Rng::seed(1337);
    std::vector<int> sequence1;
    for (int i = 0; i < 10; ++i) {
        sequence1.push_back(Rng::generate_random_number(1, 100));
    }

    Rng::seed(1337);
    std::vector<int> sequence2;
    for (int i = 0; i < 10; ++i) {
        sequence2.push_back(Rng::generate_random_number(1, 100));
    }

    EXPECT_EQ(sequence1, sequence2);
}

TEST(RngTest, GenerateRandomNumberRespectsMinAndMaxBounds) {
    Rng::seed(42);
    const int min_val = 5;
    const int max_val = 15;

    for (int i = 0; i < 100; ++i) {
        int val = Rng::generate_random_number(min_val, max_val);
        EXPECT_GE(val, min_val);
        EXPECT_LE(val, max_val);
    }
}

TEST(RngTest, CheckChanceBoundaryConditions) {
    EXPECT_FALSE(Rng::check_chance(0));
    EXPECT_FALSE(Rng::check_chance(-10));
    EXPECT_TRUE(Rng::check_chance(100));
    EXPECT_TRUE(Rng::check_chance(150));
}

TEST(LoggerTest, StoresUpToMaxCapacityAndPopsOldestFirst) {
    Logger::clear();

    for (int i = 1; i <= 5; ++i) {
        Logger::add_message_to_logger("Message " + std::to_string(i));
    }

    EXPECT_EQ(Logger::get_logs().size(), 5);
    EXPECT_EQ(Logger::get_logs().front(), "Message 1");
    EXPECT_EQ(Logger::get_logs().back(), "Message 5");

    Logger::add_message_to_logger("Message 6");

    EXPECT_EQ(Logger::get_logs().size(), 5);
    EXPECT_EQ(Logger::get_logs().front(), "Message 2");
    EXPECT_EQ(Logger::get_logs().back(), "Message 6");

    Logger::clear();
    EXPECT_TRUE(Logger::get_logs().empty());
}
