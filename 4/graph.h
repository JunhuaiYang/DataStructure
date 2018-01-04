#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/** \brief   基于邻接表的图实现
 *          该文件用于储存宏定义及头文件及函数申明
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
#define MAX_NAME 3     //顶点字符串的最大长度 +1

typedef int status;
typedef char ElemType; //数据元素类型定义
typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef struct ArcNode   //节点的结构
{
    int adjvex; /* 该弧所指向的顶点的位置 */
    struct ArcNode *nextarc; /* 指向下一条弧的指针 */
    InfoType *info; /* 弧的相关信息权值指针 */
} ArcNode; /* 表结点 */

typedef struct Vnode  //顶点
{
    VertexType data;   /* 顶点信息 */
    ArcNode *firstarc; /* 第一个表结点的地址 ,指向第一条依附该顶点的弧的指针 */
} VNode, AdjList[MAX_VERTEX_NUM]; /* 头结点 */

typedef struct   //图
{
    AdjList vertices;
    int vexnum, arcnum; /* 图的当前顶点数和弧数 */
    int kind; /* 图的种类标志 */
} ALGraph;


//全局变量定义
extern bool visited[MAX_VERTEX_NUM];

//函数定义
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

