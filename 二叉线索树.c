#include<stdio.h>
#include<stdlib.h>
#define ElemType char

typedef struct ThreadNode{
	ElemType data;
	struct ThreadNode* lchi;
	struct ThreadNode* rchi;
	int ltag;
	int rtag;
}ThreadNode;
typedef ThreadNode* ThreadTree;
char str[]= "ABDH##I##EJ###CF##G##";
int idx = 0;
ThreadTree prev;
//创建树
void creatTree(ThreadTree* T) {
	ElemType ch;
	ch = str[idx++];
	if (ch == '#')
	{
		(*T) = NULL;
		
	}
	else
	{
		(*T) = (ThreadTree)malloc(sizeof(ThreadNode));
		(*T)->data = ch;
		creatTree(&(*T)->lchi);
		if ((*T)->lchi != NULL)
			(*T)->ltag = 0;
		creatTree(&(*T)->rchi);
		if ((*T)->rchi != NULL)
			(*T)->rtag = 0;
	}
}
// 细致线索化
void threading(ThreadTree T) {
	if (T != NULL) {//先处理左孩子 然后本节点 之后右孩子 先前驱然后后继 之后更新prev
		threading(T->lchi);
		if (T->lchi == NULL)
		{
			T->lchi = prev;
			T->ltag = 1;
		}
		if (prev->rchi == NULL)
		{
			prev->rchi = T;
			prev->rtag = 1;
		}prev = T;
		threading(T->rchi);
	}
}
//初步线索化
void inithreading(ThreadTree T,ThreadTree*head) {
	(*head) = (ThreadTree)malloc(sizeof(ThreadNode));
	(*head)->ltag = 0;
	(*head)->rtag = 1;
	(*head)->rchi = (*head);
	if (T ==NULL) {
		(*head)->lchi = (*head);
	}
	else
	{
		(*head)->lchi = T;
		prev = (*head);
		threading(T);//这里线索化中间
		prev->rchi = (*head);
		prev->rtag = 1;
		(*head)->rchi = prev;
	}
}

//遍历
void inOrder(ThreadTree head) {
	ThreadTree cur = head->lchi;
	while (cur != head) {
		while (cur->ltag == 0)
		{
			cur = cur->lchi;
		}

		printf("%c ", cur->data);
		while (cur->rtag == 1 && cur->rchi != head) {
			cur = cur->rchi;
			printf("%c ", cur->data);
		}
		cur = cur->rchi;
	}
}
int main() {
	ThreadTree T;
	ThreadTree head;
	creatTree(&T);
	inithreading(T, &head);
	inOrder(head);

	return 0;
}
//【线索二叉树-创建-哔哩哔哩】 https://b23.tv/iEqfZwn
