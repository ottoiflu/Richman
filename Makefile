# 1. 编译器和编译选项
# 定义了编译器、C++标准、调试信息、警告等级以及头文件搜索路径。
CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -I./include -I./googletest/googletest/include
LDFLAGS := -L./lib -pthread

# 2. 目录定义
# 方便后续引用各个目录。
SRCDIR := src
TESTDIR := tests
BUILDDIR := obj
BINDIR := bin
LIBDIR := lib

# 3. Google Test 相关定义
# 指定gtest的源码路径，用于后续编译gtest库。
GTEST_DIR := googletest/googletest
GTEST_SRCS := $(GTEST_DIR)/src/gtest-all.cc

# 4. 自动查找源文件
# 使用wildcard函数自动查找src和tests目录下的所有.cpp文件。
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
# 自动生成所有.o文件的路径。
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TEST_SOURCES))

# 5. 主要目标
# `make all` 或 `make` 的默认目标是构建主程序。
all: $(BINDIR)/main

# `make test` 的目标是运行所有测试。这是TDD流程的核心命令。
test: $(BINDIR)/run_tests
	./$(BINDIR)/run_tests

# 6. 编译和链接规则
# 链接生成测试可执行文件。它依赖于产品代码的.o文件、测试代码的.o文件以及gtest库。
$(BINDIR)/run_tests: $(OBJECTS) $(TEST_OBJECTS) $(LIBDIR)/libgtest.a
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 链接生成最终的产品可执行文件（不包含测试代码）。
$(BINDIR)/main: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 编译Google Test库。这是一个静态库，只需编译一次。
$(LIBDIR)/libgtest.a: $(GTEST_SRCS)
	@mkdir -p $(LIBDIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -I$(GTEST_DIR) -c $^
	ar rvs $@ gtest-all.o
	rm gtest-all.o

# 通用规则，用于将任何.cpp文件编译成.o文件并存放在obj/目录下。
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 7. 批量测试目标 (方案三)
# 定义默认的测试批处理文件名。
TEST_BATCH_FILE ?= test_batch.txt

# `make run-batch` 目标，用于执行txt文件中定义的测试。
run-batch: $(BINDIR)/run_tests
	@if [ ! -f "$(TEST_BATCH_FILE)" ]; then \
		echo "错误: 测试列表文件 '$(TEST_BATCH_FILE)' 不存在。"; \
		exit 1; \
	fi
	@echo "--- Running batch tests from $(TEST_BATCH_FILE) ---"
	@grep -v -E '^\s*#|^\s*$$' $(TEST_BATCH_FILE) | xargs -I {} $(BINDIR)/run_tests --gtest_filter={}

# 8. 清理目标
# `make clean` 用于删除所有生成的文件，保持工作区干净。
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(LIBDIR)

# 9. 伪目标
# 声明这些目标不是文件名，防止与同名文件冲突。
.PHONY: all test clean run-batch