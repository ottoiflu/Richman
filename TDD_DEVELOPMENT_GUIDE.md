# Rich 大富翁项目 - TDD测试驱动开发指南

## 📖 目录
- [项目概述](#项目概述)
- [TDD开发流程](#TDD开发流程)
- [项目结构说明](#项目结构说明)
- [开发环境设置](#开发环境设置)
- [添加新功能的TDD流程](#添加新功能的TDD流程)
- [测试用例管理](#测试用例管理)
- [最佳实践](#最佳实践)
- [常见问题解答](#常见问题解答)

## 🎯 项目概述

这是一个基于TDD（测试驱动开发）的Rich大富翁游戏项目框架。项目已经搭建好了完整的测试基础设施，您可以专注于实现游戏逻辑，而不用担心测试框架的搭建。

### 核心特性
- ✅ **完整的TDD框架** - 自动化测试运行器
- ✅ **模块化架构** - 清晰的代码组织结构
- ✅ **持续集成支持** - 一键编译、测试、安装
- ✅ **Hello World基线** - 确保基础功能正常

## 🔄 TDD开发流程

### Red-Green-Refactor 循环

```
🔴 RED    → 编写失败的测试
🟢 GREEN  → 编写最少代码使测试通过  
🔵 REFACTOR → 重构代码，保持测试通过
```

### 详细步骤

#### 1. 🔴 Red - 编写失败的测试
```bash
# 创建新的测试用例目录
mkdir integration_tests/test_cases/case_new_feature

# 创建测试文件
echo "new_command" > integration_tests/test_cases/case_new_feature/cmdlist.txt
echo "期望的输出结果" > integration_tests/test_cases/case_new_feature/expected_result.txt
echo "新功能测试" > integration_tests/test_cases/case_new_feature/description.txt

# 运行测试，确认失败
make test
```

#### 2. 🟢 Green - 实现最少代码
```c
// 在相应的模块中添加最少代码使测试通过
// 例如在 src/command_processor.c 中添加命令处理
```

#### 3. 🔵 Refactor - 重构优化
```bash
# 重构代码，保持测试通过
make test  # 确保重构后测试仍然通过
```

## 📁 项目结构说明

```
Rich/Richman/
├── 📂 src/                          # 源代码目录
│   ├── main.c                       # 程序入口（简化框架）
│   ├── hello.c                      # Hello World功能（TDD基线）
│   ├── game_state.c                 # 游戏状态管理（待实现）
│   ├── command_processor.c          # 命令处理（基础框架）
│   └── game_io.c                    # 输入输出处理
├── 📂 include/                      # 头文件目录
│   ├── common.h                     # 统一头文件入口
│   ├── game_types.h                 # 数据结构定义（待实现）
│   ├── game_state.h                 # 游戏状态管理接口
│   ├── command_processor.h          # 命令处理接口
│   ├── game_io.h                    # 输入输出接口
│   └── hello.h                      # Hello World接口
├── 📂 integration_tests/            # 集成测试目录
│   ├── run_all_tests.sh            # 自动化测试运行器
│   ├── test_results.log            # 测试结果日志
│   └── 📂 test_cases/              # 测试用例目录
│       ├── case1_helloworld/       # Hello World测试（基线）
│       ├── case2_help/             # 帮助功能测试
│       └── case4_invalid_cmd/      # 错误处理测试
├── 📂 obj/                         # 编译对象文件（自动生成）
├── 📂 bin/                         # 可执行文件（自动生成）
├── Makefile                        # 构建配置
├── README.md                       # 项目说明
└── TDD_DEVELOPMENT_GUIDE.md        # 本开发指南
```

## 🔧 开发环境设置

### 1. 基础环境
```bash
# 确保安装了GCC编译器
gcc --version

# 确保有bash环境（用于测试脚本）
bash --version
```

### 2. 项目构建
```bash
# 清理并构建项目
make clean && make build

# 运行基础测试确保环境正常
make test

# 安装到系统路径（可选）
make install
```

### 3. 验证环境
```bash
# 测试Hello World功能
./rich testhelloworld

# 查看帮助信息
./rich help

# 检查测试框架
make test
```

## 🚀 添加新功能的TDD流程

### 示例：添加玩家移动功能

#### Step 1: 创建测试用例 🔴
```bash
# 创建测试目录
mkdir integration_tests/test_cases/case_player_move

# 创建命令文件
cat > integration_tests/test_cases/case_player_move/cmdlist.txt << 'EOF'
move 5
EOF

# 创建期望输出
cat > integration_tests/test_cases/case_player_move/expected_result.txt << 'EOF'
玩家移动了5步
EOF

# 创建描述文件
echo "玩家移动功能测试" > integration_tests/test_cases/case_player_move/description.txt

# 运行测试，确认失败
make test
```

#### Step 2: 定义数据结构 🟢
```c
// 在 include/game_types.h 中定义
typedef struct {
    char name;
    int position;
    int money;
} Player;

typedef struct {
    Player players[MAX_PLAYERS];
    int current_player;
    int player_count;
} GameState;
```

#### Step 3: 实现游戏状态管理 🟢
```c
// 在 include/game_state.h 中声明
GameState* get_game_state(void);
void game_init(GameState* state);
void player_move(GameState* state, int steps);

// 在 src/game_state.c 中实现
static GameState g_game_state;

GameState* get_game_state(void) {
    return &g_game_state;
}

void game_init(GameState* state) {
    state->player_count = 1;
    state->current_player = 0;
    state->players[0].name = 'A';
    state->players[0].position = 0;
    state->players[0].money = 10000;
}

void player_move(GameState* state, int steps) {
    state->players[state->current_player].position += steps;
    printf("玩家移动了%d步\n", steps);
}
```

#### Step 4: 添加命令处理 🟢
```c
// 在 src/command_processor.c 中添加
static char game_commands[][16] = {"move", ""};

// 在 process_game_command 函数中添加
if (strcmp(g_cmd_struct.instruction, "Move") == 0) {
    GameState* game = get_game_state();
    player_move(game, g_cmd_struct.parameter);
    return CMD_SUCCESS;
}
```

#### Step 5: 更新main.c初始化 🟢
```c
// 在 src/main.c 中添加
int main(int argc, char* argv[]) {
    // 初始化游戏状态
    game_init(get_game_state());
    
    // ... 其余代码保持不变
}
```

#### Step 6: 运行测试确认通过 ✅
```bash
make test
# 应该看到新的测试用例通过
```

#### Step 7: 重构优化 🔵
```c
// 可以重构代码，提取公共函数，优化结构等
// 重构后再次运行测试确保功能正常
make test
```

## 📋 测试用例管理

### 测试用例目录结构
```
integration_tests/test_cases/case_功能名称/
├── cmdlist.txt          # 测试命令列表
├── expected_result.txt  # 期望的输出结果
├── description.txt      # 测试用例描述
└── output.txt          # 实际输出（自动生成）
```

### 测试用例类型

#### 1. 单命令测试
```bash
# cmdlist.txt
help

# expected_result.txt
Rich - 大富翁程序
用法:
  rich testhelloworld    - 运行hello world测试
  rich help             - 显示帮助信息
  rich < cmdfile        - 从文件读取命令执行
```

#### 2. 多命令序列测试
```bash
# cmdlist.txt
init_game
add_player A
add_player B
start_game

# expected_result.txt
游戏初始化成功
玩家A加入游戏
玩家B加入游戏
游戏开始
```

#### 3. 交互式命令测试
```bash
# cmdlist.txt（通过stdin管道输入）
preset user AB
preset fund A 5000
preset fund B 8000
dump

# expected_result.txt
游戏状态已输出到 dump.txt
```

### 运行特定测试
```bash
# 运行所有测试
make test

# 查看测试结果
cat integration_tests/test_results.log

# 查看特定测试的输出
cat integration_tests/test_cases/case_player_move/output.txt
```

## 💡 最佳实践

### 1. 测试先行原则
- ⭐ **先写测试，后写代码**
- ⭐ **每个功能都要有对应的测试用例**
- ⭐ **保持测试简单且专注**

### 2. 小步快跑
- ⭐ **每次只添加一个小功能**
- ⭐ **频繁运行测试**
- ⭐ **及时提交代码**

### 3. 重构时机
- ⭐ **测试通过后再重构**
- ⭐ **重构后立即运行测试**
- ⭐ **保持代码整洁**

### 4. 测试命名规范
```
case[序号]_[功能描述]/
例如：
- case1_helloworld/
- case2_help/
- case3_player_move/
- case4_buy_property/
```

### 5. 代码组织原则
- ⭐ **一个文件一个职责**
- ⭐ **通过common.h统一包含**
- ⭐ **保持接口简单清晰**

## ❓ 常见问题解答

### Q1: 如何调试失败的测试？
```bash
# 1. 查看测试日志
cat integration_tests/test_results.log

# 2. 查看实际输出
cat integration_tests/test_cases/case_name/output.txt

# 3. 手动运行命令
./rich your_command

# 4. 使用gdb调试
gdb ./rich
```

### Q2: 如何处理复杂的输入输出？
```bash
# 对于复杂的交互式命令，使用管道输入
# 在 cmdlist.txt 中放置所有命令
# 测试脚本会自动通过 ./rich < cmdlist.txt 执行
```

### Q3: 如何添加新的数据结构？
```c
// 1. 在 include/game_types.h 中定义结构体
typedef struct {
    // 您的字段
} YourStruct;

// 2. 在对应的模块中实现功能函数
// 3. 在 include/game_state.h 中声明接口
// 4. 先写测试，后实现功能
```

### Q4: 如何处理编译错误？
```bash
# 1. 查看编译输出
make build

# 2. 检查头文件包含
# 确保在 common.h 中包含了新的头文件

# 3. 检查函数声明和定义是否匹配

# 4. 确保 Makefile 中包含了新的源文件
```

### Q5: 如何扩展命令系统？
```c
// 1. 在 command_processor.c 中的 game_commands 数组中添加新命令
static char game_commands[][16] = {"move", "buy", "sell", "your_command", ""};

// 2. 在 process_game_command 函数中添加处理逻辑
if (strcmp(g_cmd_struct.instruction, "Your_command") == 0) {
    // 处理您的命令
    return CMD_SUCCESS;
}

// 3. 先写测试用例，确保命令能被正确识别和执行
```

## 🎯 开发建议

1. **从简单功能开始** - 先实现基础的玩家移动、资金管理等
2. **保持测试覆盖** - 每个功能都要有对应的测试
3. **频繁提交代码** - 小步快跑，及时保存进度
4. **重构时保持测试** - 重构时确保所有测试都能通过
5. **文档同步更新** - 添加新功能时更新相关文档

## 🚀 开始您的TDD之旅

现在您已经有了一个完整的TDD开发框架！开始编写您的第一个测试用例，然后实现对应的功能吧！

```bash
# 开始开发
make test  # 确保基础测试通过
# 然后按照上面的流程添加新功能
```