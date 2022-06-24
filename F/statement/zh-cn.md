{{ self.title() }}

{{ s('description') }}

给出排列 $a_1,\dots,a_n$，你需要维护序列 $b_1,\dots,b_n$，初值为0。

共 $m$ 次操作：

修改操作：给出 $l,r$，对每个 $(i,j)$ 满足 $l\le i\le j\le r,\;a_i\le a_j$，将 $b_j$ 增加1；

查询操作：给出 $x$，查 $b_x$。

{{ s('input format') }}

{{ self.input_file() }}

第一行两个整数 $n,m$；

第二行 $n$ 个整数依次表示 $a_1,\dots,a_n$；

接下来 $m$ 行，每行 $1,l,r$ 或 $2,x$ 表示修改操作或查询操作。

$1\le n,m\le 2\times 10^5$；

$1\le a_i\le n$，$a_i$ 互不相同；

$1\le l\le r\le n$；

$1\le x\le n$；

输入的所有数值为整数。

{{ s('output format') }}

{{ self.output_file() }}

对每个查询操作，输出一行，包含一个整数，表示答案。

{{ s('sample') }}

{{ self.sample_text() }}

