# 编译器
CC = gcc

# 编译器标志
CFLAGS = -Wall -g -Isrc

# 输出目录
BIN_DIR = bin
OBJ_DIR = obj

# 可执行文件
EXECUTABLE = $(BIN_DIR)/app

# 查找源文件
SOURCES = $(wildcard src/*.c)

# 把 src/xxx.c 转换为 obj/xxx.o
OBJECTS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# 默认目标
all: $(EXECUTABLE)

# 链接规则
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 确保 bin/ 和 obj/ 目录存在
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# 编译规则：src/xxx.c -> obj/xxx.o
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# 清理规则
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean
