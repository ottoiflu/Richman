#!/bin/bash
# Rich 大富翁程序 - 自动化集成测试运行器
# 自动发现并执行所有测试用例

# 设置颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 测试计数器
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# 日志文件
TEST_LOG="integration_tests/test_results.log"
TEST_CASES_DIR="integration_tests/test_cases"

echo "开始运行 Rich 大富翁程序集成测试..."
echo "========================================"

# 清理之前的测试结果
> "$TEST_LOG"
rm -f dump.txt

# 检查Rich程序是否存在
if [ ! -f "./rich" ]; then
    echo -e "${RED}错误: ./rich 程序不存在，请先运行 make build${NC}"
    exit 1
fi

# 自动发现所有测试用例
test_cases=($(find "$TEST_CASES_DIR" -mindepth 1 -maxdepth 1 -type d | sort))

if [ ${#test_cases[@]} -eq 0 ]; then
    echo -e "${RED}错误: 在 $TEST_CASES_DIR 中没有找到测试用例${NC}"
    exit 1
fi

echo "发现 ${#test_cases[@]} 个测试用例:"
for case_dir in "${test_cases[@]}"; do
    case_name=$(basename "$case_dir")
    echo "  - $case_name"
done
echo "========================================"

# 运行每个测试用例
for case_dir in "${test_cases[@]}"; do
    case_name=$(basename "$case_dir")
    cmdlist_file="$case_dir/cmdlist.txt"
    expected_file="$case_dir/expected_result.txt"
    description_file="$case_dir/description.txt"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # 显示测试用例描述
    if [ -f "$description_file" ]; then
        echo -e "${BLUE}$(cat "$description_file" | head -1)${NC}"
    else
        echo -e "${BLUE}测试用例: $case_name${NC}"
    fi
    
    echo -n "运行测试: $case_name ... "
    
    # 检查必需文件是否存在
    if [ ! -f "$cmdlist_file" ]; then
        echo -e "${RED}FAILED${NC}"
        echo "[$case_name] FAILED - cmdlist.txt 文件不存在" >> "$TEST_LOG"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        continue
    fi
    
    if [ ! -f "$expected_file" ]; then
        echo -e "${RED}FAILED${NC}"
        echo "[$case_name] FAILED - expected_result.txt 文件不存在" >> "$TEST_LOG"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        continue
    fi
    
    # 执行测试命令
    actual_output_file="/tmp/actual_output_${case_name}.txt"
    
    # 读取命令文件并执行
    if [ -s "$cmdlist_file" ]; then
        # 如果cmdlist.txt不为空，读取命令并执行
        while IFS= read -r cmd || [ -n "$cmd" ]; do
            # 跳过空行和注释行
            if [[ -z "$cmd" || "$cmd" =~ ^[[:space:]]*// ]]; then
                continue
            fi
            # 执行命令
            ./rich $cmd >> "$actual_output_file" 2>&1
        done < "$cmdlist_file"
    else
        # 如果cmdlist.txt为空，执行无参数的rich命令
        ./rich >> "$actual_output_file" 2>&1
    fi
    
    # 比较输出结果
    if diff -q "$actual_output_file" "$expected_file" > /dev/null 2>&1; then
        echo -e "${GREEN}PASSED${NC}"
        echo "[$case_name] PASSED" >> "$TEST_LOG"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAILED${NC}"
        echo "[$case_name] FAILED - 输出不匹配" >> "$TEST_LOG"
        echo "期望输出:" >> "$TEST_LOG"
        cat "$expected_file" >> "$TEST_LOG"
        echo "实际输出:" >> "$TEST_LOG"
        cat "$actual_output_file" >> "$TEST_LOG"
        echo "差异详情:" >> "$TEST_LOG"
        diff "$expected_file" "$actual_output_file" >> "$TEST_LOG" 2>&1
        echo "---" >> "$TEST_LOG"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    # 清理临时文件
    rm -f "$actual_output_file"
done

# 生成测试报告
echo "========================================"
echo "测试完成!"
echo "总测试数: $TOTAL_TESTS"
echo -e "通过: ${GREEN}$PASSED_TESTS${NC}"
echo -e "失败: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}所有测试通过!${NC}"
    exit 0
else
    echo -e "\n${RED}有测试失败，请查看 $TEST_LOG${NC}"
    exit 1
fi