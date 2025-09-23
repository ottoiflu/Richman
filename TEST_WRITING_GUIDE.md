# 大富翁游戏测试用例撰写指南

## 📋 概述

本指南详细说明如何根据游戏规则撰写高质量的测试用例，确保测试覆盖全面、准确可靠。

## 🎯 测试用例撰写原则

### 1. 完整性原则
- 每个测试用例必须包含完整的执行流程
- 从游戏启动到游戏结束的完整路径
- 包含所有必要的验证点

### 2. 独立性原则
- 每个测试用例独立可执行
- 不依赖其他测试用例的结果
- 测试用例之间无相互影响

### 3. 准确性原则
- 期望输出必须与实际游戏行为一致
- 数值计算必须准确无误
- 状态变化必须正确反映

### 4. 可维护性原则
- 测试用例命名清晰易懂
- 测试描述详细准确
- 便于后续修改和扩展

## 📁 测试用例文件结构

### 标准目录结构
```
tests/integration/test_{功能}_{序号}/
├── cmdlist.txt           # 命令序列（必需）
├── expected_output.txt   # 期望控制台输出（必需）
├── expected_dump.json    # 期望JSON状态（必需）
├── preset.json          # 初始状态（可选）
├── description.txt       # 测试描述（推荐）
└── tags.txt             # 测试标签（推荐）
```

### 文件内容要求

#### cmdlist.txt - 命令序列
**格式要求**：
- 第一行：角色选择（1-4的数字组合）
- 后续行：游戏命令
- 最后一行：quit（退出命令）

**示例**：
```
1
step 3
query
dump
quit
```

**注意事项**：
- 命令必须小写
- 参数用空格分隔
- 每行一个命令
- 必须包含quit命令

#### expected_output.txt - 期望输出
**格式要求**：
- 包含完整的控制台输出
- 从游戏启动到游戏结束
- 包含所有提示信息和结果

**示例**：
```
大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> === 游戏状态 ===
玩家数量: 1
玩家0: 钱夫人, 资金:1500, 位置:0, 存活:是
当前玩家: 0
游戏状态: 未开始
> 游戏状态已保存到: dump.json
> 游戏结束
```

**注意事项**：
- 输出必须与实际游戏完全一致
- 包含所有换行符和空格
- 提示信息必须准确
- 状态信息必须正确

#### expected_dump.json - 期望状态
**格式要求**：
- 符合JSON格式规范
- 包含完整的游戏状态
- 数值必须准确

**示例**：
```json
{
    "players": [
        {
            "index": 0,
            "name": "钱夫人",
            "fund": 1500,
            "credit": 0,
            "location": 0,
            "alive": true,
            "prop": {
                "bomb": 0,
                "barrier": 0,
                "robot": 0,
                "total": 0
            },
            "buff": {
                "god": 0,
                "prison": 0,
                "hospital": 0
            }
        }
    ],
    "houses": {
    },
    "placed_prop": {
        "bomb": [],
        "barrier": []
    },
    "game": {
        "now_player": 0,
        "next_player": 1,
        "started": false,
        "ended": false,
        "winner": -1
    }
}
```

**注意事项**：
- JSON格式必须正确
- 数值必须准确
- 状态必须完整
- 字段必须齐全

## 🎮 具体功能测试用例撰写

### 1. 游戏启动和角色选择测试

#### 测试用例：test_startup_001
**功能**：单角色选择测试
**目标**：验证单个角色选择功能

**cmdlist.txt**：
```
1
quit
```

**expected_output.txt**：
```
大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> 游戏结束
```

**expected_dump.json**：
```json
{
    "players": [
        {
            "index": 0,
            "name": "钱夫人",
            "fund": 1500,
            "credit": 0,
            "location": 0,
            "alive": true,
            "prop": {
                "bomb": 0,
                "barrier": 0,
                "robot": 0,
                "total": 0
            },
            "buff": {
                "god": 0,
                "prison": 0,
                "hospital": 0
            }
        }
    ],
    "houses": {
    },
    "placed_prop": {
        "bomb": [],
        "barrier": []
    },
    "game": {
        "now_player": 0,
        "next_player": 1,
        "started": false,
        "ended": false,
        "winner": -1
    }
}
```

