/** \brief  基于邻接表的图实现
 *         该文件用于储存主函数
 *
 */
#include"graph.h"

int main(void)
{
    int op=1;
    ALGraph *graph = NULL;
    VertexType value, w;
    char *ch;
    int i;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Graph On Link Structure \n");
        printf("-------------------------------------------------\n");
        printf("                     Attation           \n");
        if(graph == NULL)
            printf("    There is no Graph now! Please Init a graph! \n");
        else printf("     There is a Graph now!  \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateGraph          8. InsertVex\n");
        printf("    	  2. DestroyGraph         9. DeleteVex\n");
        printf("    	  3. LocateVex            10. InsertArc \n");
        printf("    	  4. GetVex               11. DeleteArc\n");
        printf("    	  5. PutVex               12. DFSTraverse\n");
        printf("    	  6. FirstAdjVex          13. BFSTraverse\n");
        printf("    	  7. NextAdjVex                \n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~22]:");
        scanf("%d",&op);
        switch (op)
        {
        case 1://CreateGraph
            if(graph == NULL)
            {
                if(CreateGraph(&graph) == OK)
                    printf("\n该图创建成功！");
            }
            else
                printf("当前已存在图！请销毁后再建！\n");
            getch();
            break;

        case 2://DestroyGraph
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                if(DestroyGraph(&graph) == OK)
                    printf("该图销毁成功！");
            }
            getch();
            break;

        case 3://LocateVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要查找的顶点：");
                scanf("%s",value);
                i = LocateVex(*graph, value);
                if(i == -1)
                    printf("没有找到该顶点！\n");
                else
                    printf("该顶点的位置为 %d\n", i);
            }
            getch();
            break;

        case 4://GetVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要查找的顶点位置：");
                scanf("%d",&i);
                ch = GetVex(graph, i);
                if(ch == NULL)
                    printf("没有找到该顶点！\n");
                else
                    printf("该顶点的值为 %s\n", ch);
            }
            getch();
            break;

        case 5://PutVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要赋值的顶点位置：");
                scanf("%d",&i);
                printf("\n请输入要赋值的值：");
                scanf("%s", value);

                if(PutVex(graph, i, value) == OK)
                    printf("赋值成功！\n");
                else
                    printf("赋值失败！\n");
            }
            getch();
            break;

        case 6://FirstAdjVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要查找第一邻接点的值：");
                scanf("%s",value);
                i = FirstAdjVex(*graph, value);
                if(i == -1)
                    printf("没有找到该点！\n");
                else
                    printf("该顶点的第一邻接点的位置为 %d 值为 %s\n", i, graph->vertices[i].data);
            }
            getch();
            break;

        case 7://NextAdjVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要查找邻接点的值：");
                scanf("%s",value);
                printf("\n请输入要查找该点下一邻接点的值：");
                scanf("%s",w);
                i = NextAdjVex(*graph, value, w);
                if(i == -1)
                    printf("没有找到该点！\n");
                else
                    printf("该顶点%s 相对于%s的下一邻接点的位置为 %d 值为 %s\n",value, w, i, graph->vertices[i].data);
            }
            getch();
            break;

        case 8://InsertVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要新增的顶点的值：");
                scanf("%s",value);
                InsertVex(graph, value);
                printf("新增成功！");
            }
            getch();
            break;

        case 9://DeleteVex
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要删除的顶点：");
                scanf("%s",value);
                if(DeleteVex(graph, value) == OK)
                {
                    printf("\n删除成功！该顶点后的顶点位置前移一个单位！\n");
                }
                else
                    printf("\n错误！删除失败！\n");
            }
            getch();
            break;

        case 10://InsertArc
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要添加的弧两顶点：");
                scanf("%s %s", value, w);
                if(InsertArc(graph, value, w) == OK)
                    printf("\n添加成功！");
                else
                    printf("错误！添加失败！");
            }
            getch();
            break;
        case 11://DeleteArc
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("请输入要删除的弧两顶点：");
                scanf("%s %s", value, w);
                if(DeleteArc(graph, value, w) == OK)
                    printf("\n删除成功！");
                else
                    printf("错误！删除失败！");
            }
            getch();
            break;

        case 12://DFSTraverse
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("----------------------------\n");
                DFSTraverse(*graph, printf_my);
                printf("\n----------------------------\n");
            }
            getch();
            break;

        case 13://BFSTraverse
            if(graph == NULL)
            {
                printf("当前不存在图！请创建！\n");
            }
            else
            {
                printf("----------------------------\n");
                BFSTraverse(*graph, printf_my);
                printf("\n----------------------------\n");
            }
            getch();
            break;

        case 14:

            break;

        default:
            break;
        }
    }
    return 0;
}
