# C++ 完整使用指南

本指南面向使用 **Visual Studio** 学习和备考 C++ 的初学者。目标是让你可以独立下载项目、编译示例、完成练习、记录错因，并把自己的进展保存到 GitHub。

默认使用 C++17。学校使用 Visual Studio 已确认，但具体试卷范围和语言标准尚未提供；如果老师要求不同标准、禁用部分库或规定输入输出形式，以课程要求为准。

[返回项目首页](README.md) · [完整练习题](06-exercises/README.md)

## 1. 第一次使用：先跑通，再学习

1. 下载或克隆项目，找到包含 `01-basics` 和 `README.md` 的根目录。
2. 从 Visual Studio 打开 Developer PowerShell，并切换到这个目录。
3. 编译并运行基础示例，确认输出 `15`。
4. 把循环上限改为 10，保存、重新编译，再运行，确认输出 `55`。
5. 阅读基础语法说明，创建自己的第一道练习 `06-exercises/01-count-signs.cpp`。
6. 用题目样例和边界数据测试，再按第 9 节保存进展。

学校考 C++，可以直接从本仓库开始；遇到 C 与 C++ 的共同概念，再按需回看 C-language。不需要先完成所有 C 练习。

## 2. 仓库结构与语言区别

```text
Cplus/
├── README.md
├── USAGE.md
├── .gitignore
├── 01-basics/variables_and_loops.cpp
├── 02-arrays/array_max.cpp
├── 03-functions/overloaded_max.cpp
├── 04-pointers/swap.cpp
├── 05-structs/student.cpp
├── 06-exercises/README.md
└── 07-classes/README.md
```

基础主题和新增类与对象主题各自有 README；07-classes 下还包含三个独立示例。运行时生成的 `build` 不存入仓库。所有示例都是独立程序，每次只编译一个带 main 的源文件。

### C 和 C++ 对照

| 内容 | C-language | C- |
| --- | --- | --- |
| 源码后缀 | .c | .cpp |
| 编译标准 | C11 | C++17 |
| Visual Studio 语言参数 | /TC | /TP |
| 起步输入输出 | printf / scanf | std::cout / std::cin |
| 文本示例 | char 数组 | std::string |
| 修改外部变量 | 可通过指针 | 可通过指针或引用 |
| 函数重载 | 不支持 C++ 式函数重载 | 支持不同参数列表的同名函数 |
| 声明结构体对象 | 常用 struct Student | 定义后可直接使用 Student |

共同的循环、数组、函数与指针概念可以迁移，但 C++ 不只是“给 C 文件换个后缀”。例如引用、重载、std::string 的写法需要单独理解。

## 3. 获取项目并找到根目录

### 下载 ZIP

