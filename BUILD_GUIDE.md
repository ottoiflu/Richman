# Rich 大富翁程序 - 开发环境指南

## 开发环境要求

- **编译器**: gcc (支持C99标准)
- **构建工具**: make
- **操作系统**: Linux/Unix (WSL2支持)
- **标准库**: 只需要C标准库，无外部依赖

## 一键编译控制

编译Rich可执行文件：
```bash
make build
```
或简单使用：
```bash
make
```

编译成功后，可执行文件位于 `bin/rich`

## 一键测试控制

运行完整的集成测试：
```bash
make test
```

测试包括：
1. Hello World基本功能测试
2. 帮助命令测试
3. 无效命令错误处理测试

## 程序安装和使用

### 方法1：安装到系统（推荐）

```bash
# 安装rich程序
make install

# 现在可以直接使用（无需./前缀）
rich testhelloworld
rich help
```

### 方法2：本地运行

```bash
# 本地运行（需要./前缀）
./rich testhelloworld
./rich help
```

### 卸载程序

```bash
make uninstall
```

## 清理构建文件

```bash
make clean
```

## 项目结构

```
Richman/
├── src/                           # 源代码
│   ├── main.c                     # 主程序入口
│   └── hello.c                    # Hello World功能实现
├── include/                       # 头文件
│   └── hello.h                    # Hello World函数声明
├── integration_tests/             # 集成测试
│   ├── test_helloworld.sh         # 测试脚本
│   ├── expected_helloworld.txt    # 期望输出
│   ├── expected_help.txt          # 帮助信息期望输出
│   └── cmdlist_helloworld.txt     # 命令列表文件
├── bin/                           # 可执行文件 (自动生成)
├── obj/                           # 编译对象文件 (自动生成)
└── Makefile                       # 构建配置
```

## 测试系统说明

本项目使用集成测试替代传统的单元测试，测试整个程序的完整功能流程：

- 使用shell脚本进行自动化测试
- 比较实际输出与期望输出
- 验证程序退出码
- 生成详细的测试报告

这种测试方式更接近实际使用场景，确保程序在真实环境下的正确性。