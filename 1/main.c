/** \brief
 *         该文件用于储存主函数
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
        printf("    请选择你的操作[0~12]:");
        scanf("%d",&op);
        switch(op)
        {
        case 1: //IntiaList
            //printf("\n----IntiaList功能待实现！\n");
            if(L != NULL) printf("线性表已存在！！！");
            else
            {
                if(IntiaList(&L)==OK)
                {
                    printf("    Please input the name of the list :");
                    scanf("%s",L->name);
                    printf("线性表创建成功！\n");
                }
                else printf("线性表创建失败！\n");
            }
            getchar();
            getchar();
            break;
        case 2: //DestroyList
            //printf("\n----DestroyList功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                if(DestroyList(&L) == OK) printf("线性表销毁成功！");
            }
            getchar();
            getchar();
            break;
        case 3: //ClearList
            //printf("\n----ClearList功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                if(ClearList(L) == OK) printf("线性表置空成功！");
            }
            getchar();
            getchar();
            break;
        case 4: //ListEmpty
            //printf("\n----ListEmpty功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                if(ListEmpty(*L)) printf("当前线性表为空表!");
                else printf("当前线性表为非空表！");
            }
            getchar();
            getchar();
            break;
        case 5: //ListLength
            //printf("\n----ListLength功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("当前线性表长度为：%d",ListLength(*L));
            }
            getchar();
            getchar();
            break;
        case 6:  //GetElem
            //printf("\n----GetElem功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入要查找的第几个位置：");
                scanf("%d",&i);
                if(GetElem(*L, i, &e)==OK)
                    printf("\n第%d个位置的元素为：%d",i,e);
                else
                    printf("输入超出线性表范围！");
            }
            getchar();
            getchar();
            break;
        case 7:  //LocateElem
            //printf("\n----LocateElem功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入条件e：");
                scanf("%d",&e);
                printf("\n当前的compare()关系为“相等”");
                i = LocateElem(*L, e, Equal);
                if(i == 0)
                    printf("\n找不到满足该关系的元素");
                else
                    printf("\n找到满足该关系的位置，且该元素位置为：%d",i);
            }
            getchar();
            getchar();
            break;
        case 8:  //PriorElem
            //printf("\n----PriorElem功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入要查找前驱的元素（不要输入第一个元素）：");
                scanf("%d",&e);
                if(PriorElem(*L, e, &i) == OK)
                {
                    printf("%d元素的前驱是：%d",e,i);
                }
                else
                    printf("错误！");
            }
            getchar();
            getchar();
            break;
        case 9:  //NextElem
            //printf("\n----NextElem功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入要查找后继的元素（不要输入最后一个元素）：");
                scanf("%d",&e);
                if(NextElem(*L, e, &i) == OK)
                {
                    printf("%d元素的后继是：%d",e,i);
                }
                else
                    printf("错误！");
            }
            getchar();
            getchar();
            break;
        case 10:  //ListInsert
            //printf("\n----ListInsert功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入要插入的位置:");
                scanf("%d",&i);
                printf("请输入要插入的元素：");
                scanf("%d",&e);
                flag = ListInsert(L, i, e);
                if (flag == OK)
                {
                    printf("\n插入数据元素成功!");
                }
                else if (flag == OVERFLOW)
                {
                    printf("\n储存空间分配失败！");
                }
                else
                {
                    printf("\n输入非法！");
                }
            }
            getchar();
            getchar();
            break;
        case 11: //ListDelete
            //printf("\n----ListDelete功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                printf("请输入要删除元素的位置：");
                scanf("%d",&i);
                if(ListDelete(L, i, &e) == OK)
                    printf("\n删除元素成功，被删除的值为%d",e);
                else printf("输入非法");
            }
            getchar();
            getchar();
            break;
        case 12: //ListTrabverse
            //printf("\n----ListTrabverse功能待实现！\n");
            if(L == NULL) printf("当前没有线性表！请选择创建线性表或者加载数据！\n");
            else
            {
                if(!ListTrabverse(*L,print)) printf("线性表是空表！\n");
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
    printf("欢迎下次再使用本系统！\n");

    return 0;
}//end of main()
