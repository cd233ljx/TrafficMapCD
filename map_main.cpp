#include "map.h"

void menu_0()
{
    printf("                        交 通 查 询 系 统 V3.0       \n\n ");
    printf("                                   功能页面         \n");
    printf("      0. 地图的基本信息.                             \n");
    printf("      1. 可供查询的地点及其基本信息介绍                \n");
    printf("      2. 查询任意两点间所有的路径                      \n");
    printf("      3. 查询两点间最短路径                           \n");
    printf("      4. 查询从某点出发到其它位置的最短连通路径         \n");
    printf("      5. 路径的扩充                                  \n");
    printf("      6. 路径的撤销                                  \n");
    printf("      7. 新建整张地图                                \n");
    printf("      8. 添加节点                                    \n");
    printf("      9. 删除节点                                    \n");
    printf("      10.退出该系统                                   \n");
    printf("\n\n 根据序号输入你的选择：   ");
}

void point_display(map *g)
{
    int choice;
    printf("\n+++++++++当前可供查询地点信息如下+++++++++    \n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("\t%d : %s\n", i, g->point[i].name);
    }
    cout << "请输入要查询的地点对应的数字: " << endl;
    cout << "=======>>> ";
    cin >> choice;
    printf("查询到 '%s'对应信息如下: \n", g->point[choice].information);
    printf("省会城市: %s\n", g->point[choice].information);
    cout << "\n-----查询结束-----" << endl;
}

void select_point(map *g)
{
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("%d: %s\n", i, g->point[i].name);
    }
}

void display_mst(map *g, MST_point *head)
{
    print_mst(head);
    MST_point *temp;
    temp = head->next;
    printf("查询到的最短连通路径如下:\n");
    while (temp)
    {
        printf("%s --> %s\n", g->point[temp->father].name, g->point[temp->son].name);
        temp = temp->next;
    }
}

void point_add(map *g, float (*matrix)[M], int start, int end, float distance)
{
    auto *temp = (Arcnode *)malloc(sizeof(Arcnode));
    temp->vexNode = end;
    temp->distance = distance;
    temp->next = g->point[start].head->next;
    g->point[start].head->next = temp;
    matrix[start][end] = distance;
}

void point_revoke(map *g, float (*matrix)[M], int start, int end)
{
    Arcnode *temp = g->point[start].head;
    Arcnode *p;
    while (temp->next->vexNode != end)
    {
        temp = temp->next;
    }
    p = temp->next;
    temp->next = temp->next->next;
    free(p);
    matrix[start][end] = INF;
}

void add_point(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    init_map(g);
    cout << "请输入要添加的节点(地点:下同)个数: " << endl;
    cin >> vexnum;
    fprintf(fp, "%d\n", vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *)malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        printf("\n---正在添加第 %d/%d 个根节点---\n", i + 1, vexnum);
        printf("===>>>请输入第[%d]个根节点的名字:", i + 1);
        cin >> g->point[i].name;
        fwrite(g->point[i].name, 30, 1, fp);
        printf("===>>>请输入地点'%s'根的基本信息\n", g->point[i].name);
        cin >> g->point[i].information;
        fwrite(g->point[i].information, 100, 1, fp);
        printf("\n请问有多少节点连接到根节点'%s': ", g->point[i].name);
        cin >> w;
        fprintf(fp, "%d\n", w);

        for (int j = 0; j < w; ++j)
        {
            printf("**开始创建连接到'%s'的节点,当前: %d/%d 个节点**\n", g->point[i].name, j + 1, w);
            temp = (Arcnode *)malloc(sizeof(Arcnode));
            printf("请输入第%d个连接到 '%s' 的节点对应的数字编号===>>> ", j + 1, g->point[i].name);
            cin >> vexnode;
            printf("请输入该节点到 '%s' 的距离===>>> ", g->point[i].name);
            cin >> distance;
            fprintf(fp, "%d %f\n", vexnode, distance);
            temp->vexNode = vexnode;
            temp->distance = distance;

            temp->next = g->point[i].head->next;
            g->point[i].head->next = temp;

            matrix[i][vexnode] = distance;
            printf("\n地点(根节点):'%s'==>第%d个节点点创建成功!\n", g->point[i].name, j + 1);
        }
        printf("---添加第 %d个节点创建成功,名称:'%s',编号:%d!---\n", i + 1, g->point[i].name, i);
        cout << "//********************************************************//" << endl;
        system("pause");
    }
    show_matrix(g, matrix);
}

