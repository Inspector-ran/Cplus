# C++ 学习与考试基础

面向使用 Visual Studio 学习和备考 C++ 的初学者，按主题保存最小示例、学习笔记和配套练习。默认使用 **C++17**，示例保持基础写法；学校指定其他标准或题目限制时以学校要求为准。

**第一次使用请看[完整使用指南](USAGE.md)**：下载项目、Visual Studio 配置、逐个示例运行、练习方法、提交代码和常见问题。

## 三个仓库的分工

| 仓库 | 定位 | 放什么 |
| --- | --- | --- |
| [Cplus（本仓库）](https://github.com/Inspector-ran/Cplus) | C++ 主题学习与考试基础 | 标准 C++ 示例、语言特有概念、本仓库配套题 |
| [C-language](https://github.com/Inspector-ran/C-language) | C 语言基础 | C11 示例、C 的输入输出和配套题 |
| [C-practise](https://github.com/Inspector-ran/C-practise) | 作业与实践归档 | 教材章节作业、日常刷题和完整项目 |

相同概念可以在 C 与 C++ 中对照理解，但分别使用各自语言的源码与编译方式。已有作业只在 C-practise 保留一份，这里增加链接与错因总结，不复制整份项目。旧文件即使叫 .cpp，也需检查实际语法与依赖。

学校考 C++ 时，以本仓库为主要学习入口；C-language 可用于对照巩固，不必先把整个 C 仓库做完才开始 C++。

## 学习目录

| 顺序 | 主题 | 最小示例 | 重点 |
| --- | --- | --- | --- |
| 1 | [基础语法](01-basics/README.md) | [循环求和](01-basics/variables_and_loops.cpp) | 类型、cin/cout、分支与循环 |
| 2 | [数组](02-arrays/README.md) | [数组最大值](02-arrays/array_max.cpp) | 下标、容量、遍历和初值 |
| 3 | [函数](03-functions/README.md) | [函数重载](03-functions/overloaded_max.cpp) | 参数、返回值、重载 |
| 4 | [指针与引用](04-pointers/README.md) | [交换变量](04-pointers/swap.cpp) | 地址、解引用、引用对照 |
| 5 | [结构体](05-structs/README.md) | [学生信息](05-structs/student.cpp) | std::string、成员、只读引用 |
| 6 | [练习题](06-exercises/README.md) | 五道基础练习 + 三道类与对象练习 | 输入输出、边界测试、程序阅读 |
| 7 | [类与对象](07-classes/README.md) | [学生类](07-classes/student_constructor.cpp) | 成员函数、访问控制、构造函数、C/C++ 对照 |

建议先学 01～05，再完成 06 的基础题，随后学习 07 并完成新增三题。

## Visual Studio 快速运行

在 **Developer PowerShell for Visual Studio** 中进入仓库根目录：

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 01-basics/variables_and_loops.cpp /Fobuild/variables_and_loops.obj /Febuild/variables_and_loops.exe
```

确认编译成功后运行：

```powershell
.\build\variables_and_loops.exe
```

预期输出为 `15`。每次只编译一个示例，因为每个文件都有自己的 main。源码使用 .cpp；不要使用 C 仓库的 /TC 或 /std:c11 参数。

已配置 g++ 时：

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic 01-basics/variables_and_loops.cpp -o build/variables_and_loops.exe
.\build\variables_and_loops.exe
```

## 示例输出

| 文件 | 预期输出 |
| --- | --- |
| variables_and_loops.cpp | 15 |
| array_max.cpp | 9 |
| overloaded_max.cpp | Int max: 7；Double max: 3.5（分两行） |
| swap.cpp | Before: 3, 7；After: 7, 3（分两行） |
| student.cpp | Name: Chen；Age: 19；Score: 88.5（分三行） |

## 学习方法与扩展

先读说明并预测输出，再编译、修改数据、独立做题，最后记录错因。每个主题 README 留有“我的复盘”。

示例代码是起点；练习区初始只提供题目，答案由自己创建。日常编译产物统一放 build，不上传 exe 和 obj。

已增加类与对象、构造函数的渐进示例与配套练习。后续根据课程安排增加字符串、继承、多态、文件流和 STL。当前骨架优先覆盖基础知识，不代表已经覆盖学校整门 C++ 考试大纲。
