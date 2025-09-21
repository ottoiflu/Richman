# Rich 大富翁程序 - TDD测试驱动开发指南

## 📖 什么是TDD？

TDD（Test-Driven Development）是一种软件开发方法，遵循"红-绿-重构"的循环：

1. **🔴 红色阶段**: 先写一个会失败的测试
2. **🟢 绿色阶段**: 写最少的代码让测试通过
3. **🔄 重构阶段**: 在保证测试通过的前提下改进代码

## 🔄 TDD的三个阶段详解

### 🔴 红色阶段 - Red
- 写一个描述所需功能的测试
- 运行测试，确保它失败（因为功能还未实现）
- 测试失败证明测试是有效的

### 🟢 绿色阶段 - Green  
- 写最少的代码让测试通过
- 不关心代码质量，只要能通过测试即可
- 快速实现功能的最简版本

### 🔄 重构阶段 - Refactor
- 在保证测试通过的前提下改进代码
- 消除重复代码
- 提高代码可读性和性能

## 🎯 Rich项目中的TDD实践流程

### 步骤1：编写集成测试用例（红色阶段）

假设我们要添加一个"掷骰子"功能，首先编写测试：

```bash
# 1. 在测试脚本中添加新的测试用例
# integration_tests/test_helloworld.sh

# 测试用例5: 掷骰子功能
echo "测试用例5: 掷骰子功能"
run_test "Dice_Command" "./rich dice" "integration_tests/expected_dice.txt"
```

```bash
# 2. 创建期望输出文件
echo "掷骰子结果: 4" > integration_tests/expected_dice.txt
```

```bash
# 3. 运行测试 - 应该失败
make test
# 预期结果: 测试失败，因为dice命令还不存在
```

### 步骤2：实现最小功能（绿色阶段）

```c
// 1. 在include/hello.h中添加函数声明
void hello_roll_dice(char* buffer, size_t buffer_size);
```

```c
// 2. 在src/hello.c中实现最简单的版本
void hello_roll_dice(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        // 最简实现：总是返回4（硬编码）
        snprintf(buffer, buffer_size, "掷骰子结果: 4");
    }
}
```

```c
// 3. 在src/main.c中添加命令处理
else if (strcmp(argv[1], "dice") == 0) {
    char buffer[100];
    hello_roll_dice(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    return 0;
}
```

```bash
# 4. 运行测试 - 应该通过
make test
# 预期结果: 所有测试通过
```

### 步骤3：重构改进（重构阶段）

```c
// 现在可以改进实现，添加真正的随机数
#include <time.h>
#include <stdlib.h>

void hello_roll_dice(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        static int initialized = 0;
        if (!initialized) {
            srand(time(NULL));
            initialized = 1;
        }
        int result = (rand() % 6) + 1;
        snprintf(buffer, buffer_size, "掷骰子结果: %d", result);
    }
}
```

但是这会导致测试失败！因为结果是随机的。这时我们需要重新考虑测试策略。

## 🧪 TDD中的测试策略

### 策略1：确定性测试
对于有确定输出的功能，直接比较输出：
```bash
# 适用于: hello, version, help等命令
run_test "Hello_Command" "./rich testhelloworld" "integration_tests/expected_hello.txt"
```

### 策略2：模式匹配测试
对于有变化输出的功能，测试输出格式：
```bash
# 修改测试函数，支持正则表达式匹配
run_pattern_test() {
    local test_name="$1"
    local command="$2"
    local pattern="$3"
    
    eval "$command" > /tmp/actual_output.txt 2>&1
    if grep -E "$pattern" /tmp/actual_output.txt > /dev/null; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAILED${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# 使用模式测试掷骰子功能
run_pattern_test "Dice_Command" "./rich dice" "掷骰子结果: [1-6]"
```

### 策略3：退出码测试
测试程序的行为而不是具体输出：
```bash
# 测试命令是否成功执行
./rich dice > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "PASSED - 命令成功执行"
else
    echo "FAILED - 命令执行失败"
fi
```

## 🔄 完整的TDD循环示例

### 功能需求：添加玩家状态查询功能

#### 第1轮：红-绿-重构

**🔴 红色阶段：**
```bash
# 1. 编写测试
echo "测试用例6: 玩家状态查询"
run_test "Status_Command" "./rich status" "integration_tests/expected_status.txt"

# 2. 创建期望输出
echo "玩家状态: 健康, 位置: 0, 金钱: 10000" > integration_tests/expected_status.txt

# 3. 运行测试 - 失败
make test  # ❌ 失败，因为status命令不存在
```

**🟢 绿色阶段：**
```c
// 1. 添加函数声明
void hello_get_status(char* buffer, size_t buffer_size);

// 2. 硬编码实现
void hello_get_status(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        snprintf(buffer, buffer_size, "玩家状态: 健康, 位置: 0, 金钱: 10000");
    }
}

// 3. 添加命令处理
else if (strcmp(argv[1], "status") == 0) {
    char buffer[100];
    hello_get_status(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    return 0;
}

// 4. 运行测试 - 通过
make test  # ✅ 通过
```

