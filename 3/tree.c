/** \brief  ����������ʽʵ��
 *         ���ļ����ڴ���������
 *
 */

#include"tree.h"

/** \brief ��ʼ��������������������InitBiTree(T)
*        ��ʼ�����Ƕ�����T�����ڣ���������ǹ���ն�����T��
*/
status InitBiTree(Tree **T)
{
    char ch[20];
    Tree *newbase;
    SqList *L;

    newbase = (Tree*)malloc(sizeof(Tree));
    printf("��������������ƣ�");
    scanf("%s",ch);
    strcpy(newbase->name, ch);
    newbase->HeadNode = NULL; //��ͷ����ÿձ�ʾ����
    *T = newbase;

    //������������Ա�
    if(treelist == NULL)
    {
        //��������������ʱ�������Ĺ����, ��ʼ����
        L = (SqList*)malloc(sizeof(SqList));
        L->elem = (Tree**)malloc( LIST_INIT_SIZE * sizeof (Tree*));
        if(!(L)->elem) return (OVERFLOW);  //����ʧ��
        (L)->length=0;                  //�ÿձ�
        (L)->listsize=LIST_INIT_SIZE;   //��ʼ����
        treelist = L;   //��ֵ��ȫ�ֱ���

        treelist->elem[0] = newbase;
        treelist->length++;
    }
    else
    {
        //������������
        L = treelist;
        if(L->length >= L->listsize)
        {
            newbase = (Tree*) realloc(L->elem, (L->length+LISTINCREMENT)*sizeof(ElemType));
            if(!newbase) return (OVERFLOW);  //����ʧ��
            L->listsize += LISTINCREMENT;
        }
        L->elem[L->length] = newbase;
        treelist->length++;
    }
    return OK;


}

/** \brief ���ٶ�������������������DestroyBiTree(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�������������ٶ�����T
*
*         ջʵ��  �� �ɽ��ж���������
*/
status DestroyBiTree(Tree **T)
{
    char ch[20];
    int i, top = -1;
    Tree  **r, **s;
    BitNode *Tnode, *stack[100], *p, *q;

    printf("��ǰ���ڵ���Ϊ��\n");   // ����ѡ��ǰҪ���ٵ���
    for( i=0; i<treelist->length; i++)
        printf("%s   ",treelist->elem[i]->name);
    printf("\n������Ҫɾ�����������ƣ�");
    scanf("%s",ch);
    i = 1;
    while(i<=treelist->length && strcmp(ch, treelist->elem[i-1]->name)) i++;  //����Ҫ���ٵı�
    if( i == treelist->length+1)
    {
        printf("\n�Ҳ�����");
        return ERROR;
    }
    else
    {
        if(*T != NULL)
        {
            *T = NULL;
        }
        Tnode = treelist->elem[i-1]->HeadNode;
        //ɾ���ڱ��е�λ��
        r = &(treelist->elem[i-1]);   //��ȡɾ��λ��
        s = treelist->elem + treelist->length-1;  //��βλ��
        for(++r; r<=s; ++s)
            *(r-1) = *r;
        treelist->length --;

        //����
        if(Tnode == NULL)   //����ʱ
        {
            return OK;
        }
        p = Tnode->lchild;
        q = Tnode->rchild;
        if (p == NULL && q == NULL)  //ֻ�и��ڵ�
        {
            free(Tnode);
            return OK;
        }
        if (p->lchild) stack[++top] = p->lchild;   //�������ʾջ
        else if (p->rchild) stack[++top] = p->rchild;

        while (top>-1)
        {
            p = stack[top--];
            q = p;
            if (p->rchild) stack[++top] = p->rchild;
            if (p->lchild) stack[++top] = p->lchild;
            free(q);
        }
        free(Tnode);  //����ͷŸýڵ�
        return OK;
    }

}

