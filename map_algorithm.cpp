#include "map.h"

Quene *init_Quene()
{
    auto *head = (Quene *)malloc(sizeof(Quene));
    head->next = nullptr;
    return head;
}

int isEmpty(Quene *head)
{
    if (head->next)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void push(Quene *head, int i, int j)
{
    auto *temp = (Quene *)malloc(sizeof(Quene));
    if (temp)
    {
        temp->father = i;
        temp->son = j;
        temp->next = head->next;
        head->next = temp;
    }
}

void pop(Quene *head, int &i, int &j)
{
    Quene *temp;
    if (!isEmpty(head))
    {
        temp = head->next;
        i = temp->father;
        j = temp->son;
        head->next = temp->next;
        free(temp);
    }
}

void print_Quene(Quene *head)
{
    Quene *temp;
    temp = head->next;
    printf("当前队列如下: \n");
    while (temp)
    {
        printf("父节点:%d ,孩子节点:%d ", temp->father, temp->son);
        temp = temp->next;
    }
}

void print_rout(map *g, Quene *head, int end)
{
    Quene *temp = head->next;
    printf("两点之间的所有路径如下: \n");
    printf("%s <- ", g->point[end].name);
    while (temp)
    {
        printf("%s <- ", g->point[temp->father].name);
        temp = temp->next;
    }
    printf("\n");
}

int get_next(map *g, int &father, int &son)
{
    Arcnode *temp = g->point[father].head->next;
    if (son == -1)
    {
        if (temp)
        {
            son = temp->vexNode;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        while (temp->vexNode != son)
        {
            temp = temp->next;
        }
        if (temp->next)
        {
            son = temp->next->vexNode;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int continue_find(map *g, int father, int son, int start)
{
    Arcnode *temp = g->point[father].head->next;
    while (temp->vexNode != son)
    {
        temp = temp->next;
    }
    if (temp->next != nullptr)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void all_routes(map *g, Quene *head, int start, int end)
{
    head = init_Quene();
    int in_stack[M];
    int father = start;
    int son;
    int count = 0;

    for (int &i : in_stack)
        i = 0;
    if (g->point[start].head->next)
    {
        son = g->point[start].head->next->vexNode;
        push(head, father, son);
        in_stack[start] = 1;
        if (g->point[start].head->next->vexNode == end)
        {
            print_rout(g, head, end);
            count++;
            in_stack[father] = 0;
        }
        else
        {
            father = son;
            son = -1;
        }
    }
    else
    {
        printf("这两个地点暂时不支持直接到达哟~~~ \n");
        return;
    }
    while ((isEmpty(head) == 0) || (continue_find(g, father, son, start)))
    {
        if (get_next(g, father, son))
        {
            if (in_stack[father] == 0)
            {
                if (son != end)
                {
                    push(head, father, son);
                    in_stack[father] = 1;
                    father = son;
                    son = -1;
                }
                else
                {
                    push(head, father, son);
                    in_stack[father] = 1;
                    print_rout(g, head, son);
                    count++;
                }
            }
        }
        else
        {
            pop(head, father, son);
            in_stack[father] = 0;
        }
    }
    printf("总共查询到 %d 种到达方式 \n", count);
}

void dijkstra(map *g, float (*matrix)[M], int start, int end, int dist[M], int path[M][M + 1])
{
    cout << "正在调用dijkstra算法" << endl;
    int mindist;
    int t, k;
    for (int i = 0; i < g->vexnum; ++i)
    {
        path[i][0] = 0;
    }
    for (int i = 0; i < g->vexnum; ++i)
    {
        for (int j = 1; j < M + 1; ++j)
        {
            path[i][j] = -1;
        }
    }

    for (int i = 0; i < g->vexnum; ++i)
    {
        dist[i] = matrix[start][i];
        if (matrix[start][i] != INF)
        {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;
    for (int i = 1; i < g->vexnum; ++i)
    {
        mindist = INF;
        for (int j = 0; j < g->vexnum; ++j)
        {
            if (!path[j][0] && dist[j] < mindist)
            {
                k = j;
                mindist = dist[j];
            }
        }

        if (mindist == INF)
        {
            printf("暂且未查询这两点间路径!\n");
            return;
        }
        path[k][0] = 1;
        for (int j = 1; j < M; ++j)
        {
            if (!path[j][0] && matrix[k][j] < INF && (dist[k] + matrix[k][j] < dist[j]))
            {
                dist[j] = dist[k] + matrix[k][j];
                t = 1;
                while (path[k][t] != -1)
                {
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
            }
        }
    }
    printf("%s 与 %s 之间的最短路径为: \n", g->point[start].name, g->point[end].name);
    t = 1;
    while ((k = path[end][t]) != -1)
    {
        printf("%s ->", g->point[k].name);
        t++;
    }
    printf("%s\n", g->point[end].name);
    printf("\n距离为: %d\n", dist[end]);
}

void print_dijs_matrix(int *dist, int path[][M + 1])
{
    printf("\t====储存距离的数组如下所示====\n");
    for (int i = 0; i < M; ++i)
    {
        printf("%d ", dist[i]);
    }
    printf("\n\t====存储路径的数组如下所示====\n");
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M + 1; ++j)
        {
            printf("%d  ", path[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

MST_point *prim(map *g, float (*matrix)[M], int start)
{
    auto *head = (MST_point *)malloc(sizeof(MST_point));
    MST_point *temp;
    struct
    {
        int adjvex;
        int lowcost;
    } closedge[M];

    int s, min;
    head->next = nullptr;
    closedge[start].lowcost = 0;
    for (int i = 0; i < g->vexnum; ++i)
    {
        if (i != start)
        {
            closedge[i].adjvex = start;
            closedge[i].lowcost = matrix[start][i];
        }
    }

    for (int i = 0; i < g->vexnum - 1; ++i)
    {
        min = INF;
        for (int j = 0; j < g->vexnum; ++j)
        {
            if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)
            {
                s = j;
                min = closedge[j].lowcost;
            }
        }
        temp = (MST_point *)malloc(sizeof(MST_point));
        temp->father = closedge[s].adjvex;
        temp->son = s;
        temp->next = head->next;
        head->next = temp;
        closedge[s].lowcost = 0;

        for (int j = 0; j < g->vexnum; ++j)
        {
            if (j != s && matrix[s][j] < closedge[j].lowcost)
            {
                closedge[j].lowcost = matrix[s][j];
                closedge[j].adjvex = s;
            }
        }
    }
    return head;
}

void print_mst(MST_point *head)
{
    MST_point *temp;
    temp = head->next;
    printf("最小生成树如下: \n");
    while (temp)
    {
        printf("(%d,%d)  ", temp->father, temp->son);
        temp = temp->next;
    }
    printf("\n");
}
