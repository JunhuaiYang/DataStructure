/** \brief  二叉树的链式实现
 *         该文件用于储存主函数
 *
 */

#include"tree.h"

/** \brief 初始化二叉树：函数名称是InitBiTree(T)
*        初始条件是二叉树T不存在；操作结果是构造空二叉树T。
*/
status InitBiTree(Tree **T)
{
    char ch[20];
    Tree *newbase;
    SqList *L;

    newbase = (Tree*)malloc(sizeof(Tree));
    printf("请输入该树的名称：");
    scanf("%s",ch);
    strcpy(newbase->name, ch);
    newbase->HeadNode = NULL; //将头结点置空表示空树
    *T = newbase;

    //多树管理的线性表
    if(treelist == NULL)
    {
        //若不存在其他表时创建树的管理表, 初始化表
        L = (SqList*)malloc(sizeof(SqList));
        L->elem = (Tree**)malloc( LIST_INIT_SIZE * sizeof (Tree*));
        if(!(L)->elem) return (OVERFLOW);  //分配失败
        (L)->length=0;                  //置空表
        (L)->listsize=LIST_INIT_SIZE;   //初始容量
        treelist = L;   //赋值给全局变量

        treelist->elem[0] = newbase;
        treelist->length++;
    }
    else
    {
        //若存在其他表
        L = treelist;
        if(L->length >= L->listsize)
        {
            newbase = (Tree*) realloc(L->elem, (L->length+LISTINCREMENT)*sizeof(ElemType));
            if(!newbase) return (OVERFLOW);  //分配失败
            L->listsize += LISTINCREMENT;
        }
        L->elem[L->length] = newbase;
        treelist->length++;
    }
    return OK;


}

/** \brief 销毁二叉树：树函数名称是DestroyBiTree(T)
*        初始条件是二叉树T已存在；操作结果是销毁二叉树T
*
*         栈实现  ， 可进行多链表销毁
*/
status DestroyBiTree(Tree **T)
{
    char ch[20];
    int i, top = -1;
    Tree  **r, **s;
    BitNode *Tnode, *stack[100], *p, *q;

    printf("当前存在的树为：\n");   // 遍历选择当前要销毁的树
    for( i=0; i<treelist->length; i++)
        printf("%s   ",treelist->elem[i]->name);
    printf("\n请输入要删除的树的名称：");
    scanf("%s",ch);
    i = 1;
    while(i<=treelist->length && strcmp(ch, treelist->elem[i-1]->name)) i++;  //查找要销毁的表
    if( i == treelist->length+1)
    {
        printf("\n找不到！");
        return ERROR;
    }
    else
    {
        if(*T != NULL)
        {
            *T = NULL;
        }
        Tnode = treelist->elem[i-1]->HeadNode;
        //删除在表中的位置
        r = &(treelist->elem[i-1]);   //获取删除位置
        s = treelist->elem + treelist->length-1;  //表尾位置
        for(++r; r<=s; ++s)
            *(r-1) = *r;
        treelist->length --;

        //销毁
        if(Tnode == NULL)   //空树时
        {
            return OK;
        }
        p = Tnode->lchild;
        q = Tnode->rchild;
        if (p == NULL && q == NULL)  //只有根节点
        {
            free(Tnode);
            return OK;
        }
        if (p->lchild) stack[++top] = p->lchild;   //用数组表示栈
        else if (p->rchild) stack[++top] = p->rchild;

        while (top>-1)
        {
            p = stack[top--];
            q = p;
            if (p->rchild) stack[++top] = p->rchild;
            if (p->lchild) stack[++top] = p->lchild;
            free(q);
        }
        free(Tnode);  //最后释放该节点
        return OK;
    }

}

