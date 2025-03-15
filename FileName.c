#include<stdio.h>
#include<stdlib.h>
#define ElemType int
typedef struct bioNode {
	ElemType data;
	struct bioNode* last, * next;
}BioNode;
//初始化链表
BioNode* initBioNode() {
	BioNode* head = (BioNode*)malloc(sizeof(BioNode));
	head->next = NULL;
	head->last = NULL;
	head->data = 0;
	return head;
}
//头插法
void insertFromHead(BioNode* head, ElemType e) {
	BioNode* p = (BioNode*)malloc(sizeof(BioNode));
	p->data = e;
	p->last = head;
	p->next = head->next;
	if (head->next != NULL) {
		head->next->last = p;
	}
	head->next = p;
}
//遍历(避免了头结点的无用数据）
void listNode(BioNode* head)
{
	BioNode* p = head->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
//获取尾部结点
BioNode* get_tail(BioNode* L)
{
	BioNode* p = L;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//尾插法(void也行）
BioNode* insertTail(BioNode* tail, ElemType e)
{
	BioNode* p = (BioNode*)malloc(sizeof(BioNode));
	p->data = e;
	p->last = tail;
	tail->next = p;
	p->next = NULL;
	return p;
}
//释放链表
void freeList(BioNode* L)
{
	BioNode* slow = L;
	BioNode* fast = L->next;
	while (fast != NULL) {
		free(slow);
		slow = fast;
		fast = fast->next;
	}
	free(slow);
	slow = NULL;
}
//void freeList(BioNode* L)
//{
//	BioNode* current = L;
//
//	while (current != NULL) {
//		BioNode* next = current->next;
//		free(current);
//		current = next;
// }
//	
//}

void insertPos(BioNode* head, int pos, ElemType e) {
	//指定位置插入(这个代码的可读性有点差)
	/*2. 统一插入逻辑
		建议：将头插、尾插和中间插入统一到 insertPos()，通过位置参数控制。例如：
		pos = 1 表示头插（需特殊处理）。
		pos = N + 1（N为当前长度）表示尾插。*/
	if (pos < 1) {
		printf("插入位置不能小于1\n");
		return;
	}
	BioNode* find = head;
	BioNode* p = (BioNode*)malloc(sizeof(BioNode));
	p->data = e;
	for (int i = 0; i < pos - 1; i++)//这里能找到指定位置
	{
		 find= find->next;
	}
	p->next = find->next;//这里注意 第一次写成p=了
	p->last = find;
	find->next->last = p;
	find->next = p;
}
//删除节点(这个懒得写了 复制粘贴的)
//int deleteNode(Node* L, int pos)
//{
//	Node* p = L;
//	int i = 0;
//	while (i < pos - 1)
//	{
//		p = p->next;
//		i++;
//		if (p == NULL)
//		{
//			return 0;
//		}
//	}
//
//	if (p->next == NULL)
//	{
//		printf("要删除的位置错误\n");
//		return 0;
//	}
//
//	Node* q = p->next;
//	p->next = q->next;
//	q->next->prev = p;
//	free(q);
//	return 1;
//}
int main(){
	BioNode* list = initBioNode();
	insertFromHead(list,10);
	insertFromHead(list,20);
	insertFromHead(list,30);
	listNode(list);
	BioNode* tail = get_tail(list);
	tail = insertTail(tail, 10);
	tail = insertTail(tail, 20);
	tail = insertTail(tail, 30);
	listNode(list);
	insertPos(list, 2, 15);
	listNode(list);
	freeList(list);
	return 0;
	}