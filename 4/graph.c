/** \brief  基于邻接表的图实现
 *         该文件用于储存主函数
 *
 */

#include"graph.h"

bool visited[MAX_VERTEX_NUM];     //全局变量，标志数组

/** \brief 创建图：函数名称是CreateCraph(&G,V,VR)
*        初始条件是V是图的顶点集，VR是图的关系集；操作结果是按V和VR的定义构造图G。
*/
status CreateGraph(ALGraph **G)
{
    int i, vex1, vex2;
    ArcNode *newbase, *tail;

    (*G) = (ALGraph*) malloc(sizeof(ALGraph));
    printf("当前创建图的类型为无向图。");    //无向图的实现
    (*G)->kind = 0;
    printf("\n请输入图的顶点数，弧数：");
    scanf("%d %d",&(*G)->vexnum, &(*G)->arcnum);
    printf("请输入每个顶点的值,共%d个顶点\n", (*G)->vexnum);
    for(i=0; i<(*G)->vexnum; i++)
    {
        scanf("%s", (*G)->vertices[i].data);     //输入每个节点的数据
        (*G)->vertices[i].firstarc = NULL;    //先置空
    }
    //输出每个顶点的位置方便录入后面的信息
    printf("当前每个顶点的位置如下：\n");
    for(i=0; i<(*G)->vexnum; i++)
        printf("%s\t",(*G)->vertices[i].data);
    printf("\n");
    for(i=0; i<(*G)->vexnum; i++)
        printf("%d\t", i);
    printf("\n请输入每条弧的两顶点(顶点的键值按照顶点的输入顺序从0开始)：\n");
    for(i = 1; i<=(*G)->arcnum; i++)
    {
        printf("当前为第%d条弧，共%d条\n",i,(*G)->arcnum);
        scanf("%d %d",&vex1, &vex2);
        if(vex1<0 || vex1 >(*G)->vexnum || vex2<0 || vex2 >(*G)->vexnum)    //输入非法时处理
            return ERROR;
        //先对vex1创建节点
        newbase = (ArcNode*) malloc(sizeof(ArcNode));  //创建新的弧节点
        if(!newbase)          //内存申请失败
            return OVERFLOW;
        newbase->adjvex = vex2;                     //在vex1指向vex2
        newbase->nextarc = NULL;       //下条弧置空
        newbase->info = NULL;
        if((*G)->vertices[vex1].firstarc == NULL)   //如果头结点为空
        {
            (*G)->vertices[vex1].firstarc = newbase;  //将该节点赋值给头结点
        }
        else    //不空
        {
            tail = (*G)->vertices[vex1].firstarc;
            while(tail->nextarc)   //遍历找到最后一个结点
            {
                tail = tail->nextarc;
            }
            tail->nextarc = newbase;   //再赋值
        }
        //对vex2创建节点
        newbase = (ArcNode*) malloc(sizeof(ArcNode));  //创建新的弧节点
        if(!newbase)          //内存申请失败
            return OVERFLOW;
        newbase->adjvex = vex1;                     //在vex2指向vex1
        newbase->nextarc = NULL;              //下条弧置空
        newbase->info = NULL;
        if((*G)->vertices[vex2].firstarc == NULL)   //如果头结点为空
        {
            (*G)->vertices[vex2].firstarc = newbase;  //将该节点赋值给头结点
        }
        else    //不空
        {
            tail = (*G)->vertices[vex2].firstarc;
            while(tail->nextarc)   //遍历找到最后一个结点
            {
                tail = tail->nextarc;
            }
            tail->nextarc = newbase;   //再赋值
        }
        printf("该弧创建成功\n");
    }
    return OK;
}

/** \brief  销毁图：函数名称是DestroyBiTree(T)
 *
 *          初始条件图G已存在；操作结果是销毁图G。
 */

status DestroyGraph(ALGraph **G)
{
    int i;
    ArcNode *temparc, *tail;

    //先销毁弧
    for(i=0; i<(*G)->vexnum; i++)  //遍历节点
    {
        tail = (*G)->vertices[i].firstarc;
        while(tail)       //销毁每个弧节点
        {
            temparc = tail;
            tail = tail->nextarc;    // 遍历
            free(temparc);
        }
    }

    free(*G);  //直接释放图，因为点节点是其中的成员
    (*G) = NULL; //销毁置空
    return OK;
}

