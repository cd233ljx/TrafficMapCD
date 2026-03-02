#include "map.h"

void init_matrix(float (*matrix)[M])
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            matrix[i][j] = INF;
        }
    }
}

void init_map(map *g)
{
    for (auto &i : g->point)
    {
        memset(i.name, 0, 30 * sizeof(char));
        memset(i.information, 0, 100 * sizeof(char));
    }
    for (auto &i : g->point)
    {
        i.name[29] = '\n';
        i.information[29] = '\n';
    }
}

void creat_map(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    init_map(g);
    cout << "请输入要创建的节点(地点:下同)个数: " << endl;
    cin >> vexnum;
    fprintf(fp, "%d\n", vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *)malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        printf("\n---正在创建第 %d/%d 个根节点---\n", i + 1, vexnum);
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
        printf("---创建第 %d个节点创建成功,名称:'%s',编号:%d!---\n", i + 1, g->point[i].name, i);
        cout << "//********************************************************//" << endl;
        system("pause");
    }
}

void show_matrix(map *g, float (*matrix)[M])
{
    Arcnode *temp;
    printf("当前共有节点个数: %d\n", g->vexnum);
    printf("\t===矩阵如下===\n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        for (int j = 0; j < g->vexnum; ++j)
        {
            printf("%10.2f  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n %d \n", g->vexnum);
    for (int i = 0; i < g->vexnum; ++i)
    {
        temp = g->point[i].head->next;
        printf("连接的 '%s' 的地点有:", g->point[i].name);
        while (temp)
        {
            printf(" (%s,距离:%.1f) ", g->point[temp->vexNode].name, temp->distance);
            temp = temp->next;
        }
        printf("\n详细信息为: %s\n\n\n", g->point[i].information);
    }
}

void cin_file(map *g, float (*matrix)[M], FILE *fp)
{
    Arcnode *temp;
    int vexnum;
    int w;
    int vexnode;
    float distance;
    fscanf(fp, "%d\n", &vexnum);
    g->vexnum = vexnum;
    for (int i = 0; i < vexnum; ++i)
    {
        g->point[i].head = (Arcnode *)malloc(sizeof(Arcnode));
        g->point[i].head->next = nullptr;
        fread(g->point[i].name, 30, 1, fp);
        fread(g->point[i].information, 100, 1, fp);
        fscanf(fp, "%d\n", &w);
        for (int j = 0; j < w; ++j)
        {
            temp = (Arcnode *)malloc(sizeof(Arcnode));
            fscanf(fp, "%d %f\n", &vexnode, &distance);
            temp->vexNode = vexnode;
            temp->distance = distance;
            temp->next = g->point[i].head->next;
            g->point[i].head->next = temp;
            matrix[i][vexnode] = distance;
        }
    }
    show_matrix(g, matrix);
}