/** \brief ����������CreateBiTree(T,definition)��
*          ��ʼ������definition ����������T�Ķ��壻
*           ��������ǰ�definition���������T
*           ������ǰ�������������������Ϊ��ʱ����Ϊ@
*
*           �ݹ�ʵ��
*/
status CreateBiTree(BitNode **T, char **definition)
{
    if(**definition == '\0') return OK;   //count Ϊȫ�ֱ���
    if(**definition == '@')
    {
        *T = NULL;
        (*definition)++;
    }
    else
    {
        if(!(*T = (BitNode*)malloc(sizeof(BitNode)))) return OVERFLOW;   //�����ڵ�
        (*T)->value = **definition;
        (*T)->key = count++;                           //keyΪ�ڵ�Ĺ�ϣֵ
        (*definition)++;
        CreateBiTree(&((*T)->lchild), definition);      //�ݹ鴦��
        CreateBiTree(&((*T)->rchild), definition);
    }
    return OK;
}

/** \brief ����������ClearBiTree (T)����ʼ�����Ƕ�����T����
*        ��������ǽ�������T���
*
*         ��ջ
*/
status ClearBiTree (Tree *T)
{
    BitNode *Tnode,  *stack[100], *p, *q;

    int top = -1;
    Tnode = T->HeadNode;
    p = Tnode->lchild;
    q = Tnode->rchild;
    if (p == NULL && q == NULL)  //ֻ�и��ڵ�
    {
        free(Tnode);
        return OK;
    }
    if (p->lchild) stack[++top] = p->lchild;   //�������ʾջ
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

/** \brief �ж��ն�����������������BiTreeEmpty(T)��(T)
*        ��ʼ�����Ƕ�����T���ڣ������������TΪ�ն������򷵻�TRUE�����򷵻�FALSE��
*/
status BiTreeEmpty(Tree *T)
{
    if(T->HeadNode == NULL) return TRUE;
    else return FALSE;
}

/** \brief ���������ȣ�����������BiTreeDepth(T)
*        ��ʼ�����Ƕ�����T���ڣ���������Ƿ���T����ȡ�
*
*          �ݹ�, ��ȫ�ֱ���count����
*/
status BiTreeDepth(BiTree T, int i)   //i�ڳ�ʼʱӦ��Ϊ0,countҲΪ0
{
    if(T == NULL) return OK;    //countΪȫ�ֱ���
    i++;           //����+1
    if (i>count) count = i;
    BiTreeDepth(T->lchild,i);   //����������
    BiTreeDepth(T->rchild,i);   //����������
    return OK;
}

/** \brief ��ø���㣺����������Root(T)��
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ���������Ƿ���T�ĸ���
*/
char Root(Tree *T)
{
    if(T->HeadNode == NULL)
    {
        printf("��ǰ��Ϊ������");
        getch();
        return ERROR;
    }
    else
    {
        return T->HeadNode->value;
    }
}

/** \brief ��ý�㣺����������Value(T,e)(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�e��T�е�ĳ����㣻��������Ƿ���e��ֵ��
*        �ݹ�
*/
char Value(BiTree T,int e)
{
    if(T == NULL) return ERROR;
    if(T->key == e) return T->value;

    int a,b;

    a = Value(T->lchild, e);   //����������
    b = Value(T->rchild, e);   //����������

    if(a != ERROR) return a;
    if(b != ERROR) return b;

    return ERROR;    //return ERROR ��ʾû���ҵ�
}

/** \brief ��㸳ֵ������������Assign(T,&e,value)��(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�e��T�е�ĳ����㣻��������ǽ��e��ֵΪvalue��
*         �ݹ�
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
    a = Assign(T->lchild, e, value);   //����������
    b = Assign(T->rchild, e, value);   //����������

    if(a == OK) return a;
    if(b == OK) return b;

    return ERROR;    //return ERROR ��ʾû���ҵ�
}

/** \brief ���˫�׽�㣺����������Parent(T,e) ��(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�e��T�е�ĳ����㣻�����������e��T�ķǸ���㣬
*         �򷵻�����˫�׽��ָ�룬���򷵻�NULL��
*         ջʵ��
*/
BiTree Parent(Tree *T,int e)
{
    int top = -1;

    if(T->HeadNode == NULL)
    {
        printf("��ǰ��Ϊ������");
        getch();
        return NULL;
    }
    else
    {
        BitNode *stack[100], *p;   //   ����ջ
        stack[++top] = T->HeadNode;   //ͷ�����ջ
        while (top>-1)
        {
            p = stack[top--];   //��ջ
            if (p->lchild)
            {
                if (p->lchild->key == e) break;
                stack[++top] = p->lchild;   //��������ջ
            }
            if (p->rchild)
            {
                if (p->rchild->key == e) break;
                stack[++top] = p->rchild;    //��������ջ
            }
        }
        if (top<=-1) return NULL;   //��ջָ��Ϊ�գ���û���ҵ���
        return p;
    }
}

/** \brief ������ӽ�㣺����������LeftChild(T,e)(T)
*        ��ʼ�����Ƕ�����T���ڣ�e��T��ĳ���ڵ㣻��������Ƿ���e�����ӽ��ָ�롣��e�����ӣ��򷵻�NULL��
*        �ݹ�
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

    a = LeftChild(T->lchild, e);   //����������
    b = LeftChild(T->rchild, e);   //����������

    if(a != NULL) return a;
    if(b != NULL) return b;

    return NULL;    //return NULL ��ʾû���ҵ�
}

/** \brief ����Һ��ӽ�㣺����������RightChild(T,e)��(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�e��T��ĳ����㣻��������Ƿ���e���Һ��ӽ��ָ�롣��e���Һ��ӣ��򷵻�NULL
*          �ݹ�
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

    a = LeftChild(T->lchild, e);   //����������
    b = LeftChild(T->rchild, e);   //����������

    if(a != NULL) return a;
    if(b != NULL) return b;

    return NULL;    //return NULL ��ʾû���ҵ�
}

/** \brief ������ֵܽ�㣺����������LeftSibling(T,e)��(T)
*        ��ʼ�����Ƕ�����T���ڣ�e��T��ĳ����㣻��������Ƿ���e�����ֵܽ��ָ�롣��e��T�����ӻ��������ֵܣ��򷵻�NULL
*           ��ջ��ʵ��
*/
BiTree LeftSibling(Tree *T,int e)
{
    int top = -1;   //ջ��λ�ñ��

    if(T->HeadNode == NULL)
    {
        printf("��ǰ��Ϊ������");
        getch();
        return NULL;
    }
    else
    {
        BitNode *stack[100], *p;   //  ����ջ
        stack[++top] = T->HeadNode;    //ͷ�����ջ
        while (top>-1)
        {
            p = stack[top--];
            if (p->lchild)
            {
                if (p->lchild->key == e) break;
                stack[++top] = p->lchild;          //������ջ
            }
            if (p->rchild)
            {
                if (p->rchild->key == e) break;
                stack[++top] = p->rchild;     //�Һ�����ջ
            }
        }
        if (top<=-1) return NULL;   //��ջָ��Ϊ�գ���û���ҵ���
        if(p->lchild != NULL)
            return p->lchild;
        else
            return NULL;   //�������
    }
}

/** \brief ������ֵܽ�㣺����������RightSibling(T,e)��(T)
*        ��ʼ�����Ƕ�����T�Ѵ��ڣ�e��T��ĳ����㣻��������Ƿ���e�����ֵܽ��ָ�롣��e��T���Һ��ӻ��������ֵܣ��򷵻�NULL��
*       ͬ�ϸ�����
*/
BiTree RightSibling(Tree *T,int e)
{
    int top = -1;   //ջ��λ�ñ��

    if(T->HeadNode == NULL)
    {
        printf("��ǰ��Ϊ������");
        getch();
        return NULL;
    }
    else
    {
    BitNode *stack[100], *p;   //  ����ջ
    stack[++top] = T->HeadNode;    //ͷ�����ջ
    while (top>-1)
    {
        p = stack[top--];
        if (p->rchild)         //�Һ�����ǰ����ֹ���п�p->lchild->key
        {
            if (p->rchild->key == e) break;
            stack[++top] = p->rchild;     //�Һ�����ջ
        }
        if (p->lchild)
        {
            if (p->lchild->key == e) break;
            stack[++top] = p->lchild;          //������ջ
        }
    }
    if (top<=-1) return NULL;   //��ջָ��Ϊ�գ���û���ҵ���
    if(p->rchild != NULL)
        return p->rchild;
    else
        return NULL;   //�������
    }
}

/** \brief ��������������������InsertChild(T,p,LR,c)��(T)
*        ��ʼ�����Ƕ�����T���ڣ�pָ��T�е�ĳ����㣬LRΪ0��1��,
*          �ǿն�����c��T���ཻ��������Ϊ�գ���������Ǹ���LRΪ0����1������cΪT��p��ָ���������������
*          p	��ָ����ԭ������������������Ϊc����������
*/
status InsertChild(BiTree T,BiTree p,status LR,BiTree c)
{

    return OK;
}

/** \brief ɾ������������������DeleteChild(T.p.LR)��(T)
*        ��ʼ�����Ƕ�����T���ڣ�pָ��T�е�ĳ����㣬LRΪ0��1��
*          ��������Ǹ���LRΪ0����1��ɾ��cΪT��p��ָ���������������
*/
status DeleteChild(BiTree T,BiTree p,status LR)
{

    return OK;
}

/** \brief ǰ�����������������PreOrderTraverse(T,Visit())��
*        ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú���������������������t��
*          ��ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
*/
status PreOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    visit(T->value);                //�ȷ��ʸ��ڵ�
    PreOrderTraverse(T->lchild, visit);   //����������
    PreOrderTraverse(T->rchild, visit);   //����������

    return OK;
}

