# 学习用工作空间

这个工作空间用于组织和管理学习过程中的各种项目和代码。

## 目录结构

```
workspace/
├── kecheng/                    # 课程相关代码和资料 (课程)
│   ├── shujujiegou/           # 数据结构课程 (数据结构)
│   │   ├── lizi/              # 示例代码 (例子)
│   │   ├── zuoye/             # 作业项目 (作业)
│   │   │   └── 910/           # 顺序栈项目
│   │   └── bijinotes/         # 学习笔记 (笔记)
│   └── ...                    # 其他课程
├── gerenxiangmu/              # 个人开发项目 (个人项目)
│   ├── jinxingzhong/         # 进行中的项目 (进行中)
│   ├── yiwancheng/           # 已完成的项目 (已完成)
│   └── yigui/                # 已归档的项目 (已归档)
├── tools/                    # 工具脚本和实用程序
├── docs/                     # 通用文档和参考资料
├── sandbox/                  # 测试和实验代码
│   ├── work9m8/             # 实验性代码
│   ├── project test/        # 测试项目
│   └── src/                 # 其他源代码
├── goujianjiaoben/           # 构建脚本和自动化工具 (构建脚本)
├── WORKSPACE_STRUCTURE.md    # 工作空间结构说明
└── README.md                # 工作空间总体说明
```

## 使用说明

### kecheng/ (课程)
按课程分类存放学习材料，每个课程目录下包含:
- lizi/: 课程中的示例代码
- zuoye/: 课程作业项目
- bijinotes/: 学习笔记和参考资料

### gerenxiangmu/ (个人项目)
存放个人开发项目，按状态分类:
- jinxingzhong/: 正在开发的项目
- yiwancheng/: 已完成的项目
- yigui/: 已归档的旧项目

### tools/
存放各种工具脚本和实用程序，如构建脚本、代码生成器等。

### docs/
存放通用文档和参考资料，如编码规范、技术文档等。

### sandbox/
用于测试和实验的代码，不需要严格组织。

### goujianjiaoben/ (构建脚本)
存放构建脚本和自动化工具，如CMake配置、批处理脚本等。