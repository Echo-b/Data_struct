#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
// 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； 对带权图，则为权值类型
typedef int ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;

struct
{
    VertexType adjvex; //最短的边对应u中的顶点
    int lowcost;       //记录u中顶点到顶点j的最短的边
} closedge[MAX_VERTEX_NUM];

int LocateVex(MGraph G, VertexType v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (!strcmp(G.vexs[i], v))
            return i;
    }
    return -1;
}
Status CreatGraph(MGraph &G)
{
    int i, j;
    scanf("%d", &G.vexnum);
    for (i = 0; i < G.vexnum; i++)
        scanf("%s", G.vexs[i]);
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
            scanf("%d", &G.arcs[i][j]);
    G.kind = AG;
    return OK;
}
int minnum(MGraph G)
{
    int min = 999;
    int k = 0, j = 0;
    while (j < G.vexnum)
    {
        if (closedge[j].lowcost != 0 && closedge[j].lowcost < min)
        {
            min = closedge[j].lowcost;
            k = j;
        }
        j++;
    }
    return k;
}
void MinSpanTree_PRIM(MGraph G)
{
    int i, j, k;
    VertexType u;
    strcpy(u, G.vexs[G.vexnum - 1]);
    k = G.vexnum - 1;
    for (j = 0; j < G.vexnum; j++) //初始化
    {
        if (j != k)
        {
            strcpy(closedge[j].adjvex, u);
            closedge[j].lowcost = G.arcs[k][j];
        }
    }
    closedge[k].lowcost = 0;       //初始U={u}
    for (i = 1; i < G.vexnum; i++) //选择其余G.vexnum-1个顶点
    {
        k = minnum(G);                                    //求出T的下一个节点，第k顶点
        printf("%s %s\n", closedge[k].adjvex, G.vexs[k]); //输出
        closedge[k].lowcost = 0;                          //第k顶点并入U集
        for (j = 0; j < G.vexnum; j++)
            if (G.arcs[k][j] < closedge[j].lowcost)
            {
                strcpy(closedge[j].adjvex, G.vexs[k]);
                closedge[j].lowcost = G.arcs[k][j];
            }
    }
}
int main()
{
    MGraph g;
    CreatGraph(g);
    MinSpanTree_PRIM(g);
    return 0;
}