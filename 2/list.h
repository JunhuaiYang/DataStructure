#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/** \brief
 *         该文件用于储存宏定义及头文件及函数申明
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<stddef.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2


typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct Lxnode{   //节点定义
    ElemType data;
    struct Lxnode *next;
}LNode, *LinkList;

//发现在标准C语言中，函数参数无法使用&传递
//把所有&L改为了*L

//全局变量定义
extern char name[10];

//函数定义
extern status IntiaList(LinkList *L);
extern status DestroyList(LinkList *L);
extern status ClearList(LinkList L);
extern status ListEmpty(LinkList L);
extern int ListLength(LinkList L);
extern status GetElem(LinkList L,int i,ElemType *e);
extern int LocateElem(LinkList L,ElemType e, status(*compare)(ElemType,ElemType));
extern status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e);
extern status NextElem(LinkList L,ElemType cur_e,ElemType *next_e);
extern status ListInsert(LinkList L,int i,ElemType e);
extern status ListDelete(LinkList L,int i,ElemType *e);
extern status ListTrabverse(LinkList L,void (*visit)(int));
/*--------------------------------------------*/
extern status Equal(ElemType a,ElemType b);
extern void print(int a);
extern status SaveList(LinkList L);
extern status LoadList(LinkList *L);
extern status ChangeName(void);
#endif // LIST_H_INCLUDED
