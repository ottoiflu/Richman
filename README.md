# Rich - 大富翁程序 (集成测试版)

## 📖 项目简介

Rich是一个使用**TDD（测试驱动开发）**方法构建的C语言大富翁程序。本项目展示了如何在C语言环境下实践真正的TDD开发流程，包括"红-绿-重构"循环、集成测试和自动化测试管理。

**软件工程2组** - 展示C语言TDD开发最佳实践

## 🏗️ 项目结构

```
Richman/
├── src/                           # 源代码
│   ├── main.c                     # Rich程序主入口
│   └── hello.c                    # Hello World功能实现
├── include/                       # 头文件
│   └── hello.h                    # Hello World函数声明
├── integration_tests/             # 集成测试系统
│   ├── run_all_tests.sh           # 自动化测试运行器
│   ├── test_cases/                # 测试用例目录
│   │   ├── case1_helloworld/      # Hello World测试用例
│   │   ├── case2_help/            # 帮助信息测试用例
│   │   ├── case3_version/         # 版本信息测试用例
│   │   └── case4_invalid_cmd/     # 错误处理测试用例
│   └── test_results.log           # 测试结果日志 (自动生成)
├── bin/                           # 可执行文件 (自动生成)
├── obj/                           # 编译对象文件 (自动生成)
├── Makefile                       # 构建配置
├── BUILD_GUIDE.md                 # 开发环境指南
├── TDD_GUIDE.md                   # TDD测试驱动开发指南
├── TEST_CASE_GUIDE.md             # 测试用例管理指南
└── README.md                      # 本文件
```

## ⚡ 快速开始

### 前置要求

- **编译器**: gcc (支持C99)
- **构建工具**: make
- **操作系统**: Linux/Unix (WSL2支持)
- **标准库**: 只需要C标准库，无外部依赖

### 一键编译

```bash
# 编译Rich程序
make build

# 或简单使用
make
```

### 一键测试

```bash
# 运行完整的集成测试
make test
```

### Rich程序安装和使用

```bash
# 安装rich到系统（推荐）
make install

# 安装后可直接使用
rich testhelloworld
rich help

# 或者本地运行（需要./前缀）
./rich testhelloworld
./rich help
```

## 🧪 集成测试系统

本项目采用集成测试方法，测试完整的程序功能流程：

### 测试用例

1. **Hello World基本功能测试**
   - 命令: `rich testhelloworld`
   - 期望输出: `Hello, World!`

2. **帮助命令测试**
   - 命令: `rich help`
   - 验证帮助信息正确显示

3. **错误处理测试**
   - 命令: `rich invalidcmd`
   - 验证程序正确返回错误码

### 测试特性

- ✅ 自动化测试脚本
- ✅ 输出内容比较
- ✅ 退出码验证
- ✅ 彩色测试报告
- ✅ 详细日志记录

## 🎯 Hello World测试用例

作为第一个测试用例，Hello World功能展示了：

```bash
# 输入命令
./bin/rich testhelloworld

# 输出结果
Hello, World!
```

此测试用例被保留作为集成测试系统的基础示例。

## 🛠️ 开发命令

```bash
# 编译程序
make build

# 运行测试
make test

# 安装到系统（推荐）
make install

# 卸载程序
make uninstall

# 清理构建文件
make clean

# 显示帮助
make help
```

## 📋 测试结果示例

```
开始运行 Hello World 集成测试...
========================================
测试用例1: 基本 testhelloworld 命令
运行测试: HelloWorld_Basic ... PASSED
测试用例2: 帮助命令
运行测试: Help_Command ... PASSED
测试用例3: 无效命令
运行测试: Invalid_Command ... PASSED
========================================
🏁 测试完成!
总测试数: 3
通过: 3
失败: 0

🎉 所有测试通过!
```

## 🔧 集成测试 vs 单元测试

本项目选择集成测试而不是传统单元测试的原因：

- **真实性**: 测试整个程序的完整功能流程
- **简洁性**: 不需要复杂的测试框架和模拟对象
- **实用性**: 更接近用户实际使用场景
- **可靠性**: 确保程序在真实环境下的正确性

## 📖 详细文档

- **开发环境配置**: [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **TDD测试驱动开发**: [TDD_GUIDE.md](TDD_GUIDE.md) - 核心开发方法论
- **测试用例管理**: [TEST_CASE_GUIDE.md](TEST_CASE_GUIDE.md) - 测试用例添加和管理

## 🏆 项目特色

- ✨ 一键编译和测试
- 🧪 完整的集成测试系统
- 📊 详细的测试报告
- 🚀 简洁的项目结构
- 💻 跨平台支持 (Linux/WSL2)

---

**Rich大富翁程序** - 使用现代集成测试方法构建的C语言项目示例