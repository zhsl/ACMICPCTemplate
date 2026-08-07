# ACM / ICPC 算法模板

[简体中文](./README.md) | [English](./README.en.md)

一套面向 ACM/ICPC 与算法竞赛训练的 C++ 模板集合。仓库按专题整理了 59 个代码片段，并提供 LaTeX 手册源码与预编译 PDF，便于赛前复习、打印和按需复制。

[打开预编译 PDF 手册](<./ACMTemplate by zhsl.pdf>)

> **使用前须知**
>
> 这是一个历史性的个人竞赛模板集，不是可直接链接或整体编译的 C++ 库。多数文件是需要嵌入解题程序的片段，依赖外部宏、类型、常量和输入输出；仓库也没有自动化测试或 CI。请根据题目约束完成适配，并在提交前使用样例、边界数据和随机对拍充分验证。

## 内容概览

| 目录 | 数量 | 主要内容 |
| --- | ---: | --- |
| [`math/`](./math/) | 14 | 基础数论、阶乘因子、Lucas、矩阵运算、康托展开、Miller–Rabin、Pollard Rho、Möbius、Bernoulli、FFT、高斯消元、区间筛等 |
| [`datastructure/`](./datastructure/) | 10 | 状态哈希、LCA、归并排序与逆序对、Sparse Table、划分树、三维 LIS、动态 LCIS、DLX、Splay、二维 RMQ |
| [`string/`](./string/) | 6 | KMP、Trie、Manacher、后缀数组与 LCP/RMQ、字符串哈希、Aho–Corasick |
| [`graph/`](./graph/) | 17 | 2-SAT、MST/次小 MST、曼哈顿 MST、最小树形图、最短路、BCC/SCC、二分图匹配、一般图匹配、网络流、全局最小割等 |
| [`geometric/`](./geometric/) | 5 | 二维/三维凸包、单位圆覆盖、平面最近点对、点与多边形关系 |
| [`dp/`](./dp/) | 2 | 简单插头 DP 示例、用最小表示法统计 Hamilton 回路的插头 DP |
| [`others/`](./others/) | 5 个 `.cpp` + 1 个 `.txt` | 竞赛头文件、快速输入、二进制位计数、手工扩栈及旧平台效率笔记 |

### 图论模板索引

- 图的连通性：BCC、SCC、割点、桥。
- 生成树：Kruskal、次小生成树、曼哈顿距离 MST、朱刘/Edmonds 最小树形图。
- 最短路：Dijkstra、SPFA、A* K 短路。
- 匹配：二分图匹配、Kuhn–Munkres、Edmonds Blossom 带花树。
- 网络流与割：Dinic、ISAP、HLPP、最小费用最大流、Stoer–Wagner 全局最小割。

### 数学模板索引

- 数论基础：GCD、扩展 GCD、逆元、中国剩余定理、线性筛、欧拉函数。
- 素数与分解：区间筛、Miller–Rabin、Pollard Rho。
- 组合与序列：阶乘相关、Lucas、Bernoulli、Möbius、康托展开。
- 代数与计算：矩阵乘法/快速幂、FFT 与大整数乘法、高斯消元、超大指数模幂。

## 关键文件

- [`ACMTemplate.tex`](./ACMTemplate.tex)：手册主文件，依次引入各专题章节。
- `math.tex`、`datastructure.tex`、`string.tex`、`graph.tex`、`geometric.tex`、`DP.tex`：各专题的 LaTeX 索引。
- [`ACMTemplate by zhsl.pdf`](<./ACMTemplate by zhsl.pdf>)：仓库附带的 80 页 A4 预编译手册。
- [`others/header file.cpp`](<./others/header file.cpp>)：较短的公共头文件与宏定义示例。
- [`others/header file-xiaodao.cpp`](<./others/header file-xiaodao.cpp>)：更完整、但也更依赖编译器和旧式写法的竞赛模板。

## 快速开始

```bash
git clone https://github.com/zhsl/ACMICPCTemplate.git
cd ACMICPCTemplate
```

