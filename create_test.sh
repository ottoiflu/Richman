#!/bin/bash
# create_test.sh - Rich 大富翁项目测试用例生成器
# 用法: ./create_test.sh <功能名> <命令> <期望输出> [描述]

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# 显示帮助信息
show_help() {
    echo -e "${CYAN}Rich 大富翁项目 - 测试用例生成器${NC}"
    echo -e "${CYAN}===================================${NC}"
    echo ""
    echo -e "${YELLOW}用法:${NC}"
    echo "  ./create_test.sh <功能名> <命令> <期望输出> [描述]"
    echo ""
    echo -e "${YELLOW}示例:${NC}"
    echo '  ./create_test.sh map create_map "地图创建成功" "创建地图功能测试"'
    echo '  ./create_test.sh player set_money "初始资金已设置为：5000"'
    echo '  ./create_test.sh trade buy_property "购买成功"'
    echo ""
    echo -e "${YELLOW}参数说明:${NC}"
    echo "  功能名   - 功能模块名称（用于测试用例命名）"
    echo "  命令     - 要测试的命令"
    echo "  期望输出 - 命令执行后的期望输出"
    echo "  描述     - 测试用例描述（可选）"
}

# 检查参数
if [ $# -lt 3 ]; then
    echo -e "${RED}错误: 参数不足${NC}"
    echo ""
    show_help
    exit 1
fi

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

FEATURE_NAME="$1"
COMMAND="$2"
EXPECTED_OUTPUT="$3"
DESCRIPTION="${4:-${COMMAND}功能测试}"

# 生成测试用例目录名
TEST_DIR="integration_tests/test_cases/case_${FEATURE_NAME}_${COMMAND}"

# 检查目录是否已存在
if [ -d "$TEST_DIR" ]; then
    echo -e "${YELLOW}警告: 测试用例目录 $TEST_DIR 已存在${NC}"
    read -p "是否覆盖? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo -e "${BLUE}操作已取消${NC}"
        exit 0
    fi
fi

echo -e "${CYAN}正在生成测试用例: ${FEATURE_NAME}_${COMMAND}${NC}"

# 创建测试目录
mkdir -p "$TEST_DIR"

# 生成测试文件
echo "$COMMAND" > "$TEST_DIR/cmdlist.txt"
echo "$EXPECTED_OUTPUT" > "$TEST_DIR/expected_result.txt"
echo "$DESCRIPTION" > "$TEST_DIR/description.txt"

echo -e "${GREEN}✅ 测试用例已生成: $TEST_DIR${NC}"
echo ""
echo -e "${YELLOW}生成的文件:${NC}"
echo "  📄 $TEST_DIR/cmdlist.txt"
echo "  📄 $TEST_DIR/expected_result.txt"  
echo "  📄 $TEST_DIR/description.txt"
echo ""
echo -e "${YELLOW}下一步操作:${NC}"
echo "1. 运行 make test 执行测试"
echo "2. 如果测试失败，检查实际输出:"
echo "   cat $TEST_DIR/output.txt"
echo ""
echo -e "${GREEN}测试用例创建完成！🧪${NC}"