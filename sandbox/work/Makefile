# 银行模拟系统 Makefile

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -std=c99 -g -O2 -pedantic
CFLAGS += -D_DEFAULT_SOURCE  # 用于兼容较新的Linux系统

# 包含目录
INCLUDES = -Iinclude

# 目标文件
TARGET = bin/bank_simulation

# 源文件目录
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# 源文件
SRCS = $(SRC_DIR)/bank_simulation.c $(SRC_DIR)/main.c

# 对象文件
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# 依赖文件
DEPS = $(OBJS:.o=.d)

# 默认目标
all: directories $(TARGET)

# 创建所需目录
directories:
	@mkdir -p $(BIN_DIR)

# 链接目标文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@
	@echo "Build successful: $@"

# 编译源文件（包含依赖关系）
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# 包含自动生成的依赖文件
-include $(DEPS)

# 清理生成文件
clean:
	rm -rf $(BIN_DIR) $(TARGET)

# 重新编译
rebuild: clean all

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 安装（示例）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# 显示变量（调试用）
print-vars:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"

.PHONY: all clean rebuild run install print-vars directories