/** \brief 函数名称是CreateBiTree(T,definition)；
*          初始条件是definition 给出二叉树T的定义；
*           操作结果是按definition构造二叉树T
*           定义以前序遍历来创建二叉树，为空时符号为@
*
*           递归实现
*/
status CreateBiTree(BitNode **T, char **definition)
{
    if(**definition == '\0') return OK;   //count 为全局变量
    if(**definition == '@')
    {
        *T = NULL;
        (*definition)++;
    }
    else
    {
        if(!(*T = (BitNode*)malloc(sizeof(BitNode)))) return OVERFLOW;   //创建节点
        (*T)->value = **definition;
        (*T)->key = count++;                           //key为节点的哈希值
        (*definition)++;
        CreateBiTree(&((*T)->lchild), definition);      //递归处理
        CreateBiTree(&((*T)->rchild), definition);
    }
    return OK;
}

/** \brief 函数名称是ClearBiTree (T)；初始条件是二叉树T存在
*        操作结果是将二叉树T清空
*
*         用栈
*/
status ClearBiTree (Tree *T)
{
    BitNode *Tnode,  *stack[100], *p, *q;

    int top = -1;
    Tnode = T->HeadNode;
    p = Tnode->lchild;
    q = Tnode->rchild;
    if (p == NULL && q == NULL)  //只有根节点
    {
        free(Tnode);
        return OK;
    }
    if (p->lchild) stack[++top] = p->lchild;   //用数组表示栈
    else if (p->rchild) stack[++top] = p->rchild;

    while (top>-1)
    {
        p = stack[top--];
        q = p;
        if (p->rchild) stack[++top] = p->rchild;
        if (p->lchild) stack[++top] = p->lchild;
        free(q);
    }
    T->HeadNode = NULL;
    return OK;
}

/** \brief 判定空二叉树：函数名称是BiTreeEmpty(T)；(T)
*        初始条件是二叉树T存在；操作结果是若T为空二叉树则返回TRUE，否则返回FALSE。
*/
status BiTreeEmpty(Tree *T)
{
    if(T->HeadNode == NULL) return TRUE;
    else return FALSE;
}

/** \brief 求二叉树深度：函数名称是BiTreeDepth(T)
*        初始条件是二叉树T存在；操作结果是返回T的深度。
*
*          递归, 用全局变量count返回
*/
status BiTreeDepth(BiTree T, int i)   //i在初始时应该为0,count也为0
{
    if(T == NULL) return OK;    //count为全局变量
    i++;           //层数+1
    if (i>count) count = i;
    BiTreeDepth(T->lchild,i);   //遍历左子树
    BiTreeDepth(T->rchild,i);   //遍历右子树
    return OK;
}

/** \brief 获得根结点：函数名称是Root(T)；
*        初始条件是二叉树T已存在；操作结果是返回T的根。
*/
char Root(Tree *T)
{
    if(T->HeadNode == NULL)
    {
        printf("当前树为空树！");
        getch();
        return ERROR;
    }
    else
    {
        return T->HeadNode->value;
    }
}

/** \brief 获得结点：函数名称是Value(T,e)(T)
*        初始条件是二叉树T已存在，e是T中的某个结点；操作结果是返回e的值。
*        递归
*/
char Value(BiTree T,int e)
{
    if(T == NULL) return ERROR;
    if(T->key == e) return T->value;

    int a,b;

    a = Value(T->lchild, e);   //遍历左子树
    b = Value(T->rchild, e);   //遍历右子树

    if(a != ERROR) return a;
    if(b != ERROR) return b;

    return ERROR;    //return ERROR 表示没有找到
}

/** \brief 结点赋值：函数名称是Assign(T,&e,value)；(T)
*        初始条件是二叉树T已存在，e是T中的某个结点；操作结果是结点e赋值为value。
*         递归
*/
status Assign(BiTree T,int e,ElemType value)
{
    if(T == NULL) return ERROR;
    if(T->key == e)
    {
        T->value = value;
        return OK;
    }

    status a,b;
    a = Assign(T->lchild, e, value);   //遍历左子树
    b = Assign(T->rchild, e, value);   //遍历右子树

    if(a == OK) return a;
    if(b == OK) return b;

    return ERROR;    //return ERROR 表示没有找到
}

