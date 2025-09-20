# Richman - TDD开发指南

## 📖 项目简介

Richman是一个使用测试驱动开发（TDD）方法构建的C++项目。本项目展示了如何建立完整的TDD工作流程，包括自动化构建、测试管理和持续集成。

**软件工程2组** - 展示现代C++开发最佳实践

## 🏗️ 项目结构

```
Richman/
├── include/              # 头文件
│   ├── calculator.h      # 计算器类
│   ├── mathutils.h       # 数学工具类
│   └── hello.h           # 问候功能类
├── src/                  # 源代码实现
│   ├── calculator.cpp
│   ├── mathutils.cpp
│   └── hello.cpp
├── tests/                # 测试文件
│   ├── test_calculator.cpp
│   ├── test_mathutils.cpp
│   ├── test_hello.cpp
│   └── test_game_suite.cpp
├── googletest/           # Google Test框架
├── obj/                  # 编译对象文件（自动生成）
├── bin/                  # 可执行文件（自动生成）
├── lib/                  # 库文件（自动生成）
├── Makefile              # 构建配置
├── test_batch.txt        # 批量测试配置
└── README.md             # 本文件
```

## ⚡ 快速开始

### 前置要求

- **编译器**: g++ (支持C++17)
- **构建工具**: make
- **版本控制**: git
- **操作系统**: Linux/Unix (WSL2支持)

### 克隆和构建

```bash
# 克隆仓库
git clone https://github.com/ottoiflu/Richman.git
cd Richman

# 切换到开发分支
git checkout zhn

# 运行所有测试
make test

# 清理构建文件
make clean
```

## 🔄 TDD开发流程

### TDD三步法则

1. **🔴 Red**: 先写失败的测试
2. **🟢 Green**: 写最少代码让测试通过  
3. **🔵 Refactor**: 重构改进代码质量

### 实际开发示例

#### 步骤1: 创建测试文件 (Red)

```cpp
// tests/test_newfeature.cpp
#include "gtest/gtest.h"
#include "newfeature.h"

TEST(NewFeatureTest, BasicFunction) {
    NewFeature feature;
    EXPECT_EQ(feature.calculate(5), 25);
}
```

#### 步骤2: 创建头文件

```cpp
// include/newfeature.h
#ifndef NEWFEATURE_H
#define NEWFEATURE_H

class NewFeature {
public:
    int calculate(int input);
};

#endif
```

#### 步骤3: 实现功能 (Green)

```cpp
// src/newfeature.cpp
#include "newfeature.h"

int NewFeature::calculate(int input) {
    return input * input;  // 最简实现
}
```

#### 步骤4: 运行测试

```bash
make test
```

## 🧪 测试管理

### 运行所有测试

```bash
make test
```

### 运行特定测试套件

```bash
# 只运行Calculator相关测试
./bin/run_tests --gtest_filter=CalculatorTest.*

# 只运行Hello相关测试  
./bin/run_tests --gtest_filter=HelloTest.*

# 运行多个测试套件
./bin/run_tests --gtest_filter=CalculatorTest.*:MathUtilsTest.*
```

### 运行单个测试用例

```bash
# 运行特定测试用例
./bin/run_tests --gtest_filter=HelloTest.SayHello

# 使用通配符
./bin/run_tests --gtest_filter=HelloTest.Say*
```

### 批量测试配置

编辑 `test_batch.txt` 文件：

```bash
# 批量测试配置示例
CalculatorTest.*
MathUtilsTest.Power
HelloTest.Say*
```

运行批量测试：

```bash
make run-batch
```

使用自定义配置文件：

```bash
make run-batch TEST_BATCH_FILE=my_tests.txt
```

## 🛠️ 开发指南

### 添加新功能

1. **创建测试文件**: `tests/test_yourfeature.cpp`
2. **编写失败测试**: 定义期望的接口和行为
3. **创建头文件**: `include/yourfeature.h`
4. **实现功能**: `src/yourfeature.cpp`
5. **运行测试**: `make test`
6. **重构优化**: 改进代码质量

### 测试编写规范

#### 测试命名