/** \brief  查找顶点：函数名称是LocateVex(G,u)；
 *
 *           初始条件是图G存在，u和G中的顶点具有相同特征；
 *          操作结果是若u在图G中存在，返回顶点u的位置信息，否则返回其它信息。
 */
status LocateVex(ALGraph G,VertexType u)
{
    int i;
    for(i=0; i<G.vexnum; i++)    //遍历查找
    {
        if(!strcmp(u,G.vertices[i].data))
            return i;                      //找到返回位置
    }
    return -1;       //没找到返回-1
}

/** \brief  获得顶点值：函数名称是GetVex (G,v)；
 *
 *          初始条件是图G存在，v是G中的某个顶点；操作结果是返回v的值。
 */
char* GetVex(ALGraph *G,int v)
{
    if(v<G->vexnum && 0<= v)         //判断输入是否合法
        return G->vertices[v].data;
    else return NULL;           //非法返回空
}


/** \brief  顶点赋值：函数名称是PutVex (G,v,value)；
 *
 *          初始条件是图G存在，v是G中的某个顶点；操作结果是对v赋值value。
 */
status PutVex (ALGraph *G,int v,VertexType value)
{
    if(v<G->vexnum && 0<= v)         //判断输入是否合法
    {
        strcpy(G->vertices[v].data, value); //赋值
        return OK;
    }
    else return ERROR;           //非法返回空
}

/** \brief  获得第一邻接点：函数名称是FirstAdjVex(&G, v)；
 *
 *          初始条件是图G存在，v是G的一个顶点；
 *          操作结果是返回v的第一个邻接顶点，如果v没有邻接顶点，返回“空”。
 */
int FirstAdjVex(ALGraph G,VertexType v)
{
    int i;
    for(i=0; i<G.vexnum; i++)    //遍历查找
    {
        if(!strcmp(v, G.vertices[i].data))        //比较信息
        {
            if(G.vertices[i].firstarc)
                return G.vertices[i].firstarc->adjvex; //找到
            else return -1;       // 找不到
        }
    }
    return -1;      //-1表示空
}

/** \brief  获得下一邻接点：函数名称是NextAdjVex(&G, v, w)；
 *
 *          初始条件是图G存在，v是G的一个顶点,w是v的邻接顶点；
 *          操作结果是返回v的（相对于w）下一个邻接顶点，如果w是最后一个邻接顶点，返回“空”。
 */
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
    int i;
    ArcNode *tail;
    for(i=0; i<G.vexnum; i++)    //遍历查找
    {
        if(!strcmp(v, G.vertices[i].data))        //比较信息v 找到v
        {
            tail = G.vertices[i].firstarc;
            while(tail)           //遍历v的节点，比较w
            {
                if(!strcmp(w, G.vertices[(tail->adjvex)].data))  //找到w
                {
                    if(tail->nextarc)
                        return tail->nextarc->adjvex;    //找到
                    else return -1;            // 找不到
                }
                tail = tail->nextarc;
            }
        }
    }
    return -1;         //最后如果找不到-1表示空
}


/** \brief  插入顶点：函数名称是InsertVex(&G,v)；
 *
 *      初始条件是图G存在，v和G中的顶点具有相同特征；操作结果是在图G中增加新顶点v。
 */
status InsertVex(ALGraph *G,VertexType v)
{
    G->vexnum++;    //顶点数++
    strcpy(G->vertices[G->vexnum-1].data, v); //赋值
    G->vertices[G->vexnum-1].firstarc = NULL; //置空

    return OK;
}


/** \brief  删除顶点：函数名称是DeleteVex(&G,v)；
 *
 *         初始条件是图G存在，v是G的一个顶点；操作结果是在图G中删除顶点v和与v相关的弧。
 */
