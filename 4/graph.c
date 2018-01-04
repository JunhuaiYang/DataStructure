/** \brief  �����ڽӱ��ͼʵ��
 *         ���ļ����ڴ���������
 *
 */

#include"graph.h"

bool visited[MAX_VERTEX_NUM];     //ȫ�ֱ�������־����

/** \brief ����ͼ������������CreateCraph(&G,V,VR)
*        ��ʼ������V��ͼ�Ķ��㼯��VR��ͼ�Ĺ�ϵ������������ǰ�V��VR�Ķ��幹��ͼG��
*/
status CreateGraph(ALGraph **G)
{
    int i, vex1, vex2;
    ArcNode *newbase, *tail;

    (*G) = (ALGraph*) malloc(sizeof(ALGraph));
    printf("��ǰ����ͼ������Ϊ����ͼ��");    //����ͼ��ʵ��
    (*G)->kind = 0;
    printf("\n������ͼ�Ķ�������������");
    scanf("%d %d",&(*G)->vexnum, &(*G)->arcnum);
    printf("������ÿ�������ֵ,��%d������\n", (*G)->vexnum);
    for(i=0; i<(*G)->vexnum; i++)
    {
        scanf("%s", (*G)->vertices[i].data);     //����ÿ���ڵ������
        (*G)->vertices[i].firstarc = NULL;    //���ÿ�
    }
    //���ÿ�������λ�÷���¼��������Ϣ
    printf("��ǰÿ�������λ�����£�\n");
    for(i=0; i<(*G)->vexnum; i++)
        printf("%s\t",(*G)->vertices[i].data);
    printf("\n");
    for(i=0; i<(*G)->vexnum; i++)
        printf("%d\t", i);
    printf("\n������ÿ������������(����ļ�ֵ���ն��������˳���0��ʼ)��\n");
    for(i = 1; i<=(*G)->arcnum; i++)
    {
        printf("��ǰΪ��%d��������%d��\n",i,(*G)->arcnum);
        scanf("%d %d",&vex1, &vex2);
        if(vex1<0 || vex1 >(*G)->vexnum || vex2<0 || vex2 >(*G)->vexnum)    //����Ƿ�ʱ����
            return ERROR;
        //�ȶ�vex1�����ڵ�
        newbase = (ArcNode*) malloc(sizeof(ArcNode));  //�����µĻ��ڵ�
        if(!newbase)          //�ڴ�����ʧ��
            return OVERFLOW;
        newbase->adjvex = vex2;                     //��vex1ָ��vex2
        newbase->nextarc = NULL;       //�������ÿ�
        newbase->info = NULL;
        if((*G)->vertices[vex1].firstarc == NULL)   //���ͷ���Ϊ��
        {
            (*G)->vertices[vex1].firstarc = newbase;  //���ýڵ㸳ֵ��ͷ���
        }
        else    //����
        {
            tail = (*G)->vertices[vex1].firstarc;
            while(tail->nextarc)   //�����ҵ����һ�����
            {
                tail = tail->nextarc;
            }
            tail->nextarc = newbase;   //�ٸ�ֵ
        }
        //��vex2�����ڵ�
        newbase = (ArcNode*) malloc(sizeof(ArcNode));  //�����µĻ��ڵ�
        if(!newbase)          //�ڴ�����ʧ��
            return OVERFLOW;
        newbase->adjvex = vex1;                     //��vex2ָ��vex1
        newbase->nextarc = NULL;              //�������ÿ�
        newbase->info = NULL;
        if((*G)->vertices[vex2].firstarc == NULL)   //���ͷ���Ϊ��
        {
            (*G)->vertices[vex2].firstarc = newbase;  //���ýڵ㸳ֵ��ͷ���
        }
        else    //����
        {
            tail = (*G)->vertices[vex2].firstarc;
            while(tail->nextarc)   //�����ҵ����һ�����
            {
                tail = tail->nextarc;
            }
            tail->nextarc = newbase;   //�ٸ�ֵ
        }
        printf("�û������ɹ�\n");
    }
    return OK;
}

/** \brief  ����ͼ������������DestroyBiTree(T)
 *
 *          ��ʼ����ͼG�Ѵ��ڣ��������������ͼG��
 */

status DestroyGraph(ALGraph **G)
{
    int i;
    ArcNode *temparc, *tail;

    //�����ٻ�
    for(i=0; i<(*G)->vexnum; i++)  //�����ڵ�
    {
        tail = (*G)->vertices[i].firstarc;
        while(tail)       //����ÿ�����ڵ�
        {
            temparc = tail;
            tail = tail->nextarc;    // ����
            free(temparc);
        }
    }

    free(*G);  //ֱ���ͷ�ͼ����Ϊ��ڵ������еĳ�Ա
    (*G) = NULL; //�����ÿ�
    return OK;
}

