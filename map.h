#ifndef MAP_H
#define MAP_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <conio.h>

#define   M 40      //最大数据规模
#define   INF 99999 //以99999代表无穷

using namespace std;

/**定义结构体类型存储弧结构*/
typedef struct node
{
    float distance;  //距离
    int vexNode;     //顶点
    struct node *next; //指向下一条弧的指针
} Arcnode;

/**交通图节点元素类型*/
typedef struct vertexnode
{
    char name[30];         //地名
    char information[100]; //相应信息
    Arcnode *head;         //下一个路径
} Line;

/**图的存储结构定义*/
typedef struct adjlist
{
    Line point[M];  //顶点集合
    int arcnum;     //顶点数
    int vexnum;     //弧数
} map;

/**队列结构体用于实现迪杰斯特拉算法*/
typedef struct quene
{
    int father;
    int son;
    struct quene *next;
} Quene;

/**最小生成树节点定义:两点间最短路径*/
typedef struct mst_point
{
    int father;
    int son;
    struct mst_point *next;
} MST_point;

/**初始化矩阵*/
void init_matrix(float (*matrix)[M]);

/**开辟空间存放地点名和地点信息*/
void init_map(map *g);

/**地图的创建*/
void creat_map(map *g, float (*matrix)[M], FILE *fp);

/**显示矩阵存储信息*/
void show_matrix(map *g, float (*matrix)[M]);

/**初始化队列*/
Quene *init_Quene();

/**判断队列是否为空*/
int isEmpty(Quene *head);

/**入队操作 插入元素,i:父亲节点   j:孩子节点*/
void push(Quene *head, int i, int j);

/**出队操作*/
void pop(Quene *head, int &i, int &j);

/**显示当前队列*/
void print_Quene(Quene *head);

/**找到两点之间的所有路径*/
void print_rout(map *g, Quene *head, int end);

/**是否存在下一个节点*/
int get_next(map *g, int &father, int &son);

/**查看father是否还有son节点,有返回0*/
int continue_find(map *g, int father, int son, int start);

/**求两点间的所有路径*/
void all_routes(map *g, Quene *head, int start, int end);

/**dijkstra算法求两点之间的最短路径*/
void dijkstra(map *g, float (*matrix)[M], int start, int end, int dist[M], int path[M][M + 1]);

/**显示dijkstra存储的数组示意图*/
void print_dijs_matrix(int *dist, int path[][M + 1]);

/**Prim算法获取最小生成树*/
MST_point *prim(map *g, float(*matrix)[M], int start);

/**查看最小生成树*/
void print_mst(MST_point *head);

/**文件读入*/
void cin_file(map *g, float (*matrix)[M], FILE *fp);

/**节点信息查询模块*/
void point_display(map *g);

/**对应节点选择模块*/
void select_point(map *g);

/**显示最短连通路径*/
void display_mst(map *g, MST_point *head);

/**节点添加*/
void point_add(map *g, float(*matrix)[M], int start, int end, float distance);

/**节点撤销*/
void point_revoke(map *g, float(*matrix)[M], int start, int end);

/**根节点的添加*/
void add_point(map *g, float (*matrix)[M], FILE *fp);

/**主界面菜单*/
void menu_0();

#endif // MAP_H