status DeleteVex(ALGraph *G,VertexType v)
{
    int i, j, vex, flag = 0;
    VertexType w;
    ArcNode *tail;
    for(i=0; i<G->vexnum; i++)    //遍历查找v
    {
        if(!strcmp(v, G->vertices[i].data))        //比较信息
        {
            vex = i;                          //查找v位置
            flag = 1;      //找到
        }
    }
    if(flag == 0)   //没有找到v
    {
        return ERROR;
    }

    //先删除所有跟v节点有关的弧
    for(i=0; i<G->vexnum; i++)
    {
        strcpy(w, G->vertices[i].data);
        DeleteArc(G, v, w);      //直接调用DeleteArc函数来删除
    }

    //删除在表中的顶点, 并使后面的顶点前移
    for(j=vex ; j<G->vexnum-1 ; j++)
    {
        G->vertices[j] = G->vertices[j+1];
    }
    G->vexnum--;         //顶点数--

    //更新其他顶点在链表中的位置
    for(i=0; i<G->vexnum; i++)
    {
        tail = G->vertices[i].firstarc;
        while(tail)          //遍历每个顶点的邻接顶点
        {
            if(tail->adjvex > vex)
                tail->adjvex--;        //向前移一位
            tail = tail->nextarc;
        }
    }

    return OK;
}


/** \brief  插入弧：函数名称是InsertArc(&G,v,w)
 *
 *      初始条件是图G存在，v、w是G的顶点；
 *      操作结果是在图G中增加弧<v,w>，如果图G是无向图，还需要增加<w,v>。
 */
status InsertArc(ALGraph *G,VertexType v,VertexType w)
{
    int vex1,vex2, flag1 = 0, flag2 = 0;
    int i;
    ArcNode *newbase, *tail;
    for(i=0; i<G->vexnum; i++)    //遍历查找v
    {
        if(!strcmp(v, G->vertices[i].data))        //比较信息
        {
            vex1 = i;
            flag1 = 1;
            break;
        }
    }
    for(i=0; i<G->vexnum; i++)    //遍历查找w
    {
        if(!strcmp(w, G->vertices[i].data))        //比较信息
        {
            vex2 = i;
            flag2 = 1;
            break;
        }
    }
    if(flag1 == 0 || flag2 == 0)
        return ERROR;
    //先对vex1创建节点
    newbase = (ArcNode*) malloc(sizeof(ArcNode));  //创建新的弧节点
    if(!newbase)          //内存申请失败
        return OVERFLOW;
    newbase->adjvex = vex2;                     //在vex1指向vex2
    newbase->nextarc = NULL;       //下条弧置空
    newbase->info = NULL;
    if((G)->vertices[vex1].firstarc == NULL)   //如果头结点为空
    {
        (G)->vertices[vex1].firstarc = newbase;  //将该节点赋值给头结点
    }
    else    //不空
    {
        tail = (G)->vertices[vex1].firstarc;
        while(tail->nextarc)   //遍历找到最后一个结点
        {
            tail = tail->nextarc;
        }
        tail->nextarc = newbase;   //再赋值
    }
    //对vex2创建节点
    newbase = (ArcNode*) malloc(sizeof(ArcNode));  //创建新的弧节点
    if(!newbase)          //内存申请失败
        return OVERFLOW;
    newbase->adjvex = vex1;                     //在vex2指向vex1
    newbase->nextarc = NULL;              //下条弧置空
    newbase->info = NULL;
    if(G->vertices[vex2].firstarc == NULL)   //如果头结点为空
    {
        G->vertices[vex2].firstarc = newbase;  //将该节点赋值给头结点
    }
    else    //不空
    {
        tail = (G)->vertices[vex2].firstarc;
        while(tail->nextarc)   //遍历找到最后一个结点
        {
            tail = tail->nextarc;
        }
        tail->nextarc = newbase;   //再赋值
    }
    printf("该弧创建成功\n");
    G->arcnum++;  //弧数+1
    return OK;
}

/** \brief  删除弧：函数名称是DeleteArc(&G,v,w)；
 *
 *  初始条件是图G存在，v、w是G的顶点；操作结果是在图G中删除弧<v,w>，如果图G是无向图，还需要删除<w,v>。
 */
