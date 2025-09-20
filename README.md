# Richman - C语言TDD开发指南

## 📖 项目简介

Richman是一个使用测试驱动开发（TDD）方法构建的C语言项目。本项目展示了如何在C语言环境下建立完整的TDD工作流程，包括自制测试框架、自动化构建和测试管理。

**软件工程2组** - 展示C语言TDD开发最佳实践

## 🏗️ 项目结构

```
Richman/
├── include/              # 头文件
│   ├── calculator.h      # 计算器函数声明
│   ├── mathutils.h       # 数学工具函数声明
│   ├── hello.h           # 问候功能函数声明
│   └── test_framework.h  # 自制测试框架
├── src/                  # 源代码实现
│   ├── calculator.c      # 计算器功能实现
│   ├── mathutils.c       # 数学工具实现
│   ├── hello.c           # 问候功能实现
│   └── test_framework.c  # 测试框架实现
├── tests/                # 测试文件
│   ├── test_calculator.c # 计算器测试
│   ├── test_mathutils.c  # 数学工具测试
│   ├── test_hello.c      # 问候功能测试
│   └── test_runner.c     # 测试运行器
├── obj/                  # 编译对象文件（自动生成）
├── bin/                  # 可执行文件（自动生成）
├── Makefile              # 构建配置
├── test_batch.txt        # 批量测试配置
└── README.md             # 本文件
```

## ⚡ 快速开始

### 前置要求

- **编译器**: gcc (支持C99)
- **构建工具**: make
- **版本控制**: git
- **操作系统**: Linux/Unix (WSL2支持)
- **标准库**: 只需要C标准库，无外部依赖

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

```c
// tests/test_newfeature.c
#include "test_framework.h"
#include "newfeature.h"

TEST(NewFeatureTest, BasicFunction) {
    int result = newfeature_calculate(5);
    EXPECT_EQ(25, result);
}
```

#### 步骤2: 创建头文件

```c
// include/newfeature.h
#ifndef NEWFEATURE_H
#define NEWFEATURE_H

#ifdef __cplusplus
extern "C" {
#endif

// 新功能函数声明
int newfeature_calculate(int input);

#ifdef __cplusplus
}
#endif

#endif /* NEWFEATURE_H */
```

#### 步骤3: 实现功能 (Green)

```c
// src/newfeature.c
#include "newfeature.h"

int newfeature_calculate(int input) {
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

### 自定义测试运行

由于我们使用自制的测试框架，测试运行更加简单：

```bash
# 运行所有测试（默认行为）
make test

# 直接运行测试可执行文件
./bin/run_tests
```

注意：我们的轻量级测试框架会自动运行所有测试，输出清晰的测试结果。

### 单独测试特定功能

虽然我们的测试框架默认运行所有测试，但你可以通过以下方法测试特定功能：

#### 方法1：编译并运行单个测试文件

```bash
# 只编译和测试calculator模块
gcc -std=c99 -g -Wall -I./include -c src/calculator.c -o obj/calculator.o
gcc -std=c99 -g -Wall -I./include -c src/test_framework.c -o obj/test_framework.o
gcc -std=c99 -g -Wall -I./include -c tests/test_calculator.c -o obj/test_calculator.o

# 创建单独的测试程序
gcc -std=c99 -g -Wall -I./include -o bin/test_calculator obj/calculator.o obj/test_framework.o obj/test_calculator.o -lm

# 但需要添加main函数，见下面的方法2
```

#### 方法2：创建临时测试运行器

创建一个临时的测试运行器来只运行特定测试：

```bash
# 创建临时测试文件
cat > temp_test_calculator.c << 'EOF'
#include "test_framework.h"

// 声明要测试的函数
extern void run_CalculatorTest_Add(void);
extern void run_CalculatorTest_Subtract(void);

int main(void) {
    init_test_framework();
    
    printf("[----------] 2 tests from CalculatorTest\n");
    RUN_TEST(CalculatorTest, Add);
    RUN_TEST(CalculatorTest, Subtract);
    printf("[----------] 2 tests from CalculatorTest (0 ms total)\n\n");
    
    print_test_results();
    return run_all_tests();
}
EOF

