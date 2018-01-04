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
status IntiaList(LinkList *L)
{
    *L = (LNode*)malloc(sizeof(LNode));  //����һ��ͷ���
    (*L)->next = NULL;           //����

	return OK;
}

/** \brief ���ٱ� ����������DestroyList(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
 */
status DestroyList(LinkList *L)
{
    LNode *tail, *p;
    tail = *L;
    if(tail->next == NULL)
    {
        free(tail);          //����Ϊ������ʱ
    }
    else     //����Ϊ�ǿ�����ʱ
    {
        p = tail;
        tail = tail->next;
        while(tail)   //����ÿ������
        {
            tail = tail->next;
            free(p);      //�ͷſռ�
            p = tail;
        }

    }
    *L = NULL;   //��L�ÿ�

    return OK;
}

/** \brief ��ձ� ����������ClearList(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
 */
status ClearList(LinkList L)
{
    LNode *tail, *p;
    tail = L;
    if(tail->next == NULL)  //����Ϊ������ʱ
    {
        printf("�����Ա��Ѿ�Ϊ�ձ�\n");
        getch();
        return OK;
    }
    else     //����Ϊ�ǿ�����ʱ,�ͷ����ݽڵ�
    {
        p = tail->next;
        tail = tail->next;  //����ͷ���
        while(tail)
        {
            tail =tail->next;  //tail����
            free(p);       //�ͷ���ʱ�ڵ�p
            p = tail;
        }
        L->next = NULL;  //���ڵ��next��Ϊ��
        return OK;
    }
}

/** \brief �ж��ձ�  ����������ListEmpty(L)
 *        ��ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
 */
status ListEmpty(LinkList L)
{
    if(L->next == NULL) return TRUE;  //ͷ���û��ָ����Ϊ��
    else return FALSE;
}

/** \brief ���
 *        ��ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
 */
int ListLength(LinkList L)
{
    LNode *tail = L;
    int count = 0;
    if(tail->next == NULL)   //�ձ�ʱ��Ϊ0
    {
        count = 0;
    }
    else   //�ǿձ�ʱ
    {
        tail = tail->next;   //����
        while(tail)
        {
            count++;       //count ����
            tail = tail->next;
        }
    }
    return count;
}

/** \brief ���Ԫ�� ����������GetElem(L,i,e)��
 *        ��ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ��
 */
status GetElem(LinkList L,int i,ElemType *e)
{
    LNode *tail = L;
    int count;
    if(tail->next == NULL)   //�ձ�
    {
        return ERROR;
    }
    else
    {
        tail = tail->next;
        while(tail)   //����
        {
            count++;
            if(count == i)        //����Ԫ��
            {
                *e = tail->data;   //�ҵ���e����
                return OK;
            }
            tail = tail->next;
        }
        return ERROR;  //û���ҵ����ش���
    }

}

/** \brief ����Ԫ�� ����������LocateElem(L,e,compare())��
 *        ��ʼ���������Ա��Ѵ��ڣ�
 *        ��������Ƿ���L�е�1����e�����ϵcompare������ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
 */
int LocateElem(LinkList L,ElemType e, status(*compare)(ElemType,ElemType))
{
    LNode *tail = L;
    int count = 0;
    if(tail->next == NULL)   //�ձ�
    {
        printf("\n�ñ�Ϊ�ձ�\n");
        return ERROR;
    }
    else      //�ǿձ�
    {
        tail = tail->next;
        while(tail)         //����
        {
            count++;
            if(compare(tail->data,e))   //�ж��������
            {
                return count;      //����λ��
            }
            tail = tail->next;
        }
        return ERROR;   //û���ҵ����ش���
    }
}

/** \brief ���ǰ�� ����������PriorElem(L,cur_e,pre_e)��
 *        ��ʼ���������Ա�L�Ѵ���
 *        �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��塣
 *
 */
status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
{
    LNode *tail = L, *p;
    if(tail->next == NULL)   //�ձ�
    {
        printf("�ñ�Ϊ�ձ�\n");
        return ERROR;
    }
    else      //Ϊ�ǿձ�
    {
        tail = tail->next;
        if(tail->data == cur_e) return ERROR;  //������һ������
        p = tail;         //pΪ��ʱָ��
        tail = tail->next;  //����
        while(tail)
        {
            if(tail->data == cur_e)  //�����ҵ�
            {
                *pre_e = p->data;  //������ʱָ���ֵ
                return OK;
            }
            p = tail;          //��ʱָ��Ϊtail����һ��
            tail = tail->next;
        }
        return ERROR;  //û���ҵ����ش���
    }
    return OK;
}