/** \brief  ���Ҷ��㣺����������LocateVex(G,u)��
 *
 *           ��ʼ������ͼG���ڣ�u��G�еĶ��������ͬ������
 *          �����������u��ͼG�д��ڣ����ض���u��λ����Ϣ�����򷵻�������Ϣ��
 */
status LocateVex(ALGraph G,VertexType u)
{
    int i;
    for(i=0; i<G.vexnum; i++)    //��������
    {
        if(!strcmp(u,G.vertices[i].data))
            return i;                      //�ҵ�����λ��
    }
    return -1;       //û�ҵ�����-1
}

/** \brief  ��ö���ֵ������������GetVex (G,v)��
 *
 *          ��ʼ������ͼG���ڣ�v��G�е�ĳ�����㣻��������Ƿ���v��ֵ��
 */
char* GetVex(ALGraph *G,int v)
{
    if(v<G->vexnum && 0<= v)         //�ж������Ƿ�Ϸ�
        return G->vertices[v].data;
    else return NULL;           //�Ƿ����ؿ�
}


/** \brief  ���㸳ֵ������������PutVex (G,v,value)��
 *
 *          ��ʼ������ͼG���ڣ�v��G�е�ĳ�����㣻��������Ƕ�v��ֵvalue��
 */
status PutVex (ALGraph *G,int v,VertexType value)
{
    if(v<G->vexnum && 0<= v)         //�ж������Ƿ�Ϸ�
    {
        strcpy(G->vertices[v].data, value); //��ֵ
        return OK;
    }
    else return ERROR;           //�Ƿ����ؿ�
}

/** \brief  ��õ�һ�ڽӵ㣺����������FirstAdjVex(&G, v)��
 *
 *          ��ʼ������ͼG���ڣ�v��G��һ�����㣻
 *          ��������Ƿ���v�ĵ�һ���ڽӶ��㣬���vû���ڽӶ��㣬���ء��ա���
 */
int FirstAdjVex(ALGraph G,VertexType v)
{
    int i;
    for(i=0; i<G.vexnum; i++)    //��������
    {
        if(!strcmp(v, G.vertices[i].data))        //�Ƚ���Ϣ
        {
            if(G.vertices[i].firstarc)
                return G.vertices[i].firstarc->adjvex; //�ҵ�
            else return -1;       // �Ҳ���
        }
    }
    return -1;      //-1��ʾ��
}

/** \brief  �����һ�ڽӵ㣺����������NextAdjVex(&G, v, w)��
 *
 *          ��ʼ������ͼG���ڣ�v��G��һ������,w��v���ڽӶ��㣻
 *          ��������Ƿ���v�ģ������w����һ���ڽӶ��㣬���w�����һ���ڽӶ��㣬���ء��ա���
 */
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
    int i;
    ArcNode *tail;
    for(i=0; i<G.vexnum; i++)    //��������
    {
        if(!strcmp(v, G.vertices[i].data))        //�Ƚ���Ϣv �ҵ�v
        {
            tail = G.vertices[i].firstarc;
            while(tail)           //����v�Ľڵ㣬�Ƚ�w
            {
                if(!strcmp(w, G.vertices[(tail->adjvex)].data))  //�ҵ�w
                {
                    if(tail->nextarc)
                        return tail->nextarc->adjvex;    //�ҵ�
                    else return -1;            // �Ҳ���
                }
                tail = tail->nextarc;
            }
        }
    }
    return -1;         //�������Ҳ���-1��ʾ��
}


/** \brief  ���붥�㣺����������InsertVex(&G,v)��
 *
 *      ��ʼ������ͼG���ڣ�v��G�еĶ��������ͬ�����������������ͼG�������¶���v��
 */
status InsertVex(ALGraph *G,VertexType v)
{
    G->vexnum++;    //������++
    strcpy(G->vertices[G->vexnum-1].data, v); //��ֵ
    G->vertices[G->vexnum-1].firstarc = NULL; //�ÿ�

    return OK;
}


/** \brief  ɾ�����㣺����������DeleteVex(&G,v)��
 *
 *         ��ʼ������ͼG���ڣ�v��G��һ�����㣻�����������ͼG��ɾ������v����v��صĻ���
 */
