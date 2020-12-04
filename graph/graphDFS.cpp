#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 图的数组(邻接矩阵)存储表示
#define MAX_VERTEX_NUM 30 // 最大顶点个数
#define OK 1
#define ERROR 0

enum GraphKind
{
    DG,
    DN,
    AG,
    AN
}; // {有向图,有向网,无向图,无向网}

typedef int Status;
typedef char VertexType[6];
bool visit[MAX_VERTEX_NUM];
// 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； 对带权图，则为权值类型
typedef int ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

struct MGraph
{
    VertexType vexs[MAX_VERTEX_NUM]; // 顶点向量
    AdjMatrix arcs;                  // 邻接矩阵
    int vexnum, arcnum;              // 图的当前顶点数和弧数
    GraphKind kind;                  // 图的种类标志
};

// 图的数组(邻接矩阵)存储基本操作
int LocateVex(MGraph G, VertexType u)
{ // 初始条件:图G存在,u和G中顶点有相同特征
    // 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (strcmp(G.vexs[i], u) == 0)
            return i;
    return -1;
}

Status CreateAG(MGraph &G)
{ // 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G
    int i, j;
    scanf("%d", &G.vexnum);
    for (i = 0; i < G.vexnum; i++) // 构造顶点向量
        scanf(" %s", G.vexs[i]);
    for (i = 0; i < G.vexnum; i++) // 初始化邻接矩阵
        for (j = 0; j < G.vexnum; j++)
            scanf("%d", &G.arcs[i][j]);
    G.kind = AG;
    return OK;
}

void DFS(MGraph G, int i)
{
    int j;
    visit[i] = true;
    printf("%s ", G.vexs[i]);
    for (j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[i][j] >= 1 && !visit[j])
            DFS(G, j);
    }
}
void DFSTraverse(MGraph G)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        visit[i] = false;
    }
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visit[i])
            DFS(G, i);
    }
}
int main()
{
    MGraph g;
    CreateAG(g);
    DFSTraverse(g);
    return 0;
}