### 2. 移动功能测试

#### 测试用例：test_move_001
**功能**：Step命令基础测试
**目标**：验证Step命令的移动功能

**cmdlist.txt**：
```
1
step 3
query
dump
quit
```

**expected_output.txt**：
```
大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> 钱夫人移动了3步，当前位置：3
> === 游戏状态 ===
玩家数量: 1
玩家0: 钱夫人, 资金:1500, 位置:3, 存活:是
当前玩家: 0
游戏状态: 未开始
> 游戏状态已保存到: dump.json
> 游戏结束
```

**expected_dump.json**：
```json
{
    "players": [
        {
            "index": 0,
            "name": "钱夫人",
            "fund": 1500,
            "credit": 0,
            "location": 3,
            "alive": true,
            "prop": {
                "bomb": 0,
                "barrier": 0,
                "robot": 0,
                "total": 0
            },
            "buff": {
                "god": 0,
                "prison": 0,
                "hospital": 0
            }
        }
    ],
    "houses": {
    },
    "placed_prop": {
        "bomb": [],
        "barrier": []
    },
    "game": {
        "now_player": 0,
        "next_player": 1,
        "started": false,
        "ended": false,
        "winner": -1
    }
}
```

### 3. 房产购买测试

#### 测试用例：test_land_001
**功能**：地段1空地购买测试
**目标**：验证地段1空地的购买功能

**cmdlist.txt**：
```
1
step 1
buy
query
dump
quit
```

**expected_output.txt**：
```
大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> 钱夫人移动了1步，当前位置：1
> 当前位置是空地，是否购买？(y/n): 购买成功！花费200元
> === 游戏状态 ===
玩家数量: 1
玩家0: 钱夫人, 资金:1300, 位置:1, 存活:是
当前玩家: 0
游戏状态: 未开始
> 游戏状态已保存到: dump.json
> 游戏结束
```

**expected_dump.json**：
```json
{
    "players": [
        {
            "index": 0,
            "name": "钱夫人",
            "fund": 1300,
            "credit": 0,
            "location": 1,
            "alive": true,
            "prop": {
                "bomb": 0,
                "barrier": 0,
                "robot": 0,
                "total": 0
            },
            "buff": {
                "god": 0,
                "prison": 0,
                "hospital": 0
            }
        }
    ],
    "houses": {
        "1": {
            "owner": "钱夫人",
            "level": 0
        }
    },
    "placed_prop": {
        "bomb": [],
        "barrier": []
    },
    "game": {
        "now_player": 0,
        "next_player": 1,
        "started": false,
        "ended": false,
        "winner": -1
    }
}
```

### 4. 道具使用测试

#### 测试用例：test_prop_001
**功能**：路障使用测试
**目标**：验证路障的放置和使用功能

**cmdlist.txt**：
```
1
step 25
buy 1
step 1
block 5
query
dump
quit
```

**expected_output.txt**：
```
大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> 钱夫人移动了1步，当前位置：26
> 欢迎光临道具屋，请选择您所需要的道具:
> 1.路障(50点) 2.机器娃娃(30点) 3.炸弹(50点)
> 购买成功！花费50点
> 钱夫人移动了1步，当前位置：27
> 路障放置成功！位置：32
> === 游戏状态 ===
玩家数量: 1
玩家0: 钱夫人, 资金:1500, 位置:27, 存活:是
当前玩家: 0
游戏状态: 未开始
> 游戏状态已保存到: dump.json
> 游戏结束
```

