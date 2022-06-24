{{ self.title() }}

{{ s('description') }}

给序列 $a_1,\dots,a_n$，$b_1,\dots,b_n$，$c_1,\dots,c_n$，

定义区间 $[l,r]$ 的价值为 $a_l,\dots,a_r$ 按位与，$b_l,\dots,b_r$ 按位或，$c_l,\dots,c_r$ 的最大公因数，这三者的乘积；

$m$ 次查询，每次查询给出区间 $[l,r]$，查询满足 $l\le l'\le r'\le r$ 的 $[l',r']$ 的价值之和。

{{ s('input format') }}

{{ self.input_file() }}

第一行两个整数 $n,m$；

第二行 $n$ 个整数 $a_1,\dots,a_n$；

第三行 $n$ 个整数 $b_1,\dots,b_n$；

第四行 $n$ 个整数 $c_1,\dots,c_n$；

接下来 $n$ 行，每行两个整数 $l,r$ 表示一次查询。

$1\le n\le 10^6$

$1\le m\le 5\times 10^6$

$1\le a_i,b_i,c_i\le n$

$1\le l\le r\le n$

{{ s('output format') }}

{{ self.output_file() }}

共 $m$ 行，每行一个整数，表示对应的答案。

{{ s('sample') }}

{{ self.sample_text() }}

{{ s('hint') }}

建议使用高效的输入输出方式。

