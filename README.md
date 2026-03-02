# 交通咨询系统 V3.0

## 项目简介

本系统是一个基于C++实现的简易交通咨询系统，采用邻接表存储图结构，实现了多种最短路径算法。用户可以咨询任意两城市之间的最短距离、最少时间等问题。

## 项目结构

```
TrafficMap/
├── map.h              # 头文件：结构体定义和函数声明
├── map_data.cpp      # 地图数据操作模块
├── map_algorithm.cpp # 算法模块：Dijkstra、Prim、路径搜索
├── map_main.cpp      # 主函数和菜单模块
├── map_new.exe       # 编译后的可执行文件
├── map.txt           # 地图数据文件
└── 中国各省份初始信息.txt  # 省份参考信息
```

## 模块说明

### map.h - 头文件
- 宏定义：`M`（最大数据规模40）、`INF`（无穷大99999）
- 结构体定义：
  - `Arcnode` - 弧结构（距离、顶点、下一条弧指针）
  - `Line` - 交通图节点（地名、信息、邻接表头指针）
  - `map` - 图的邻接表存储结构
  - `Quene` - 队列结构（用于路径查找）
  - `MST_point` - 最小生成树节点

### map_data.cpp - 地图数据模块
- `init_matrix` - 初始化距离矩阵
- `init_map` - 初始化地图节点
- `creat_map` - 创建地图
- `show_matrix` - 显示矩阵信息
- `cin_file` - 从文件读取地图数据

### map_algorithm.cpp - 算法模块
- 队列操作：`init_Quene`、`push`、`pop`、`isEmpty`
- 路径搜索：`all_routes`、`print_rout`、`get_next`、`continue_find`
- 最短路径：`dijkstra`、`print_dijs_matrix`
- 最小生成树：`prim`、`print_mst`

### map_main.cpp - 主程序模块
- `menu_0` - 主界面菜单
- `point_display` - 节点信息查询
- `select_point` - 节点选择
- `display_mst` - 显示最小生成树
- `point_add` / `point_revoke` - 路径添加/撤销
- `add_point` - 添加新节点

## 系统功能

```
交 通 查 询 系 统 V3.0

      0. 地图的基本信息.
      1. 可供查询的地点及其基本信息介绍
      2. 查询任意两点间所有的路径
      3. 查询两点间最短路径
      4. 查询从某点出发到其它位置的最短连通路径
      5. 路径的扩充
      6. 路径的撤销
      7. 新建整张地图
      8. 添加节点
      9. 删除节点
      10.退出该系统
```

## 算法说明

- **Dijkstra算法**：求指定两点间的最短路径
- **Prim算法**：求最小生成树，实现从某点出发到其他所有点的最短连通路径
- **深度优先搜索**：求两点间的所有路径

## 编译与运行

### 编译
```bash
g++ -o map_new map_main.cpp map_data.cpp map_algorithm.cpp
```

### 运行
```bash
./map_new.exe
```

或直接双击 `map_new.exe` 运行。

## 数据格式

地图数据存储在 `map.txt` 文件中，格式如下：
- 第1行：节点个数
- 每个节点包含：
  - 节点名称（30字节）
  - 节点信息（100字节）
  - 连接的节点个数
  - 每个连接节点的编号和距离

## 注意事项

1. 程序启动时会自动切换控制台编码为UTF-8，确保中文正常显示
2. 新建地图需要管理员密码：`123456`
3. 数据规模最大支持40个节点

## 开发环境

- 编译器：MinGW / GCC
- 语言：C++
- 存储结构：邻接表

2026/3/2