**expected_dump.json**：
```json
{
    "players": [
        {
            "index": 0,
            "name": "钱夫人",
            "fund": 1500,
            "credit": 0,
            "location": 27,
            "alive": true,
            "prop": {
                "bomb": 0,
                "barrier": 0,
                "robot": 0,
                "total": 1
            },
            "buff": {
                "god": 0,
                "prison": 0,
                "hospital": 0
            }
        }
    ],
    "houses": {
    },
    "placed_prop": {
        "bomb": [],
        "barrier": [32]
    },
    "game": {
        "now_player": 0,
        "next_player": 1,
        "started": false,
        "ended": false,
        "winner": -1
    }
}
```

## 🔧 测试用例撰写工具

### 1. 测试用例生成器

```python
#!/usr/bin/env python3
"""
测试用例生成器
根据模板自动生成测试用例
"""

import os
import json
from pathlib import Path

class TestCaseGenerator:
    def __init__(self, base_dir="tests/integration"):
        self.base_dir = Path(base_dir)
        self.test_counter = 1
    
    def generate_move_test(self, steps):
        """生成移动测试用例"""
        test_name = f"test_move_{self.test_counter:03d}"
        test_dir = self.base_dir / test_name
        test_dir.mkdir(exist_ok=True)
        
        # 生成cmdlist.txt
        cmdlist_content = f"""1
step {steps}
query
dump
quit"""
        
        with open(test_dir / "cmdlist.txt", "w", encoding="utf-8") as f:
            f.write(cmdlist_content)
        
        # 生成expected_output.txt
        expected_output = f"""大富翁游戏启动
欢迎来到大富翁，请按数字键选择你的角色：
1.钱夫人
2.阿土伯
3.孙小美
4.金贝贝
请输入选择 (1-4): 您选择了: 钱夫人
游戏开始！
> 钱夫人移动了{steps}步，当前位置：{steps}
> === 游戏状态 ===
玩家数量: 1
玩家0: 钱夫人, 资金:1500, 位置:{steps}, 存活:是
当前玩家: 0
游戏状态: 未开始
> 游戏状态已保存到: dump.json
> 游戏结束"""
        
        with open(test_dir / "expected_output.txt", "w", encoding="utf-8") as f:
            f.write(expected_output)
        
        # 生成expected_dump.json
        expected_dump = {
            "players": [
                {
                    "index": 0,
                    "name": "钱夫人",
                    "fund": 1500,
                    "credit": 0,
                    "location": steps,
                    "alive": True,
                    "prop": {
                        "bomb": 0,
                        "barrier": 0,
                        "robot": 0,
                        "total": 0
                    },
                    "buff": {
                        "god": 0,
                        "prison": 0,
                        "hospital": 0
                    }
                }
            ],
            "houses": {},
            "placed_prop": {
                "bomb": [],
                "barrier": []
            },
            "game": {
                "now_player": 0,
                "next_player": 1,
                "started": False,
                "ended": False,
                "winner": -1
            }
        }
        
        with open(test_dir / "expected_dump.json", "w", encoding="utf-8") as f:
            json.dump(expected_dump, f, indent=4, ensure_ascii=False)
        
        self.test_counter += 1
        return test_name

# 使用示例
generator = TestCaseGenerator()
for steps in range(1, 7):
    generator.generate_move_test(steps)
```

### 2. 测试用例验证器

