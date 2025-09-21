# Richman 大富翁程序 - 集成测试系统 Makefile
# 编译器和编译选项
CC := gcc
CFLAGS := -std=c99 -g -Wall -I./include
LDFLAGS := -lm

# 目录定义
SRCDIR := src
TESTDIR := integration_tests
BUILDDIR := obj
BINDIR := bin

# 源文件（只包含hello.c和main.c）
SOURCES := $(SRCDIR)/hello.c $(SRCDIR)/main.c
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# 主要目标
.PHONY: all build test clean help install uninstall

# 默认目标：编译rich程序
all: build

# 一键编译：构建rich可执行文件
build: $(BINDIR)/rich
	@cp $(BINDIR)/rich ./rich
	@echo "编译完成！可执行文件：$(BINDIR)/rich"



# 构建rich可执行文件
$(BINDIR)/rich: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 编译规则
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 一键测试：运行集成测试
test: build
	@echo " 开始运行集成测试..."
	@if [ -f "./integration_tests/run_all_tests.sh" ]; then \
		chmod +x ./integration_tests/run_all_tests.sh; \
		./integration_tests/run_all_tests.sh; \
	else \
		echo " 测试脚本不存在"; \
		exit 1; \
	fi

# 创建测试脚本
create-test-scripts:
	@mkdir -p integration_tests
	@echo "正在创建集成测试脚本..."

# 安装到用户本地bin目录
install: build
	@mkdir -p ~/.local/bin
	@cp $(BINDIR)/rich ~/.local/bin/rich
	@echo "✅ Rich程序已安装到 ~/.local/bin/rich"
	@echo ""
	@if echo $$PATH | grep -q "$(HOME)/.local/bin"; then \
		echo "🎯 PATH已配置，可直接使用：rich testhelloworld"; \
	else \
		echo "🔧 正在配置PATH环境变量..."; \
		echo 'export PATH="$$HOME/.local/bin:$$PATH"' >> ~/.bashrc; \
		echo "✅ PATH已添加到 ~/.bashrc"; \
		echo ""; \
		echo "🎯 使用方法："; \
		echo "  当前会话：export PATH=\"\$$HOME/.local/bin:\$$PATH\""; \
		echo "  新会话：直接使用 rich testhelloworld"; \
		echo "  或重新加载：source ~/.bashrc"; \
	fi


# 卸载
uninstall:
	@rm -f ~/.local/bin/rich
	@echo "Rich程序已从系统中卸载"

# 清理生成的文件
clean:
	rm -rf $(BUILDDIR) $(BINDIR)
	rm -f ./rich
	@echo "🧹 清理完成！"

# 帮助信息
help:
	@echo "Richman 大富翁程序 - 构建系统"
	@echo ""
	@echo "可用命令："
	@echo "  make build (或 make)  - 一键编译rich程序"
	@echo "  make test            - 一键运行集成测试"
	@echo "  make install         - 安装rich到系统（推荐）"
	@echo "  make uninstall       - 卸载rich程序"
	@echo "  make clean           - 清理生成的文件"
	@echo "  make help            - 显示此帮助信息"
	@echo ""
	@echo "程序使用："
	@echo "  ./rich testhelloworld     - 本地运行（需要./前缀）"
	@echo "  rich testhelloworld      - 安装后直接使用（推荐）"
	@echo "  rich help               - 显示程序帮助"