/** \brief �������������������InOrderTraverse(T,Visit))��(T)
*        ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú���������������������t��
*          ��ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
*/
status InOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    PreOrderTraverse(T->lchild, visit);   //����������
    visit(T->value);                //���ʸ��ڵ�
    PreOrderTraverse(T->rchild, visit);   //����������

    return OK;
}

/** \brief �������������������PostOrderTraverse(T,Visit))��(T)
*        ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú�������������Ǻ������t��
*          ��ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ��
*/
status PostOrderTraverse(BiTree T,void (*visit)(char c) )
{
    if(T == NULL) return ERROR;

    PreOrderTraverse(T->lchild, visit);   //����������
    PreOrderTraverse(T->rchild, visit);   //����������
    visit(T->value);                //�����ʸ��ڵ�

    return OK;
}

/** \brief �������������������LevelOrderTraverse(T,Visit))��
*        ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú�������������ǲ������t��
*          ��ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ��
*          ͨ��������ʵ��
*          F�Ƕ��е�βָ�룬H�Ƕ��е�ͷָ�룬��������������
*/
status LevelOrderTraverse(BiTree T,void (*visit)(char c), BiTree *F,BiTree *H )
{
    *F=T;            //����ǰ�ڵ���������ָ����ָλ��
    visit((*F)->value);   //���βָ��
    if((*F)->lchild!=NULL)
    {
        H=H+1;             //ͷָ�����
        *H=(*F)->lchild;    //�ڵ������ӷ����β
    }
    if((*F)->rchild!=NULL)
    {
        H=H+1;                //ͷ������ƶ�һ��
        *H=(*F)->rchild;    //�ڵ���Ҷ��ӷ����β
    }

    F=F+1;    //βָ�����һλ
    if(F!=H)
        LevelOrderTraverse(*F ,visit ,F ,H);//�ݹ�
    else
        visit((*F)->value);    //���βָ��
    return OK;
}