```cpp
TEST(ClassNameTest, MethodName_Condition_ExpectedBehavior) {
    // 测试实现
}
```

#### 测试结构 (AAA模式)

```cpp
TEST(CalculatorTest, Add_TwoPositiveNumbers_ReturnsSum) {
    // Arrange (准备)
    Calculator calc;
    int a = 2, b = 3;
    
    // Act (执行)
    int result = calc.add(a, b);
    
    // Assert (断言)
    EXPECT_EQ(result, 5);
}
```

#### 测试套件 (Test Fixtures)

```cpp
class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = new Game();
    }
    
    void TearDown() override {
        delete game;
    }
    
    Game* game;
};

TEST_F(GameTest, StartGame_InitialState_IsCorrect) {
    EXPECT_TRUE(game->isInitialized());
}
```

## 📊 测试策略

### 测试类型

1. **单元测试**: 测试单个类或函数
2. **集成测试**: 测试模块间交互
3. **系统测试**: 测试完整功能流程

### 测试覆盖

- **功能覆盖**: 测试所有公共接口
- **边界测试**: 测试边界条件和异常情况
- **回归测试**: 确保修改不破坏现有功能

### 测试组织

```cpp
// 按功能分组
class GameCalculationTest : public ::testing::Test { ... };
TEST_F(GameCalculationTest, HealthCalculation) { ... }
TEST_F(GameCalculationTest, ExperienceCalculation) { ... }

// 按场景分组  
TEST(CalculatorTest, Add_PositiveNumbers) { ... }
TEST(CalculatorTest, Add_NegativeNumbers) { ... }
TEST(CalculatorTest, Add_ZeroValues) { ... }
```

## 🚀 构建和部署

### 本地开发

```bash
# 开发模式：持续测试
make test

# 清理重建
make clean && make test

# 构建主程序（如果有main函数）
make all
```

### CI/CD集成

项目支持持续集成，每次提交都会自动运行测试：

```bash
# 提交前确保测试通过
make test
git add .
git commit -m "feat: 添加新功能"
git push origin your-branch
```

## 🔧 常见问题

### Q1: 编译错误 "missing separator"

**问题**: Makefile格式错误
**解决**: 确保命令行使用TAB字符缩进，不是空格

### Q2: 测试失败 "undefined reference to main"

**问题**: 缺少main函数
**解决**: 在测试文件中添加Google Test的main函数：

```cpp
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### Q3: 找不到头文件

**问题**: 包含路径错误
**解决**: 确保头文件在 `include/` 目录下，使用相对路径包含

### Q4: 链接错误

**问题**: 源文件未编译或链接
**解决**: 确保源文件在 `src/` 目录下，Makefile会自动发现

## 📚 学习资源

### Google Test文档

- [Google Test官方文档](https://google.github.io/googletest/)
- [测试断言参考](https://google.github.io/googletest/reference/assertions.html)

### TDD最佳实践

- **Red-Green-Refactor**: 严格遵循TDD循环
- **小步快跑**: 每次只添加最小可测试功能
- **测试先行**: 永远先写测试再写实现
- **重构习惯**: 定期重构提高代码质量

### 示例代码

查看 `tests/` 目录下的测试文件，了解不同测试模式：

- `test_calculator.cpp`: 基础单元测试
- `test_mathutils.cpp`: 算法测试
- `test_hello.cpp`: 字符串处理测试
- `test_game_suite.cpp`: 测试套件示例

## 🤝 贡献指南

1. **Fork仓库**: 创建自己的分支
2. **遵循TDD**: 先写测试再写实现
3. **代码规范**: 遵循C++编码标准
4. **测试覆盖**: 确保新功能有对应测试
5. **提交规范**: 使用清晰的提交信息
6. **Pull Request**: 提交前确保所有测试通过

## 📄 许可证

本项目采用MIT许可证 - 查看 [LICENSE](LICENSE) 文件了解详情

## 👥 团队成员

**软件工程2组**
- @Cliper314 (zc)
- @ottoiflu (Otto_Hust)

---

**Happy Coding with TDD! 🎉**

有问题请提交Issue或联系团队成员。