/** \brief ��ú�� ����������NextElem(L,cur_e,next_e)
 *        ��ʼ���������Ա�L�Ѵ��ڣ�
 *        �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��塣
 *
 */
status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
{
    LNode *tail = L;
    if(tail->next == NULL)   //�ձ�
    {
        printf("�ñ�Ϊ�ձ�\n");
        return ERROR;
    }
    else   //�ǿձ�ʱ
    {
        tail = tail->next;
        while(tail)      //����
        {
            if(tail->data == cur_e)
            {
                if(tail->next)    //���Һ��
                {
                    *next_e = tail->next->data;      //�ҵ��򷵻���һ����ֵ
                    return OK;
                }
                else
                {
                    return ERROR;   //�������һ��Ԫ�ط��ش���
                }
            }
            tail = tail->next;
        }
        return ERROR;    //û���ҵ����ش���
    }
}

/** \brief ����Ԫ��
 *        ����������ListInsert(L,i,e)��
 *        ��ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
 *        �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e��
 *
 */
status ListInsert(LinkList L,int i,ElemType e)
{
    LNode *p = L, *s;
    int j = 0;
    while(p && j<i-1)           //Ѱ�ҵ�i-1���ڵ�
    {
        p = p->next;
        j++;
    }
    if(!p || j>i-1) return ERROR;         //����Ƿ�
    s = (LNode*)malloc(sizeof(LNode));   //�����½ڵ�
    s->data = e;                 //�����½ڵ�
    s->next = p->next;
    p->next = s;

    return OK;
}

/** \brief ɾ��Ԫ��
 *        ����������ListDelete(L,i,e)��
 *        ��ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
 *        ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
 *
 */
status ListDelete(LinkList L,int i,ElemType *e)
{
    LNode *p = L, *q;
    int j = 0;
    while(p->next && j<i-1)    //Ѱ�ҵ�i���ڵ㣬��ʱpΪi-1���ڵ�
    {
        p = p->next;
        j++;
    }
    if(!(p->next) || j>i-1) return ERROR; //�ýڵ㲻���ڣ�ɾ��λ�ò�����
    q = p->next;     //qΪiλ���ϵ�Ҫɾ����Ԫ��
    p->next = q->next;   //����������
    *e = q->data;
    free(q);

    return OK;
}

/** \brief ������
 *        ����������ListTraverse(L,visit())
 *        ��ʼ���������Ա�L�Ѵ��ڣ�
 *        ������������ζ�L��ÿ������Ԫ�ص��ú���visit()��
 *
 */
status ListTrabverse(LinkList L,void (*visit)(int))
{
   LNode *tail = L;
   if(tail->next == NULL)    //Ϊ�ձ�ʱ
   {
       return ERROR;
   }
   tail = tail->next;
   printf("\n-----------all elements -----------------------\n");
   while(tail)
   {
       printf("%d ",tail->data);     //�������
       tail = tail->next;
   }
   printf("\n------------------ end ------------------------\n");
   return OK;
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
 *        �����ʽΪ ���� length  ����\n
 *
 */
status SaveList(LinkList L)
{
    FILE *fp = fopen("list.dat","a");   //�򿪷�ʽΪa���������ļ����ݺ���д
    LNode *tail;
    if(fp != NULL)
    {
        tail = L->next;
        fprintf(fp,"%s %d",name, ListLength(L));
        while(tail)
        {
            fprintf(fp," %d",tail->data);   //���������浽�ļ�
            tail = tail->next;
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

/** \brief ��ȡ����
 *
 *        ��ȡ�ļ��е����ݲ����ص����Ա���
 *
 */
status LoadList(LinkList *L)
{
    FILE *fp = fopen("list.dat","r");
    FILE *tpf;
    fpos_t fps;   //�ļ����λ��
    LNode *tail, *p;
    int i=0;
    int t, flag = 1, length;
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
            strcpy(name, tname);
            fscanf(tpf,"%d",&length);
            p = *L;
            while(i < length)         //��ȡ�ļ��е����Ա�
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
        printf("\n�ļ���ȡ�ɹ���");
        getch();
        return OK;
    }
    else
    {
        printf("�ļ���ʧ�ܣ�");
        return ERROR;
    }
}

/** \brief �ı䵱ǰ���������
 *
 */
status ChangeName(void)
{
    printf("��ǰ���������Ϊ��%s",name);
    printf("\n������Ҫ���ĵ����֣�");
    scanf("%s",name);
    printf("�޸ĳɹ���");
    return OK;
}
