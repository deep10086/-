#include<stdio.h>
#include<stdlib.h>
#define ElemType int 
typedef struct node {
	ElemType data;
	struct node* next;
}Node;
//初始化
Node* initNode() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}
//头插法
void insertFromHead(Node* head, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = head->next;
	head->next = p;
}
//寻找尾节点
Node* findTail(Node* L) {
	Node* p = L;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}
//尾插法
Node* insertFromTail(Node* tail, ElemType e) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	tail->next = p;
	p->next = NULL;
	return p;
}
//遍历(这样能避免第一个的0）
void listNode(Node* head) {
	Node* p = head->next;
	while (p!= NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
//指定位置插入(这个代码的可读性有点差)
void insertPos(Node* head, int pos, ElemType e) {
	if (pos < 1) {
		printf("插入位置不能小于1\n");
		return;
	}
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	for (int i = 0; i < pos - 1; i++)//这里能找到指定位置
	{
		head = head->next;
	}
	p->next = head->next;//这里注意 第一次写成p=了
	head->next = p;
}
//释放内存
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
		Node* next = current->next;  // 先保存下一节点地址
		free(current);               // 安全释放当前节点
		current = next;             // 通过预存地址移动指针
	}
}*/
//删除元素
void deleteNode(Node* head, int pos) {
	Node* p = head;
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
	}
	Node* dele = p->next;
	p->next = p->next->next;
	printf("删除了第%d个，他是%d\n", pos, dele->data);
	free(dele);
}
//获取长度
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
	printf("链表长度为%d 其中包含头节点数据 否则为%d", lengthOfNode(p), lengthOfNode(p)-1);
	freeNode(p);
	return 0;
}
