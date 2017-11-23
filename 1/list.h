#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/** \brief
 *         该文件用于储存宏定义及头文件及函数申明
 *
 */


/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int status;
typedef int ElemType; //数据元素类型定义


typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
	char name[10];  //用于list命名
}SqList;

//发现在标准C语言中，函数参数无法使用&传递
//把所有&L改为了*L

//函数定义
/*-----page 19 on textbook ---------*/
extern status IntiaList(SqList **L);
extern status DestroyList(SqList **L);
extern status ClearList(SqList *L);
extern status ListEmpty(SqList L);
extern int ListLength(SqList L);
extern status GetElem(SqList L,int i,ElemType *e);
extern int LocateElem(SqList L,ElemType e, status(*compare)(ElemType,ElemType));
extern status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e);
extern status NextElem(SqList L,ElemType cur_e,ElemType *next_e);
extern status ListInsert(SqList *L,int i,ElemType e);
extern status ListDelete(SqList *L,int i,ElemType *e);
extern status ListTrabverse(SqList L,void (*visit)(int));
/*--------------------------------------------*/
extern status Equal(ElemType a,ElemType b);
extern void print(int a);
extern status SaveList(SqList *L);
extern status LoadList(SqList **L);

#endif // LIST_H_INCLUDED
