# Rich 大富翁项目 - TDD开发框架

## 🎯 项目简介

这是一个基于**测试驱动开发（TDD）**的Rich大富翁游戏项目框架。项目提供了完整的测试基础设施和模块化架构，让您可以专注于游戏逻辑的实现，而无需从零搭建测试框架。

## ✨ 框架特性

- ✅ **完整的TDD框架** - 自动化测试运行器，支持多种测试场景
- ✅ **模块化架构** - 清晰的代码组织结构，支持多人协作开发
- ✅ **命令注册系统** - 自动化命令管理，简化新功能开发流程
- ✅ **一键构建系统** - Makefile支持编译、测试、安装、清理
- ✅ **Hello World基线** - 确保基础功能正常，作为TDD起点
- ✅ **自动化测试报告** - 详细的测试结果和错误信息
- ✅ **命令行友好** - 支持CLI命令和交互式模式

## 🚀 快速开始

### 1. 环境准备
```bash
# 确保安装了GCC编译器
gcc --version

# 克隆或下载项目到本地
cd Rich/Richman
```

### 2. 构建和测试
```bash
# 清理并构建项目
make clean && make build

# 运行所有测试（确保框架正常）
make test

# 测试Hello World功能
./rich testhelloworld
```

### 3. 开始开发
```bash
# 查看详细的TDD开发指南
cat TDD_DEVELOPMENT_GUIDE.md

# 查看命令注册系统开发指南
cat COMMAND_REGISTRY_DEVELOPMENT_GUIDE.md

# 该指南包含完整的TDD开发流程和命令注册系统使用方法
```

## 📁 项目结构

```
Rich/Richman/
├── 📂 src/                          # 源代码目录
│   ├── main.c                       # 程序入口（简化框架）
│   ├── hello.c                      # Hello World功能（TDD基线）
│   ├── game_state.c                 # 🔧 游戏状态管理（待您实现）
│   ├── command_processor.c          # 命令处理（基础框架已搭建）
│   └── game_io.c                    # 输入输出处理
├── 📂 include/                      # 头文件目录
│   ├── common.h                     # 统一头文件入口
│   ├── game_types.h                 # ✅ 数据结构定义（包含张弛的Player）
│   ├── game_state.h                 # ✅ 游戏状态管理接口（包含Player功能）
│   ├── command_registry.h           # 🎯 命令注册系统接口
│   ├── command_processor.h          # 命令处理接口
│   ├── game_io.h                    # 输入输出接口
│   └── hello.h                      # Hello World接口
├── 📂 integration_tests/            # 集成测试目录
│   ├── run_all_tests.sh            # 🎯 自动化测试运行器
│   ├── test_results.log            # 测试结果日志
│   └── 📂 test_cases/              # 测试用例目录
│       ├── case1_helloworld/       # ✅ Hello World测试（基线）
│       ├── case2_help/             # ✅ 帮助功能测试
│       └── case4_invalid_cmd/      # ✅ 错误处理测试
├── Makefile                        # 🔧 构建配置
├── README.md                       # 本文档
├── TDD_DEVELOPMENT_GUIDE.md        # 📖 TDD开发指南
└── COMMAND_REGISTRY_DEVELOPMENT_GUIDE.md # 📖 命令注册系统开发指南
```

**图例说明：**
- ✅ 已完成的基础功能
- 🔧 待您实现的核心功能
- 🎯 重要的工具和脚本
- 📖 文档和指南

## 🛠️ Makefile 命令

```bash
# 构建项目
make build          # 编译源代码
make clean          # 清理编译产物
make all            # 清理后重新构建

# 测试相关
make test           # 运行所有集成测试
                   # 输出测试报告和结果日志

# 安装和卸载
make install        # 安装rich到系统路径
make uninstall      # 从系统路径卸载

# 帮助信息
make help          # 显示所有可用命令
```

## 🧪 测试框架使用

### 运行测试
```bash
make test
```

