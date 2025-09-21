# 1. 编译器和编译选项
# 定义了编译器、C标准、调试信息、警告等级以及头文件搜索路径。
CC := gcc
CFLAGS := -std=c99 -g -Wall -I./include
LDFLAGS := -L./lib -lm

# 2. 目录定义
# 方便后续引用各个目录。
SRCDIR := src
TESTDIR := tests
BUILDDIR := obj
BINDIR := bin
LIBDIR := lib

# 3. C语言单元测试框架
# 使用简单的C语言测试框架
TEST_FRAMEWORK := unity

# 源文件（包含命令注册系统的所有源文件）
SOURCES := $(SRCDIR)/main.c $(SRCDIR)/hello.c $(SRCDIR)/game_state.c $(SRCDIR)/command_registry.c $(SRCDIR)/command_processor.c $(SRCDIR)/game_io.c
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%.o,$(TEST_SOURCES))

# 5. 主要目标
# `make all` 或 `make` 的默认目标是构建主程序。
all: $(BINDIR)/main

# `make test` 的目标是运行所有测试。这是TDD流程的核心命令。
test: $(BINDIR)/run_tests
	./$(BINDIR)/run_tests

# 6. 编译和链接规则
# 链接生成测试可执行文件。它依赖于产品代码的.o文件和测试代码的.o文件。
$(BINDIR)/run_tests: $(OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 链接生成最终的产品可执行文件（不包含测试代码）。
$(BINDIR)/main: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# C语言不需要额外的测试库编译

# 通用规则，用于将任何.c文件编译成.o文件并存放在obj/目录下。
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

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
	@$(BINDIR)/run_tests

# 8. 清理目标
# `make clean` 用于删除所有生成的文件，保持工作区干净。
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(LIBDIR)

# 9. 伪目标
# 声明这些目标不是文件名，防止与同名文件冲突。
.PHONY: all test clean run-batch