# 编译并运行
gcc -std=c99 -g -Wall -I./include -o bin/test_calc_only \
    src/calculator.c src/test_framework.c tests/test_calculator.c temp_test_calculator.c -lm

# 运行特定测试
./bin/test_calc_only

# 清理临时文件
rm temp_test_calculator.c
```

#### 方法3：修改test_runner.c（推荐用于开发阶段）

临时注释掉不需要的测试：

```c
// 在 tests/test_runner.c 中注释掉不需要的测试
int main(void) {
    init_test_framework();
    
    // 只运行Calculator测试
    printf("[----------] 2 tests from CalculatorTest\n");
    RUN_TEST(CalculatorTest, Add);
    RUN_TEST(CalculatorTest, Subtract);
    printf("[----------] 2 tests from CalculatorTest (0 ms total)\n\n");
    
    // 注释掉其他测试
    /*
    printf("[----------] 2 tests from MathUtilsTest\n");
    RUN_TEST(MathUtilsTest, Power);
    RUN_TEST(MathUtilsTest, Factorial);
    printf("[----------] 2 tests from MathUtilsTest (0 ms total)\n\n");
    
    printf("[----------] 3 tests from HelloTest\n");
    RUN_TEST(HelloTest, SayHello);
    RUN_TEST(HelloTest, SayHelloWithName);
    RUN_TEST(HelloTest, GetGreeting);
    printf("[----------] 3 tests from HelloTest (0 ms total)\n\n");
    */
    
    print_test_results();
    return run_all_tests();
}
```

然后运行：
```bash
make test
```

#### 方法4：使用条件编译（高级用法）

在测试文件中使用条件编译：

```c
// 在 tests/test_runner.c 开头添加
#define RUN_CALCULATOR_TESTS 1
#define RUN_MATHUTILS_TESTS 0
#define RUN_HELLO_TESTS 0

int main(void) {
    init_test_framework();
    
#if RUN_CALCULATOR_TESTS
    printf("[----------] 2 tests from CalculatorTest\n");
    RUN_TEST(CalculatorTest, Add);
    RUN_TEST(CalculatorTest, Subtract);
    printf("[----------] 2 tests from CalculatorTest (0 ms total)\n\n");
#endif

#if RUN_MATHUTILS_TESTS
    printf("[----------] 2 tests from MathUtilsTest\n");
    RUN_TEST(MathUtilsTest, Power);
    RUN_TEST(MathUtilsTest, Factorial);
    printf("[----------] 2 tests from MathUtilsTest (0 ms total)\n\n");
#endif

#if RUN_HELLO_TESTS
    printf("[----------] 3 tests from HelloTest\n");
    RUN_TEST(HelloTest, SayHello);
    RUN_TEST(HelloTest, SayHelloWithName);
    RUN_TEST(HelloTest, GetGreeting);
    printf("[----------] 3 tests from HelloTest (0 ms total)\n\n");
#endif
    
    print_test_results();
    return run_all_tests();
}
```

### 快速单模块测试（推荐方法）

项目提供了`test_single.sh`脚本，可以轻松测试单个模块：

```bash
# 测试calculator模块
./test_single.sh calculator

# 测试mathutils模块  
./test_single.sh mathutils

# 测试hello模块
./test_single.sh hello

# 查看可用模块
./test_single.sh
```

#### 示例输出：

```bash
$ ./test_single.sh calculator
=== 测试 calculator 模块 ===
编译Calculator模块测试...
运行测试...
[==========] Running tests.
[----------] Global test environment set-up.
[----------] 2 tests from CalculatorTest
[ RUN      ] CalculatorTest.Add
[       OK ] CalculatorTest.Add
[ RUN      ] CalculatorTest.Subtract
[       OK ] CalculatorTest.Subtract
[----------] 2 tests from CalculatorTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 test(s) ran.
[  PASSED  ] 2 test(s).

