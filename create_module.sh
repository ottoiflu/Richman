#!/bin/bash
# create_module.sh - Rich 大富翁项目模块生成器
# 用法: ./create_module.sh <模块名> <开发者姓名> [命令1] [命令2] ...

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# 显示帮助信息
show_help() {
    echo -e "${CYAN}Rich 大富翁项目 - 模块生成器${NC}"
    echo -e "${CYAN}================================${NC}"
    echo ""
    echo -e "${YELLOW}用法:${NC}"
    echo "  ./create_module.sh <模块名> <开发者姓名> [命令1] [命令2] ..."
    echo ""
    echo -e "${YELLOW}示例:${NC}"
    echo "  ./create_module.sh map 张三 create_map show_map reset_map"
    echo "  ./create_module.sh trade 李四 buy_property sell_property"
    echo "  ./create_module.sh item 王五 use_bomb use_barrier"
    echo ""
    echo -e "${YELLOW}参数说明:${NC}"
    echo "  模块名     - 功能模块名称（如: map, trade, item）"
    echo "  开发者姓名 - 您的姓名，用于代码标记"
    echo "  命令列表   - 该模块包含的命令（可选，可后续添加）"
    echo ""
    echo -e "${YELLOW}生成的文件:${NC}"
    echo "  src/modules/<模块名>_<开发者>.c           - 模块源代码"
    echo "  integration_tests/test_cases/case_<模块名>_*/ - 测试用例"
}

# 检查帮助参数
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

