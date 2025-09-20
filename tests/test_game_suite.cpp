// tests/test_game_suite.cpp
// 演示如何组织游戏相关的测试套件
#include "gtest/gtest.h"
#include "calculator.h"
#include "mathutils.h"

// 游戏计算相关的测试套件
class GameCalculationTest : public ::testing::Test {
protected:
    void SetUp() override {
        calc = new Calculator();
        utils = new MathUtils();
    }
    
    void TearDown() override {
        delete calc;
        delete utils;
    }
    
    Calculator* calc;
    MathUtils* utils;
};

TEST_F(GameCalculationTest, HealthCalculation) {
    // 测试游戏中的生命值计算
    int currentHealth = 100;
    int damage = calc->subtract(currentHealth, 25);
    EXPECT_EQ(damage, 75);
}

TEST_F(GameCalculationTest, ExperienceCalculation) {
    // 测试经验值计算
    int baseExp = 100;
    int levelMultiplier = utils->power(2, 3); // 2^3 = 8
    int totalExp = calc->add(baseExp, levelMultiplier);
    EXPECT_EQ(totalExp, 108);
}