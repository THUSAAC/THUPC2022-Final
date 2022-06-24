{{ self.title() }}

{{ s('description') }}

给序列 $a_1,\dots,a_n$ 和排列 $b_1,\dots,b_n$，共有 $m$ 次操作：

修改操作：给定 $x,y$，将 $a_x$ 改为 $y$；

查询操作：给定 $l,r,x$，查区间 $[l,r]$ 内最长的子区间 $[l',r']$（即满足 $l\le l'\le r'\le r$），使得对 $l'\le i<r$ 有 $a_{i+1}=b_{a_i}$，且存在 $l'\le i\le r'$ 使得 $a_i=x$。只需输出 $r'-l'+1$ 的最大值，若不存在则输出 $0$。

{{ s('input format') }}

{{ self.input_file() }}

第一行两个整数 $n,m$；

第二行 $n$ 个整数依次表示 $a_1,\dots,a_n$；

第三行 $n$ 个整数依次表示 $b_1,\dots,b_n$；

接下来 $m$ 行，每行 $1,x,y$ 或 $2,l,r,x$ 表示进行一次修改操作或查询操作。

$1\le n,m\le 10^6$；

$1\le a_i\le n$；

$1\le b_i\le n$，$b_i$ 互不相同；

对修改操作，满足 $1\le x,y\le n$；

对查询操作，满足 $1\le l\le r\le n$，$1\le x\le n$；

输入的所有数值为整数。

{{ s('output format') }}

{{ self.output_file() }}

对每个查询操作，输出一行，表示相应的答案。

{{ s('sample') }}

{{ self.sample_text() }}
