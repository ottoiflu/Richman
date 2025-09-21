# Rich 大富翁项目 - 命令注册系统开发指南

## 📖 目录
- [概述](#概述)
- [开发流程对比](#开发流程对比)
- [添加新功能的完整流程](#添加新功能的完整流程)
- [代码模板和示例](#代码模板和示例)
- [文件修改清单](#文件修改清单)
- [测试指南](#测试指南)
- [常见问题解答](#常见问题解答)
- [最佳实践](#最佳实践)

## 🎯 概述

命令注册系统是Rich项目的核心架构改进，它解决了以下问题：
- ✅ **简化开发流程** - 新功能只需在一个地方注册命令
- ✅ **避免命令冲突** - 自动检测重复命令
- ✅ **自动化测试** - 测试脚本自动发现新命令
- ✅ **模块化管理** - 每个模块独立管理自己的命令
- ✅ **动态帮助** - 帮助信息自动更新

## 🔄 开发流程对比

### ❌ 旧流程（繁琐）
```
1. 编写功能代码
2. 修改 command_processor.c 添加命令到硬编码表
3. 修改 command_processor.c 添加命令处理逻辑
4. 修改 run_all_tests.sh 添加命令识别
5. 编写测试用例
6. 可能需要修改帮助信息
```

### ✅ 新流程（简化）
```
1. 编写功能代码
2. 在模块中注册命令（一行代码）
3. 编写测试用例（测试脚本自动识别命令）
```

## 🚀 添加新功能的完整流程

### 示例：添加地图管理功能

#### Step 1: 创建测试用例（TDD原则）🔴

```bash
# 创建测试目录
mkdir integration_tests/test_cases/case9_create_map

# 创建命令文件
echo "create_map 70" > integration_tests/test_cases/case9_create_map/cmdlist.txt

# 创建期望输出
echo "地图创建成功，大小：70" > integration_tests/test_cases/case9_create_map/expected_result.txt

# 创建描述文件
echo "创建地图功能测试 - 开发者：您的姓名" > integration_tests/test_cases/case9_create_map/description.txt

# 运行测试确认失败
make test
```

#### Step 2: 定义数据结构 🟢

在 `include/game_types.h` 中添加：

```c
// =============================================================================
// Map模块数据结构 - 开发者：您的姓名
// =============================================================================

typedef struct {
    int size;                    // 地图大小
    int owner_id[MAX_LOCATIONS]; // 每个位置的拥有者
    int level[MAX_LOCATIONS];    // 每个位置的建筑等级
    int property_type[MAX_LOCATIONS]; // 地产类型
} GameMap;

// 在GameState中添加
typedef struct {
    Player players[MAX_PLAYERS];
    int player_count;
    int current_player_index;
    int initial_money;
    GameMap map;                 // 新增：地图数据 - 开发者：您的姓名
} GameState;
```

#### Step 3: 实现功能函数 🟢

在 `src/game_state.c` 中添加：

```c
// =============================================================================
// Map模块功能实现 - 开发者：您的姓名
// =============================================================================

void map_init(GameMap* map, int size) {
    if (!map || size <= 0 || size > MAX_LOCATIONS) return;
    
    map->size = size;
    for (int i = 0; i < size; i++) {
        map->owner_id[i] = -1;  // 无主
        map->level[i] = 0;      // 空地
        map->property_type[i] = 0; // 普通地产
    }
}

void map_create(GameState* state, int size) {
    if (!state) return;
    
    map_init(&state->map, size);
    printf("地图创建成功，大小：%d\n", size);
}

// =============================================================================
// Map模块命令处理函数 - 开发者：您的姓名
// =============================================================================

CommandResult cmd_create_map(const char* args) {
    if (!args || strlen(args) == 0) {
        show_command_error("create_map", "需要指定地图大小参数");
        return CMD_ERROR;
    }
    
    int size = atoi(args);
    if (size <= 0 || size > MAX_LOCATIONS) {
        printf("地图大小无效，范围：1-%d\n", MAX_LOCATIONS);
        return CMD_ERROR;
    }
    
    GameState* state = get_game_state();
    map_create(state, size);
    return CMD_SUCCESS;
}

CommandResult cmd_show_map(const char* args) {
    GameState* state = get_game_state();
    printf("=== 地图信息 ===\n");
    printf("大小：%d\n", state->map.size);
    // 显示地图详细信息...
    return CMD_SUCCESS;
}

// =============================================================================
// Map模块初始化和注册 - 开发者：您的姓名
// =============================================================================

void map_module_init(void) {
    // 注册Map模块的所有命令
    register_command("create_map", "创建指定大小的地图", cmd_create_map, "Map-您的姓名");
    register_command("show_map", "显示地图信息", cmd_show_map, "Map-您的姓名");
    register_command("reset_map", "重置地图", cmd_reset_map, "Map-您的姓名");
}
```

#### Step 4: 声明接口 🟢

在 `include/game_state.h` 中添加：

```c
// =============================================================================
// Map模块接口 - 开发者：您的姓名
// =============================================================================

// 地图管理函数
void map_init(GameMap* map, int size);
void map_create(GameState* state, int size);

// 命令处理函数
CommandResult cmd_create_map(const char* args);
CommandResult cmd_show_map(const char* args);
CommandResult cmd_reset_map(const char* args);

// 模块初始化
void map_module_init(void);
```

#### Step 5: 注册模块 🟢

在 `src/main.c` 中添加：

```c
int main(int argc, char* argv[]) {
    // 初始化命令注册系统
    command_registry_init();
    
    // 初始化游戏状态
    game_init(get_game_state());
    
    // 初始化各模块并注册命令
    player_module_init();  // 张弛的Player模块
    map_module_init();     // 您的Map模块 - 开发者：您的姓名
    
    // 处理命令行参数
    CommandResult result = process_cli_command(argc, argv);
    // ...
}
```

#### Step 6: 运行测试验证 ✅

```bash
make test
# 应该看到新的测试用例通过
```

#### Step 7: 验证功能 🎮

```bash
# 测试新命令
echo -e "create_map 50\nshow_map" | ./rich

# 查看帮助信息
./rich help

# 查看所有模块
echo "modules" | ./rich
```

## 📝 代码模板和示例

### 命令处理函数模板

```c
// 命令处理函数模板
CommandResult cmd_your_command(const char* args) {
    // 1. 参数验证
    if (!args || strlen(args) == 0) {
        show_command_error("your_command", "需要参数");
        return CMD_ERROR;
    }
    
    // 2. 解析参数
    int param = atoi(args);
    if (param < 0) {
        printf("参数无效\n");
        return CMD_ERROR;
    }
    
    // 3. 获取游戏状态
    GameState* state = get_game_state();
    
    // 4. 执行功能
    your_function(state, param);
    
    // 5. 输出结果
    printf("操作成功\n");
    return CMD_SUCCESS;
}
```

### 模块初始化模板

```c
void your_module_init(void) {
    // 注册模块的所有命令
    register_command("cmd1", "命令1描述", cmd_handler1, "YourModule-您的姓名");
    register_command("cmd2", "命令2描述", cmd_handler2, "YourModule-您的姓名");
    register_command("cmd3", "命令3描述", cmd_handler3, "YourModule-您的姓名");
}
```

### 测试用例模板

```bash
# 创建测试目录
mkdir integration_tests/test_cases/case_your_feature

# cmdlist.txt - 要执行的命令
echo "your_command param1 param2" > integration_tests/test_cases/case_your_feature/cmdlist.txt

# expected_result.txt - 期望输出
echo "期望的输出结果" > integration_tests/test_cases/case_your_feature/expected_result.txt

# description.txt - 测试描述
echo "您的功能测试 - 开发者：您的姓名" > integration_tests/test_cases/case_your_feature/description.txt
```

## 📋 文件修改清单

### ✅ 必须修改的文件

| 文件 | 修改内容 | 示例 |
|------|----------|------|
| `include/game_types.h` | 添加数据结构定义 | `typedef struct { ... } YourStruct;` |
| `src/game_state.c` | 实现功能函数和命令处理 | `CommandResult cmd_xxx(const char* args)` |
| `include/game_state.h` | 声明函数接口 | `void your_function(void);` |
| `src/main.c` | 注册模块 | `your_module_init();` |
| `integration_tests/test_cases/` | 创建测试用例 | 新目录和测试文件 |

### ❌ 不需要修改的文件

| 文件 | 原因 |
|------|------|
| `src/command_processor.c` | 使用注册系统，无需硬编码 |
| `integration_tests/run_all_tests.sh` | 自动发现新命令 |
| `src/command_registry.c` | 核心系统，无需修改 |
| `include/command_registry.h` | 接口稳定，无需修改 |

## 🧪 测试指南

### 1. TDD开发流程

```bash
# Red: 先写失败的测试
mkdir integration_tests/test_cases/case_new_feature
echo "new_command" > integration_tests/test_cases/case_new_feature/cmdlist.txt
echo "期望输出" > integration_tests/test_cases/case_new_feature/expected_result.txt
make test  # 确认测试失败

# Green: 实现最少代码让测试通过
# 按照上面的流程实现功能
make test  # 确认测试通过

# Refactor: 重构代码
# 优化实现，保持测试通过
make test  # 确认重构后仍然通过
```

### 2. 测试命令

```bash
# 运行所有测试
make test

# 查看测试日志
cat integration_tests/test_results.log

# 查看特定测试输出
cat integration_tests/test_cases/case_your_feature/output.txt

# 手动测试命令
echo "your_command param" | ./rich

# 查看所有注册的命令
./rich list-game-commands

# 查看帮助信息
./rich help
```

### 3. 调试测试

```bash
# 比较期望输出和实际输出
diff integration_tests/test_cases/case_name/expected_result.txt \
     integration_tests/test_cases/case_name/output.txt

# 手动运行命令查看输出
./rich your_command > debug_output.txt
cat debug_output.txt
```

## ❓ 常见问题解答

### Q1: 如何添加带多个参数的命令？

```c
CommandResult cmd_complex_command(const char* args) {
    char param1[64], param2[64];
    int param3;
    
    // 解析多个参数
    int parsed = sscanf(args, "%63s %63s %d", param1, param2, &param3);
    if (parsed < 3) {
        show_command_error("complex_command", "需要3个参数：param1 param2 param3");
        return CMD_ERROR;
    }
    
    // 处理命令...
    return CMD_SUCCESS;
}
```

### Q2: 如何处理可选参数？

```c
CommandResult cmd_optional_params(const char* args) {
    char required[64];
    char optional[64] = "default_value";  // 默认值
    
    int parsed = sscanf(args, "%63s %63s", required, optional);
    if (parsed < 1) {
        show_command_error("command", "至少需要1个参数");
        return CMD_ERROR;
    }
    
    // 使用required和optional参数...
    return CMD_SUCCESS;
}
```

### Q3: 如何添加命令别名？

```c
void your_module_init(void) {
    // 注册主命令
    register_command("create_map", "创建地图", cmd_create_map, "Map-您的姓名");
    
    // 注册别名（指向同一个处理函数）
    register_command("cm", "创建地图（别名）", cmd_create_map, "Map-您的姓名");
    register_command("new_map", "创建地图（别名）", cmd_create_map, "Map-您的姓名");
}
```

### Q4: 如何查看某个模块的所有命令？

```bash
# 在交互模式中
echo "modules" | ./rich                    # 查看所有模块
echo "help" | ./rich                       # 查看所有命令

# 通过代码查看
void show_commands_by_module(const char* module_name);  // 已实现的函数
```

### Q5: 命令注册失败怎么办？

命令注册失败的常见原因：
- ✅ **命令名重复** - 检查是否已有相同命令
- ✅ **参数无效** - 确保所有参数都不为NULL
- ✅ **注册表满了** - 检查是否超过MAX_REGISTERED_COMMANDS限制

```c
// 检查注册结果
if (!register_command("cmd", "desc", handler, "module")) {
    printf("命令注册失败\n");
}
```

### Q6: 如何在多人协作中避免命令冲突？

**建议的命名规范**：
```c
// 使用模块前缀
register_command("player_move", "玩家移动", cmd_player_move, "Player-张三");
register_command("map_create", "创建地图", cmd_map_create, "Map-李四");
register_command("trade_buy", "购买交易", cmd_trade_buy, "Trade-王五");

// 或使用开发者前缀
register_command("zhang_move", "张三的移动功能", cmd_move, "Player-张三");
register_command("li_create", "李四的创建功能", cmd_create, "Map-李四");
```

## 💡 最佳实践

### 1. 命名规范

```c
// ✅ 好的命名
register_command("set_money", "设置初始资金", cmd_set_money, "Player-张弛");
register_command("show_player", "显示玩家信息", cmd_show_player, "Player-张弛");

// ❌ 避免的命名
register_command("sm", "设置钱", cmd_sm, "P-张弛");  // 太简短，不清楚
register_command("SetMoney", "设置资金", cmd_SetMoney, "Player-张弛");  // 大小写不一致
```

### 2. 模块组织

```c
// ✅ 按功能模块组织
void player_module_init(void) {
    register_command("set_money", "设置初始资金", cmd_set_money, "Player-张弛");
    register_command("show_characters", "显示角色列表", cmd_show_characters, "Player-张弛");
    register_command("choose_player", "选择玩家", cmd_choose_player, "Player-张弛");
}

void map_module_init(void) {
    register_command("create_map", "创建地图", cmd_create_map, "Map-您的姓名");
    register_command("show_map", "显示地图", cmd_show_map, "Map-您的姓名");
}
```

### 3. 错误处理

```c
// ✅ 统一的错误处理
CommandResult cmd_your_command(const char* args) {
    if (!args || strlen(args) == 0) {
        show_command_error("your_command", "需要参数");
        return CMD_ERROR;
    }
    
    // 业务逻辑错误也要有清晰的提示
    if (some_condition_failed) {
        printf("操作失败：具体原因\n");
        return CMD_ERROR;
    }
    
    return CMD_SUCCESS;
}
```

### 4. 测试覆盖

```bash
# ✅ 为每个命令创建测试
integration_tests/test_cases/
├── case_player_set_money/      # 测试设置资金
├── case_player_choose/         # 测试选择角色
├── case_map_create/           # 测试创建地图
├── case_map_show/             # 测试显示地图
└── case_error_handling/       # 测试错误处理
```

### 5. 文档更新

每次添加新功能后，记得更新：
- ✅ 命令的描述要清晰明确
- ✅ 在模块名中标注开发者
- ✅ 测试用例要有描述文件
- ✅ 复杂功能要添加使用示例

## 🎯 开发检查清单

添加新功能前，请检查：

- [ ] **设计阶段**
  - [ ] 功能需求明确
  - [ ] 数据结构设计合理
  - [ ] 命令名称不冲突
  - [ ] 遵循TDD原则

- [ ] **实现阶段**
  - [ ] 在`game_types.h`中定义数据结构
  - [ ] 在`game_state.c`中实现功能和命令处理
  - [ ] 在`game_state.h`中声明接口
  - [ ] 在`main.c`中注册模块
  - [ ] 创建测试用例

- [ ] **测试阶段**
  - [ ] 所有测试通过 (`make test`)
  - [ ] 手动验证功能正常
  - [ ] 检查帮助信息更新
  - [ ] 验证错误处理

- [ ] **文档阶段**
  - [ ] 代码注释完整
  - [ ] 开发者标记清晰
  - [ ] 测试用例有描述



---

**提示**：如果在开发过程中遇到问题，可以参考张弛的Player模块实现作为参考示例。