status DeleteArc(ALGraph *G,VertexType v,VertexType w)
{
    int vex1,vex2, flag = 0, flag1 = 0, flag2 = 0;
    int i;
    ArcNode *tail, *p;

    if(!strcmp(v, w))       //输入了相同顶点错误
        return ERROR;

    for(i=0; i<G->vexnum; i++)    //遍历查找v
    {
        if(!strcmp(v, G->vertices[i].data))        //比较信息
        {
            vex1 = i;
            flag1 =1;
            break;
        }
    }
    for(i=0; i<G->vexnum; i++)    //遍历查找w
    {
        if(!strcmp(w, G->vertices[i].data))        //比较信息
        {
            vex2 = i;
            flag2 = 1;
            break;
        }
    }
    if(flag1 == 0 || flag2 == 0)   //没有找到两节点
        return ERROR;
    //先删除vex1节点中的
    tail = G->vertices[vex1].firstarc;
    if(tail)   //遇到该节点没有任何弧
    {
        if(tail->adjvex == vex2)          //如果是头结点
        {
            G->vertices[vex1].firstarc = tail->nextarc;    //头结点指向下一个
            free(tail);
            flag = 1;          //flag 标记是否找到
        }
        else  //非头结点
        {
            p = tail;
            tail = tail->nextarc;
            while(tail)
            {
                if(tail->adjvex == vex2)          //找到
                {
                    p->nextarc = tail->nextarc;     //结点指向下一个
                    free(tail);
                    flag = 1;          //flag 标记是否找到
                    break;
                }
                p = tail;
                tail = tail->nextarc;
            }
        }
    }
    //删除vex2节点中的
    tail = G->vertices[vex2].firstarc;
    if(tail)        //遇到该节点没有任何弧
    {
        if(tail->adjvex == vex1)          //如果是头结点
        {
            G->vertices[vex2].firstarc = tail->nextarc;    //头结点指向下一个
            free(tail);
            flag = 1;          //flag 标记是否找到
        }
        else  //非头结点
        {
            p = tail;
            tail = tail->nextarc;
            while(tail)
            {
                if(tail->adjvex == vex1)          //找到
                {
                    p->nextarc = tail->nextarc;     //结点指向下一个
                    free(tail);
                    flag = 1;          //flag 标记是否找到
                    break;
                }
                p = tail;
                tail = tail->nextarc;
            }
        }
    }

    if(flag == 1)     //删除成功
    {
        G->arcnum--;    //弧长-1
        return OK;
    }
    else
        return FALSE;
}


/** \brief  深度优先搜索遍历：函数名称是DFSTraverse(G,visit())
 *
 *  初始条件是图G存在；操作结果是图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次。
 */
status DFSTraverse(ALGraph G,void (*visit)(char*))
{
    int i;
    for(i=0; i<G.vexnum; i++)  //标志数组初始化
        visited[i] = FALSE;
    for(i=0; i<G.vexnum; i++)
        if(!visited[i]) DFS(G, i, visit);    //访问未访问的顶点
    return OK;
}

/** \brief 广深度优先搜索遍历：函数名称是BFSTraverse(G,visit())；
 *
 *  初始条件是图G存在；操作结果是图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次。
 */
status BFSTraverse(ALGraph G,void (*visit)(char *))
{
    int i, u;
    int Queue[MAX_VERTEX_NUM];
    int *qhead, *qtail;
    ArcNode *tail;
    for(i=0; i<G.vexnum; i++)  //标志数组初始化
        visited[i] = FALSE;

    qhead = Queue;
    qtail = qhead;
    for(i=0; i<G.vexnum; i++)
        if(!visited[i])      //没有被访问
        {
            visit(G.vertices[i].data);
            visited[i] = TRUE;      //访问标记
            *qhead = i;       //i入队列
            qhead++;        //队头前移
            while(qhead != qtail)   //队空
            {
                u = *qtail;    //出队
                qtail++;
                tail = G.vertices[u].firstarc;
                while(tail)                 //遍历队尾的邻接点
                {
                    if(!visited[tail->adjvex])      //没有被访问则访问
                    {
                        visit(G.vertices[tail->adjvex].data);
                        visited[tail->adjvex] = TRUE;                //标记
                        *qhead = tail->adjvex;       //使其入队
                        qhead++;
                    }
                    tail = tail->nextarc;
                }
            }
        }

    return OK;
}

void DFS(ALGraph G, int v, void (*visit)(char*))
{
    ArcNode *tail;
    visit(G.vertices[v].data);        //访问第v个顶点
    visited[v] = TRUE;             //标记

    tail = G.vertices[v].firstarc;
    while(tail)              //遍历邻接节点
    {
        if(!visited[tail->adjvex])
            DFS(G, tail->adjvex, visit);       //若没有访问，递归处理
        tail = tail->nextarc;
    }
}

void printf_my(char* a)
{
    printf("%s  ",a);
}