status DeleteVex(ALGraph *G,VertexType v)
{
    int i, j, vex, flag = 0;
    VertexType w;
    ArcNode *tail;
    for(i=0; i<G->vexnum; i++)    //��������v
    {
        if(!strcmp(v, G->vertices[i].data))        //�Ƚ���Ϣ
        {
            vex = i;                          //����vλ��
            flag = 1;      //�ҵ�
        }
    }
    if(flag == 0)   //û���ҵ�v
    {
        return ERROR;
    }

    //��ɾ�����и�v�ڵ��йصĻ�
    for(i=0; i<G->vexnum; i++)
    {
        strcpy(w, G->vertices[i].data);
        DeleteArc(G, v, w);      //ֱ�ӵ���DeleteArc������ɾ��
    }

    //ɾ���ڱ��еĶ���, ��ʹ����Ķ���ǰ��
    for(j=vex ; j<G->vexnum-1 ; j++)
    {
        G->vertices[j] = G->vertices[j+1];
    }
    G->vexnum--;         //������--

    //�������������������е�λ��
    for(i=0; i<G->vexnum; i++)
    {
        tail = G->vertices[i].firstarc;
        while(tail)          //����ÿ��������ڽӶ���
        {
            if(tail->adjvex > vex)
                tail->adjvex--;        //��ǰ��һλ
            tail = tail->nextarc;
        }
    }

    return OK;
}


/** \brief  ���뻡������������InsertArc(&G,v,w)
 *
 *      ��ʼ������ͼG���ڣ�v��w��G�Ķ��㣻
 *      �����������ͼG�����ӻ�<v,w>�����ͼG������ͼ������Ҫ����<w,v>��
 */
status InsertArc(ALGraph *G,VertexType v,VertexType w)
{
    int vex1,vex2, flag1 = 0, flag2 = 0;
    int i;
    ArcNode *newbase, *tail;
    for(i=0; i<G->vexnum; i++)    //��������v
    {
        if(!strcmp(v, G->vertices[i].data))        //�Ƚ���Ϣ
        {
            vex1 = i;
            flag1 = 1;
            break;
        }
    }
    for(i=0; i<G->vexnum; i++)    //��������w
    {
        if(!strcmp(w, G->vertices[i].data))        //�Ƚ���Ϣ
        {
            vex2 = i;
            flag2 = 1;
            break;
        }
    }
    if(flag1 == 0 || flag2 == 0)
        return ERROR;
    //�ȶ�vex1�����ڵ�
    newbase = (ArcNode*) malloc(sizeof(ArcNode));  //�����µĻ��ڵ�
    if(!newbase)          //�ڴ�����ʧ��
        return OVERFLOW;
    newbase->adjvex = vex2;                     //��vex1ָ��vex2
    newbase->nextarc = NULL;       //�������ÿ�
    newbase->info = NULL;
    if((G)->vertices[vex1].firstarc == NULL)   //���ͷ���Ϊ��
    {
        (G)->vertices[vex1].firstarc = newbase;  //���ýڵ㸳ֵ��ͷ���
    }
    else    //����
    {
        tail = (G)->vertices[vex1].firstarc;
        while(tail->nextarc)   //�����ҵ����һ�����
        {
            tail = tail->nextarc;
        }
        tail->nextarc = newbase;   //�ٸ�ֵ
    }
    //��vex2�����ڵ�
    newbase = (ArcNode*) malloc(sizeof(ArcNode));  //�����µĻ��ڵ�
    if(!newbase)          //�ڴ�����ʧ��
        return OVERFLOW;
    newbase->adjvex = vex1;                     //��vex2ָ��vex1
    newbase->nextarc = NULL;              //�������ÿ�
    newbase->info = NULL;
    if(G->vertices[vex2].firstarc == NULL)   //���ͷ���Ϊ��
    {
        G->vertices[vex2].firstarc = newbase;  //���ýڵ㸳ֵ��ͷ���
    }
    else    //����
    {
        tail = (G)->vertices[vex2].firstarc;
        while(tail->nextarc)   //�����ҵ����һ�����
        {
            tail = tail->nextarc;
        }
        tail->nextarc = newbase;   //�ٸ�ֵ
    }
    printf("�û������ɹ�\n");
    G->arcnum++;  //����+1
    return OK;
}

/** \brief  ɾ����������������DeleteArc(&G,v,w)��
 *
 *  ��ʼ������ͼG���ڣ�v��w��G�Ķ��㣻�����������ͼG��ɾ����<v,w>�����ͼG������ͼ������Ҫɾ��<w,v>��
 */