打开 [C++ 仓库](https://github.com/Inspector-ran/Cplus) GitHub 页面，在 Code 菜单中选择 Download ZIP，完整解压。GitHub 解压目录通常叫 `Cplus-main`；拿到本次交付的源码包时，目录叫 `Cplus`。两者都可以使用。

找到包含 `README.md`、`USAGE.md` 和 `01-basics` 的那一层。不要直接在压缩包内编辑或运行。

### 使用 Git

在准备存放项目的父目录执行：

```powershell
git clone https://github.com/Inspector-ran/Cplus.git
Set-Location Cplus
```

已经有工作副本时不要重复克隆。用 ZIP 获取项目不需要安装 Git，但后续不会自动同步网页上的变化。

### 切换终端目录

复制资源管理器中项目根目录的地址，替换下面引号里的文字：

```powershell
Set-Location -LiteralPath "替换为你电脑上的仓库文件夹完整路径"
Get-Location
Get-ChildItem
```

后文所有编译命令均从仓库根目录执行。

## 4. Visual Studio 的两种运行方式

### 4.1 首选：开发者终端单文件编译

电脑已经安装 Visual Studio C/C++ 工具时可以直接使用。若缺少组件，在 Visual Studio Installer 中检查“使用 C++ 的桌面开发”及 Windows SDK。

从 Visual Studio 菜单选择 **工具 → 命令行 → Developer PowerShell**；或者在 Windows 开始菜单搜索 Developer PowerShell。该终端会初始化编译器环境。[微软开发者终端说明](https://learn.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell?view=visualstudio)

进入仓库根目录，依次执行：

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 01-basics/variables_and_loops.cpp /Fobuild/variables_and_loops.obj /Febuild/variables_and_loops.exe
```

检查编译命令退出码：

```powershell
$LASTEXITCODE
```

为 0 且没有编译错误时，再运行：

```powershell
.\build\variables_and_loops.exe
```

预期：

```text
15
```

| 参数 | 含义 |
| --- | --- |
| /TP | 按 C++ 编译 |
| /std:c++17 | 选择 C++17 标准 |
| /EHsc | 使用标准 C++ 异常处理模式 |
| /W4 | 显示较详细的警告 |
| /utf-8 | 按 UTF-8 处理源码与执行字符集 |
| /Fo...obj | 指定中间目标文件 |
| /Fe...exe | 指定可执行文件 |

不要混用 C 项目的 `/TC /std:c11`。标准选项可查阅[微软语言标准设置说明](https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version)。

### 4.2 使用 Visual Studio 项目界面

如果老师上课习惯使用解决方案和项目，可以：

1. 创建 C++ 类型的“空项目”。
2. 添加当前要学习的一个已有 `.cpp` 文件。
3. 在项目属性的 C/C++ 设置中选择 ISO C++17 语言标准；确认没有强制按 C 编译。
4. 将该项目设为启动项目，然后生成并运行。
5. 切换到另一个示例时，排除或移除原来的入口文件，使参与生成的源码中只有一个 main。

菜单名称可能随界面语言略有不同；关键是选择 C++17，并且只生成当前示例。仓库本身不要求创建或提交 .sln 工程文件。

想逐步观察程序，可在语句左侧设置断点后启动调试，观察当前行和变量窗口。每次先预测变量会如何变化，再单步执行确认。

### 4.3 一次修改的完整流程

打开 `01-basics/variables_and_loops.cpp`，把 `limit = 5` 改为 `limit = 10`：

**Ctrl+S 保存 → 重新编译 → 检查编译成功 → 运行 → 确认 55。**

仅保存不会生成新程序；编译失败后运行旧 exe 也不能证明新代码正确。完成实验后可以恢复上限 5，让示例继续与文档对应。

## 5. 五个基础主题怎样学

### 5.1 基础语法

运行命令见第 4 节。重点看初始化、循环条件、累加和 `std::cout`。

试着回答：sum 为什么从 0 开始？为什么条件是 <=？输出末尾的 `'\n'` 起什么作用？如果读取输入失败，为什么不能继续计算？

### 5.2 数组

```powershell
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 02-arrays/array_max.cpp /Fobuild/array_max.obj /Febuild/array_max.exe
.\build\array_max.exe
```

编译成功后执行，预期输出 `9`。把数组换成 `{-4, -1, -9}`，结果应为 `-1`。

注意最大值用第一个元素初始化，而不是 0。区分“数组容量”和“有效元素个数”；下标不能等于元素个数。起步阶段使用固定容量数组，不使用 `int values[n]` 这样的运行时长度数组声明。

### 5.3 函数

```powershell
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 03-functions/overloaded_max.cpp /Fobuild/overloaded_max.obj /Febuild/overloaded_max.exe
.\build\overloaded_max.exe
```

预期：

```text
Int max: 7
Double max: 3.5
```

同名函数有两套参数类型，编译器根据实参选择。试着分别改整数和浮点数的值；不要用“只改返回类型”的方式定义重载。对本例混合传入一个 int 和一个 double 可能造成调用歧义，初学时先保持参数类型一致。

### 5.4 指针与引用

```powershell
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 04-pointers/swap.cpp /Fobuild/swap.obj /Febuild/swap.exe
.\build\swap.exe
```

预期：

```text
Before: 3, 7
After: 7, 3
```

先理解“通过指针访问另一个变量”，再对照 C++ 引用。指针可以保存地址；引用是已有对象的别名。空指针使用 `nullptr` 表示，不能解引用。此阶段不需要用 new/delete 动态分配内存。

延伸：把交换函数自行改写成两个 `int&` 参数，比较调用时是否需要传入 `&first`。指针版本保留在原示例，另写实验文件或在笔记中记录差异。

### 5.5 结构体

```powershell
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 05-structs/student.cpp /Fobuild/student.obj /Febuild/student.exe
.\build\student.exe
```

预期：

```text
Name: Chen
Age: 19
Score: 88.5
```

重点看 `std::string`、`Student`、`const Student&` 和成员访问。打印函数使用只读引用，不复制整个结构体，也不能通过该参数修改它。

`std::fixed` 配合 `std::setprecision(1)` 才是保留一位小数；单独使用 setprecision 的含义不同。不要把“类与对象、继承、多态”都塞进这个起步示例，它们适合后续按课程单独学习。

学完结构体后，继续阅读[类与对象](07-classes/README.md)，按成员函数 → 访问控制 → 构造函数的顺序学习。新主题含 C/C++ 对照、三个可运行示例及三道独立练习。

## 6. 独立完成基础与类对象练习

[练习题完整说明](06-exercises/README.md)是各题要求的入口。本节先介绍 01～05 基础题；06～08 类与对象题见[新增三题](07-classes/README.md#三道独立练习)，使用固定数据，不需要键盘输入。

| 题号 | 文件名（放在 06-exercises） | 核心目标 | 必测情况 |
| --- | --- | --- | --- |
| 01 | 01-count-signs.cpp | 循环与分支统计正、负、零 | 全零、全正、全负、混合 |
| 02 | 02-array-min-max.cpp | 数组最小值与最大值 | 单元素、全负、重复值 |
| 03 | 03-is-prime.cpp | bool 函数判断素数 | 0、1、2、9、17、25 |
| 04 | 04-increment-array.cpp | 通过指针原地修改数组 | 单元素、负数、零、重复值 |
| 05 | 05-top-student.cpp | 结构体数组查找最高分 | 一名学生、并列、0 分与 100 分 |

这些答案文件还没有创建；请自己建立。下面是入口框架，不是完整解答：

```cpp
#include <iostream>

int main()
{
    // TODO: read input, validate it, compute, then print.
    return 0;
}
```

做题顺序：读题 → 手算样例 → 写步骤 → 实现输入和检查 → 实现计算 → 输出 → 编译 → 测试。

输入失败可以通过 `if (!(std::cin >> value))` 检测。范围检查仍需自己写；读取成功不等于数值符合题意。题目要求什么就输出什么，不额外输出“请输入”等提示。

第一题完成后编译：

```powershell
cl /nologo /TP /std:c++17 /EHsc /W4 /utf-8 06-exercises/01-count-signs.cpp /Fobuild/01-count-signs.obj /Febuild/01-count-signs.exe
```

成功后执行：

```powershell
.\build\01-count-signs.exe
```

输入 `-2 0 3 5 -1` 并回车，预期输出 `2 2 1`。也可以用管道提供样例：

```powershell
"-2 0 3 5 -1" | .\build\01-count-signs.exe
```

每次修改后重新编译再测试。不要只测题目给的一个样例：例如全零、全部为负的输入往往能发现初始化或条件分支错误。

本页不直接提供题目答案，目的是让你练习独立编码。遇到问题时先对照主题示例和边界提示，再记录错误原因。

## 7. 如果以后使用 g++ 或 clang++

目前学校用 Visual Studio，可跳过本节。

Windows PowerShell，已安装并配置 g++ 的情况下：

```powershell
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -Wall -Wextra -Wpedantic 01-basics/variables_and_loops.cpp -o build/variables_and_loops.exe
.\build\variables_and_loops.exe
```

使用 Clang 时将 `g++` 换成 `clang++`。C++ 程序使用 C++ 驱动程序，避免直接套用 C 的 gcc 命令而遗漏 C++ 标准库链接。

Linux/macOS：

```sh
mkdir -p build
c++ -std=c++17 -Wall -Wextra -Wpedantic 01-basics/variables_and_loops.cpp -o build/variables_and_loops
./build/variables_and_loops
```

这里 c++ 应为 g++ 或 clang++ 对应的 C++ 编译器。换编译器后仍需按题目测试，不只看能否生成文件。

## 8. 每天怎样用这个仓库

一次学习可以控制在 40～60 分钟，不必一天学完一个主题。

| 环节 | 建议时间 | 具体做什么 |
| --- | --- | --- |
| 回顾 | 5 分钟 | 不看答案，解释上次错在哪里 |
| 阅读 | 10 分钟 | 读主题 README 和最小示例，先写下预测输出 |
| 实验 | 10 分钟 | 运行示例，只修改一个条件或一组数据，再解释变化 |
| 做题 | 15～25 分钟 | 独立实现一道配套题，测普通值和边界值 |
| 复盘 | 5 分钟 | 保存代码，记录错因，提交今天的进展 |

“看懂”之后，还要能不看示例重新写出关键部分。遇到编译错误时，优先处理第一条错误，后面的错误可能只是连带结果。

### 复盘模板

把下面内容复制到对应主题 README 的“我的复盘”下面，再填写：

```markdown
### YYYY-MM-DD：本次练习

- 主题 / 题号：
- 我原本以为：
- 实际发生：
- 原因：
- 修改方法：
- 测试输入 → 预期输出 → 实际输出：
- 下次复习时要能回答的问题：
```

一条有用的记录可以是：“循环条件写成 i <= count，访问了数组末尾之后的位置；改成 i < count，并用单元素数组重新验证。”不要只写“数组越界，下次注意”。

## 9. 怎样保存到 GitHub

**本地保存文件、Git 提交、上传 GitHub 是三个不同动作。** 按下 Ctrl+S 只更新电脑上的文件；完成 commit 才形成版本记录；push 后网页才会显示新版本。

### 方法 A：暂时不用 Git 命令

适合通过 ZIP 下载、还没学 Git 的阶段。

1. 先在电脑上编译运行，确认文件已经保存。
2. 打开自己的仓库，进入目标目录，例如 `06-exercises`。
3. 选择 **Add file → Upload files**，上传这次写好的源码文件。
4. 检查文件名、目录及差异，填写说明，例如“完成练习 01，补充边界测试”，再提交。
5. 改笔记可在对应 README 页面使用编辑按钮；保存前同样检查内容。
6. 上传后刷新页面，确认新文件确实出现在目标目录。

只上传本次修改的源码和笔记，不要上传整个下载包或编译生成的文件。网页上传不会自动应用你电脑上的 `.gitignore`，需要自己选对文件。网页文件上传流程可参阅 [GitHub 官方说明](https://docs.github.com/en/repositories/working-with-files/managing-files/adding-a-file-to-a-repository)。

ZIP 解压目录通常没有 Git 历史，不能直接在那里执行 `git pull` 或 `git push`。以后改用 Git 时，在新的空位置克隆仓库，再将自己尚未上传的源码逐个核对并放进去。

### 方法 B：使用 Git 持续练习

只适用于通过 `git clone` 获取的工作副本。下面命令在仓库根目录执行，且默认你在 `main` 分支。

学习开始前：

```powershell
git status
git branch --show-current
git pull --ff-only
```

先看 `git status`：有尚未保存到版本记录的修改时，应先整理并提交，不要直接覆盖文件。第三条命令在本地可以直接跟上远程进度时更新；双方都有独立提交时会停止。[Git 官方文档](https://git-scm.com/docs/git-pull)说明了这一行为。

完成一道题后，按实际文件名执行，例如：

```powershell
git status
git diff
git add 06-exercises/01-count-signs.cpp
git diff --cached
git commit -m "practice: complete exercise 01 with boundary checks"
git push origin main
```

这里以第 01 题为例；提交其他题目时，换成实际文件名。新文件在暂存前不一定出现在 `git diff` 中，`git status` 和 `git diff --cached` 可以帮助检查。笔记改了，也要按实际路径添加。

每条命令执行成功后再继续。上传后打开 GitHub 核对最新提交；`git push` 才把本地提交送到远程仓库。[Git 官方说明](https://git-scm.com/docs/git-push)

第一次提交若提示缺少姓名或邮箱，在当前仓库内设置：

```powershell
git config user.name "Inspector-ran"
git config user.email "替换为你的GitHub提交邮箱"
```

第二条需替换为真实提交邮箱，也可使用 GitHub 邮箱设置中提供的 noreply 地址。这是提交署名配置，不是登录操作。

如果 push 要求登录，使用安装的 Git 凭据管理器提供的 GitHub 登录流程。若提示远程有新提交，先查看状态；不要使用强制推送来掩盖差异。无法快进或出现冲突时，保留当前文件和完整报错，再核对本地、远程各改了什么。

## 10. 常见问题排查

| 现象 | 常见原因 | 下一步 |
| --- | --- | --- |
| 找不到 cl | 打开的是普通终端，或没有安装编译工具 | 从 Visual Studio 的“工具 → 命令行”打开 Developer PowerShell；必要时在安装器检查桌面 C++ 工作负载 |
| 找不到源文件 / C1083 | 当前目录不对、文件名拼错、源码尚未创建 | 用 Get-Location 和 Get-ChildItem 检查位置、路径和扩展名 |
| 找不到 stdio.h 或 iostream | 开发环境未初始化，或组件安装不完整 | 重新打开开发者终端；再检查编译器与 Windows SDK 组件 |
| LNK2005 / main 已定义 | 一次链接了多个带 main 的源码文件 | 每次只编译一个示例；IDE 项目中只保留一个入口 |
| 编译后找不到 exe | 编译失败，或输出路径和运行路径不一致 | 先看编译错误和退出码，再核对 build 下的文件名 |
| 改了代码但输出没变 | 忘记保存、忘记重新编译，或运行了旧程序 | Ctrl+S → 重新编译 → 确认成功 → 运行对应 exe |
| 窗口一闪而过 | 直接双击了程序 | 从终端运行；无需为了停住窗口加入 system("pause") |
| 运行后没反应 | 程序正在等待输入，或循环未结束 | 按题目输入数据并回车；本仓库教学示例及 06～08 练习不需要输入；01～05 练习按各题要求输入 |
| 数组结果混乱 / 程序崩溃 | 越界、未初始化、无效指针等 | 检查下标范围、初始值、指针指向和循环边界 |
| 中文显示异常 | 源码保存编码与终端显示设置不一致 | 使用 UTF-8 保存源码；先用项目中的英文输出验证程序逻辑 |
| 文件其实叫 xxx.c.txt 或 xxx.cpp.txt | 编辑器追加了文本扩展名 | 在资源管理器显示文件扩展名，保存时选择所有文件并核对后缀 |
| GitHub 看不到修改 | 只在本地保存，或只 commit 没有 push | 查看 git status、push 结果及网页当前分支 |
| not a git repository | 在 ZIP 解压目录或错误目录执行 Git | 换到克隆的仓库；ZIP 用户可先使用网页上传 |
| push 被拒绝 | 登录、写权限、分支规则或远程更新问题 | 阅读具体错误，保留本地修改后处理对应原因 |

要定位问题，可以准备：编译器名称、完整命令、完整报错、相关源码、输入数据、预期输出和实际输出。比“运行不了”的信息更有用。

## 11. 考前怎样复习

按学校题型调整下面的方法，不把运行通过当成唯一目标。

- **程序阅读题**：先手算变量变化和输出，再编译验证；能解释每轮循环及函数调用。
- **程序填空题**：重点检查循环边界、返回值、数组下标、指针访问和成员访问。
- **程序改错题**：区分编译错误、运行时错误与逻辑错误；写出触发错误的最小输入。
- **编程题**：先写输入输出要求，再写步骤，最后写代码；至少验证一个普通情况和两个边界情况。

每个主题能做到“讲清概念、手算输出、独立实现、测试边界”，再进入下一主题。遇到学校试卷中特有的输入输出格式，以试卷要求为准。

## 12. 文件归档与后续扩展

本仓库的主题说明、示例和配套题保留在这里。教材题、平台刷题、课程大作业以及完整小游戏继续放入 [C-practise](https://github.com/Inspector-ran/C-practise)。

判断一个新文件放哪里：

| 新内容 | 放置位置 |
| --- | --- |
| 对某个知识点的总结 | 对应主题 README 的复盘部分 |
| 一个概念的短小示例 | 对应主题目录，使用有意义的英文文件名 |
| 本仓库指定的练习答案 | 06-exercises，按题号命名 |
| 学校教材原题或完整作业 | C-practise，可在这里建立链接 |
| 编译生成的 exe、obj 或缓存 | build 或 IDE 输出目录，不作为学习源码上传 |

旧项目的 `.cpp` 后缀不代表它已经覆盖了 C++ 的全部知识，也不保证使用标准 C++ 写法。先阅读依赖与语法，不要仅靠改扩展名迁移代码。

以后增加主题时，一次增加一个目录，配套写清学习目标、最小示例、预期输出和练习入口。避免预先创建大量没有内容的文件夹。