/** \brief 获得双亲结点：函数名称是Parent(T,e) ；(T)
*        初始条件是二叉树T已存在，e是T中的某个结点；操作结果是若e是T的非根结点，
*         则返回它的双亲结点指针，否则返回NULL。
*         栈实现
*/
BiTree Parent(Tree *T,int e)
{
    int top = -1;

    if(T->HeadNode == NULL)
    {
        printf("当前树为空树！");
        getch();
        return NULL;
    }
    else
    {
        BitNode *stack[100], *p;   //   创建栈
        stack[++top] = T->HeadNode;   //头结点入栈
        while (top>-1)
        {
            p = stack[top--];   //出栈
            if (p->lchild)
            {
                if (p->lchild->key == e) break;
                stack[++top] = p->lchild;   //左子树入栈
            }
            if (p->rchild)
            {
                if (p->rchild->key == e) break;
                stack[++top] = p->rchild;    //右子树入栈
            }
        }
        if (top<=-1) return NULL;   //若栈指针为空，则没有找到！
        return p;
    }
}

/** \brief 获得左孩子结点：函数名称是LeftChild(T,e)(T)
*        初始条件是二叉树T存在，e是T中某个节点；操作结果是返回e的左孩子结点指针。若e无左孩子，则返回NULL。
*        递归
*/
BiTree LeftChild(BiTree T,int e)
{
    if(T == NULL) return ERROR;
    if(T->key == e)
    {
        if(T->lchild == NULL)
        {
            return NULL;
        }
        else return T->lchild;
    }

    BiTree a,b;

    a = LeftChild(T->lchild, e);   //遍历左子树
    b = LeftChild(T->rchild, e);   //遍历右子树

    if(a != NULL) return a;
    if(b != NULL) return b;

    return NULL;    //return NULL 表示没有找到
}

/** \brief 获得右孩子结点：函数名称是RightChild(T,e)；(T)
*        初始条件是二叉树T已存在，e是T中某个结点；操作结果是返回e的右孩子结点指针。若e无右孩子，则返回NULL
*          递归
*/
BiTree RightChild(BiTree T,int e)
{
    if(T == NULL) return ERROR;
    if(T->key == e)
    {
        if(T->rchild == NULL)
        {
            return NULL;
        }
        else return T->rchild;
    }

    BiTree a,b;

    a = LeftChild(T->lchild, e);   //遍历左子树
    b = LeftChild(T->rchild, e);   //遍历右子树

    if(a != NULL) return a;
    if(b != NULL) return b;

    return NULL;    //return NULL 表示没有找到
}

/** \brief 获得左兄弟结点：函数名称是LeftSibling(T,e)；(T)
*        初始条件是二叉树T存在，e是T中某个结点；操作结果是返回e的左兄弟结点指针。若e是T的左孩子或者无左兄弟，则返回NULL
*           用栈来实现
*/
BiTree LeftSibling(Tree *T,int e)
{
    int top = -1;   //栈顶位置标记

    if(T->HeadNode == NULL)
    {
        printf("当前树为空树！");
        getch();
        return NULL;
    }
    else
    {
        BitNode *stack[100], *p;   //  创建栈
        stack[++top] = T->HeadNode;    //头结点入栈
        while (top>-1)
        {
            p = stack[top--];
            if (p->lchild)
            {
                if (p->lchild->key == e) break;
                stack[++top] = p->lchild;          //左孩子入栈
            }
            if (p->rchild)
            {
                if (p->rchild->key == e) break;
                stack[++top] = p->rchild;     //右孩子入栈
            }
        }
        if (top<=-1) return NULL;   //若栈指针为空，则没有找到！
        if(p->lchild != NULL)
            return p->lchild;
        else
            return NULL;   //其他情况
    }
}

