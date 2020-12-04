#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 100 //存储空间初始分配
#define STACKINCREMENT 10   //存储空间分配增量
#define OVERFLOW -1
#define OK 1
#define ERROR 0

#define MAX_VERTEX_NUM 30 // 最大顶点个数
enum GraphKind
{
    DG,
    DN,
    AG,
    AN
}; // {有向图,有向网,无向图,无向网}
typedef int Status;
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

int LocateVex(ALGraph G, VertexType v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (!strcmp(G.vertices[i].data, v))
            return i;
    }
    return -1;
}
Status CreateGraph(ALGraph &G)
{
    ArcNode *p;
    int i, j, k;
    VertexType va, vb;
    scanf("%d%d", &G.vexnum, &G.arcnum);
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++)
    {
        scanf("%s%s", va, vb);
        i = LocateVex(G, va);
        j = LocateVex(G, vb);
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
    return OK;
}
//栈
typedef int SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;
typedef int Status;

Status InitStack(SqStack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); //存储分配失败
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

int GetTop(SqStack &s, SElemType &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *(s.top - 1);
    return e;
}

Status Push(SqStack &s, SElemType e)
{ //插入元素e为新的栈顶元素
    if (s.top - s.base >= s.stacksize)
    { //栈满,追加存储空间
        s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!s.base)
            exit(OVERFLOW); //存储分配失败
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }

    *s.top++ = e;
    return OK;
}

Status Pop(SqStack &s, SElemType &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *--s.top;
    return OK;
}
Status StackEmpty(SqStack s)
{
    if (s.top == s.base)
        return OK;
    else
        return ERROR;
}
int indegree[MAX_VERTEX_NUM] = {0};
void FindInDegree(ALGraph G)
{
    int i;
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        p = G.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}
void topologicalsort(ALGraph G)
{
    FindInDegree(G);
    SqStack s;
    int i, count = 0, k;
    InitStack(s);
    ArcNode *p;
    for (i = 0; i < G.vexnum; i++)
    {
        if (!indegree[i])
            Push(s, i);
    }
    while (!StackEmpty(s))
    {
        Pop(s, i);
        printf("%s ", G.vertices[i].data);
        ++count;
        for (p = G.vertices[i].firstarc; p; p = p->nextarc)
        {
            k = p->adjvex;
            if (!(--indegree[k]))
                Push(s, k);
        }
    }
    if (count < G.vexnum)
        printf("error");
}
int main()
{
    ALGraph g;
    CreateGraph(g);
    topologicalsort(g);
    return 0;
}