### 测试输出示例
```
开始运行 Rich 大富翁程序集成测试...
========================================
发现 3 个测试用例:
  - case1_helloworld
  - case2_help
  - case4_invalid_cmd
========================================
测试用例1: Hello World基本功能测试
运行测试: case1_helloworld ... PASSED
测试用例2: 帮助信息功能测试
运行测试: case2_help ... PASSED
测试用例4: 无效命令错误处理测试
运行测试: case4_invalid_cmd ... PASSED
========================================
测试完成!
总测试数: 3
通过: 3
失败: 0

所有测试通过!
```

### 测试用例结构
每个测试用例包含：
- `cmdlist.txt` - 要执行的命令
- `expected_result.txt` - 期望的输出结果
- `description.txt` - 测试用例描述
- `output.txt` - 实际输出（自动生成）

## 🎯 TDD开发流程

### 1. Red-Green-Refactor 循环
```
🔴 RED    → 编写失败的测试用例
🟢 GREEN  → 编写最少代码使测试通过  
🔵 REFACTOR → 重构代码，保持测试通过
```

### 2. 添加新功能的步骤
1. **创建测试用例**：在 `integration_tests/test_cases/` 下创建新目录
2. **定义期望行为**：编写 `cmdlist.txt` 和 `expected_result.txt`
3. **运行测试确认失败**：`make test`
4. **实现最少代码**：在相应模块中添加功能
5. **运行测试确认通过**：`make test`
6. **重构优化**：改进代码质量，保持测试通过

## 📖 详细开发指南

请查看 [`TDD_DEVELOPMENT_GUIDE.md`](TDD_DEVELOPMENT_GUIDE.md) 获取：

- 🔄 完整的TDD开发流程
- 🎯 添加新功能的详细示例
- 📋 测试用例管理最佳实践
- 💡 代码组织和架构建议
- ❓ 常见问题解答

## 🔧 待实现的核心功能

框架已为您准备好以下模块，等待您的实现：

### 1. 游戏数据结构 (`include/game_types.h`)
```c
// TODO: 定义您的游戏数据结构
// 例如：Player, Map, Property, GameState 等
```

### 2. 游戏状态管理 (`src/game_state.c`)
```c
// TODO: 实现游戏状态的初始化、更新、查询等功能
// 例如：玩家管理、地图状态、回合控制等
```

### 3. 游戏命令扩展 (`src/command_processor.c`)
```c
// TODO: 添加您的游戏命令
// 例如：move, buy, sell, query, roll等
```

## 🎮 示例功能实现

以下是一个简单的玩家移动功能的TDD实现示例：

### 1. 创建测试用例
```bash
mkdir integration_tests/test_cases/case_player_move
echo "move 5" > integration_tests/test_cases/case_player_move/cmdlist.txt
echo "玩家移动了5步" > integration_tests/test_cases/case_player_move/expected_result.txt
```

### 2. 运行测试（应该失败）
```bash
make test  # 确认测试失败
```

### 3. 实现功能
```c
// 在相应模块中添加移动功能的实现
```

### 4. 验证测试通过
```bash
make test  # 确认测试通过
```

## 🤝 多人协作开发

框架的模块化设计支持多人协作：

- **开发者A**：实现玩家系统 (`game_state.c`)
- **开发者B**：实现地图系统 (`map.c` - 您可以添加)
- **开发者C**：实现交易系统 (`trade.c` - 您可以添加)

每个开发者都可以：
1. 为自己的模块编写测试用例
2. 独立实现功能
3. 通过 `make test` 验证整体功能

## 📝 版本信息

- **框架版本**: 1.0.0
- **TDD支持**: ✅ 完整支持
- **C标准**: C99
- **编译器**: GCC
- **测试框架**: 自定义Shell脚本

## 🎉 开始您的TDD之旅

现在您已经有了一个完整的TDD开发框架！

1. 📖 **阅读开发指南**：`TDD_DEVELOPMENT_GUIDE.md`
2. 🧪 **运行基础测试**：`make test`
3. 🔴 **编写第一个测试**：创建新的测试用例
4. 🟢 **实现对应功能**：让测试通过
5. 🔵 **重构优化代码**：保持测试通过

祝您开发愉快！🚀

---

**提示**：如果您在开发过程中遇到任何问题，请参考 `TDD_DEVELOPMENT_GUIDE.md` 中的常见问题解答部分。