#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

/** \brief   ����������ʽʵ��
 *          ���ļ����ڴ���궨�弰ͷ�ļ�����������
 *
 */
/* Linear Table On Sequence Structure */
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

#define LEFT 0
#define RIGHT  1

#define LIST_INIT_SIZE 20
#define LISTINCREMENT 5

typedef int status;
typedef char ElemType; //����Ԫ�����Ͷ���

typedef struct bitnode    //�������ṹ����
{
    int key;
    ElemType value;
    struct bitnode *lchild;
    struct bitnode *rchild;
} BitNode, *BiTree;

typedef struct tree   //����ͷ���
{
    char name[20];
    BitNode *HeadNode;
} Tree;


typedef struct  //���Ա������
{
    Tree** elem;
    int length;
    int listsize;
} SqList;

//ȫ�ֱ�������
extern SqList *treelist;
extern int count;

//��������
extern status InitBiTree(Tree **T);
extern status DestroyBiTree(Tree **T);
extern status CreateBiTree(BitNode **T, char **definition);
extern status ClearBiTree (Tree *T);
extern status BiTreeEmpty(Tree *T);
extern status BiTreeDepth(BiTree T, int i);
extern char Root(Tree *T);
extern char Value(BiTree T,int e);
extern status Assign(BiTree T,int e,ElemType value);
extern BiTree Parent(Tree *T,int e);
extern BiTree LeftChild(BiTree T,int e);
extern BiTree RightChild(BiTree T,int e);
extern BiTree LeftSibling(Tree *T,int e);
extern BiTree RightSibling(Tree *T,int e);
extern status InsertChild(BiTree T,BiTree p,status LR,BiTree c);
extern status DeleteChild(BiTree T,BiTree p,status LR);
extern status PreOrderTraverse(BiTree T,void (*visit)(char c) );
extern status InOrderTraverse(BiTree T,void (*visit)(char c) );
extern status PostOrderTraverse(BiTree T,void (*visit)(char c) );
extern status LevelOrderTraverse(BiTree T,void (*visit)(char c), BiTree *F,BiTree *H);
/*--------------------------------------------*/

extern void printf_my(char a);
extern status SavePreOrderTraverse(BiTree T, FILE *fp);
extern status SaveTree(SqList *treelist);
extern status LoadTree(Tree **base);
extern status ChooseTree(Tree **base);
extern BiTree FindNode(BiTree T,int e);

#endif // TREE_H_INCLUDED
