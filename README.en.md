# ACM / ICPC Algorithm Templates

[简体中文](./README.md) | [English](./README.en.md)

A C++ template collection for ACM/ICPC and competitive programming practice. The repository groups 59 code snippets by topic and includes both LaTeX manual sources and a prebuilt PDF for review, printing, and selective reuse.

[Open the prebuilt PDF manual](<./ACMTemplate by zhsl.pdf>)

> **Before you use the code**
>
> This is a historical personal contest-template collection, not a C++ library that can be linked or compiled as a whole. Most files are fragments intended to be embedded in a solution and rely on external macros, types, constants, and I/O. The repository also has no automated tests or CI. Adapt each snippet to the problem constraints and validate it with samples, edge cases, and randomized differential tests before submitting.

## What's included

| Directory | Count | Main topics |
| --- | ---: | --- |
| [`math/`](./math/) | 14 | Number-theory utilities, factorial factors, Lucas, matrices, Cantor expansion, Miller–Rabin, Pollard Rho, Möbius, Bernoulli, FFT, Gaussian elimination, segmented sieve, and more |
| [`datastructure/`](./datastructure/) | 10 | State hash table, LCA, merge sort and inversion counting, Sparse Table, partition tree, 3D LIS, dynamic LCIS, DLX, Splay, and 2D RMQ |
| [`string/`](./string/) | 6 | KMP, Trie, Manacher, suffix array with LCP/RMQ, string hashing, and Aho–Corasick |
| [`graph/`](./graph/) | 17 | 2-SAT, MST/second-best MST, Manhattan MST, directed MST, shortest paths, BCC/SCC, matching, network flow, global min-cut, and more |
| [`geometric/`](./geometric/) | 5 | 2D/3D convex hull, unit-circle coverage, closest pair of points, and point-in-polygon tests |
| [`dp/`](./dp/) | 2 | A simple plug-DP example and a canonical-state plug DP for counting Hamiltonian cycles |
| [`others/`](./others/) | 5 `.cpp` + 1 `.txt` | Contest headers, fast input, population-count methods, manual stack expansion, and a legacy performance note |

### Graph template index

- Connectivity: BCC, SCC, articulation points, and bridges.
- Spanning trees: Kruskal, second-best MST, Manhattan-distance MST, and Chu–Liu/Edmonds directed MST.
- Shortest paths: Dijkstra, SPFA, and A* K-shortest paths.
- Matching: bipartite matching, Kuhn–Munkres, and Edmonds' Blossom algorithm.
- Flow and cuts: Dinic, ISAP, HLPP, min-cost max-flow, and Stoer–Wagner global min-cut.

### Math template index

- Number-theory basics: GCD, extended GCD, modular inverse, CRT, linear sieve, and Euler's totient.
- Primes and factorization: segmented sieve, Miller–Rabin, and Pollard Rho.
- Combinatorics and sequences: factorial utilities, Lucas, Bernoulli, Möbius, and Cantor expansion.
- Algebra and computation: matrix multiplication/exponentiation, FFT and big-integer multiplication, Gaussian elimination, and modular exponentiation with a huge exponent.

## Key files

- [`ACMTemplate.tex`](./ACMTemplate.tex): the manual entry point, which includes each topic section.
- `math.tex`, `datastructure.tex`, `string.tex`, `graph.tex`, `geometric.tex`, and `DP.tex`: LaTeX indexes for the topic directories.
- [`ACMTemplate by zhsl.pdf`](<./ACMTemplate by zhsl.pdf>): the bundled 80-page, A4 prebuilt manual.
- [`others/header file.cpp`](<./others/header file.cpp>): a shorter example of shared includes, types, constants, and macros.
- [`others/header file-xiaodao.cpp`](<./others/header file-xiaodao.cpp>): a larger contest template with more compiler-specific and legacy constructs.

## Quick start

```bash
git clone https://github.com/zhsl/ACMICPCTemplate.git
cd ACMICPCTemplate
```

You can read the prebuilt PDF directly or browse the topic directories for a specific implementation. When integrating a snippet into a solution:

1. Copy only the algorithm needed for the current problem; do not try to compile the entire repository.
2. Add the required `#include` directives, `main()`, I/O, and shared definitions such as `N`, `LL`, `INF`, `mem`, `Min`, `Max`, and `pii`.
3. Some `.cpp` files under `math/` contain LaTeX markers such as `\subsection` and `verbatim`; remove those markers before compiling the code.
4. Recheck array capacities, indexing conventions, infinity values, integer overflow, recursion depth, and floating-point tolerances against the problem limits.
5. Compile with an environment close to the target judge, then test samples, edge cases, and randomized cases.

After adapting a snippet, a local compilation check might look like this:

```bash
g++ -std=c++17 -O2 -Wall -Wextra solution.cpp -o solution
```

Some legacy snippets use non-standard or platform-specific constructs and will need modernization first.

## Building the PDF from source

Based on [`ACMTemplate.tex`](./ACMTemplate.tex), the intended typesetting environment includes:

- XeLaTeX and `xeCJK`;
- the `SimSun` font, or a locally installed CJK font substituted in `\setCJKmainfont{SimSun}`;
- LaTeX packages including `graphicx`, `amsmath`, `xcolor`, `booktabs`, `geometry`, `verbatim`, `fancyhdr`, `hyperref`, and `minted`;
- Pygments and the `-shell-escape` option required for external `minted` commands.

After resolving the known source-assembly issues below, run XeLaTeX twice from the repository root to populate the table of contents and cross-references:

```bash
xelatex -shell-escape ACMTemplate.tex
xelatex -shell-escape ACMTemplate.tex
```

The current snapshot is **not guaranteed to rebuild the PDF without changes**. Several section indexes still use historical filenames:

| Path referenced by TeX | Actual repository path |
| --- | --- |
| `geometric/3d_convex_hull.cpp` | `geometric/3d convex hull.cpp` |
| `string/suffix_array.cpp` | `string/suffix array.cpp` |
| `string/String_Hash.cpp` | `string/String Hash.cpp` |
| `others/header_file.cpp` | `others/header file.cpp` |
| `DP/简单状压.cpp` | `dp/simple plug dp.cpp` |
| `DP/插头DP.cpp` | `dp/插头DP(哈密顿回路数).cpp` |

The source tree also mixes LaTeX-wrapped C++ with raw C++. Raw snippets need to be escaped through `minted`, `verbatim`, `listings`, or an equivalent mechanism before they can be included safely with `\input`. The bundled PDF is the most convenient manual entry point, but it may not match every current source file exactly.

## Compatibility and known limitations

- The code follows an older contest style, with global arrays, fixed capacities, short names, and mixed zero-/one-based indexing.
- Multiple snippets declare the same structs, globals, or functions and cannot be combined in one translation unit unchanged.
- Some files use platform-specific syntax such as `__int64`, `%I64d`, MSVC `#pragma comment`, 32-bit x86 assembly, or GNU `__typeof`.
- A few files contain a complete `main()` or problem-specific I/O; most provide only the core implementation.
- There is no unified build script, test suite, or CI, so users must verify correctness and applicability themselves.

## Contributing

When proposing an improvement:

- document the purpose, complexity, indexing, preconditions, and capacity requirements;
- prefer portable modern C++, and call out any required compiler extensions;
- include a minimal runnable example, reference problem, or testing method;
- update the relevant `.tex` index and both READMEs when adding or renaming a template.

## License

This repository currently contains no `LICENSE` or `COPYING` file and therefore declares no explicit code license. Confirm the necessary permission before copying, redistributing, or incorporating the code into another project; maintainers may add an explicit license separately.