status DeleteArc(ALGraph *G,VertexType v,VertexType w)
{
    int vex1,vex2, flag = 0, flag1 = 0, flag2 = 0;
    int i;
    ArcNode *tail, *p;

    if(!strcmp(v, w))       //��������ͬ�������
        return ERROR;

    for(i=0; i<G->vexnum; i++)    //��������v
    {
        if(!strcmp(v, G->vertices[i].data))        //�Ƚ���Ϣ
        {
            vex1 = i;
            flag1 =1;
            break;
        }
    }
    for(i=0; i<G->vexnum; i++)    //��������w
    {
        if(!strcmp(w, G->vertices[i].data))        //�Ƚ���Ϣ
        {
            vex2 = i;
            flag2 = 1;
            break;
        }
    }
    if(flag1 == 0 || flag2 == 0)   //û���ҵ����ڵ�
        return ERROR;
    //��ɾ��vex1�ڵ��е�
    tail = G->vertices[vex1].firstarc;
    if(tail)   //�����ýڵ�û���κλ�
    {
        if(tail->adjvex == vex2)          //�����ͷ���
        {
            G->vertices[vex1].firstarc = tail->nextarc;    //ͷ���ָ����һ��
            free(tail);
            flag = 1;          //flag ����Ƿ��ҵ�
        }
        else  //��ͷ���
        {
            p = tail;
            tail = tail->nextarc;
            while(tail)
            {
                if(tail->adjvex == vex2)          //�ҵ�
                {
                    p->nextarc = tail->nextarc;     //���ָ����һ��
                    free(tail);
                    flag = 1;          //flag ����Ƿ��ҵ�
                    break;
                }
                p = tail;
                tail = tail->nextarc;
            }
        }
    }
    //ɾ��vex2�ڵ��е�
    tail = G->vertices[vex2].firstarc;
    if(tail)        //�����ýڵ�û���κλ�
    {
        if(tail->adjvex == vex1)          //�����ͷ���
        {
            G->vertices[vex2].firstarc = tail->nextarc;    //ͷ���ָ����һ��
            free(tail);
            flag = 1;          //flag ����Ƿ��ҵ�
        }
        else  //��ͷ���
        {
            p = tail;
            tail = tail->nextarc;
            while(tail)
            {
                if(tail->adjvex == vex1)          //�ҵ�
                {
                    p->nextarc = tail->nextarc;     //���ָ����һ��
                    free(tail);
                    flag = 1;          //flag ����Ƿ��ҵ�
                    break;
                }
                p = tail;
                tail = tail->nextarc;
            }
        }
    }

    if(flag == 1)     //ɾ���ɹ�
    {
        G->arcnum--;    //����-1
        return OK;
    }
    else
        return FALSE;
}


/** \brief  ���������������������������DFSTraverse(G,visit())
 *
 *  ��ʼ������ͼG���ڣ����������ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ�Ρ�
 */
status DFSTraverse(ALGraph G,void (*visit)(char*))
{
    int i;
    for(i=0; i<G.vexnum; i++)  //��־�����ʼ��
        visited[i] = FALSE;
    for(i=0; i<G.vexnum; i++)
        if(!visited[i]) DFS(G, i, visit);    //����δ���ʵĶ���
    return OK;
}

/** \brief �����������������������������BFSTraverse(G,visit())��
 *
 *  ��ʼ������ͼG���ڣ����������ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ�Ρ�
 */
status BFSTraverse(ALGraph G,void (*visit)(char *))
{
    int i, u;
    int Queue[MAX_VERTEX_NUM];
    int *qhead, *qtail;
    ArcNode *tail;
    for(i=0; i<G.vexnum; i++)  //��־�����ʼ��
        visited[i] = FALSE;

    qhead = Queue;
    qtail = qhead;
    for(i=0; i<G.vexnum; i++)
        if(!visited[i])      //û�б�����
        {
            visit(G.vertices[i].data);
            visited[i] = TRUE;      //���ʱ��
            *qhead = i;       //i�����
            qhead++;        //��ͷǰ��
            while(qhead != qtail)   //�ӿ�
            {
                u = *qtail;    //����
                qtail++;
                tail = G.vertices[u].firstarc;
                while(tail)                 //������β���ڽӵ�
                {
                    if(!visited[tail->adjvex])      //û�б����������
                    {
                        visit(G.vertices[tail->adjvex].data);
                        visited[tail->adjvex] = TRUE;                //���
                        *qhead = tail->adjvex;       //ʹ�����
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
    visit(G.vertices[v].data);        //���ʵ�v������
    visited[v] = TRUE;             //���

    tail = G.vertices[v].firstarc;
    while(tail)              //�����ڽӽڵ�
    {
        if(!visited[tail->adjvex])
            DFS(G, tail->adjvex, visit);       //��û�з��ʣ��ݹ鴦��
        tail = tail->nextarc;
    }
}

void printf_my(char* a)
{
    printf("%s  ",a);
}
