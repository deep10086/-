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
//生成树(前序 第一次到达 中序 转弯时 后序 返回时)
void creatTree(BiTree* T) {
	ElemType ch;
	ch = str[id++];
	if (ch == '#')//第一次这里弄成双引号了 
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
//读取树
void readTree(BiTree T){
	if (T == NULL) {
		return;
	}
	printf("%c", T->data);//前序
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
