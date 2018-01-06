/** \brief  二叉树的链式实现
 *         该文件用于储存主函数
 *
 */
#include"tree.h"

SqList *treelist = NULL; //多树管理的线性表
int count;

int main(void)
{
    Tree *base = NULL;
    int op=1, e, LR;
    char key, *p, value;
    char definition[100];
    BiTree ptree;
    BiTree newtree;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Link Structure \n");
        printf("-------------------------------------------------\n");
        printf("                     Attation           \n");
        if(treelist == NULL)
            printf("   There is no Tree_Sqlist now! Please Init it!\n");
        else
            printf("   There is a Tree_Sqlist now!  You can use ChooseTree To Choose it!\n" );
        if(base == NULL)
            printf("    There is no BiTree now! Please Init a list! \n");
        else printf("     There is a BiTree now!    BiTree name: %s\n",base->name);
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
        printf("    	  10. Parent             \n");
        printf("    	  11. LeftChild          \n\n");
        printf("    	  21. LoadTree           22. SaveTree\n");
        printf("    	  23. ChooseTree    \n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~23]:");
        scanf("%d",&op);
        switch (op)
        {
        case 1: //InitBiTree
            if(base != NULL)
            {
                printf("现在已存在二叉树！错误！\n");
                printf("是否在多树管理中新建二叉树？是请按Y,否请按任意键...\n");
                scanf(" %c",&key);
                if(key == 'Y' || key == 'y')
                {
                    if(InitBiTree(&base) == OK)
                        printf("二叉树创建成功！\n");
                    else printf("二叉树创建失败！\n");
                }
            }
            else
            {
                if(InitBiTree(&base) == OK)
                    printf("二叉树创建成功！\n");
                else printf("二叉树创建失败！\n");
            }
            getch();
            break;

        case 2://DestroyBiTree
            if(DestroyBiTree(&base) == OK)
                printf("二叉树销毁成功！\n");
            else printf("二叉树销毁失败！\n");

            getch();
            break;

        case 3://CreateBiTree
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入二叉树的前序序列，遇到空用 @ 符号代替：\n");
                scanf("%s",definition);
                count = 1;
                p = definition;
                if(CreateBiTree(&base->HeadNode, &p) == OK)
                    printf("二叉树创建成功！\n");
            }
            getch();
            break;

        case 4://ClearBiTree
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                if(ClearBiTree(base) == OK)
                    printf("二叉树清空成功！\n");
            }
            getch();
            break;

        case 5://BiTreeEmpty
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                if(BiTreeEmpty(base) == TRUE)
                    printf("二叉树为空树！\n");
                else printf("二叉树为非空树！\n");
            }
            getch();
            break;

        case 6://BiTreeDepth
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                count = 0;      //将count置零
                if(BiTreeDepth(base->HeadNode, 0) == TRUE);
                    printf("二叉树的深度为%d！\n", count);
            }
            getch();
            break;

        case 7://Root
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                key = Root(base);
                if(key == ERROR)
                    printf("错误！\n");
                else printf("二叉树的根为%c\n", key);
            }
            getch();
            break;

        case 8://Value
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                key = Value(base->HeadNode, e);
                if(key == ERROR)
                    printf("错误！\n没有找到该节点！\n");
                else printf("二叉树的该节点为%c\n", key);
            }
            getch();
            break;

        case 9://Assign
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要赋值的节点的哈希值（该值为创建时前序序列的编号）和赋值的值：");
                scanf("%d %c",&e, &value);
                key = Assign(base->HeadNode, e, value);
                if(key == ERROR)
                    printf("错误！\n没有找到该节点！\n");
                else printf("赋值成功！\n");
            }
            getch();
            break;

        case 10://Parent
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找双亲的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                ptree = Parent(base, e);
                if(ptree == ERROR)
                    printf("错误！\n没有找到该节点的双亲！\n");
                else printf("二叉树的该节点双亲的键值为：%d 值为%c\n", ptree->key, ptree->value);
            }
            getch();
            break;

        case 11://LeftChild
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找左孩子的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                ptree = LeftChild(base->HeadNode, e);
                if(ptree == ERROR)
                    printf("错误！\n没有找到该节点的左孩子！\n");
                else printf("二叉树的该节点左孩子的键值为：%d 值为%c\n", ptree->key, ptree->value);
            }
            getch();
            break;

        case 12://RightChild
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找右孩子的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                ptree = RightChild(base->HeadNode, e);
                if(ptree == ERROR)
                    printf("错误！\n没有找到该节点的右孩子！\n");
                else printf("二叉树的该节点右孩子的键值为：%d 值为%c\n", ptree->key, ptree->value);
            }
            getch();
            break;

        case 13://LeftSibling
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找左兄弟的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                ptree = LeftSibling(base, e);
                if(ptree == ERROR)
                    printf("错误！\n没有找到该节点的左兄弟！\n");
                else printf("二叉树的该节点左兄弟的键值为：%d 值为%c\n", ptree->key, ptree->value);
            }
            getch();
            break;

        case 14://RightSibling
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                printf("请输入要查找右兄弟的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                ptree = RightSibling(base, e);
                if(ptree == ERROR)
                    printf("错误！\n没有找到该节点的右兄弟！\n");
                else printf("二叉树的该节点右兄弟的键值为：%d 值为%c\n", ptree->key, ptree->value);
            }
            getch();
            break;

        case 15://InsertChild
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                if(base->HeadNode == NULL)
                {
                    printf("当前树为空树！\n");
                    break;
                }
                printf("请输入要插入子树节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                //找节点e
                ptree = FindNode(base->HeadNode, e);
                if(ptree == NULL)
                {
                    printf("\n没有找到该节点！请重试！");
                    getch();
                    break;
                }
                printf("\n请输入要插入在左子树或右子树？（左子树为0，右子树为1）");
                scanf("%d", &LR);
                printf("请输入要插入的子树的前序序列，遇到空用 @ 符号代替：\n");
                scanf("%s", definition);
                p = definition;
                CreateBiTree(&newtree, &p);


                //判断插入的右子树是否存在
                if(LeftChild(newtree, 1) == NULL)   //右子树不存在则插入
                {
                    if (InsertChild(base->HeadNode, ptree, LR, newtree) == OK)
                        printf("\n插入成功！");
                }
                else
                {
                    printf("\n错误！ 输入的子树存在右子树！");
                }
                getch();
                break;
            }

        case 16://DeleteChild
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else
            {
                if(base->HeadNode == NULL)
                {
                    printf("当前树为空树！\n");
                    break;
                }
                printf("请输入要删除子树的节点的哈希值（该值为创建时前序序列的编号）：");
                scanf("%d",&e);
                //找节点e
                ptree = FindNode(base->HeadNode, e);
                //printf("%d %c\n", ptree->key, ptree->value);
                if(ptree == NULL)
                {
                    printf("\n没有找到该节点！请重试！");
                    getch();
                    break;
                }
                printf("\n请输入要删除左子树还是右子树？（左子树为0，右子树为1）");
                scanf("%d", &LR);

                //删除
                if(DeleteChild(base->HeadNode, ptree, LR) == OK)
                    printf("删除成功！");
                else
                    printf("\n错误！");
                getch();
                break;
            }

        case 17://PreOrderTraverse
            if(base == NULL)
                printf("当前不存在二叉树，请创建或加载！\n");
            else if(base->HeadNode == NULL)
            {
                printf("当前二叉树为空树！\n");
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
                printf("当前不存在二叉树，请创建或加载！\n");
            else if(base->HeadNode == NULL)
            {
                printf("当前二叉树为空树！\n");
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
                printf("当前不存在二叉树，请创建或加载！\n");
            else if(base->HeadNode == NULL)
            {
                printf("当前二叉树为空树！\n");
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
                printf("当前不存在二叉树，请创建或加载！\n");
            else if(base->HeadNode == NULL)
            {
                printf("当前二叉树为空树！\n");
            }
            else
            {
                BiTree queue[128];  //创建一个队列
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