可以直接阅读预编译 PDF，也可以进入专题目录查找所需实现。将片段用于题解时，建议按以下顺序处理：

1. 只复制当前题目需要的算法，不要尝试把整个仓库一起编译。
2. 补齐 `#include`、`main()`、输入输出，以及 `N`、`LL`、`INF`、`mem`、`Min`、`Max`、`pii` 等公共定义。
3. `math/` 中部分 `.cpp` 混有 `\subsection`、`verbatim` 等 LaTeX 标记；复制到解题代码前需要移除这些标记。
4. 根据数据范围检查数组容量、下标约定、无穷大取值、整数溢出、递归深度和精度误差。
5. 使用目标 OJ 相同或相近的编译器进行样例、边界和随机测试。

片段完成适配后，可以使用类似下面的命令做本地编译检查：

```bash
g++ -std=c++17 -O2 -Wall -Wextra solution.cpp -o solution
```

部分旧代码包含非标准或平台相关写法，可能需要先改成现代编译器支持的形式。

## 从源码生成 PDF

根据 [`ACMTemplate.tex`](./ACMTemplate.tex)，预期的排版环境包括：

- XeLaTeX 与 `xeCJK`；
- `SimSun` 字体，或将 `\setCJKmainfont{SimSun}` 改为本机已有的中文字体；
- `graphicx`、`amsmath`、`xcolor`、`booktabs`、`geometry`、`verbatim`、`fancyhdr`、`hyperref`、`minted` 等 LaTeX 包；
- Pygments，以及允许 `minted` 调用外部命令的 `-shell-escape` 选项。

修正下述已知的源码组装问题后，在仓库根目录运行两次 XeLaTeX，以生成目录和交叉引用：

```bash
xelatex -shell-escape ACMTemplate.tex
xelatex -shell-escape ACMTemplate.tex
```

当前快照**不能保证未经修改即可重新生成 PDF**。章节索引保留了若干旧文件名：

| TeX 中的引用 | 仓库中的实际路径 |
| --- | --- |
| `geometric/3d_convex_hull.cpp` | `geometric/3d convex hull.cpp` |
| `string/suffix_array.cpp` | `string/suffix array.cpp` |
| `string/String_Hash.cpp` | `string/String Hash.cpp` |
| `others/header_file.cpp` | `others/header file.cpp` |
| `DP/简单状压.cpp` | `dp/simple plug dp.cpp` |
| `DP/插头DP.cpp` | `dp/插头DP(哈密顿回路数).cpp` |

此外，源码同时存在“带 LaTeX 包装的 C++”和“原始 C++”两种格式；直接用 `\input` 引入原始代码时，还需要使用 `minted`、`verbatim`、`listings` 或等价方式进行转义。仓库中的预编译 PDF 可作为当前最方便的手册入口，但它不一定与所有现有源码完全同步。

## 兼容性与已知限制

- 代码主要采用早期竞赛风格，常见全局数组、固定容量、短变量名和 0/1 起始下标混用。
- 多个片段会声明同名结构体、全局变量或函数，不能直接合并到同一翻译单元。
- 部分文件使用 `__int64`、`%I64d`、MSVC `#pragma comment`、32 位 x86 汇编或 GNU `__typeof` 等平台相关语法。
- 少量文件包含完整 `main()` 或特定题目的输入输出；其余大多只提供核心实现。
- 仓库没有统一构建脚本、测试套件或 CI，模板正确性和适用范围需要使用者自行确认。

## 参与维护

如果要提交改进，建议：

- 写清算法用途、复杂度、下标约定、前置条件和容量要求；
- 尽量使用可移植的现代 C++，必须依赖特定编译器时明确注明；
- 附带最小可运行示例、参考题目或测试方法；
- 修改文件名或新增模板时，同步更新相应的 `.tex` 索引及中英文 README。

## 许可证

仓库目前没有提供 `LICENSE` 或 `COPYING` 文件，因此没有声明明确的代码使用许可证。复制、再发布或用于其他项目之前，请先确认相应授权；维护者也可以补充一份明确的许可证。
