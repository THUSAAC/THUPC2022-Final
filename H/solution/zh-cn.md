{{ self.title() }}

## 算法

扫描线扫 $r$，维护每个 $l$ 对应区间 $[l,r]$ 的按位与、按位或、最大公因数。

按位与、按位或、最大公因数都构成高度 $O(\log n)$ 的半格，因此每个左端点的价值只变化 $O(\log n)$ 次，且每扫一步，价值发生变化的是当前扫过位置的一个后缀。用带时间戳的前缀和支持末端插入删除，维护前缀历史和（对每个 $l$ 维护 $l'\le l,\;r'\le r$ 的 $[l',r']$ 的价值和），将区间所有子区间查询差分为两次前缀历史和查询。

时间复杂度 $O(n\log n+m)$。