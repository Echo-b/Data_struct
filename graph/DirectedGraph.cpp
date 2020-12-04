#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1
typedef int Status;

#define MAX_VERTEX_NUM 30 // 最大顶点个数
enum GraphKind
{
    DG,
    DN,
    AG,
    AN
}; // {有向图,有向网,无向图,无向网}

//图的邻接表存储表示
typedef char VertexType[6];
struct ArcNode
{
    int adjvex;       // 该弧所指向的顶点的位置
    ArcNode *nextarc; // 指向下一条弧的指针
    int info;         // 网的权值
};                    // 表结点
typedef struct
{
    VertexType data;              // 顶点信息
    ArcNode *firstarc;            // 第一个表结点的地址,指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM]; // 头结点
struct ALGraph
{
    AdjList vertices;
    int vexnum, arcnum; // 图的当前顶点数和弧数
    int kind;           // 图的种类标志
};

int LocateVex(ALGraph G, VertexType u)
{ // 初始条件: 图G存在,u和G中顶点有相同特征
    // 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
    int i;
    for (i = 0; i < G.vexnum; ++i)
        if (!strcmp(G.vertices[i].data, u))
            return i;
    return -1;
}

Status CreateGraph(ALGraph &G)
{ //采用头插法,构造有向网
    int i, j, k;
    int w; // 权值
    VertexType va, vb;
    ArcNode *p;
    G.kind = DN;
    printf("请输入图的顶点数,弧数: ");
    scanf("%d,%d", &G.vexnum, &G.arcnum);
    printf("\n请输入%d个顶点的值:\n", G.vexnum);
    for (i = 0; i < G.vexnum; ++i) // 构造顶点向量
    {
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = 0;
    }
    printf("请依次输入每条弧弧尾和弧头、权值(以空格作为间隔):\n");
    for (k = 0; k < G.arcnum; ++k) // 构造表结点链表
    {
        scanf("%s%s%d", va, vb, &w);
        i = LocateVex(G, va); // 弧尾
        j = LocateVex(G, vb); // 弧头
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->info = w;
        p->nextarc = G.vertices[i].firstarc; // 插在表头
        G.vertices[i].firstarc = p;
    }
    return OK;
}

void DestroyGraph(ALGraph &G)
{ // 初始条件: 图G存在。操作结果: 销毁图G
    int i;
    ArcNode *p, *q;
    for (i = 0; i < G.vexnum; ++i)
    {
        p = G.vertices[i].firstarc;
        while (p)
        {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
}

Status PutVex(ALGraph &G, VertexType v, VertexType value)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 对v赋新值value
    int i;
    i = LocateVex(G, v);
    if (i > -1) // v是G的顶点
    {
        strcpy(G.vertices[i].data, value);
        return OK;
    }
    return ERROR;
}

int FirstAdjVex(ALGraph G, VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
    ArcNode *p;
    int v1;
    v1 = LocateVex(G, v); // v1为顶点v在图G中的序号
    p = G.vertices[v1].firstarc;
    if (p)
        return p->adjvex;
    else
        return -1;
}

int NextAdjVex(ALGraph G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
    // 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。
    //           若w是v的最后一个邻接点,则返回-1
    ArcNode *p;
    int v1, w1;
    v1 = LocateVex(G, v); // v1为顶点v在图G中的序号
    w1 = LocateVex(G, w); // w1为顶点w在图G中的序号
    p = G.vertices[v1].firstarc;
    while (p && p->adjvex != w1) // 指针p不空且所指表结点不是w
        p = p->nextarc;
    if (!p || !p->nextarc) // 没找到w或w是最后一个邻接点
        return -1;
    else
        return p->nextarc->adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号
}

void InsertVex(ALGraph &G, VertexType v)
{ // 初始条件: 图G存在,v和图中顶点有相同特征
    // 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
    strcpy(G.vertices[G.vexnum].data, v); // 构造新顶点向量
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++; // 图G的顶点数加1
}

Status DeleteVex(ALGraph &G, VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 删除G中顶点v及其相关的弧
    int i, j;
    ArcNode *p, *q;
    j = LocateVex(G, v); // j是顶点v的序号
    if (j < 0)           // v不是图G的顶点
        return ERROR;
    p = G.vertices[j].firstarc; // 删除以v为出度的弧
    while (p)
    {
        q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--; // 弧或边数减1
    }

    G.vexnum--;                    // 顶点数减1
    for (i = j; i < G.vexnum; i++) // 顶点v后面的顶点前移
        G.vertices[i] = G.vertices[i + 1];
    for (i = 0; i < G.vexnum; i++) // 删除以v为入度的弧且必要时修改表结点的顶点位置值
    {
        p = G.vertices[i].firstarc; // 指向第1条弧
        while (p)                   // 有弧
        {
            if (p->adjvex == j)
            {
                if (p == G.vertices[i].firstarc) // 待删结点是第1个结点
                {
                    G.vertices[i].firstarc = p->nextarc;
                    free(p);
                    p = G.vertices[i].firstarc;
                    G.arcnum--; // 弧数减1
                }
                else
                {
                    q = p;
                    free(p);
                    p = q->nextarc;
                    G.arcnum--; // 弧减1
                }
            }
            else
            {
                if (p->adjvex > j)
                    p->adjvex--; // 修改表结点的顶点位置值(序号)
                q = p;
                p = p->nextarc;
            }
        }
    }
    return OK;
}

Status InsertArc(ALGraph &G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v和w是G中两个顶点
    // 操作结果: 在G中增添弧<v,w>
    ArcNode *p;
    int w1, i, j;
    i = LocateVex(G, v); // 弧尾的序号
    j = LocateVex(G, w); // 弧头的序号
    if (i < 0 || j < 0)
        return ERROR;
    G.arcnum++; // 图G的弧或边的数目加1
    printf("\n请输入弧%s→%s的权值: ", v, w);
    scanf("%d", &w1);
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = j;
    p->info = w1;
    p->nextarc = G.vertices[i].firstarc; // 插在表头
    G.vertices[i].firstarc = p;
    return OK;
}

Status DeleteArc(ALGraph &G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v和w是G中两个顶点
    // 操作结果: 在G中删除弧<v,w>
    ArcNode *p, *q;
    int i, j;
    i = LocateVex(G, v); // i是顶点v(弧尾)的序号
    j = LocateVex(G, w); // j是顶点w(弧头)的序号
    if (i < 0 || j < 0 || i == j)
        return ERROR;
    p = G.vertices[i].firstarc; // p指向顶点v的第一条出弧
    while (p && p->adjvex != j) // p不空且所指之弧不是待删除弧<v,w>
    {                           // p指向下一条弧
        q = p;
        p = p->nextarc;
    }
    if (p && p->adjvex == j) // 找到弧<v,w>
    {
        if (p == G.vertices[i].firstarc)         // p所指是第1条弧
            G.vertices[i].firstarc = p->nextarc; // 指向下一条弧
        else
            q->nextarc = p->nextarc; // 指向下一条弧
        free(p);                     // 释放此结点
        G.arcnum--;                  // 弧或边数减1
    }
    return OK;
}

void Display(ALGraph G)
{ // 输出图的邻接矩阵G
    int i;
    ArcNode *p;
    printf("%d个顶点：\n", G.vexnum);
    for (i = 0; i < G.vexnum; ++i)
        printf("%s ", G.vertices[i].data);
    printf("\n%d条弧:\n", G.arcnum);
    for (i = 0; i < G.vexnum; i++)
    {
        p = G.vertices[i].firstarc;
        while (p)
        {
            printf("%s→%s ", G.vertices[i].data, G.vertices[p->adjvex].data);
            printf(":%d ", p->info);
            p = p->nextarc;
            printf("\n");
        }
    }
}

int main()
{
    int i, j, k, n;
    ALGraph g;
    VertexType v1, v2;
    CreateGraph(g);
    Display(g);
    printf("删除一条弧，请输入待删除弧的弧尾 弧头：");
    scanf(" %s%s", v1, v2);
    DeleteArc(g, v1, v2);
    printf("\n修改顶点的值，请输入原值 新值: ");
    scanf(" %s%s", v1, v2);
    PutVex(g, v1, v2);
    printf("\n插入新顶点，请输入顶点的值: ");
    scanf("%s", v1);
    InsertVex(g, v1);
    printf("\n插入与新顶点有关的弧，请输入弧数: ");
    scanf("%d", &n);
    for (k = 0; k < n; k++)
    {
        printf("\n请输入另一顶点的值: ");
        scanf("%s", v2);
        InsertArc(g, v2, v1);
    }
    printf("\n");
    Display(g);
    printf("删除顶点及相关的弧，请输入顶点的值: ");
    scanf("%s", v1);
    DeleteVex(g, v1);
    printf("\n");
    Display(g);
    DestroyGraph(g);
    return 0;
}