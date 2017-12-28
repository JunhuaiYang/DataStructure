/**
 *         ���ļ����ڴ��溯��ʵ��
 *
 */

 #include"list.h"

//�����ڱ�׼C�����У����������޷�ʹ��&����
//������&L��Ϊ��*L

/** \brief ��ʼ���� ����������InitaList(L)
 *        ��ʼ���������Ա�L�����ڣ���������ǹ���һ���յ����Ա�
 */
status IntiaList(SqList **L)
{
    *L = (SqList*)malloc(sizeof(SqList));
	(*L)->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!(*L)->elem) return (OVERFLOW);  //����ʧ��
	(*L)->length=0;                  //�ÿձ�
    (*L)->listsize=LIST_INIT_SIZE;   //��ʼ����

	return OK;
}

/** \brief ���ٱ� ����������DestroyList(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
 */
status DestroyList(SqList **L)
{
    int i;
    int *tail;
    for(i = 0; i<(*L)->length; i++)  //�ͷ�elem������ڴ�ռ�
    {
        tail = (*L)->elem++;
        free(tail);
    }
    free((*L)); //�ͷ�L
    *L = NULL;

    return OK;
}

/** \brief ��ձ� ����������ClearList(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
 */
status ClearList(SqList *L)
{
    L->length = 0;  //ֱ�ӽ�������0
    return OK;
}

/** \brief �ж��ձ�  ����������ListEmpty(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
 */
status ListEmpty(SqList L)
{
    if(L.length == 0) return TRUE;
    else return FALSE;
}

/** \brief ���
 *        ��ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
 */
int ListLength(SqList L)
{
    return L.length;
}

/** \brief ���Ԫ�� ����������GetElem(L,i,e)��
 *        ��ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ��
 */
status GetElem(SqList L,int i,ElemType *e)
{
    if(i> L.length) return (ERROR);
    *e = L.elem[i-1];
    return OK;

}

/** \brief ����Ԫ�� ����������LocateElem(L,e,compare())��
 *        ��ʼ���������Ա��Ѵ��ڣ�
 *        ��������Ƿ���L�е�1����e�����ϵcompare������ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
 */
int LocateElem(SqList L,ElemType e, status(*compare)(ElemType,ElemType))
{
    int i = 1;
    int *p = L.elem;
    while(i<=L.listsize && !((*compare)(*p++,e))) i++;
    if(i<=L.length) return i;
    else return 0;
}

/** \brief ���ǰ�� ����������PriorElem(L,cur_e,pre_e)��
 *        ��ʼ���������Ա�L�Ѵ���
 *        �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��塣
 *
 */
status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
{
    int i;
    if(cur_e == *L.elem)   //�ж��Ƿ��ǵ�һ��Ԫ��
        return (ERROR);
    i = LocateElem(L,cur_e, Equal);   //���Ҹ�Ԫ�ص�ַ
    if(i == 0 )
    {
        printf("\nû���ҵ�Ԫ�أ�");    //û���ҵ���ָ���ָ��
        return FALSE;
    }
    else *pre_e = L.elem[i-2];
    return OK;
}

/** \brief ��ú�� ����������NextElem(L,cur_e,next_e)
 *        ��ʼ���������Ա�L�Ѵ��ڣ�
 *        �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��塣
 *
 */
status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
{
    int i;
    if(cur_e == L.elem[L.length-1]) //�ж��Ƿ�Ϊ�Ƿ������һ��
        return (ERROR);
    i = LocateElem(L,cur_e,Equal); //����
    if(i == 0 )
    {
        printf("\nû���ҵ�Ԫ�أ�");    //û���ҵ���ָ���ָ��
        return FALSE;
    }
    else *next_e = L.elem[i];
    return OK;
}

/** \brief ����Ԫ��
 *        ����������ListInsert(L,i,e)��
 *        ��ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
 *        �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e��
 *
 */
