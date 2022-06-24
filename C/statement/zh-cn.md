{{ self.title() }}

{{ s('description') }}

*有人说，它拯救了世界；也有人说，它毁灭了世界。*

这个世界危在旦夕！秩序已然一片混乱。

秩序可以抽象成一个 $n\times n$ 的矩阵，矩阵中是一个 $1\sim n^2$ 的排列。你想要拯救世界，于是请来了神，来帮忙把秩序恢复原状。然而神也不是万能的，它只能做到交换矩阵中同一行或者同一列中的两个数。而且，它并不知道要怎么交换才能复原，得听你的指导。

幸好，你不一定需要在最少的交换次数之内完成复原。你只需要不比最糟糕的情况差就好。也就是说，如果你的交换次数为 $k$，且对于所有 $1\sim n^2$ 的排列，最小交换次数的最大值为 $k_0$，你只需要满足 $k\le k_0$。

注：复原指的是将矩阵变为如下的一个矩阵：

$\begin{matrix} 1 & 2 & 3 & \cdots & n \\ n+1 & n+2 & n+3 & \cdots & 2n \\ 2n+1 & 2n+2 & 2n+3 & \cdots & 3n\\ \vdots & \vdots & \vdots & \ddots & \vdots \\ (n-1)n+1 & (n-1)n+2 & (n-1)n+3 & \cdots & n^2 \end{matrix}$

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $n$。

接下来 $n$ 行，每行 $n$ 个正整数，表示这个 $n\times n$ 的矩阵。保证 $1\sim n^2$ 中的每个数恰好出现一次。

{{ s('output format') }}

{{ self.output_file() }}

第一行一个非负整数 $k$，表示你的交换次数。

接下来 $k$ 行，每行四个正整数 $x_1,y_1,x_2,y_2$，表示将第 $x_1$ 行 $y_1$ 列的数与第 $x_2$ 行 $y_2$ 列的数交换。

你需要保证 $x_1=x_2$ 或 $y_1=y_2$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

可以证明这是交换次数最少的方案之一，显然它符合条件。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

对于这个输入来说，这个样例输出的方案不是交换次数最少的方案，但是我们知道存在一个 $1\sim n^2$ 的排列（即上一个样例）需要至少 $3$ 次的交换，所以这个方案也是可行的。

{{ s('sample', 3) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

我们允许出现 $(x_1,y_1)=(x_2,y_2)$ 的情况。

{{ s('sample', 4) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

注意 $k$ 可以等于 $0$。

{{ s('subtasks') }}

保证 $1\le n\le 1000$。

保证输入的矩阵中 $1\sim n^2$ 恰好各出现一次。