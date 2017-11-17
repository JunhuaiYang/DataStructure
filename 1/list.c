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
status IntiaList(SqList **L)
{
    *L = (SqList*)malloc(sizeof(SqList));
	(*L)->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!(*L)->elem) return (OVERFLOW);  //分配失败
	(*L)->length=0;                  //置空表
    (*L)->listsize=LIST_INIT_SIZE;   //初始容量
    printf("    Please input the name of the list :");
    scanf("%s",(*L)->name);
	return OK;
}

/** \brief 销毁表 函数名称是DestroyList(L)
 *        初始条件是线性表L已存在；操作结果是销毁线性表L
 */
status DestroyList(SqList **L)
{
    int i;
    int *tail;
    for(i = 0; i<(*L)->listsize; i++)  //释放elem申请的内存空间
    {
        tail = (*L)->elem++;
        free(tail);
    }
    free((*L)); //释放L
    *L = NULL;

    return OK;
}

/** \brief 清空表 函数名称是ClearList(L)
 *        初始条件是线性表L已存在；操作结果是将L重置为空表。
 */
status ClearList(SqList *L)
{
    L->length = 0;  //直接将长度置0
    return OK;
}

/** \brief 判定空表  函数名称是ListEmpty(L)
 *        初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
 */
status ListEmpty(SqList L)
{
    if(L.length == 0) return TRUE;
    else return FALSE;
}

/** \brief 求表长
 *        初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
 */
int ListLength(SqList L)
{
    return L.length;
}

/** \brief 获得元素 函数名称是GetElem(L,i,e)；
 *        初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值。
 */
status GetElem(SqList L,int i,ElemType *e)
{
    if(i> L.length) return (ERROR);
    *e = L.elem[i-1];
    return OK;

}

/** \brief 查找元素 函数名称是LocateElem(L,e,compare())；
 *        初始条件是线性表已存在；
 *        操作结果是返回L中第1个与e满足关系compare（）关系的数据元素的位序，若这样的数据元素不存在，则返回值为0。
 */
int LocateElem(SqList L,ElemType e, status(*compare)(ElemType,ElemType))
{
    int i = 1;
    int *p = L.elem;
    while(i<=L.listsize && !((*compare)(*p++,e))) i++;
    if(i<=L.length) return i;
    else return 0;
}

/** \brief 获得前驱 函数名称是PriorElem(L,cur_e,pre_e)；
 *        初始条件是线性表L已存在
 *        操作结果是若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
 *
 */
status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
{
    int i;
    if(cur_e == *L.elem)   //判断是否是第一个元素
        return (ERROR);
    i = LocateElem(L,cur_e, Equal);   //查找该元素地址
    if(i == 0 )
    {
        printf("\n没有找到元素！");    //没有找到则指向空指针
        return FALSE;
    }
    else *pre_e = L.elem[i-2];
    return OK;
}

/** \brief 获得后继 函数名称是NextElem(L,cur_e,next_e)
 *        初始条件是线性表L已存在；
 *        操作结果是若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义。
 *
 */
status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
{
    int i;
    if(cur_e == L.elem[L.length-1]) //判断是否为是否是最后一个
        return (ERROR);
    i = LocateElem(L,cur_e,Equal); //查找
    if(i == 0 )
    {
        printf("\n没有找到元素！");    //没有找到则指向空指针
        return FALSE;
    }
    else *next_e = L.elem[i];
    return OK;
}

/** \brief 插入元素
 *        函数名称是ListInsert(L,i,e)；
 *        初始条件是线性表L已存在且非空，1≤i≤ListLength(L)+1；
 *        操作结果是在L的第i个位置之前插入新的数据元素e。
 *
 */
status ListInsert(SqList *L,int i,ElemType e)
{
    ElemType *newbase;
    int *p, *q;
    if(i<1 || i>L->length+1) return ERROR;  //判断输入是否合法
    //是否表满
    if(L->length >= L->listsize)
    {
        newbase = (ElemType*) realloc(L->elem, (L->length+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) return (OVERFLOW);  //分配失败
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }

    q = &(L->elem[i-1]);  // 获取现在插入的值
    for(p = &(L->elem[L->length-1]); p>=q; --p)   //后移
        *(p+1) = *p;
    *q = e;

    ++L->length;   //表长+1

    return OK;
}

/** \brief 删除元素
 *        函数名称是ListDelete(L,i,e)；
 *        初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；
 *        操作结果：删除L的第i个数据元素，用e返回其值。
 *
 */
status ListDelete(SqList *L,int i,ElemType *e)
{
    if(i<1 || i>L->length+1) return ERROR;  //判断输入是否合法
    int *p, *q;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length-1;  //表尾位置
    for(++p; p<=q; ++p)
        *(p-1) = *p;
    L->length --;
    return OK;
}

/** \brief 遍历表
 *        函数名称是ListTraverse(L,visit())
 *        初始条件是线性表L已存在；
 *        操作结果是依次对L的每个数据元素调用函数visit()。
 *
 */
status ListTrabverse(SqList L,void (*visit)(int))
{
   int i;
   printf("\n-----------all elements -----------------------\n");
   for(i=0;i<L.length;i++) visit(L.elem[i]);
   printf("\n------------------ end ------------------------\n");
   return L.length;
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
 *        储存格式为 名称 length listsize 数据\n
 *
 */
status SaveList(SqList *L)
{
    FILE *fp = fopen("list.dat",a);
    int i;
    if(fp != NULL)
    {
        fprintf(fp,"%s %d %d",L->name,L->length,L->listsize);
        for(i = 1; i<=L->length; i++)
            fprintf(fp," %d",L->elem[i-1]);
        fprintf(fp,"\n")
        fclose(fp);
        return OK;
    }
    else
    {
        print("文件打开失败！");
        return ERROR;
    }
}

status LoadList(SqList **L)
{
    FILE *fp = fopen("list.dat",r);
    FILE *tpf;
    int i=0;
    char tname[10],iname[10];
    if (fp != NULL)
    {
        printf("当前的线性表名称为：\n");
        tpf = fp;
        if(*L != NULL)
        {
            DestroyList(L);
        }
        while(tpf)
        {
            fscanf(tfp,"%s",tname);
            printf("%s\t",tname);
            while(fgetc(tpf)!='\n') tfp++;
        }
        loop1:
        printf("\n请选择要加载的线性表：");
        scanf("%s",iname);
        tpf = fp;
        while(tpf)
        {
            fscanf(tfp,"%s",tname);
            if(!strcmp(iname,tname)) break;
            while(fgetc(tpf)!='\n') tfp++;
        }
        if(tpf == NULL)
        {
            printf("\n没有找到，请重新输入！");
            goto loop1;
        }
        else
        {
            IntiaList(L);
            strcpy((*L)->name, tname);
            fscanf(tpf,"%d%d",&(*L)->length,&(*L)->listsize);
            while(fgetc(tpf)!='\n')
            {
                fscanf(tpf,"%d",&(*L)->elem[i]);
                i++;
            }
        }
    }
    else
    {
        print("文件打开失败！");
        return ERROR;
    }


}
