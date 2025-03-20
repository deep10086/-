#include<stdio.h>
#include<stdlib.h>
#define Vertex char
#define Edge int
#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x7fffffff
typedef struct
{
	Vertex ver[MAXSIZE];
	Edge area[MAXSIZE][MAXSIZE];
	int verNum;
	int edgeNum;
}MatGraph;
typedef struct
{
	int begin;
	int end;
	int weight;
}Edges;
//制图
void creatGraph(MatGraph* G)
{
	G->verNum = 9;
	G->edgeNum = 15;

	G->ver[0] = 'A';
	G->ver[1] = 'B';
	G->ver[2] = 'C';
	G->ver[3] = 'D';
	G->ver[4] = 'E';
	G->ver[5] = 'F';
	G->ver[6] = 'G';
	G->ver[7] = 'H';
	G->ver[8] = 'I';

	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			if (i == j)
			{
				G->area[i][j] = 0;
			}
			else
			{
				G->area[i][j] = MAX;
			}

		}
	}

	//A-B A-F
	G->area[0][1] = 10;
	G->area[0][5] = 11;

	//B-C B-G B-I
	G->area[1][2] = 18;
	G->area[1][6] = 16;
	G->area[1][8] = 12;

	//C-D C-I
	G->area[2][3] = 22;
	G->area[2][8] = 8;

	//D-E D-G D-H D-I
	G->area[3][4] = 20;
	G->area[3][6] = 24;
	G->area[3][7] = 16;
	G->area[3][8] = 21;

	//E-F E-H
	G->area[4][5] = 26;
	G->area[4][7] = 7;

	//F-G
	G->area[5][6] = 17;

	//G-H
	G->area[6][7] = 19;
	//减少冗余的邻接矩阵对称赋值
	//	问题：creatGraph函数中显式地对邻接矩阵进行双向赋值（G->area[j][i] = G->area[i][j]）。
	//	优化：
	//	直接在初始化时仅赋值一次，利用图的对称性。例如，在设置G->area[0][1] = 10时，同时设置G->area[1][0] = 10，避免后续循环重复赋值。
	//	代码修改：
	//	c
	//示例：A-B的边赋值
	//	G->area[0][1] = G->area[1][0] = 10;
	//删除最后的对称赋值循环。

	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->area[j][i] = G->area[i][j];
		}
	}
}
void swap(Edges* edges, int i, int j)
{
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;

	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;

	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}
int find(int* parent, int x) {
	if (parent[x] != x) {
		parent[x] = find(parent, parent[x]);  // 递归路径压缩
	}
	return parent[x];
}
void sortEdges(Edges edges[], int edgeNum) {
	for (int i = 0; i < edgeNum; i++)
	{
		for (int j = i + 1; j < edgeNum; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				swap(edges, i, j);
			}
		}
	}
}
//Kruskal算法
void Kruskal(MatGraph G) {
	Edges edges[MAXEDGE];
	int k = 0;
	for (int i = 0; i < G.verNum;i++) {
		for (int j= i+1; j< G.verNum; j++) {
			if (G.area[i][j] < MAX) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.area[i][j];
				k++;
			}
		}

	}
	sortEdges(edges, G.edgeNum);
	/*并查集操作：
	初始化：parent数组初始化为本身，表示每个顶点初始时独立成树。
	查找根节点：find函数递归查找顶点所属树的根节点。
	合并树：若两顶点的根不同（n != m），则将一棵树的根指向另一棵树的根（parent[n] = m）*/
int fa[MAXSIZE];
for (int i = 0; i < G.verNum; i++) {
	fa[i] = i;
}
int n, m;
int count = 0;
for (int i = 0; i < G.edgeNum && count < G.verNum - 1; i++)
{
	n = find(fa, edges[i].begin);//6
	m = find(fa, edges[i].end);//6

	if (n != m)
	{
		fa[n] = m;
		printf("(%d, %d) ", edges[i].begin, edges[i].end);
		printf("(%c, %c) %d\n", G.ver[edges[i].begin], G.ver[edges[i].end], edges[i].weight);
		count++;
	}
}
}
int main() {
	MatGraph G;
	creatGraph(&G);
	Kruskal(G);
	return 0;
}