void printf_my(char a)
{
    printf("%c  ",a);
}

status SaveTree(SqList *treelist)
{
    FILE *fp = fopen("Bitree.dat","w");   //ֻд�ķ�ʽ���ļ�
    int i;
    if(fp != NULL)
    {
        fprintf(fp,"%d %d",treelist->length,treelist->listsize);  //��һ�б��������������Ϣ
        fprintf(fp,"\n");
        for(i=0;i<treelist->length;i++)   //��������ǰ�����е���Ϣ
        {
            fprintf(fp,"%s ", treelist->elem[i]->name);
            SavePreOrderTraverse(treelist->elem[i]->HeadNode, fp);
        }
        fprintf(fp,"\n");
        fclose(fp);
        printf("\n�ļ�����ɹ���");
        getch();
        return OK;
    }
    else
    {
        printf("�ļ���ʧ�ܣ�");
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

    fprintf(fp,"%c", T->value);               //�ȷ��ʸ��ڵ�
    SavePreOrderTraverse(T->lchild, fp);   //����������
    SavePreOrderTraverse(T->rchild, fp);   //����������

    return OK;
}

status LoadTree(Tree **base)
{
    FILE *fp = fopen("Bitree.dat","r");
    FILE *tpf;
    Tree *newbase;
    SqList *L;
    fpos_t fps;   //�ļ����λ��
    int i=0, size, listlength;
    char name[20], definition[100], *p;

    if (fp != NULL)
    {
        tpf = fp;
        fgetpos(tpf,&fps);   //��ȡ�ļ����λ�ã���ʼֵ��0��

        fscanf(tpf,"%d %d",&listlength, &size);

        if(treelist != NULL)  //���ڱ�ʱ�Ĵ���
        {
            free(treelist);
            treelist = NULL;   //�ÿ�
        }
            //��������������ʱ�������Ĺ����, ��ʼ����
            L = (SqList*)malloc(sizeof(SqList));
            L->elem = (Tree**)malloc( size * sizeof (Tree*));
            if(!(L)->elem) return (OVERFLOW);  //����ʧ��
            (L)->length=listlength;                  //�ÿձ�
            (L)->listsize=size;   //��ʼ����
            treelist = L;   //��ֵ��ȫ�ֱ���

        for(i = 0; i<listlength; i++)   //����ÿһ����
        {
            newbase = (Tree*)malloc(sizeof(Tree));
            fscanf(tpf,"%s %s",name, definition);
            strcpy(newbase->name, name);
            newbase->HeadNode = NULL; //��ͷ����ÿձ�ʾ����
            treelist->elem[i] = newbase;   //�������

            count = 1;   //countȫ�ֱ�����1
            p = definition;
            if(CreateBiTree(&newbase->HeadNode, &p) == OK)   //����������
                printf("�ļ��еĶ�����%s���سɹ���\n", name);
        }
        printf("\nOK!\n\n");
        ChooseTree(base);  //����
        getch();
        return OK;

    }
    else
    {
        printf("�ļ���ʧ�ܣ�");
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
        printf("��ǰû�б����������Ա���ѡ���ʼ�������߼������ݣ�");
        return ERROR;
    }
    printf("��ǰ�����У�\n");
    for(i = 0; i<treelist->length; i++)   //������Ա��е���������
    {
        printf("%s  ", treelist->elem[i]->name);
    }
    printf("\n������Ҫ���ص�����");   //ѡ��Ҫ���ص���
    scanf("%s", name);
    for(i = 0; i<treelist->length; i++)
    {
        if( !strcmp(treelist->elem[i]->name, name))  //�ҵ�
        {
            *base = treelist->elem[i];
            printf("\n���سɹ���\n");
            return OK;
        }
    }     //ѭ����δ�ҵ�

    printf("\n�Ҳ����������¼��أ�\n");
    return ERROR;

}
