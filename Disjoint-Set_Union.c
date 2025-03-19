//并查集
#include<stdio.h>
#define MAX_N 100
int fa[MAX_N];
void init(int n) {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
}
int findRoot(int x) {
	int root = x;
	while (root != fa[x])
		root = fa[x];

	while (x != root) {
		int temp = fa[x];
		fa[x] = root;
		x = temp;
	}
	return root;
}
//int findRoot(int x) {
//	if (fa[x] != x) {
//		fa[x] = findRoot(fa[x]); // 递归实现完全路径压缩
//	}
//	return fa[x];
//}
void merge(int a, int b) {
	int root_a = findRoot(a);
	int root_b = findRoot(b);
	if (root_a != root_b) {
		fa[root_a] = root_b;
	}
}