#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/** \brief   �����ڽӱ��ͼʵ��
 *          ���ļ����ڴ���궨�弰ͷ�ļ�����������
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<stddef.h>
#include<stdbool.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

#define MAX_VERTEX_NUM 20
#define MAX_NAME 3     //�����ַ�������󳤶� +1

typedef int status;
typedef char ElemType; //����Ԫ�����Ͷ���
typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef struct ArcNode   //�ڵ�Ľṹ
{
    int adjvex; /* �û���ָ��Ķ����λ�� */
    struct ArcNode *nextarc; /* ָ����һ������ָ�� */
    InfoType *info; /* ���������ϢȨֵָ�� */
} ArcNode; /* ���� */

typedef struct Vnode  //����
{
    VertexType data;   /* ������Ϣ */
    ArcNode *firstarc; /* ��һ������ĵ�ַ ,ָ���һ�������ö���Ļ���ָ�� */
} VNode, AdjList[MAX_VERTEX_NUM]; /* ͷ��� */

typedef struct   //ͼ
{
    AdjList vertices;
    int vexnum, arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
    int kind; /* ͼ�������־ */
} ALGraph;


//ȫ�ֱ�������
extern bool visited[MAX_VERTEX_NUM];

//��������
extern status CreateGraph(ALGraph **G);
extern status DestroyGraph(ALGraph **G);
extern status LocateVex(ALGraph G,VertexType u);
extern int FirstAdjVex(ALGraph G,VertexType v);
extern int NextAdjVex(ALGraph G,VertexType v,VertexType w);
extern status InsertVex(ALGraph *G,VertexType v);
extern status DeleteVex(ALGraph *G,VertexType v);
extern status InsertArc(ALGraph *G,VertexType v,VertexType w);
extern status DeleteArc(ALGraph *G,VertexType v,VertexType w);
extern status DFSTraverse(ALGraph G,void (*visit)(char*));
extern status BFSTraverse(ALGraph G,void (*visit)(char *));
extern char* GetVex(ALGraph *G,int v);
extern status PutVex (ALGraph *G,int v,VertexType value);
/*--------------------------------------------*/

extern void printf_my(char* a);
extern void DFS(ALGraph G, int v, void (*visit)(char*));

#endif // GRAPH_H_INCLUDED

