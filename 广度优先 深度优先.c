#include<stdio.h>
#include<stdlib.h>
#define Vertex char
#define Edge int
#define MAXSIZE 100
typedef struct {
	int verNum;
	int edgeNum;
	Edge area[MAXSIZE][MAXSIZE];
	Vertex ver[MAXSIZE];
}MatGraph;
int visited[MAXSIZE];
int front = 0;//DFS不需要
int rear = 0;
int que[MAXSIZE];
//制图
void creatGraph(MatGraph* G) {
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
			G->area[i][j] = 0;
		}
	}

	//A-B A-F
	G->area[0][1] = 1;
	G->area[0][5] = 1;

	//B-C B-G B-I
	G->area[1][2] = 1;
	G->area[1][6] = 1;
	G->area[1][8] = 1;

	//C-D C-I
	G->area[2][3] = 1;
	G->area[2][8] = 1;

	//D-E D-G D-H D-I
	G->area[3][4] = 1;
	G->area[3][6] = 1;
	G->area[3][7] = 1;
	G->area[3][8] = 1;

	//E-F E-H
	G->area[4][5] = 1;
	G->area[4][7] = 1;

	//F-G
	G->area[5][6] = 1;

	//G-H
	G->area[6][7] = 1;

	for (int i = 0; i < G->verNum; i++)
	{
		for (int j = 0; j < G->verNum; j++)
		{
			G->area[j][i] = G->area[i][j];
		}
	}
}
//广度遍历
void bfs(MatGraph G){
	int i = 0;
	visited[i] = 1;
	printf("%c", G.ver[i]);
	que[rear] = i;
	rear++;
	while (rear != front) {
		i = que[front];//出队
		front++;
		for (int j = 0; j < G.ver[MAXSIZE]; j++) {
			if (G.area[i][j] == 1 && visited[j] != 1) {
				visited[j] = 1;
				printf("%c", G.ver[j]);
				que[rear] = j;
				rear++;
			}
		}
	}


}
//深度遍历
void dfs(MatGraph G,int i) {
	visited[i] = 1;
	printf("%c", G.ver[i]);
	for (int j = 0; j < G.verNum; j++) {
		if (G.area[i][j] == 1 && visited[j] == 0) {
			dfs(G, j);
		}
	}

}
int main() {
	MatGraph G;
	creatGraph(&G);
	//空间换时间 数组记录访问状态 flag

	for (int i = 0; i < G.verNum; i++)
	{
		visited[i] = 0;
	}
	bfs(G);
	dfs(G, 0);
	return 0;
}
