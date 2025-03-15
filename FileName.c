#include<stdio.h>
#include<stdlib.h>
#define ElemType int 
typedef struct node {
	ElemType data;
	struct node* next;
}Node;
//��ʼ��
Node* initNode() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}
//ͷ�巨
void insertFromHead(Node* head, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = head->next;
	head->next = p;
}
//Ѱ��β�ڵ�
Node* findTail(Node* L) {
	Node* p = L;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}
//β�巨
Node* insertFromTail(Node* tail, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	tail->next = p;
	p->next = NULL;
	return p;
}
//����(�����ܱ����һ����0��
void listNode(Node* head) {
	Node* p = head->next;
	while (p!= NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
//ָ��λ�ò���(�������Ŀɶ����е��)
void insertPos(Node* head, int pos, ElemType e) {
	if (pos < 1) {
		printf("����λ�ò���С��1\n");
		return;
	}
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	for (int i = 0; i < pos - 1; i++)//�������ҵ�ָ��λ��
	{
		head = head->next;
	}
	p->next = head->next;//����ע�� ��һ��д��p=��
	head->next = p;
}
//�ͷ��ڴ�
void freeNode(Node* head) {

	Node* fast = head->next;
	Node* slow = head;
	while (fast != NULL) {
		free(slow);
		slow = fast;
		fast = fast->next;
	}
	free(slow);
	slow = NULL;
}
/*void freeNode(Node* head) {
	Node* current = head;
	while (current != NULL) {
		Node* next = current->next;  // �ȱ�����һ�ڵ��ַ
		free(current);               // ��ȫ�ͷŵ�ǰ�ڵ�
		current = next;             // ͨ��Ԥ���ַ�ƶ�ָ��
	}
}*/
//ɾ��Ԫ��
void deleteNode(Node* head, int pos) {
	Node* p = head;
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
	}
	Node* dele = p->next;
	p->next = p->next->next;
	printf("ɾ���˵�%d��������%d\n", pos, dele->data);
	free(dele);
}
//��ȡ����
int lengthOfNode(Node* head){
	Node* p = head;
	int length = 0;
	while (p != NULL) {
		length++;
		p = p->next;
	}
	return length;
}
int main() {
	Node* p = initNode();
	insertFromHead(p, 5);
	Node* tail = findTail(p);
	tail = insertFromTail(tail, 10);
	tail = insertFromTail(tail, 20);
	tail = insertFromTail(tail, 30);
	tail = insertFromTail(tail, 40);
	listNode(p);
	insertPos(p, 4, 25);
	listNode(p);
	deleteNode(p, 2);
	listNode(p);
	printf("������Ϊ%d ���а���ͷ�ڵ����� ����Ϊ%d", lengthOfNode(p), lengthOfNode(p)-1);
	freeNode(p);
	return 0;
}