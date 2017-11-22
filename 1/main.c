/** \brief
 *         ���ļ����ڴ���������
 *
 */
#include"list.h"

int main(void)
{
    SqList *L =NULL;
    int op=1;
    int i, e, flag;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("                     Attation           \n");
        if(L == NULL)
            printf("    There is no list now! Please Init a list! \n");
        else printf("     There is a list now!    list name: %s\n",L->name);
        printf("-------------------------------------------------\n");
        printf("    	  1. IntiaList       7. LocateElem\n");
        printf("    	  2. DestroyList     8. PriorElem\n");
        printf("    	  3. ClearList       9. NextElem \n");
        printf("    	  4. ListEmpty       10. ListInsert\n");
        printf("    	  5. ListLength      11. ListDelete\n");
        printf("    	  6. GetElem         12. ListTrabverse\n\n");
        printf("    	  13. SaveList       14. LoadList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf("%d",&op);
        switch(op)
        {
        case 1: //IntiaList
            //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
            if(L != NULL) printf("���Ա��Ѵ��ڣ�����");
            else
            {
                if(IntiaList(&L)==OK)
                {
                    printf("    Please input the name of the list :");
                    scanf("%s",L->name);
                    printf("���Ա����ɹ���\n");
                }
                else printf("���Ա���ʧ�ܣ�\n");
            }
            getchar();
            getchar();
            break;
        case 2: //DestroyList
            //printf("\n----DestroyList���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                if(DestroyList(&L) == OK) printf("���Ա����ٳɹ���");
            }
            getchar();
            getchar();
            break;
        case 3: //ClearList
            //printf("\n----ClearList���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                if(ClearList(L) == OK) printf("���Ա��ÿճɹ���");
            }
            getchar();
            getchar();
            break;
        case 4: //ListEmpty
            //printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                if(ListEmpty(*L)) printf("��ǰ���Ա�Ϊ�ձ�!");
                else printf("��ǰ���Ա�Ϊ�ǿձ�");
            }
            getchar();
            getchar();
            break;
        case 5: //ListLength
            //printf("\n----ListLength���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("��ǰ���Ա���Ϊ��%d",ListLength(*L));
            }
            getchar();
            getchar();
            break;
        case 6:  //GetElem
            //printf("\n----GetElem���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("������Ҫ���ҵĵڼ���λ�ã�");
                scanf("%d",&i);
                if(GetElem(*L, i, &e)==OK)
                    printf("\n��%d��λ�õ�Ԫ��Ϊ��%d",i,e);
                else
                    printf("���볬�����Ա�Χ��");
            }
            getchar();
            getchar();
            break;
        case 7:  //LocateElem
            //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("����������e��");
                scanf("%d",&e);
                printf("\n��ǰ��compare()��ϵΪ����ȡ�");
                i = LocateElem(*L, e, Equal);
                if(i == 0)
                    printf("\n�Ҳ�������ù�ϵ��Ԫ��");
                else
                    printf("\n�ҵ�����ù�ϵ��λ�ã��Ҹ�Ԫ��λ��Ϊ��%d",i);
            }
            getchar();
            getchar();
            break;
        case 8:  //PriorElem
            //printf("\n----PriorElem���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("������Ҫ����ǰ����Ԫ�أ���Ҫ�����һ��Ԫ�أ���");
                scanf("%d",&e);
                if(PriorElem(*L, e, &i) == OK)
                {
                    printf("%dԪ�ص�ǰ���ǣ�%d",e,i);
                }
                else
                    printf("����");
            }
            getchar();
            getchar();
            break;
        case 9:  //NextElem
            //printf("\n----NextElem���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("������Ҫ���Һ�̵�Ԫ�أ���Ҫ�������һ��Ԫ�أ���");
                scanf("%d",&e);
                if(NextElem(*L, e, &i) == OK)
                {
                    printf("%dԪ�صĺ���ǣ�%d",e,i);
                }
                else
                    printf("����");
            }
            getchar();
            getchar();
            break;
        case 10:  //ListInsert
            //printf("\n----ListInsert���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("������Ҫ�����λ��:");
                scanf("%d",&i);
                printf("������Ҫ�����Ԫ�أ�");
                scanf("%d",&e);
                flag = ListInsert(L, i, e);
                if (flag == OK)
                {
                    printf("\n��������Ԫ�سɹ�!");
                }
                else if (flag == OVERFLOW)
                {
                    printf("\n����ռ����ʧ�ܣ�");
                }
                else
                {
                    printf("\n����Ƿ���");
                }
            }
            getchar();
            getchar();
            break;
        case 11: //ListDelete
            //printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                printf("������Ҫɾ��Ԫ�ص�λ�ã�");
                scanf("%d",&i);
                if(ListDelete(L, i, &e) == OK)
                    printf("\nɾ��Ԫ�سɹ�����ɾ����ֵΪ%d",e);
                else printf("����Ƿ�");
            }
            getchar();
            getchar();
            break;
        case 12: //ListTrabverse
            //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
            if(L == NULL) printf("��ǰû�����Ա���ѡ�񴴽����Ա���߼������ݣ�\n");
            else
            {
                if(!ListTrabverse(*L,print)) printf("���Ա��ǿձ�\n");
            }
            getchar();
            getchar();
            break;
        case 13:  //SaveList
            SaveList(L);
            break;
        case 14: //LoadList
            LoadList(&L);
            break;
        case 0:
            break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");

    return 0;
}//end of main()