# 检查参数
if [ $# -lt 2 ]; then
    echo -e "${RED}错误: 参数不足${NC}"
    echo ""
    show_help
    exit 1
fi

MODULE_NAME="$1"
DEVELOPER_NAME="$2"
shift 2
COMMANDS=("$@")

# 验证模块名
if [[ ! "$MODULE_NAME" =~ ^[a-zA-Z][a-zA-Z0-9_]*$ ]]; then
    echo -e "${RED}错误: 模块名只能包含字母、数字和下划线，且必须以字母开头${NC}"
    exit 1
fi

# 生成文件名
MODULE_FILE="src/modules/${MODULE_NAME}_${DEVELOPER_NAME}.c"
MODULE_UPPER=$(echo "$MODULE_NAME" | tr '[:lower:]' '[:upper:]')
MODULE_TITLE=$(echo "$MODULE_NAME" | sed 's/^./\U&/')

# 检查文件是否已存在
if [ -f "$MODULE_FILE" ]; then
    echo -e "${YELLOW}警告: 文件 $MODULE_FILE 已存在${NC}"
    read -p "是否覆盖? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo -e "${BLUE}操作已取消${NC}"
        exit 0
    fi
fi

echo -e "${CYAN}正在生成模块: ${MODULE_NAME}${NC}"
echo -e "${CYAN}开发者: ${DEVELOPER_NAME}${NC}"
if [ ${#COMMANDS[@]} -gt 0 ]; then
    echo -e "${CYAN}命令列表: ${COMMANDS[*]}${NC}"
fi
echo ""

# 生成模块源代码
cat > "$MODULE_FILE" << EOF
// src/modules/${MODULE_NAME}_${DEVELOPER_NAME}.c - ${MODULE_TITLE}模块
// 开发者: ${DEVELOPER_NAME}
// 自动生成时间: $(date '+%Y-%m-%d %H:%M:%S')

#include "common.h"

// =============================================================================
// ${MODULE_TITLE}模块数据结构 - 开发者: ${DEVELOPER_NAME}
// =============================================================================

// TODO: 在这里定义您的数据结构
// 示例:
// typedef struct {
//     int property1;
//     char property2[64];
// } ${MODULE_TITLE}Data;

// 模块内部数据（如果需要）
// MODULE_DATA(${MODULE_TITLE}Data, g_${MODULE_NAME}_data, {0});

// =============================================================================
// ${MODULE_TITLE}模块内部函数 - 开发者: ${DEVELOPER_NAME}
// =============================================================================

// TODO: 在这里实现您的内部函数
// 示例:
// static void ${MODULE_NAME}_internal_function() {
//     // 内部实现逻辑
// }

// =============================================================================
// ${MODULE_TITLE}模块命令实现 - 开发者: ${DEVELOPER_NAME}
// =============================================================================

EOF

# 生成命令实现
if [ ${#COMMANDS[@]} -eq 0 ]; then
    # 没有指定命令，生成示例命令
    cat >> "$MODULE_FILE" << EOF
// 示例命令 - 请根据需要修改或删除
DEFINE_COMMAND("${MODULE_NAME}_example", "${MODULE_TITLE}示例命令", cmd_${MODULE_NAME}_example, "${MODULE_TITLE}-${DEVELOPER_NAME}") {
    // TODO: 实现您的命令逻辑
    
    // 示例: 参数验证
    // REQUIRE_ARGS("${MODULE_NAME}_example");
    
    // 示例: 获取游戏状态
    // GameState* state = GET_GAME_STATE();
    
    // 示例: 参数解析
    // int param = atoi(args);
    // VALIDATE_INT_RANGE(param, 1, 100, "参数必须在1-100之间");
    
    // 示例: 成功返回
    SUCCESS_MSG("${MODULE_TITLE}示例命令执行成功");
}

EOF
else
    # 生成指定的命令
    for cmd in "${COMMANDS[@]}"; do
        # 验证命令名
        if [[ ! "$cmd" =~ ^[a-zA-Z][a-zA-Z0-9_]*$ ]]; then
            echo -e "${YELLOW}警告: 跳过无效命令名: $cmd${NC}"
            continue
        fi
        
        cat >> "$MODULE_FILE" << EOF
// ${cmd} 命令实现
DEFINE_COMMAND("${cmd}", "${cmd}命令", cmd_${cmd}, "${MODULE_TITLE}-${DEVELOPER_NAME}") {
    // TODO: 实现 ${cmd} 命令的逻辑
    
    // 参数验证示例:
    // REQUIRE_ARGS("${cmd}");
    
    // 获取游戏状态:
    // GameState* state = GET_GAME_STATE();
    
    // 参数解析示例:
    // int param = atoi(args);
    // VALIDATE_INT_RANGE(param, 0, 100, "参数范围错误");
    
    // 实现您的功能逻辑...
    printf("执行 ${cmd} 命令: %s\\n", args ? args : "无参数");
    
    return CMD_SUCCESS;
}

EOF
    done
fi

# 添加模块初始化函数（可选）
cat >> "$MODULE_FILE" << EOF
// =============================================================================
// ${MODULE_TITLE}模块初始化 - 开发者: ${DEVELOPER_NAME}
// =============================================================================

// 模块初始化函数（可选）
// 如果需要在模块加载时执行初始化代码，请取消注释并实现
/*
DEFINE_MODULE_INIT(${MODULE_NAME}) {
    // TODO: 在这里添加模块初始化代码
    // 例如: 初始化数据结构、设置默认值等
    
    printf("${MODULE_TITLE}模块已初始化 - 开发者: ${DEVELOPER_NAME}\\n");
}
*/

// =============================================================================
// 开发提示
// =============================================================================
/*
开发提示:
1. 使用 DEFINE_COMMAND 宏来定义命令，会自动注册到系统中
2. 使用 REQUIRE_ARGS 宏来验证参数
3. 使用 GET_GAME_STATE() 来获取游戏状态
4. 使用 SUCCESS_MSG 和 ERROR_MSG 来返回结果
5. 编译后命令会自动可用，无需手动注册

测试您的模块:
1. 运行 make build 编译
2. 运行 ./rich help 查看新命令
3. 运行 echo "your_command args" | ./rich 测试命令

创建测试用例:
./create_test.sh ${MODULE_NAME} your_command "expected_output"
*/
EOF

echo -e "${GREEN}✅ 模块源代码已生成: $MODULE_FILE${NC}"

# 生成测试用例
if [ ${#COMMANDS[@]} -gt 0 ]; then
    echo -e "${CYAN}正在生成测试用例...${NC}"
    
    for cmd in "${COMMANDS[@]}"; do
        if [[ ! "$cmd" =~ ^[a-zA-Z][a-zA-Z0-9_]*$ ]]; then
            continue
        fi
        
        test_dir="integration_tests/test_cases/case_${MODULE_NAME}_${cmd}"
        mkdir -p "$test_dir"
        
        # 生成测试文件
        echo "$cmd test_param" > "$test_dir/cmdlist.txt"
        echo "执行 ${cmd} 命令: test_param" > "$test_dir/expected_result.txt"
        echo "${cmd}命令测试 - 开发者: ${DEVELOPER_NAME}" > "$test_dir/description.txt"
        
        echo -e "${GREEN}  ✅ 测试用例已生成: $test_dir${NC}"
    done
fi

# 更新Makefile（如果需要）
if ! grep -q "src/modules/\*.c" Makefile 2>/dev/null; then
    echo -e "${CYAN}正在更新Makefile...${NC}"
    
    # 备份原Makefile
    cp Makefile Makefile.backup
    
    # 更新SOURCES行
    sed -i 's|^SOURCES := .*|& $(wildcard src/modules/*.c)|' Makefile
    
    echo -e "${GREEN}✅ Makefile已更新${NC}"
fi

# 显示使用说明
echo ""
echo -e "${CYAN}🎉 模块生成完成！${NC}"
echo ""
echo -e "${YELLOW}下一步操作:${NC}"
echo "1. 编辑 $MODULE_FILE 实现您的功能"
echo "2. 运行 make build 编译项目"
echo "3. 运行 ./rich help 查看新命令"
echo "4. 运行 make test 测试功能"
echo ""
echo -e "${YELLOW}快速测试:${NC}"
if [ ${#COMMANDS[@]} -gt 0 ]; then
    echo "echo \"${COMMANDS[0]} test\" | ./rich"
else
    echo "echo \"${MODULE_NAME}_example test\" | ./rich"
fi
echo ""
echo -e "${YELLOW}开发提示:${NC}"
echo "- 使用 DEFINE_COMMAND 宏定义命令"
echo "- 使用 REQUIRE_ARGS 验证参数"
echo "- 使用 SUCCESS_MSG/ERROR_MSG 返回结果"
echo "- 查看生成的文件末尾有详细的开发提示"
echo ""
echo -e "${GREEN}Happy Coding! 🚀${NC}"