/** \brief 获得右兄弟结点：函数名称是RightSibling(T,e)；(T)
*        初始条件是二叉树T已存在，e是T中某个结点；操作结果是返回e的右兄弟结点指针。若e是T的右孩子或者无有兄弟，则返回NULL。
*       同上个函数
*/
BiTree RightSibling(Tree *T,int e)
{
    int top = -1;   //栈顶位置标记

    if(T->HeadNode == NULL)
    {
        printf("当前树为空树！");
        getch();
        return NULL;
    }
    else
    {
    BitNode *stack[100], *p;   //  创建栈
    stack[++top] = T->HeadNode;    //头结点入栈
    while (top>-1)
    {
        p = stack[top--];
        if (p->rchild)         //右孩子在前，防止被判空p->lchild->key
        {
            if (p->rchild->key == e) break;
            stack[++top] = p->rchild;     //右孩子入栈
        }
        if (p->lchild)
        {
            if (p->lchild->key == e) break;
            stack[++top] = p->lchild;          //左孩子入栈
        }
    }
    if (top<=-1) return NULL;   //若栈指针为空，则没有找到！
    if(p->rchild != NULL)
        return p->rchild;
    else
        return NULL;   //其他情况
    }
}

/** \brief 插入子树：函数名称是InsertChild(T,p,LR,c)；(T)
*        初始条件是二叉树T存在，p指向T中的某个结点，LR为0或1，,
*          非空二叉树c与T不相交且右子树为空；操作结果是根据LR为0或者1，插入c为T中p所指结点的左或右子树，
*          p	所指结点的原有左子树或右子树则为c的右子树。
*/
status InsertChild(BiTree T,BiTree p,status LR,BiTree c)
{

    return OK;
}

/** \brief 删除子树：函数名称是DeleteChild(T.p.LR)；(T)
*        初始条件是二叉树T存在，p指向T中的某个结点，LR为0或1。
*          操作结果是根据LR为0或者1，删除c为T中p所指结点的左或右子树。
*/
status DeleteChild(BiTree T,BiTree p,status LR)
{

    return OK;
}

/** \brief 前序遍历：函数名称是PreOrderTraverse(T,Visit())；
*        初始条件是二叉树T存在，Visit是对结点操作的应用函数；操作结果：先序遍历t，
*          对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
*/
status PreOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    visit(T->value);                //先访问根节点
    PreOrderTraverse(T->lchild, visit);   //访问左子树
    PreOrderTraverse(T->rchild, visit);   //访问右子树

    return OK;
}

/** \brief 中序遍历：函数名称是InOrderTraverse(T,Visit))；(T)
*        初始条件是二叉树T存在，Visit是对结点操作的应用函数；操作结果是中序遍历t，
*          对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
*/
status InOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    PreOrderTraverse(T->lchild, visit);   //访问左子树
    visit(T->value);                //访问根节点
    PreOrderTraverse(T->rchild, visit);   //访问右子树

    return OK;
}

/** \brief 后序遍历：函数名称是PostOrderTraverse(T,Visit))；(T)
*        初始条件是二叉树T存在，Visit是对结点操作的应用函数；操作结果是后序遍历t，
*          对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败
*/
status PostOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    PreOrderTraverse(T->lchild, visit);   //访问左子树
    PreOrderTraverse(T->rchild, visit);   //访问右子树
    visit(T->value);                //最后访问根节点

    return OK;
}

/** \brief 按层遍历：函数名称是LevelOrderTraverse(T,Visit))；
*        初始条件是二叉树T存在，Visit是对结点操作的应用函数；操作结果是层序遍历t，
*          对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败
*          通过队列来实现
*          F是队列的尾指针，H是队列的头指针，定义在主函数中
*/
status LevelOrderTraverse(BiTree T,void (*visit)(char c), BiTree *F,BiTree *H )
{
    *F=T;            //将当前节点放入队列首指针所指位置
    visit((*F)->value);   //输出尾指针
    if((*F)->lchild!=NULL)
    {
        H=H+1;             //头指针后移
        *H=(*F)->lchild;    //节点的左儿子放入队尾
    }
    if((*F)->rchild!=NULL)
    {
        H=H+1;                //头针向后移动一格
        *H=(*F)->rchild;    //节点的右儿子放入队尾
    }

    F=F+1;    //尾指针后移一位
    if(F!=H)
        LevelOrderTraverse(*F ,visit ,F ,H);//递归
    else
        visit((*F)->value);    //输出尾指针
    return OK;
}

