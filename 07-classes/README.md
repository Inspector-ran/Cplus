# 从学生结构体到类与对象

[返回项目首页](../README.md) · [结构体起点](../05-structs/README.md) · [练习入口](../06-exercises/README.md)

适用：C11 对照、C++17、Visual Studio。一次只读、编译一个文件，再独立完成对应练习。

## 起点与来源

本主题接续[学生结构体示例](../05-structs/student.cpp)，按成员函数、访问控制、构造函数的顺序学习。

现有学生示例本身是 C++：成员为 `std::string name`、`int age`、`double score`，用 `const Student&` 传给外部打印函数。本套保留这些字段和 Chen / 19 / 88.5 数据。

C 对照参照 [C-language 学生示例](https://github.com/Inspector-ran/C-language/blob/main/05-structs/student.c)，将原来的 Lin / 18 / 92.5 改成相同数据，并增加外部打印函数，以便逐项比较。它是新编写的对照版，不是原文件的原样复制。

## 五个小步骤

所有示例均完整、可独立编译，都输出：

```text
Name: Chen
Age: 19
Score: 88.5
```

| 顺序 | 示例文件 | 只关注的新内容 | 观察任务 |
| --- | --- | --- | --- |
| 0 | [student_print.c](https://github.com/Inspector-ran/C-language/blob/main/05-structs/student_print.c) | C 结构体与外部函数 | 为什么调用时写 `&student`，函数内写 `student->name`？ |
| 1 | [student.cpp](../05-structs/student.cpp) | C++ 原示例：string、只读引用 | 找出与 C 版本不同的四处写法 |
| 2 | [student_member.cpp](student_member.cpp) | 把打印行为放进结构体 | 将调用从 `print_student(student)` 改为 `student.print()` |
| 3 | [student_private.cpp](student_private.cpp) | class、private、public | 临时尝试在 main 读取 `student.score_`，观察报错后撤销 |
| 4 | [student_constructor.cpp](student_constructor.cpp) | 构造函数、成员初始化列表 | 创建第二名学生，观察每个对象保存自己的数据 |

第 3 步暂时把默认值写在成员声明处，让你只关注访问权限；第 4 步再让每个对象通过构造函数接收不同的数据。

`Student` 是类型，`student` 是这个类型的一个对象。C++ 的结构体变量也可以称为对象，不是写了 class 才成为对象。

## C / C++ 对照

| 含义 | C11 | C++17 |
| --- | --- | --- |
| 保存姓名 | `char name[20];` | `std::string name;` |
| 声明学生 | `struct Student student = {"Chen", 19, 88.5};` | `Student student{"Chen", 19, 88.5};` |
| 外部函数只读访问 | `const struct Student* student` | `const Student& student` |
| 调用外部函数 | `print_student(&student);` | `print_student(student);` |
| 外部函数内访问成员 | `student->score` | `student.score` |
| 打印一位小数 | `printf("%.1f\n", student->score);` | `std::cout << std::fixed << std::setprecision(1) << student.score << '\n';` |
| 成员函数 | C 不支持直接定义成员函数 | `void print() const`，通过 `student.print()` 调用 |
| 访问控制 | 没有 C++ 的 public/private 语法 | 外部只能直接访问 public 成员 |

C 版数组总容量是 20 个字符，最多保存 19 个非终止字符及结尾的 `\0`；`std::string` 管理自身字符串存储。本套固定初始化姓名，不涉及输入缓冲区问题。

第 2 步的核心变化：

```cpp
struct Student {
    std::string name;
    int age;
    double score;

    void print() const {
        // 在这里直接使用 name、age、score。
    }
};
// 调用：student.print();
```

这里的 `const` 表示该函数不修改对象的普通成员，所以原例中的 `const Student student` 也能调用它。函数仍然可以向屏幕输出。

第 4 步的核心变化：

```cpp
Student(const std::string& name, int age, double score)
    : name_(name), age_(age), score_(score)
{
}
```

构造函数与类同名，没有返回类型。冒号之后是成员初始化列表：左边 `name_` 是成员，括号里的 `name` 是参数。成员按类内声明顺序初始化，这里也按相同顺序书写。结尾下划线只是命名习惯，不是私有权限的来源。

第 1 步的花括号是聚合初始化，第 4 步相同形状的花括号调用了构造函数。初学时先记住“创建对象时，数据就准备好”。基础构造示例假定参数有效；private 本身不会检查成绩范围。

## 三道独立练习

题目属于本仓库主题配套练习，初始不提供答案文件。每道新建独立 `.cpp`，不要在同一个项目里同时编译多个 main。先做完一题、核对结果，再继续下一题。

### 练习 1：两名学生各自打印（成员函数）

建议文件名：`06-student-members.cpp`。

从空白文件写一个 C++ `struct Student`，包含 name、age、score 和 `void print() const`。创建两个 const 对象 Chen / 19 / 88.5、Lin / 18 / 92.5，分别调用成员函数。main 中不直接逐项输出成员。

第一步：先写出结构体的三个成员声明，再考虑打印函数。

预期输出：

```text
Name: Chen
Age: 19
Score: 88.5
Name: Lin
Age: 18
Score: 92.5
```

验收：把 Lin 的初始化分数改为 60.0 后重新编译运行，确认只改变 Lin 的输出；能解释 `print_student(student)` 与 `student.print()` 的区别。打印格式与原例保持一致。

### 练习 2：受控修改成绩（封装）

建议文件名：`07-student-score.cpp`。

以第 3 步为基础，保留默认 Chen / 19 / 88.5。成员全部 private，在 public 部分新增：

```cpp
bool set_score(double new_score);
double get_score() const;
```

成绩在闭区间 [0, 100] 内才更新并返回 true；否则返回 false，原成绩不变。推荐用“同时满足大于等于 0、小于等于 100”来判定有效值。不要求处理文本输入或实现交互菜单。

第一步：先写下“什么时候允许赋值”的条件，再写赋值语句。

使用非 const 对象，按以下顺序调用并核对。每次只输出返回值（默认 1/0）和当前成绩，空格分隔，成绩保留一位小数：

| 调用 | 预期一行输出 |
| --- | --- |
| `set_score(95.0)` | `1 95.0` |
| `set_score(-1.0)` | `0 95.0` |
| `set_score(101.0)` | `0 95.0` |
| `set_score(0.0)` | `1 0.0` |
| `set_score(100.0)` | `1 100.0` |

验收：非法值不会先写进对象；main 不直接访问 score_；能解释为什么 get_score 后面可以加 const，而 set_score 不应加 const。

### 练习 3：创建时准备好数据（构造函数）

建议文件名：`08-student-constructors.cpp`。

在练习 2 的类上新增两个构造函数，保留打印和成绩检查接口：

```cpp
Student();
Student(const std::string& name, int age, double score);
```

无参数时得到 Unknown / 0 / 0.0；有参数时使用传入姓名与年龄，成绩有效则采用传入值，无效则设为 0.0。此题假定姓名与年龄已经有效，只练成绩规则。可先把 score_ 初始化为 0.0，再复用 set_score 检查，避免重复写两份范围规则。

第一步：先列出两个构造函数各自应给三个成员什么初值。

创建以下对象并逐个 print，仍采用原例的三行格式：

| 对象定义 | 预期数据（姓名 / 年龄 / 成绩） |
| --- | --- |
| `Student a{};` | Unknown / 0 / 0.0 |
| `Student b{"Chen", 19, 88.5};` | Chen / 19 / 88.5 |
| `Student c{"Lin", 18, 120.0};` | Lin / 18 / 0.0 |

补充边界：分别用 0.0、100.0、-1.0 构造，成绩应为 0.0、100.0、0.0。然后把 b 改成 90.0，确认 a 与 c 的数据不变。

验收：创建后即可调用 print；无需额外 init 函数；每个成员都有明确初值；能解释为什么定义带参数构造函数后，还要自己提供无参数构造函数才能写 `Student a{};`。

## 常见错误提醒

以下是本套练习的预防提示，不代表你已经犯过这些错误。

| 现象 | 原因与修正 |
| --- | --- |
| 换成 class 后 main 不能访问成员 | class 的成员默认 private，struct 默认 public；写清 public/private。C++ struct 也能有成员函数、构造函数和私有成员 |
| `const Student` 不能调用 print | 将只读成员函数声明为 `void print() const` |
| 修改成绩时报 const 错误 | 需要修改的对象不要声明成 const；set_score 不加末尾 const |
| 写 `void Student(...)` | 构造函数不写任何返回类型，连 void 也不写 |
| 写 `Student student();` 后不能访问对象 | 这是函数声明；创建默认对象用 `Student student{};` |
| 定义带参数构造函数后 `Student student{}` 报错 | 编译器不会再自动提供无参数构造函数；传入所需参数，或显式定义默认构造函数 |
| 认为 private 会自动拦截 120 分 | private 管访问权限，范围检查要自己写；构造和修改两个入口都要遵守规则 |
| 类定义后编译错误 | 检查最后是不是 `};`，分号不能省 |
| 成绩只显示 88 或位数不对 | 用 `std::fixed << std::setprecision(1)`；仅 setprecision(1) 不表示固定一位小数 |
| 链接时报 main 重复定义 | 每个示例是独立程序，只编译一个文件，或为各例创建独立项目 |
| C 文件中使用 string、引用或 class | C 文件用 C11 编译；C++ 文件用 C++17 编译，不能仅靠改扩展名完成迁移 |

## 文件归档

教学示例放在本目录，配套练习答案由学习者完成后保存到 `06-exercises`，不预先放入答案。

| 内容 | 仓库内路径 | 状态 |
| --- | --- | --- |
| 教学说明与三道练习 | `Cplus/07-classes/README.md` | 本页 |
| C11 外部打印函数对照 | `C-language/05-structs/student_print.c` | 跨仓库链接引用 |
| C++ 结构体起点 | `Cplus/05-structs/student.cpp` | 复用原例 |
| 成员函数示例 | `Cplus/07-classes/student_member.cpp` | 完整可运行 |
| 访问控制示例 | `Cplus/07-classes/student_private.cpp` | 完整可运行 |
| 构造函数示例 | `Cplus/07-classes/student_constructor.cpp` | 完整可运行 |
| 练习 1 自写答案 | `Cplus/06-exercises/06-student-members.cpp` | 完成后自行创建 |
| 练习 2 自写答案 | `Cplus/06-exercises/07-student-score.cpp` | 完成后自行创建 |
| 练习 3 自写答案 | `Cplus/06-exercises/08-student-constructors.cpp` | 完成后自行创建 |

以后若扩展为带菜单、文件保存的学生管理项目，再归 `C-practise`，本仓库只保留链接，不复制完整项目。

## Visual Studio 运行

图形界面：创建 C++ 空项目，添加一个 `.cpp` 文件；项目属性 → C/C++ → 语言 → C++ 语言标准，选择 ISO C++17。使用 Ctrl+F5 运行。切换示例时移除前一个源文件的项目引用，或将其“从生成中排除”；不要把五个示例一起参与生成。

C 对照例单独使用 `.c` 文件并选择 C11；若通过属性强制语言，C 为 /TC，C++ 为 /TP。

命令行：在 Developer PowerShell for Visual Studio 中进入 Cplus 仓库根目录。C++ 示例：

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 07-classes/student_constructor.cpp /Fobuild/student_constructor.obj /Febuild/student_constructor.exe
# 看到编译成功后再运行
.\build\student_constructor.exe
```

C 对照例：切换到 C-language 仓库根目录后执行。

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /TC /std:c11 /W4 /utf-8 05-structs/student_print.c /Fobuild/student_c.obj /Febuild/student_c.exe
.\build\student_c.exe
```

修改源文件名和输出名即可逐个运行其他示例。编译产物放 build，不上传 exe、obj。

## 示例核验

2026-10-21，使用本机 Visual Studio Community 2026 的 MSVC 14.50 工具集，在 x64 环境逐个编译运行上述五个示例。C 使用 C11，C++ 使用 C++17，均开启 `/W4 /WX /utf-8`；五个程序退出码均为 0，输出与本页预期逐行一致。核验使用命令行完成。三道练习只提供题目与验收标准，不代表学习者已经完成。

## 我的复盘

每题记录三句话：我第一步写了什么；运行输出是否符合预期；如果出错，具体是哪一行、为什么、如何修正。提交代码与运行结果后才能判断是否独立完成。
