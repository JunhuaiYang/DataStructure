/** \brief  �����ڽӱ��ͼʵ��
 *         ���ļ����ڴ���������
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
        printf("    ��ѡ����Ĳ���[0~22]:");
        scanf("%d",&op);
        switch (op)
        {
        case 1://CreateGraph
            if(graph == NULL)
            {
                if(CreateGraph(&graph) == OK)
                    printf("\n��ͼ�����ɹ���");
            }
            else
                printf("��ǰ�Ѵ���ͼ�������ٺ��ٽ���\n");
            getch();
            break;

        case 2://DestroyGraph
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                if(DestroyGraph(&graph) == OK)
                    printf("��ͼ���ٳɹ���");
            }
            getch();
            break;

        case 3://LocateVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ���ҵĶ��㣺");
                scanf("%s",value);
                i = LocateVex(*graph, value);
                if(i == -1)
                    printf("û���ҵ��ö��㣡\n");
                else
                    printf("�ö����λ��Ϊ %d\n", i);
            }
            getch();
            break;

        case 4://GetVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ���ҵĶ���λ�ã�");
                scanf("%d",&i);
                ch = GetVex(graph, i);
                if(ch == NULL)
                    printf("û���ҵ��ö��㣡\n");
                else
                    printf("�ö����ֵΪ %s\n", ch);
            }
            getch();
            break;

        case 5://PutVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ��ֵ�Ķ���λ�ã�");
                scanf("%d",&i);
                printf("\n������Ҫ��ֵ��ֵ��");
                scanf("%s", value);

                if(PutVex(graph, i, value) == OK)
                    printf("��ֵ�ɹ���\n");
                else
                    printf("��ֵʧ�ܣ�\n");
            }
            getch();
            break;

        case 6://FirstAdjVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ���ҵ�һ�ڽӵ��ֵ��");
                scanf("%s",value);
                i = FirstAdjVex(*graph, value);
                if(i == -1)
                    printf("û���ҵ��õ㣡\n");
                else
                    printf("�ö���ĵ�һ�ڽӵ��λ��Ϊ %d ֵΪ %s\n", i, graph->vertices[i].data);
            }
            getch();
            break;

        case 7://NextAdjVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ�����ڽӵ��ֵ��");
                scanf("%s",value);
                printf("\n������Ҫ���Ҹõ���һ�ڽӵ��ֵ��");
                scanf("%s",w);
                i = NextAdjVex(*graph, value, w);
                if(i == -1)
                    printf("û���ҵ��õ㣡\n");
                else
                    printf("�ö���%s �����%s����һ�ڽӵ��λ��Ϊ %d ֵΪ %s\n",value, w, i, graph->vertices[i].data);
            }
            getch();
            break;

        case 8://InsertVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ�����Ķ����ֵ��");
                scanf("%s",value);
                InsertVex(graph, value);
                printf("�����ɹ���");
            }
            getch();
            break;

        case 9://DeleteVex
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫɾ���Ķ��㣺");
                scanf("%s",value);
                if(DeleteVex(graph, value) == OK)
                {
                    printf("\nɾ���ɹ����ö����Ķ���λ��ǰ��һ����λ��\n");
                }
                else
                    printf("\n����ɾ��ʧ�ܣ�\n");
            }
            getch();
            break;

        case 10://InsertArc
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫ��ӵĻ������㣺");
                scanf("%s %s", value, w);
                if(InsertArc(graph, value, w) == OK)
                    printf("\n��ӳɹ���");
                else
                    printf("�������ʧ�ܣ�");
            }
            getch();
            break;
        case 11://DeleteArc
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
            }
            else
            {
                printf("������Ҫɾ���Ļ������㣺");
                scanf("%s %s", value, w);
                if(DeleteArc(graph, value, w) == OK)
                    printf("\nɾ���ɹ���");
                else
                    printf("����ɾ��ʧ�ܣ�");
            }
            getch();
            break;

        case 12://DFSTraverse
            if(graph == NULL)
            {
                printf("��ǰ������ͼ���봴����\n");
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
                printf("��ǰ������ͼ���봴����\n");
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