```python
#!/usr/bin/env python3
"""
测试用例验证器
验证测试用例的正确性
"""

import subprocess
import json
import difflib
from pathlib import Path

class TestValidator:
    def __init__(self, game_binary="./richman"):
        self.game_binary = game_binary
    
    def validate_test_case(self, test_dir):
        """验证单个测试用例"""
        test_dir = Path(test_dir)
        
        # 检查必需文件
        required_files = ["cmdlist.txt", "expected_output.txt", "expected_dump.json"]
        for file in required_files:
            if not (test_dir / file).exists():
                print(f"❌ 缺少文件: {file}")
                return False
        
        # 运行游戏程序
        cmdlist_file = test_dir / "cmdlist.txt"
        with open(cmdlist_file, 'r', encoding='utf-8') as f:
            cmd_input = f.read()
        
        try:
            result = subprocess.run(
                [self.game_binary],
                input=cmd_input,
                text=True,
                capture_output=True,
                timeout=30
            )
            
            # 保存实际输出
            with open(test_dir / "output.txt", "w", encoding="utf-8") as f:
                f.write(result.stdout)
            
            # 比较输出
            expected_output_file = test_dir / "expected_output.txt"
            with open(expected_output_file, 'r', encoding='utf-8') as f:
                expected_output = f.read()
            
            if result.stdout.strip() == expected_output.strip():
                print(f"✅ 输出匹配: {test_dir.name}")
                return True
            else:
                print(f"❌ 输出不匹配: {test_dir.name}")
                # 显示差异
                diff = difflib.unified_diff(
                    expected_output.splitlines(keepends=True),
                    result.stdout.splitlines(keepends=True),
                    fromfile="期望输出",
                    tofile="实际输出"
                )
                for line in diff:
                    print(line, end="")
                return False
                
        except subprocess.TimeoutExpired:
            print(f"❌ 超时: {test_dir.name}")
            return False
        except Exception as e:
            print(f"❌ 错误: {test_dir.name} - {e}")
            return False
    
    def validate_all_tests(self, test_dir="tests/integration"):
        """验证所有测试用例"""
        test_dir = Path(test_dir)
        passed = 0
        total = 0
        
        for test_case in test_dir.iterdir():
            if test_case.is_dir():
                total += 1
                if self.validate_test_case(test_case):
                    passed += 1
        
        print(f"\n📊 验证结果: {passed}/{total} 通过")
        return passed == total

# 使用示例
validator = TestValidator()
validator.validate_all_tests()
```

## 📋 测试用例撰写检查清单

### 撰写前检查
- [ ] 确定测试目标和功能点
- [ ] 分析游戏规则和预期行为
- [ ] 设计测试场景和命令序列
- [ ] 准备期望输出和状态

### 撰写中检查
- [ ] cmdlist.txt格式正确
- [ ] 命令序列完整可执行
- [ ] 期望输出准确完整
- [ ] JSON状态正确无误
- [ ] 测试用例独立可运行

### 撰写后检查
- [ ] 运行测试用例验证
- [ ] 检查输出是否匹配
- [ ] 验证JSON状态正确
- [ ] 确认测试用例通过
- [ ] 更新测试文档

## 🚀 最佳实践

### 1. 测试用例设计
- 一个测试用例只测试一个功能点
- 测试用例要简单明了
- 避免复杂的测试场景
- 优先测试核心功能

### 2. 命令序列设计
- 命令序列要简洁有效
- 避免不必要的命令
- 确保命令顺序正确
- 包含必要的验证命令

### 3. 期望输出设计
- 期望输出要完整准确
- 包含所有必要的提示信息
- 状态信息要正确
- 格式要与实际输出一致

### 4. JSON状态设计
- JSON格式要正确
- 数值要准确
- 状态要完整
- 字段要齐全

### 5. 测试用例维护
- 定期更新测试用例
- 及时修复发现的问题
- 保持测试用例的时效性
- 优化测试用例的性能

## 📞 技术支持

### 常见问题
1. **测试用例不通过怎么办？**
   - 检查期望输出是否准确
   - 验证JSON状态是否正确
   - 确认命令序列是否完整

2. **如何生成期望输出？**
   - 运行游戏程序
   - 手动执行命令序列
   - 记录实际输出
   - 保存游戏状态

3. **如何验证JSON状态？**
   - 使用dump命令保存状态
   - 检查JSON格式是否正确
   - 验证数值是否准确
   - 确认状态是否完整

### 获取帮助
- 查看现有测试用例作为参考
- 使用测试用例生成器
- 运行测试用例验证器
- 在团队群中讨论问题

---

**记住**：高质量的测试用例是游戏质量的重要保障，请认真对待每一个测试用例的撰写！