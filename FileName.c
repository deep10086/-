#include<stdio.h>
#include<stdlib.h>
#define ElemType int
typedef struct bioNode {
	ElemType data;
	struct bioNode* last, * next;
}BioNode;
//��ʼ������
BioNode* initBioNode() {
	BioNode* head = (BioNode*)malloc(sizeof(BioNode));
	head->next = NULL;
	head->last = NULL;
	head->data = 0;
	return head;
}
//ͷ�巨
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
//����(������ͷ�����������ݣ�
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
//��ȡβ�����
BioNode* get_tail(BioNode* L)
{
	BioNode* p = L;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//β�巨(voidҲ�У�
BioNode* insertTail(BioNode* tail, ElemType e)
{
	BioNode* p = (BioNode*)malloc(sizeof(BioNode));
	p->data = e;
	p->last = tail;
	tail->next = p;
	p->next = NULL;
	return p;
}
//�ͷ�����
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
	//ָ��λ�ò���(�������Ŀɶ����е��)
	/*2. ͳһ�����߼�
		���飺��ͷ�塢β����м����ͳһ�� insertPos()��ͨ��λ�ò������ơ����磺
		pos = 1 ��ʾͷ�壨�����⴦����
		pos = N + 1��NΪ��ǰ���ȣ���ʾβ�塣*/
	if (pos < 1) {
		printf("����λ�ò���С��1\n");
		return;
	}
	BioNode* find = head;
	BioNode* p = (BioNode*)malloc(sizeof(BioNode));
	p->data = e;
	for (int i = 0; i < pos - 1; i++)//�������ҵ�ָ��λ��
	{
		 find= find->next;
	}
	p->next = find->next;//����ע�� ��һ��д��p=��
	p->last = find;
	find->next->last = p;
	find->next = p;
}
//ɾ���ڵ�(�������д�� ����ճ����)
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
//		printf("Ҫɾ����λ�ô���\n");
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