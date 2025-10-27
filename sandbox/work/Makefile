# 银行模拟系统 Makefile

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -std=c99 -g

# 目标文件
TARGET = bank_simulation

# 源文件
SRCS = BankSimulation.c main_bank.c

# 头文件
HEADERS = BankSimulation.h

# 目标文件
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 编译源文件
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成文件
clean:
	rm -f $(OBJS) $(TARGET)

# 重新编译
rebuild: clean all

# 运行程序
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run