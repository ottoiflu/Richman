# Rich 大富翁程序 - 测试用例管理指南

## 📁 测试用例结构

每个测试用例都位于独立的文件夹中，包含以下标准文件：

```
integration_tests/test_cases/
├── case1_helloworld/
│   ├── cmdlist.txt          # 测试命令列表
│   ├── expected_result.txt  # 期望输出结果
│   └── description.txt      # 测试用例描述
├── case2_help/
│   ├── cmdlist.txt
│   ├── expected_result.txt
│   └── description.txt
└── ...
```

## 📝 文件说明

### cmdlist.txt - 测试命令文件
包含要执行的命令，每行一个命令参数：
```
# 示例1: 单个命令
testhelloworld

# 示例2: 多个命令
help
version

# 示例3: 复杂命令序列（您提到的大富翁游戏格式）
preset user AQSJ
preset map 0 A 1
preset fund A 1000
step 5
dump
```

### expected_result.txt - 期望结果文件
包含命令执行后的期望输出：
```
Hello, World!
```

### description.txt - 描述文件
包含测试用例的说明信息：
```
测试用例1: Hello World基本功能测试
描述: 测试rich testhelloworld命令是否正确输出Hello, World!
预期: 程序正常退出并输出Hello, World!
```

## 🚀 添加新测试用例的步骤

### 步骤1：创建测试用例文件夹
```bash
mkdir -p integration_tests/test_cases/case5_newfeature
```

### 步骤2：创建命令文件
```bash
echo "newcommand" > integration_tests/test_cases/case5_newfeature/cmdlist.txt
```

### 步骤3：生成期望结果
```bash
# 先实现功能，然后生成期望结果
./rich newcommand > integration_tests/test_cases/case5_newfeature/expected_result.txt
```

### 步骤4：添加描述文件
```bash
cat > integration_tests/test_cases/case5_newfeature/description.txt << 'EOF'
测试用例5: 新功能测试
描述: 测试新实现的功能是否正常工作
预期: 程序正确执行并输出预期结果
EOF
```

### 步骤5：运行测试验证
```bash
make test
```

## 🎯 TDD开发流程中的测试用例管理

### 红色阶段 - 创建失败的测试
```bash
# 1. 创建新测试用例文件夹
mkdir -p integration_tests/test_cases/case_dice_roll

# 2. 定义命令
echo "dice" > integration_tests/test_cases/case_dice_roll/cmdlist.txt

# 3. 定义期望结果（即使功能还未实现）
echo "掷骰子结果: 4" > integration_tests/test_cases/case_dice_roll/expected_result.txt

# 4. 添加描述
cat > integration_tests/test_cases/case_dice_roll/description.txt << 'EOF'
测试用例: 掷骰子功能测试
描述: 测试dice命令是否能正确掷骰子
预期: 输出掷骰子结果
EOF

# 5. 运行测试 - 应该失败
make test
```

### 绿色阶段 - 实现最小功能让测试通过
```bash
# 在代码中实现dice功能...

# 运行测试 - 应该通过
make test
```

### 重构阶段 - 改进实现
```bash
# 重构代码...

# 确保测试仍然通过
make test
```

## 🧪 高级测试用例示例

### 示例1：多命令序列测试
```bash
# cmdlist.txt
help
version
testhelloworld

# expected_result.txt
Rich - 大富翁程序
用法:
  rich testhelloworld    - 运行hello world测试
  rich version          - 显示版本信息
  rich help             - 显示帮助信息
Rich v1.0.0 - 大富翁程序集成测试版
Hello, World!
```

### 示例2：错误处理测试
```bash
# cmdlist.txt
nonexistentcommand

# expected_result.txt
错误: 未知命令 'nonexistentcommand'
Rich - 大富翁程序
用法:
  rich testhelloworld    - 运行hello world测试
  rich version          - 显示版本信息
  rich help             - 显示帮助信息
```

### 示例3：复杂游戏状态测试（您提到的大富翁格式）
```bash
# cmdlist.txt
preset user AQSJ
preset map 0 A 1
preset map 1 Q 2
preset fund A 1000
preset fund Q 3000
preset userloc A 0
preset userloc Q 1
preset nextuser A
step 3
dump

# expected_result.txt
user AQS
map[0] A 1
map[1] Q 2
fund A 1000
fund Q 3000
userloc A 3
userloc Q 1
nextuser Q
```

## 🔧 测试系统特性

### 自动发现
- 测试系统自动发现 `integration_tests/test_cases/` 下的所有测试用例
- 按文件夹名称字母顺序执行测试

### 灵活的命令格式
- 支持单行命令：`testhelloworld`
- 支持多行命令序列
- 支持注释行（以`//`开头）
- 支持空行

### 详细的测试报告
- 显示每个测试用例的描述
- 提供通过/失败统计
- 失败时显示详细的差异信息
- 生成测试日志文件

### 易于维护
- 每个测试用例独立，互不影响
- 添加新测试用例无需修改测试脚本
- 测试数据和测试逻辑分离

## 📋 测试用例命名规范

建议的命名格式：
```
case[序号]_[功能名称]/
├── case1_helloworld/      # 基本功能测试
├── case2_help/            # 帮助信息测试  
├── case3_version/         # 版本信息测试
├── case4_invalid_cmd/     # 错误处理测试
├── case5_dice_roll/       # 掷骰子功能测试
├── case6_player_status/   # 玩家状态测试
└── case7_game_preset/     # 游戏预设测试
```

## 🎯 最佳实践

### DO - 应该做的
- ✅ 每个测试用例测试一个明确的功能点
- ✅ 使用描述性的测试用例名称
- ✅ 在description.txt中清楚说明测试目的
- ✅ 期望结果文件包含完整的预期输出
- ✅ 遵循TDD流程：先写测试，再写代码

### DON'T - 不应该做的
- ❌ 不要在一个测试用例中测试多个无关功能
- ❌ 不要硬编码路径或时间相关的内容
- ❌ 不要忘记更新期望结果文件
- ❌ 不要跳过测试验证步骤

## 🚀 运行测试

```bash
# 运行所有测试
make test

# 或直接运行测试脚本
./integration_tests/run_all_tests.sh

# 查看测试结果日志
cat integration_tests/test_results.log
```

通过这个测试用例管理系统，您可以轻松地为Rich大富翁程序添加任意数量的测试用例，确保每个功能都得到充分测试！