#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define ElemType int
typedef struct {
	ElemType* data;
	int length;
}SeqList;
//初始化线性表
SeqList* iniList() {
	SeqList* L = (SeqList*)malloc(sizeof(SeqList));
	L->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	L->length = 0;
	return L;
}
//添加元素
void appendElem(SeqList* L, ElemType e) {
	if (L->length >= MAXSIZE) {
		printf("满了");
		return;
	}
	else {
		L->data[L->length] = e;
		L->length++;
	}
}
//遍历
void looklook(SeqList* L) {
	for (int i = 0; i < L->length; i++) {
		printf("%d ", L->data[i]);
	}
	printf("\n");
}
//插入
void insertElem(SeqList* L, int pos, ElemType e) {
	if (L->length >= MAXSIZE) {
		printf("满了");
		return;
	}
	if (pos<1 || pos>L->length + 1) {
		printf("位置错了");
		return;
	}
	else {
		int i = 0;
		for (i = L->length; i >= pos; i--) {
			L->data[i] = L->data[i - 1];
		}
		L->data[i] = e;
		L->length++;
	}
}
//删除
void DeletElem(SeqList* L, int pos) {
	if (pos<1 || pos>L->length) {
		printf("位置错了");
	}
	else {
		printf("删除的是%d\n", L->data[pos - 1]);
		for (int i = pos; i < L->length; i++) {
			L->data[i - 1] = L->data[i];
		}
		L->length--;
	}
}
//查找
void findElem(SeqList* L, ElemType e) {
	for (int i = 0; i < L->length; i++) {
		if (e == L->data[i])
			printf("找到了 是第%d个", i + 1);
	}
}//销毁
void destroy(SeqList* L) {
	free(L->data);
	free(L);
	L = NULL;
}

int main() {
	SeqList* list = iniList();
	appendElem(list, 88);
	appendElem(list, 67);
	appendElem(list, 40);
	appendElem(list, 8);
	appendElem(list, 23);
	looklook(list);
	insertElem(list, 3, 18);
	looklook(list);
	DeletElem(list, 2);
	looklook(list);
	findElem(list, 40);
	destroy(list);
	return 0;
}
