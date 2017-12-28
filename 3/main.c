/** \brief  ����������ʽʵ��
 *         ���ļ����ڴ���������
 *
 */
#include"tree.h"

SqList *treelist = NULL; //������������Ա�
int count;

int main(void)
{
    Tree *base = NULL;
    int op=1, e;
    char key, *p, value;
    char definition[100];
    BiTree ptree;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Link Structure \n");
        printf("-------------------------------------------------\n");
        printf("                     Attation           \n");
        if(base == NULL)
            printf("    There is no BiTree now! Please Init a list! \n");
        else printf("     There is a list now!    list name: %s\n",base->name);
        printf("-------------------------------------------------\n");
        printf("    	  1. InitBiTree          12. RightChild\n");
        printf("    	  2. DestroyBiTree       13. LeftSibling\n");
        printf("    	  3. CreateBiTree        14. RightSibling \n");
        printf("    	  4. ClearBiTree         15. InsertChild\n");
        printf("    	  5. BiTreeEmpty         16. DeleteChild\n");
        printf("    	  6. BiTreeDepth         17. PreOrderTraverse\n");
        printf("    	  7. Root                18. InOrderTraverse\n");
        printf("    	  8. Value               19. PostOrderTraverse\n");
        printf("    	  9. Assign              20. LevelOrderTraverse\n");
        printf("    	  10. Parent             21. LoadTree\n");
        printf("    	  11. LeftChild          22. SaveTree\n");
        printf("    	  23. ChooseTree    \n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~22]:");
        scanf("%d",&op);
        switch (op)
        {
        case 1: //InitBiTree
            if(base != NULL)
            {
                printf("�����Ѵ��ڶ�����������\n");
                printf("�Ƿ��ڶ����������½������������밴Y,���밴�����...\n");
                scanf(" %c",&key);
                if(key == 'Y' || key == 'y')
                {
                    if(InitBiTree(&base) == OK)
                        printf("�����������ɹ���\n");
                    else printf("����������ʧ�ܣ�\n");
                }
            }
            else
            {
                if(InitBiTree(&base) == OK)
                    printf("�����������ɹ���\n");
                else printf("����������ʧ�ܣ�\n");
            }
            getch();
            break;

        case 2://DestroyBiTree
            if(DestroyBiTree(&base) == OK)
                printf("���������ٳɹ���\n");
            else printf("����������ʧ�ܣ�\n");

            getch();
            break;

        case 3://CreateBiTree
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("�������������ǰ�����У��������� @ ���Ŵ��棺\n");
                scanf("%s",definition);
                count = 1;
                p = definition;
                if(CreateBiTree(&base->HeadNode, &p) == OK)
                    printf("�����������ɹ���\n");
            }
            getch();
            break;

        case 4://ClearBiTree
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                if(ClearBiTree(base) == OK)
                    printf("��������ճɹ���\n");
            }
            getch();
            break;

        case 5://BiTreeEmpty
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                if(BiTreeEmpty(base) == TRUE)
                    printf("������Ϊ������\n");
                else printf("������Ϊ�ǿ�����\n");
            }
            getch();
            break;

        case 6://BiTreeDepth
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                count = 0;      //��count����
                if(BiTreeEmpty(base) == TRUE);
                    printf("�����������Ϊ%d��\n", count);
            }
            getch();
            break;

        case 7://Root
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                key = Root(base);
                if(key == ERROR)
                    printf("����\n");
                else printf("�������ĸ�Ϊ%c\n", key);
            }
            getch();
            break;

        case 8://Value
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ���ҵĽڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                key = Value(base->HeadNode, e);
                if(key == ERROR)
                    printf("����\nû���ҵ��ýڵ㣡\n");
                else printf("�������ĸýڵ�Ϊ%c\n", key);
            }
            getch();
            break;

        case 9://Assign
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ��ֵ�Ľڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ��͸�ֵ��ֵ��");
                scanf("%d %c",&e, &value);
                key = Assign(base->HeadNode, e, value);
                if(key == ERROR)
                    printf("����\nû���ҵ��ýڵ㣡\n");
                else printf("��ֵ�ɹ���\n");
            }
            getch();
            break;

        case 10://Parent
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ����˫�׵Ľڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                ptree = Parent(base, e);
                if(ptree == ERROR)
                    printf("����\nû���ҵ��ýڵ��˫�ף�\n");
                else printf("�������ĸýڵ�˫�׵ĵ�ַΪ��%p ֵΪ%c\n", ptree, ptree->value);
            }
            getch();
            break;

        case 11://LeftChild
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ�������ӵĽڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                ptree = LeftChild(base->HeadNode, e);
                if(ptree == ERROR)
                    printf("����\nû���ҵ��ýڵ�����ӣ�\n");
                else printf("�������ĸýڵ����ӵĵ�ַΪ��%p ֵΪ%c\n", ptree, ptree->value);
            }
            getch();
            break;

        case 12://RightChild
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ�����Һ��ӵĽڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                ptree = RightChild(base->HeadNode, e);
                if(ptree == ERROR)
                    printf("����\nû���ҵ��ýڵ���Һ��ӣ�\n");
                else printf("�������ĸýڵ��Һ��ӵĵ�ַΪ��%p ֵΪ%c\n", ptree, ptree->value);
            }
            getch();
            break;

        case 13://LeftSibling
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ�������ֵܵĽڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                ptree = LeftSibling(base, e);
                if(ptree == ERROR)
                    printf("����\nû���ҵ��ýڵ�����ֵܣ�\n");
                else printf("�������ĸýڵ����ֵܵĵ�ַΪ��%p ֵΪ%c\n", ptree, ptree->value);
            }
            getch();
            break;

        case 14://RightSibling
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else
            {
                printf("������Ҫ�������ֵܵĽڵ�Ĺ�ϣֵ����ֵΪ����ʱǰ�����еı�ţ���");
                scanf("%d",&e);
                ptree = RightSibling(base, e);
                if(ptree == ERROR)
                    printf("����\nû���ҵ��ýڵ�����ֵܣ�\n");
                else printf("�������ĸýڵ����ֵܵĵ�ַΪ��%p ֵΪ%c\n", ptree, ptree->value);
            }
            getch();
            break;

        case 15://InsertChild
            break;

        case 16://DeleteChild
            break;

        case 17://PreOrderTraverse
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else if(base->HeadNode == NULL)
            {
                printf("��ǰ������Ϊ������\n");
            }
            else
            {
                printf("--------------------------------\n");
                PreOrderTraverse(base->HeadNode,printf_my);
                printf("\n--------------------------------\n");
            }
            getch();
            break;

        case 18://InOrderTraverse
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else if(base->HeadNode == NULL)
            {
                printf("��ǰ������Ϊ������\n");
            }
            else
            {
                printf("--------------------------------\n");
                InOrderTraverse(base->HeadNode,printf_my);
                printf("\n--------------------------------\n");
            }
            getch();
            break;

        case 19://PostOrderTraverse
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else if(base->HeadNode == NULL)
            {
                printf("��ǰ������Ϊ������\n");
            }
             else
            {
                printf("--------------------------------\n");
                PostOrderTraverse(base->HeadNode,printf_my);
                printf("\n--------------------------------\n");
            }
            getch();
            break;

        case 20://LevelOrderTraverse
            if(base == NULL)
                printf("��ǰ�����ڶ��������봴������أ�\n");
            else if(base->HeadNode == NULL)
            {
                printf("��ǰ������Ϊ������\n");
            }
            else
            {
                BiTree queue[128];  //����һ������
                printf("--------------------------------\n");
                LevelOrderTraverse(base->HeadNode,printf_my, queue, queue);
                printf("\n--------------------------------\n");
            }
            getch();
            break;

        case 21://LoadTree
            LoadTree(&base);
            break;

        case 22://SaveTree
            SaveTree(treelist);
            break;

        case 23://ChooseTree
                ChooseTree(&base);
            getch();
            break;
        default:
            break;
        }
    }
    return 0;
}
