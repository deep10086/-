#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
	ElemType* data;
	int front;
	int rear;

}Queue;

//初始化
Queue* initQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	q->front = 0;
	q->rear = 0;
	return q;
}

//判断队列是否为空
int isEmpty(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

//出队
ElemType dequeue(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	ElemType e = Q->data[Q->front];
	Q->front++;
	return e;
}
//入队代码块
void eQueue(Queue* Q,ElemType e){
	if (Q->rear>=MAXSIZE) {
		if (QueueFull(Q) )
			return;
		

	}
	Q->data[Q->rear] = e;
	Q->rear++;
	

}
int QueueFull(Queue* Q) {
	if (Q->front > 0) {
		int depth = Q->front;
		for (int i = Q->front; i <= Q->rear; i++) {
			Q->data[i - depth] = Q->data[i];//这个地方会越界访问
			Q->front = 0;
			return 0;
		}
	}
	else
	{
		printf("满了");
		return 1;
	}
}
/*int QueueFull(Queue* Q)
{
	if (Q->front > 0)
	{
		int numElements = Q->rear - Q->front;
		for (int i = 0; i < numElements; i++)
		{
			Q->data[i] = Q->data[Q->front + i];
		}
		Q->front = 0;
		Q->rear = numElements;
		return 0;
	}
	else
	{
		printf("队列已满\n");
		return 1;
	}
}*/

//获取队头元素
int getHead(Queue* Q, ElemType* e)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
}

int main(int argc, char const* argv[])
{

	Queue* q = initQueue();

	equeue(q, 10);
	equeue(q, 20);
	equeue(q, 30);
	equeue(q, 40);
	equeue(q, 50);

	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	ElemType e;
	getHead(q, &e);
	printf("%d\n", e);

	return 0;
}



