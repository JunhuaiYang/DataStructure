/**
 *         该文件用于储存函数实现
 *
 */

 #include"list.h"

//发现在标准C语言中，函数参数无法使用&传递
//把所有&L改为了*L

/** \brief 初始化表 函数名称是InitaList(L)
 *        初始条件是线性表L不存在，操作结果是构造一个空的线性表
 */
status IntiaList(LinkList *L)
{
    *L = (LNode*)malloc(sizeof(LNode));  //申请一个头结点
    (*L)->next = NULL;           //赋空

	return OK;
}

/** \brief 销毁表 函数名称是DestroyList(L)
 *        初始条件是线性表L已存在；操作结果是销毁线性表L
 */
status DestroyList(LinkList *L)
{
    LNode *tail, *p;
    tail = *L;
    if(tail->next == NULL)
    {
        free(tail);          //当其为空链表时
    }
    else     //当其为非空链表时
    {
        p = tail;
        tail = tail->next;
        while(tail)   //销毁每个几点
        {
            tail = tail->next;
            free(p);      //释放空间
            p = tail;
        }

    }
    *L = NULL;   //将L置空

    return OK;
}

/** \brief 清空表 函数名称是ClearList(L)
 *        初始条件是线性表L已存在；操作结果是将L重置为空表。
 */
status ClearList(LinkList L)
{
    LNode *tail, *p;
    tail = L;
    if(tail->next == NULL)  //当其为空链表时
    {
        printf("该线性表已经为空表！\n");
        getch();
        return OK;
    }
    else     //当其为非空链表时,释放数据节点
    {
        p = tail->next;
        tail = tail->next;  //跳过头结点
        while(tail)
        {
            tail =tail->next;  //tail遍历
            free(p);       //释放临时节点p
            p = tail;
        }
        L->next = NULL;  //将节点的next置为空
        return OK;
    }
}

/** \brief 判定空表  函数名称是ListEmpty(L)
 *        初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
 */
status ListEmpty(LinkList L)
{
    if(L->next == NULL) return TRUE;  //头结点没有指向则为空
    else return FALSE;
}

/** \brief 求表长
 *        初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
 */
int ListLength(LinkList L)
{
    LNode *tail = L;
    int count = 0;
    if(tail->next == NULL)   //空表时表长为0
    {
        count = 0;
    }
    else   //非空表时
    {
        tail = tail->next;   //遍历
        while(tail)
        {
            count++;       //count 计数
            tail = tail->next;
        }
    }
    return count;
}

/** \brief 获得元素 函数名称是GetElem(L,i,e)；
 *        初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值。
 */
status GetElem(LinkList L,int i,ElemType *e)
{
    LNode *tail = L;
    int count;
    if(tail->next == NULL)   //空表
    {
        return ERROR;
    }
    else
    {
        tail = tail->next;
        while(tail)   //遍历
        {
            count++;
            if(count == i)        //查找元素
            {
                *e = tail->data;   //找到用e返回
                return OK;
            }
            tail = tail->next;
        }
        return ERROR;  //没有找到返回错误
    }

}

/** \brief 查找元素 函数名称是LocateElem(L,e,compare())；
 *        初始条件是线性表已存在；
 *        操作结果是返回L中第1个与e满足关系compare（）关系的数据元素的位序，若这样的数据元素不存在，则返回值为0。
 */
int LocateElem(LinkList L,ElemType e, status(*compare)(ElemType,ElemType))
{
    LNode *tail = L;
    int count = 0;
    if(tail->next == NULL)   //空表
    {
        printf("\n该表为空表！\n");
        return ERROR;
    }
    else      //非空表
    {
        tail = tail->next;
        while(tail)         //遍历
        {
            count++;
            if(compare(tail->data,e))   //判断相等条件
            {
                return count;      //返回位序
            }
            tail = tail->next;
        }
        return ERROR;   //没有找到返回错误
    }
}

/** \brief 获得前驱 函数名称是PriorElem(L,cur_e,pre_e)；
 *        初始条件是线性表L已存在
 *        操作结果是若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
 *
 */
status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
{
    LNode *tail = L, *p;
    if(tail->next == NULL)   //空表
    {
        printf("该表为空表！\n");
        return ERROR;
    }
    else      //为非空表
    {
        tail = tail->next;
        if(tail->data == cur_e) return ERROR;  //遇到第一个报错
        p = tail;         //p为临时指针
        tail = tail->next;  //遍历
        while(tail)
        {
            if(tail->data == cur_e)  //遍历找到
            {
                *pre_e = p->data;  //返回临时指针的值
                return OK;
            }
            p = tail;          //临时指针为tail的上一个
            tail = tail->next;
        }
        return ERROR;  //没有找到返回错误
    }
    return OK;
}

/** \brief 获得后继 函数名称是NextElem(L,cur_e,next_e)
 *        初始条件是线性表L已存在；
 *        操作结果是若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义。
 *
 */
status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
{
    LNode *tail = L;
    if(tail->next == NULL)   //空表
    {
        printf("该表为空表！\n");
        return ERROR;
    }
    else   //非空表时
    {
        tail = tail->next;
        while(tail)      //遍历
        {
            if(tail->data == cur_e)
            {
                if(tail->next)    //查找后继
                {
                    *next_e = tail->next->data;      //找到则返回下一个的值
                    return OK;
                }
                else
                {
                    return ERROR;   //遇到最后一个元素返回错误
                }
            }
            tail = tail->next;
        }
        return ERROR;    //没有找到返回错误
    }
}