void printf_my(char a)
{
    printf("%c  ",a);
}

status SaveTree(SqList *treelist)
{
    FILE *fp = fopen("Bitree.dat","w");   //只写的方式打开文件
    int i;
    if(fp != NULL)
    {
        fprintf(fp,"%d %d",treelist->length,treelist->listsize);  //第一行保存多链表管理的信息
        fprintf(fp,"\n");
        for(i=0;i<treelist->length;i++)   //保存树的前序序列的信息
        {
            fprintf(fp,"%s ", treelist->elem[i]->name);
            SavePreOrderTraverse(treelist->elem[i]->HeadNode, fp);
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

status SavePreOrderTraverse(BiTree T, FILE *fp)
{
    if(T == NULL)
    {
        fprintf(fp,"@");
        return ERROR;
    }

    fprintf(fp,"%c", T->value);               //先访问根节点
    SavePreOrderTraverse(T->lchild, fp);   //访问左子树
    SavePreOrderTraverse(T->rchild, fp);   //访问右子树

    return OK;
}

status LoadTree(Tree **base)
{
    FILE *fp = fopen("Bitree.dat","r");
    FILE *tpf;
    Tree *newbase;
    SqList *L;
    fpos_t fps;   //文件光标位置
    int i=0, size, listlength;
    char name[20], definition[100], *p;

    if (fp != NULL)
    {
        tpf = fp;
        fgetpos(tpf,&fps);   //读取文件光标位置，起始值（0）

        fscanf(tpf,"%d %d",&listlength, &size);

        if(treelist != NULL)  //存在表时的处理
        {
            free(treelist);
            treelist = NULL;   //置空
        }
            //若不存在其他表时创建树的管理表, 初始化表
            L = (SqList*)malloc(sizeof(SqList));
            L->elem = (Tree**)malloc( size * sizeof (Tree*));
            if(!(L)->elem) return (OVERFLOW);  //分配失败
            (L)->length=listlength;                  //置空表
            (L)->listsize=size;   //初始容量
            treelist = L;   //赋值给全局变量

        for(i = 0; i<listlength; i++)   //加载每一颗树
        {
            newbase = (Tree*)malloc(sizeof(Tree));
            fscanf(tpf,"%s %s",name, definition);
            strcpy(newbase->name, name);
            newbase->HeadNode = NULL; //将头结点置空表示空树
            treelist->elem[i] = newbase;   //加入表中

            count = 1;   //count全局变量置1
            p = definition;
            if(CreateBiTree(&newbase->HeadNode, &p) == OK)   //创建二叉树
                printf("文件中的二叉树%s加载成功！\n", name);
        }
        printf("\nOK!\n\n");
        ChooseTree(base);  //加载
        getch();
        return OK;

    }
    else
    {
        printf("文件打开失败！");
        getch();
        return ERROR;
    }
}

status ChooseTree(Tree **base)
{
    int i;
    char name[20];
    if(treelist == NULL)
    {
        printf("当前没有保存树的线性表！请选择初始化树或者加载数据！");
        return ERROR;
    }
    printf("当前的树有：\n");
    for(i = 0; i<treelist->length; i++)   //输出线性表中的树的名字
    {
        printf("%s  ", treelist->elem[i]->name);
    }
    printf("\n请输入要加载的树：");   //选择要加载的树
    scanf("%s", name);
    for(i = 0; i<treelist->length; i++)
    {
        if( !strcmp(treelist->elem[i]->name, name))  //找到
        {
            *base = treelist->elem[i];
            printf("\n加载成功！\n");
            return OK;
        }
    }     //循环完未找到

    printf("\n找不到！请重新加载！\n");
    return ERROR;

}