int main(int argc, char const *argv[])
{
    system("chcp 65001 > nul");
    system("color e");
    system("cls");
    map g;
    Quene *head = nullptr;
    float matrix[M][M];
    int path[M][M + 1];
    int start, end;
    int dist[M];
    MST_point *Head;
    init_matrix(matrix);
    int choice = 0;
    FILE *fp;
    float distance;
    while (true)
    {
        menu_0();
        cin >> choice;
        if (choice == 10)
        {
            printf("\n\n感谢你的使用,再见...\n\n");
            system("pause");
            system("cls");
            break;
        }
        switch (choice)
        {
        case 0:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            fclose(fp);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 1:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            fclose(fp);
            point_display(&g);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 2:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            fclose(fp);
            select_point(&g);
            cout << "====>>>请输入起始点: " << endl;
            cin >> start;
            cout << "====>>>请输入终点: " << endl;
            cin >> end;
            all_routes(&g, head, start, end);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 3:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            fclose(fp);
            select_point(&g);
            cout << "====>>>请输入起始点: " << endl;
            cin >> start;
            cout << "====>>>请输入终点: " << endl;
            cin >> end;
            dijkstra(&g, matrix, start, end, dist, path);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 4:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            fclose(fp);
            select_point(&g);
            cout << "====>>>请输入要查询的起点: " << endl;
            cin >> start;
            Head = prim(&g, matrix, start);
            display_mst(&g, Head);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 5:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            select_point(&g);
            fclose(fp);
            cout << "====>>>请输入要扩充的路径编号" << endl;
            cout << "开始节点: ";
            cin >> start;
            cout << "结束节点: ";
            cin >> end;
            cout << "两点间距离距离为: ";
            cin >> distance;
            printf("\n");
            point_add(&g, matrix, start, end, distance);
            cout << "扩充后的地图如下所示:" << endl;
            show_matrix(&g, matrix);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 6:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            select_point(&g);
            fclose(fp);
            cout << "====>>>请输入需要撤销的路径编号:" << endl;
            cout << "开始节点: ";
            cin >> start;
            cout << "结束节点: ";
            cin >> end;
            printf("\n");
            point_revoke(&g, matrix, start, end);
            cout << "撤销路径后的地图如下所示:" << endl;
            show_matrix(&g, matrix);
        }
        break;
        case 7:
        {
            int yn;
            cout << "!!!!>>> 该操作会覆盖原有文件 <<<!!!!,是否继续?1=是,2=否" << endl;
            cin >> yn;
            if (yn == 2)
            {
                cout << "正在返回..." << endl;
                while (getch())
                {
                    system("cls");
                    break;
                }
                break;
            }
            else
            {
                int password = 0;
                cout << "请输入管理员密码!!!" << endl;
                cin >> password;
                if (password == 123456)
                {
                    fp = fopen("map.txt", "wt");
                    creat_map(&g, matrix, fp);
                    fclose(fp);
                    show_matrix(&g, matrix);
                    cout << "按任意键继续..." << endl;
                    while (getch())
                    {
                        system("cls");
                        break;
                    }
                }
                else
                {
                    cout << "输入错误,请联系管理员...." << endl;
                }
            }
        }
        break;
        case 8:
        {
            fp = fopen("map.txt", "at");
            cin_file(&g, matrix, fp);
            fclose(fp);
            add_point(&g, matrix, fp);
            show_matrix(&g, matrix);
            fclose(fp);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        case 9:
        {
            fp = fopen("map.txt", "rt");
            cin_file(&g, matrix, fp);
            select_point(&g);
            fclose(fp);
            show_matrix(&g, matrix);
            cout << "按任意键继续..." << endl;
            while (getch())
            {
                system("cls");
                break;
            }
        }
        break;
        default:
            printf("输错啦,查无此功能!\n");
            break;
        }
    }
    return 0;
}
