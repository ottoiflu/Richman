#!/bin/bash
# Rich 大富翁程序 - 自动化集成测试运行器

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

TEST_LOG="integration_tests/test_results.log"
TEST_CASES_DIR="integration_tests/test_cases"

echo "开始运行 Rich 大富翁程序集成测试..."
echo "========================================"

> "$TEST_LOG"
rm -f dump.txt

# 检查Rich程序是否存在
if [ ! -f "./bin/rich" ] && [ ! -f "./rich" ]; then
    echo -e "${RED}错误: ./bin/rich 或 ./rich 不存在，请先运行 make build${NC}"
    exit 1
fi

BIN="./bin/rich"
[ -f "./rich" ] && BIN="./rich"

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
    result_file="$case_dir/result.txt"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # 显示测试用例描述
    if [ -f "$description_file" ]; then
        echo -e "${BLUE}$(head -1 "$description_file")${NC}"
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

    # 生成 result.txt
    if [ -s "$cmdlist_file" ]; then
        > "$result_file"
        while IFS= read -r cmd || [ -n "$cmd" ]; do
            if [[ -z "$cmd" || "$cmd" =~ ^[[:space:]]*// ]]; then
                continue
            fi
            $BIN $cmd >> "$result_file" 2>&1
        done < "$cmdlist_file"
    else
        $BIN > "$result_file" 2>&1
    fi

    # 比较输出结果
    if diff -q "$result_file" "$expected_file" > /dev/null 2>&1; then
        echo -e "${GREEN}PASSED${NC}"
        echo "[$case_name] PASSED" >> "$TEST_LOG"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAILED${NC}"
        echo "[$case_name] FAILED - 输出不匹配" >> "$TEST_LOG"
        echo "期望输出:" >> "$TEST_LOG"
        cat "$expected_file" >> "$TEST_LOG"
        echo "实际输出:" >> "$TEST_LOG"
        cat "$result_file" >> "$TEST_LOG"
        echo "差异详情:" >> "$TEST_LOG"
        diff "$expected_file" "$result_file" >> "$TEST_LOG" 2>&1
        echo "---" >> "$TEST_LOG"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
done

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