✅ calculator 模块测试通过！
```

这种方法的优势：
- ✅ **快速**：只编译和测试指定模块
- ✅ **独立**：不影响其他模块
- ✅ **清晰**：输出专注于测试的模块
- ✅ **自动化**：自动清理临时文件

### 批量测试配置

我们的C语言版本保持了批量测试功能：

```bash
# 运行批量测试
make run-batch
```

注意：批量测试在C语言版本中运行所有已编译的测试，配置文件用于记录测试计划。

## 🛠️ 开发指南

### 添加新功能

1. **创建测试文件**: `tests/test_yourfeature.c`
2. **编写失败测试**: 定义期望的接口和行为
3. **创建头文件**: `include/yourfeature.h`
4. **实现功能**: `src/yourfeature.c`
5. **更新测试运行器**: 在 `tests/test_runner.c` 中添加新测试
6. **运行测试**: `make test`
7. **重构优化**: 改进代码质量

### 测试编写规范

#### 测试命名

```c
TEST(ModuleNameTest, FunctionName_Condition_ExpectedBehavior) {
    // 测试实现
}
```

#### 测试结构 (AAA模式)

```c
TEST(CalculatorTest, Add_TwoPositiveNumbers_ReturnsSum) {
    // Arrange (准备)
    int a = 2, b = 3;
    
    // Act (执行)
    int result = calculator_add(a, b);
    
    // Assert (断言)
    EXPECT_EQ(5, result);
}
```

#### 字符串测试

```c
TEST(HelloTest, SayHello_DefaultGreeting_ReturnsCorrectString) {
    // Arrange
    char buffer[100];
    
    // Act
    hello_say_hello(buffer, sizeof(buffer));
    
    // Assert
    EXPECT_STREQ("Hello, World!", buffer);
}
```

#### 添加新测试到运行器

在 `tests/test_runner.c` 中添加：

```c
// 声明新测试函数
extern void run_YourModuleTest_YourFunction(void);

// 在main函数中添加
int main(void) {
    // ... 现有代码 ...
    
    // 运行你的新测试
    printf("[----------] 1 test from YourModuleTest\n");
    RUN_TEST(YourModuleTest, YourFunction);
    printf("[----------] 1 test from YourModuleTest (0 ms total)\n\n");
    
    // ... 现有代码 ...
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

```c
// 按功能分组 - 将相关测试放在同一个测试文件中
// tests/test_game_calculation.c
TEST(GameCalculationTest, HealthCalculation) { ... }
TEST(GameCalculationTest, ExperienceCalculation) { ... }

// 按场景分组 - 在同一个TEST套件中测试不同情况
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
**解决**: 确保 `tests/test_runner.c` 中包含main函数，并且正确链接了所有测试文件。

### Q3: 找不到头文件

**问题**: 包含路径错误
**解决**: 确保头文件在 `include/` 目录下，使用相对路径包含

### Q4: 链接错误

**问题**: 源文件未编译或链接
**解决**: 确保源文件在 `src/` 目录下，Makefile会自动发现

### Q5: 新测试没有运行

**问题**: 添加了新测试但没有执行
**解决**: 在 `tests/test_runner.c` 中添加新测试的声明和调用

## 📚 学习资源

### C语言TDD资源

- [C语言单元测试最佳实践](https://github.com/ThrowTheSwitch/Unity)
- [TDD by Example (Kent Beck)](https://www.amazon.com/Test-Driven-Development-Kent-Beck/dp/0321146530)

### TDD最佳实践

- **Red-Green-Refactor**: 严格遵循TDD循环
- **小步快跑**: 每次只添加最小可测试功能
- **测试先行**: 永远先写测试再写实现
- **重构习惯**: 定期重构提高代码质量

### 示例代码

查看 `tests/` 目录下的测试文件，了解不同测试模式：

- `test_calculator.c`: 基础单元测试
- `test_mathutils.c`: 算法测试
- `test_hello.c`: 字符串处理测试
- `test_runner.c`: 测试运行器示例

### C语言特有注意事项

- **内存管理**: 手动管理内存分配和释放
- **字符串处理**: 使用字符数组和标准字符串函数
- **函数命名**: 使用模块前缀避免命名冲突
- **头文件保护**: 使用 `#ifdef __cplusplus` 支持C++兼容

## 🤝 贡献指南

1. **Fork仓库**: 创建自己的分支
2. **遵循TDD**: 先写测试再写实现
3. **代码规范**: 遵循C语言编码标准
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