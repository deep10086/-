#include<stdio.h>
#include<stdlib.h>
#define ElemType char
typedef struct TreeNode {
	ElemType data;
	struct TreeNode* rchi;
		struct TreeNode* lchi;
}TreeNode;
typedef TreeNode* BiTree;
char str[] = "ABDH#K###E##CFI###G#J##";
int id = 0;
//������
void creatTree(BiTree* T) {
	ElemType ch;
	ch = str[id++];
	if (ch == '#')//��һ������Ū��˫������ 
	{
		*T = NULL;
	}
	else {
		*T = (BiTree)malloc(sizeof(TreeNode));
		(*T)->data = ch;
		creatTree(&(*T)->lchi);
		creatTree(&(*T)->rchi);
	}
}
//��ȡ��
void readTree(BiTree T){
	if (T == NULL) {
		return;
	}
	printf("%c", T->data);//ǰ��
	readTree(T->lchi);
	readTree(T->rchi);

}
int main()
{
	BiTree T;
	creatTree(&T);
	readTree(T);
	
	printf("\n");
	return 0;
}