/** \brief 插入元素
 *        函数名称是ListInsert(L,i,e)；
 *        初始条件是线性表L已存在且非空，1≤i≤ListLength(L)+1；
 *        操作结果是在L的第i个位置之前插入新的数据元素e。
 *
 */
status ListInsert(LinkList L,int i,ElemType e)
{
    LNode *p = L, *s;
    int j = 0;
    while(p && j<i-1)           //寻找第i-1个节点
    {
        p = p->next;
        j++;
    }
    if(!p || j>i-1) return ERROR;         //输入非法
    s = (LNode*)malloc(sizeof(LNode));   //生成新节点
    s->data = e;                 //插入新节点
    s->next = p->next;
    p->next = s;

    return OK;
}

/** \brief 删除元素
 *        函数名称是ListDelete(L,i,e)；
 *        初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；
 *        操作结果：删除L的第i个数据元素，用e返回其值。
 *
 */
status ListDelete(LinkList L,int i,ElemType *e)
{
    LNode *p = L, *q;
    int j = 0;
    while(p->next && j<i-1)    //寻找第i个节点，此时p为i-1个节点
    {
        p = p->next;
        j++;
    }
    if(!(p->next) || j>i-1) return ERROR; //该节点不存在，删除位置不合理
    q = p->next;     //q为i位置上的要删除的元素
    p->next = q->next;   //链接两链表
    *e = q->data;
    free(q);

    return OK;
}

/** \brief 遍历表
 *        函数名称是ListTraverse(L,visit())
 *        初始条件是线性表L已存在；
 *        操作结果是依次对L的每个数据元素调用函数visit()。
 *
 */
status ListTrabverse(LinkList L,void (*visit)(int))
{
   LNode *tail = L;
   if(tail->next == NULL)    //为空表时
   {
       return ERROR;
   }
   tail = tail->next;
   printf("\n-----------all elements -----------------------\n");
   while(tail)
   {
       printf("%d ",tail->data);     //遍历输出
       tail = tail->next;
   }
   printf("\n------------------ end ------------------------\n");
   return OK;
}


/** \brief 大小相等判断
 *
 */
status Equal(ElemType a,ElemType b)
{
    if(a == b) return TRUE;
    else return FALSE;
}

/** \brief 输出函数
 *
 */
void print(int a)
{
    printf("%d ",a);
}

/** \brief 保存表到文件
 *
 *        储存格式为 名称 length  数据\n
 *
 */
status SaveList(LinkList L)
{
    FILE *fp = fopen("list.dat","a");   //打开方式为a，在已有文件内容后面写
    LNode *tail;
    if(fp != NULL)
    {
        tail = L->next;
        fprintf(fp,"%s %d",name, ListLength(L));
        while(tail)
        {
            fprintf(fp," %d",tail->data);   //遍历链表储存到文件
            tail = tail->next;
        }
        fprintf(fp,"\n");
        fclose(fp);
        printf("\n文件保存成功！");
        getch();
        return OK;
    }
    else
    {
        printf("文件打开失败！");
        return ERROR;
    }
}

/** \brief 读取数据
 *
 *        读取文件中的数据并加载到线性表中
 *
 */
status LoadList(LinkList *L)
{
    FILE *fp = fopen("list.dat","r");
    FILE *tpf;
    fpos_t fps;   //文件光标位置
    LNode *tail, *p;
    int i=0;
    int t, flag = 1, length;
    char tname[10],iname[10];
    if (fp != NULL)
    {
        printf("当前文件中存在的线性表名称为：\n");
        tpf = fp;
        fgetpos(tpf,&fps);   //读取文件光标位置，起始值（0）
        if(*L != NULL)
        {
            DestroyList(L);
        }
        while(flag)    //遍历输出中的线性表
        {
            t = fscanf(tpf,"%s",tname);
            if(t == EOF) break;    //遇到文件尾，跳出
            printf("%s\t",tname);
            while(flag)
            {
                t = fgetc(tpf);
                if(t == EOF) flag = 0;
                if(t == '\n') break;
            }
        }
        flag = 1;
        printf("\n请选择要加载的线性表：");
        scanf("%s",iname);
        fsetpos(tpf, &fps);
        while(flag)  //查找线性表
        {
            fscanf(tpf,"%s",tname);
            if(!strcmp(tname,iname)) break;
            while(flag)
            {
                t = fgetc(tpf);
                if(t == EOF) flag = 0;
                if(t == '\n') break;
            }
        }
        if(flag == 0)
        {
            printf("\n没有找到, 错误！！！\n按任意键返回!");
            getch();
            return ERROR;
        }
        else
        {
            IntiaList(L);
            strcpy(name, tname);
            fscanf(tpf,"%d",&length);
            p = *L;
            while(i < length)         //读取文件中的线性表
            {
                tail = (LNode*)malloc(sizeof(LNode));
                fscanf(tpf,"%d", &tail->data);
                tail->next = NULL;
                p->next = tail;
                p = tail;
                i++;
            }
        }
        fclose(fp);
        printf("\n文件读取成功！");
        getch();
        return OK;
    }
    else
    {
        printf("文件打开失败！");
        return ERROR;
    }
}

/** \brief 改变当前链表的名字
 *
 */
status ChangeName(void)
{
    printf("当前链表的名字为：%s",name);
    printf("\n请输入要更改的名字：");
    scanf("%s",name);
    printf("修改成功！");
    return OK;
}
