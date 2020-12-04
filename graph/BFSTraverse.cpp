#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXQSIZE 100
#define ERROR 0
#define OK 1
#define OVERFLOW -1
typedef int Status;
typedef int QElemType;
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

typedef struct
{
    QElemType *base; //初始化的动态分配存储空间
    int front;       //头指针,若队列不空,指向队列头元
    int rear;
} SqQueue;

bool visit[MAX_VERTEX_NUM] = {0};
Status InitQueue(SqQueue &Q)
{ //  构造一个空队列Q
    Q.base = (QElemType *)malloc(sizeof(QElemType) * MAXQSIZE);
    if (!Q.base)
        exit(OVERFLOW); //存储分配失败
    Q.front = 0;
    Q.rear = 0;
    return OK;
}
int QueueLength(SqQueue Q)
{ //返回Q的元素个数,即队列的长度
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
Status EnQueue(SqQueue &Q, QElemType e)
{                                           // 插入元素e为Q的新的队尾元素
    if ((Q.rear + 1) % MAXQSIZE == Q.front) //队列满
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}
Status DeQueue(SqQueue &Q, QElemType &e)
{ // 删除队头元素，送给变量e
    if (Q.rear == Q.front)
        return ERROR; //队列空
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}
Status QueueEmpty(SqQueue Q)
{
    if (Q.rear == Q.front)
        return OK;
    return ERROR;
}

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
    VertexType va, vb;
    ArcNode *p;
    G.kind = DN;
    scanf("%d%d", &G.vexnum, &G.arcnum);
    for (i = 0; i < G.vexnum; i++) // 构造顶点向量
    {
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++) // 构造表结点链表
    {
        scanf("%s%s", va, vb);
        i = LocateVex(G, va); // 弧尾
        j = LocateVex(G, vb); // 弧头
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = G.vertices[i].firstarc; // 插在表头
        G.vertices[i].firstarc = p;
    }
    return OK;
}
void BFSTrverse(ALGraph G)
{
    SqQueue Q;
    InitQueue(Q);
    int i;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            printf("%s ", G.vertices[i].data);
            EnQueue(Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(Q, i);
                p = G.vertices[i].firstarc;
                while (p)
                {
                    if (!visit[p->adjvex])
                    {
                        visit[p->adjvex] = true;
                        printf("%s ", G.vertices[p->adjvex].data);
                        EnQueue(Q, p->adjvex);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
}
int main()
{
    ALGraph g;
    CreateGraph(g);
    BFSTrverse(g);
    return 0;
}
