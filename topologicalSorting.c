//一、与常规 typedef 的核心差异
//常规 typedef 的用法
//通常用于为单一类型（如基本类型、结构体）定义别名，例如：
//c
//typedef int Integer;          // 为 int 定义别名
//typedef struct Node Node;     // 为结构体定义别名
//此时别名表示的是单个变量类型，与数组无关。
//用户代码的特殊性
//c
//typedef VertextNode Adj_List[MAXSIZE];
//定义了一个数组类型的别名，将 Adj_List 绑定到 VertextNode 数组，且数组长度固定为 MAXSIZE。
//后续使用时，Adj_List arr; 等价于 VertextNode arr[MAXSIZE]; ，直接声明了一个固定长度的数组。
//二、为何这种写法是合法的？
//C 语言允许通过 typedef 为复合类型（包括数组、结构体等）定义别名。其语法规则是：
//
//c
//typedef <原始类型> <新类型名>;
//关键点：这里的 <原始类型> 可以是一个完整的数组类型（如 VertextNode[MAXSIZE]）。
//从右向左阅读：
//typedef VertextNode Adj_List[MAXSIZE]; 应理解为：
//“定义 Adj_List 为 VertextNode 类型的一维数组，长度为 MAXSIZE”。
//三、实际应用场景
//这种写法在图论和数据结构中常见，尤其是在** 邻接表（Adjacency List）** 的实现中。例如，在文档提到的邻接表结构体定义中：
//
//c
//typedef struct {
//    VNode adjlist[maxSize];  // 固定大小的顶点数组
//    int n, e;
//} AGraph;
//这里的 VNode adjlist[maxSize] 与 Adj_List 的用法一致，目的是通过类型别名简化代码，同时明确数组的固定大小。
//
//四、潜在问题与改进建议
//固定数组的局限性
//若顶点数超过 MAXSIZE，会导致数组越界。
//改进：改用动态内存分配（如 VertextNode* adj_list）或封装为结构体（如包含容量字段）。
//可读性问题
//对不熟悉 typedef 数组用法的人来说，代码可能难以理解。
//改进：显式注释或使用结构体封装，例如：
//c
//typedef struct {
//    VertextNode nodes[MAXSIZE];
//    int size;
//} VertexArray;  // 更清晰的命名
//五、总结
//合法性：该用法符合 C 语言语法，但需注意数组维度和内存管理的限制。
//适用场景：适合顶点数固定的图结构（如静态邻接表），可简化代码并提高一致性。
//权衡：在灵活性与简洁性之间取舍，动态场景建议改用指针或结构体封装。
//若需进一步优化代码结构，可参考文档中邻接矩阵与邻接表转换的算法设计，结合动态内存管理实现更通用的图结构。
#include <stdio.h>
#include <stdlib.h>

typedef int VertextType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct
{
	VertextType vertex[MAXSIZE];
	EdgeType arc[MAXSIZE][MAXSIZE];
	int vertex_num;
	int edge_num;
}Mat_Graph;

typedef struct EdgeNode
{
	int edge_vex;
	struct EdgeNode* next;
}EdgeNode;

typedef struct VertextNode
{
	int in;
	VertextType data;
	EdgeNode* head;
}VertextNode;

typedef VertextNode Adj_List[MAXSIZE];//adjacency毗邻邻接
typedef struct
{
	Adj_List adj_list;
	int vertex_num;
	int edge_num;
}Adj_Graph;
//vertex_num与edge_num
//分别记录图的顶点总数和边的总数，用于遍历和操作时的边界控制（如循环顶点 / 边、统计复杂度等）。

typedef Adj_Graph* Adj_List_Graph;

int top = -1;
int stack[MAXSIZE];

void push(int e)
{
	if (top > MAXSIZE)
	{
		printf("满了\n");
		return;
	}

	top++;
	stack[top] = e;
}

int pop()
{
	if (top == -1)
	{
		printf("空的\n");
		return 0;
	}

	int elem = stack[top];
	top--;
	return elem;
}

int is_empty()
{
	if (top == -1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void create_graph(Mat_Graph* G)
{
	G->vertex_num = 14;
	G->edge_num = 20;

	for (int i = 0; i < G->vertex_num; i++)
	{
		G->vertex[i] = i;
	}

	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	G->arc[0][4] = 1;
	G->arc[0][5] = 1;
	G->arc[0][11] = 1;
	G->arc[1][2] = 1;
	G->arc[1][4] = 1;
	G->arc[1][8] = 1;
	G->arc[2][5] = 1;
	G->arc[2][6] = 1;
	G->arc[2][9] = 1;
	G->arc[3][2] = 1;
	G->arc[3][13] = 1;
	G->arc[4][7] = 1;
	G->arc[5][8] = 1;
	G->arc[5][12] = 1;
	G->arc[6][5] = 1;
	G->arc[8][7] = 1;
	G->arc[9][10] = 1;
	G->arc[9][11] = 1;
	G->arc[10][13] = 1;
	G->arc[12][9] = 1;
}

void create_adj_graph(Mat_Graph G, Adj_List_Graph* ALG)
{
	EdgeNode* e;

	*ALG = (Adj_List_Graph)malloc(sizeof(Adj_Graph));
	(*ALG)->vertex_num = G.vertex_num;
	(*ALG)->edge_num = G.edge_num;

	for (int i = 0; i < G.vertex_num; i++)
	{
		(*ALG)->adj_list[i].in = 0;
		(*ALG)->adj_list[i].data = G.vertex[i];
		(*ALG)->adj_list[i].head = NULL;
	}//现在的数组都只有表头元素

	for (int i = 0; i < G.vertex_num; i++)
	{
		for (int j = 0; j < G.vertex_num; j++)
		{
			if (G.arc[i][j] == 1)
			{
				e = (EdgeNode*)malloc(sizeof(EdgeNode));
				e->edge_vex = j;
				e->next = (*ALG)->adj_list[i].head;//头插
				(*ALG)->adj_list[i].head = e;
				(*ALG)->adj_list[j].in++;
			}
		}
	}
}

void topological_sort(Adj_List_Graph ALG)
{
	EdgeNode* e;
	int curr;
	int k;

	for (int i = 0; i < ALG->vertex_num; i++)
	{
		if (ALG->adj_list[i].in == 0)
		{
			push(i);
		}
	}

	while (is_empty() != 0)
	{
		curr = pop();
		printf("V%d -> ", ALG->adj_list[curr].data);//记录出栈元素
		e = ALG->adj_list[curr].head;//元素的后续节点 直到为空

		while (e != NULL)
		{
			k = e->edge_vex;//访问后续节点
			ALG->adj_list[k].in--;//减少入度
			if (ALG->adj_list[k].in == 0)
			{
				push(k);
			}
			e = e->next;//更新
		}
	}
}

int main(int argc, char const* argv[])
{
	Mat_Graph G;
	Adj_List_Graph ALG;
	create_graph(&G);
	create_adj_graph(G, &ALG);
	topological_sort(ALG);
	return 0;
}