status ListInsert(SqList *L,int i,ElemType e)
{
    ElemType *newbase;
    int *p, *q;
    if(i<1 || i>L->length+1) return ERROR;  //�ж������Ƿ�Ϸ�
    //�Ƿ����
    if(L->length >= L->listsize)
    {
        newbase = (ElemType*) realloc(L->elem, (L->length+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) return (OVERFLOW);  //����ʧ��
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }

    q = &(L->elem[i-1]);  // ��ȡ���ڲ����ֵ
    for(p = &(L->elem[L->length-1]); p>=q; --p)   //����
        *(p+1) = *p;
    *q = e;

    ++L->length;   //��+1

    return OK;
}

/** \brief ɾ��Ԫ��
 *        ����������ListDelete(L,i,e)��
 *        ��ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
 *        ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
 *
 */
status ListDelete(SqList *L,int i,ElemType *e)
{
    if(i<1 || i>L->length+1) return ERROR;  //�ж������Ƿ�Ϸ�
    int *p, *q;
    p = &(L->elem[i-1]);   //��ȡɾ��λ��
    *e = *p;
    q = L->elem + L->length-1;  //��βλ��
    for(++p; p<=q; ++p)
        *(p-1) = *p;
    L->length --;
    return OK;
}

/** \brief ������
 *        ����������ListTraverse(L,visit())
 *        ��ʼ���������Ա�L�Ѵ��ڣ�
 *        ������������ζ�L��ÿ������Ԫ�ص��ú���visit()��
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
/** \brief ��С����ж�
 *
 */
status Equal(ElemType a,ElemType b)
{
    if(a == b) return TRUE;
    else return FALSE;
}

/** \brief �������
 *
 */
void print(int a)
{
    printf("%d ",a);
}

/** \brief ������ļ�
 *
 *        �����ʽΪ ���� length listsize ����\n
 *
 */
status SaveList(SqList *L)
{
    FILE *fp = fopen("list.dat","a");
    int i;
    if(fp != NULL)
    {
        fprintf(fp,"%s %d %d",L->name,L->length,L->listsize);
        for(i = 1; i<=L->length; i++)
            fprintf(fp," %d",L->elem[i-1]);
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

/** \brief ��ȡ����
 *
 *        ��ȡ�ļ��е����ݲ����ص����Ա���
 *
 */
status LoadList(SqList **L)
{
    FILE *fp = fopen("list.dat","r");
    FILE *tpf;
    fpos_t fps;   //�ļ����λ��
    int i=0;
    int t, flag = 1;
    char tname[10],iname[10];
    if (fp != NULL)
    {
        printf("��ǰ�ļ��д��ڵ����Ա�����Ϊ��\n");
        tpf = fp;
        fgetpos(tpf,&fps);   //��ȡ�ļ����λ�ã���ʼֵ��0��
        if(*L != NULL)
        {
            DestroyList(L);
        }
        while(flag)    //��������е����Ա�
        {
            t = fscanf(tpf,"%s",tname);
            if(t == EOF) break;    //�����ļ�β������
            printf("%s\t",tname);
            while(flag)
            {
                t = fgetc(tpf);
                if(t == EOF) flag = 0;
                if(t == '\n') break;
            }
        }
        flag = 1;
        printf("\n��ѡ��Ҫ���ص����Ա�");
        scanf("%s",iname);
        fsetpos(tpf, &fps);
        while(flag)  //�������Ա�
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
            printf("\nû���ҵ�, ���󣡣���\n�����������!");
            getch();
            return ERROR;
        }
        else
        {
            IntiaList(L);
            strcpy((*L)->name, tname);
            fscanf(tpf,"%d%d",&(*L)->length,&(*L)->listsize);
            while(i<=(*L)->length)         //��ȡ�ļ��е����Ա�
            {
                if(fscanf(tpf,"%d",&(*L)->elem[i]) ==EOF) break;   // ��ֹ�����ļ�β
                i++;
                //fgetc(tpf)!='\n' && fgetc(tpf)!=EOF
            }
        }
        fclose(fp);
        printf("\n�ļ���ȡ�ɹ���");
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


/** \brief �ı䵱ǰ���������
 *
 */
status ChangeName(SqList **L)
{
    printf("��ǰ���������Ϊ��%s",(*L)->name);
    printf("\n������Ҫ���ĵ����֣�");
    scanf("%s",(*L)->name);
    printf("�޸ĳɹ���");
    return OK;
}
