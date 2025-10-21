# 顺序栈演示程序

这是一个基于C++实现的顺序栈数据结构演示程序，展示了栈的基本操作和两个实际应用：
1. 数值进制转换（十进制转八进制）
2. 括号匹配检查

## 项目结构

```
.
├── CMakeLists.txt          # CMake构建配置文件
├── README.md               # 项目说明文档
├── .gitignore              # Git忽略文件配置
├── main.cpp                # 程序入口和测试代码
├── SeqStack.h              # 顺序栈数据结构定义和函数声明
└── SeqStack.cpp            # 顺序栈函数实现
```

## 构建说明

### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```

### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
```

## 运行程序

构建完成后，可执行文件位于:
- Windows: `build/bin/Debug/SeqStackDemo.exe`
- Linux/macOS: `build/bin/SeqStackDemo`

## 功能说明

### 数值转换
将十进制整数转换为八进制表示。

### 括号匹配
检查表达式中的括号是否正确匹配，支持 `()`, `[]`, `{}` 三种括号类型。