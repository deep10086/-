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
//��ͼ
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
	//����������ڽӾ���ԳƸ�ֵ
	//	���⣺creatGraph��������ʽ�ض��ڽӾ������˫��ֵ��G->area[j][i] = G->area[i][j]����
	//	�Ż���
	//	ֱ���ڳ�ʼ��ʱ����ֵһ�Σ�����ͼ�ĶԳ��ԡ����磬������G->area[0][1] = 10ʱ��ͬʱ����G->area[1][0] = 10���������ѭ���ظ���ֵ��
	//	�����޸ģ�
	//	c
	//ʾ����A-B�ı߸�ֵ
	//	G->area[0][1] = G->area[1][0] = 10;
	//ɾ�����ĶԳƸ�ֵѭ����

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
//Kruskal�㷨
void Kruskal(MatGraph G) {
	Edges edges[MAXEDGE];
	int k = 0;
	for (int i = 0; i < G.verNum;i++) {
		for (int j= i+1; i < G.verNum; i++) {
			if (G.area[i][j] < MAX) {
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.area[i][j];
				k++;
			}
		}

	}
	sortEdges(edges, G.edgeNum);
}
int main() {
	MatGraph G;
	creatGraph(&G);
	Kruskal(G);
	return 0;
}