**🔄 重构阶段：**
```c
// 引入数据结构，改进代码组织
typedef struct {
    char health[20];
    int position;
    int money;
} PlayerStatus;

void hello_get_status(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        PlayerStatus status = {"健康", 0, 10000};
        snprintf(buffer, buffer_size, 
                "玩家状态: %s, 位置: %d, 金钱: %d", 
                status.health, status.position, status.money);
    }
}

// 运行测试确保重构没有破坏功能
make test  # ✅ 仍然通过
```

#### 第2轮：增加新需求

**🔴 红色阶段：**
```bash
# 需求：支持指定玩家名称查询状态
echo "测试用例7: 指定玩家状态查询"
run_test "Status_Player_Command" "./rich status Alice" "integration_tests/expected_status_alice.txt"

echo "玩家Alice状态: 健康, 位置: 5, 金钱: 8500" > integration_tests/expected_status_alice.txt

make test  # ❌ 失败，因为不支持参数
```

**🟢 绿色阶段：**
```c
// 修改main.c支持参数
else if (strcmp(argv[1], "status") == 0) {
    char buffer[100];
    if (argc > 2) {
        hello_get_player_status(buffer, sizeof(buffer), argv[2]);
    } else {
        hello_get_status(buffer, sizeof(buffer));
    }
    printf("%s\n", buffer);
    return 0;
}

// 添加新函数
void hello_get_player_status(char* buffer, size_t buffer_size, const char* player_name) {
    if (buffer && buffer_size > 0 && player_name) {
        if (strcmp(player_name, "Alice") == 0) {
            snprintf(buffer, buffer_size, "玩家Alice状态: 健康, 位置: 5, 金钱: 8500");
        } else {
            snprintf(buffer, buffer_size, "玩家%s状态: 健康, 位置: 0, 金钱: 10000", player_name);
        }
    }
}

make test  # ✅ 通过
```

**🔄 重构阶段：**
```c
// 进一步重构，引入玩家数据管理
typedef struct {
    char name[50];
    char health[20];
    int position;
    int money;
} Player;

Player* get_player_data(const char* name) {
    static Player players[] = {
        {"Alice", "健康", 5, 8500},
        {"Bob", "生病", 10, 7200},
        {"Charlie", "健康", 0, 10000}
    };
    
    for (int i = 0; i < 3; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return &players[i];
        }
    }
    return NULL;
}

make test  # ✅ 确保重构后仍然通过
```

## 🎯 TDD的核心原则

### 1. 测试先行
- **永远**先写测试，再写代码
- 测试描述你期望的行为
- 测试失败证明测试有效

### 2. 最小实现
- 写最少的代码让测试通过
- 不要过度设计
- 硬编码是可以接受的第一步

### 3. 持续重构
- 在绿色状态下改进代码
- 消除重复
- 提高可读性

### 4. 小步前进
- 每次只添加一个小功能
- 频繁运行测试
- 保持反馈循环短小

## 🛠️ Rich项目的TDD工作流

```bash
# 1. 添加新测试用例（红色）
vim integration_tests/test_helloworld.sh

# 2. 创建期望输出文件
echo "期望输出" > integration_tests/expected_newfeature.txt

# 3. 运行测试，确认失败
make test

# 4. 实现最小功能（绿色）
vim include/hello.h
vim src/hello.c
vim src/main.c

# 5. 运行测试，确认通过
make test

# 6. 重构改进（重构）
vim src/hello.c  # 改进实现

# 7. 再次运行测试，确保没有破坏
make test

# 8. 安装验证
make install
rich newcommand
```

## 📈 TDD的优势

- ✅ **防止缺陷**: 测试先行确保功能正确
- ✅ **设计改进**: 测试驱动更好的API设计
- ✅ **重构安全**: 测试保护确保重构不破坏功能
- ✅ **文档作用**: 测试即文档，描述系统行为
- ✅ **信心提升**: 全面的测试覆盖提供开发信心

## 🎓 TDD最佳实践

### DO - 应该做的
- ✅ 测试失败后立即停止，写代码让它通过
- ✅ 只写让测试通过的最小代码
- ✅ 频繁运行测试，保持快速反馈
- ✅ 测试名称清晰描述功能
- ✅ 一次只测试一个功能点

### DON'T - 不应该做的
- ❌ 不要在没有失败测试的情况下写产品代码
- ❌ 不要跳过重构阶段
- ❌ 不要写复杂的测试
- ❌ 不要测试实现细节，只测试行为
- ❌ 不要让测试变慢

遵循这个TDD指南，您可以构建高质量、可维护的Rich大富翁程序！