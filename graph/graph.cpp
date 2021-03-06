// 图的数组(邻接矩阵)存储表示
#define MAX_VERTEX_NUM 20 // 最大顶点个数
enum GraphKind
{
    DG,
    DN,
    AG,
    AN
}; // {有向图,有向网,无向图,无向网}

typedef char VertexType[6];

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
    for (i = 0; i < G.vexnum; ++i)
        if (strcmp(G.vexs[i], u) == 0)
            return i;
    return -1;
}

Status CreateAG(MGraph &G)
{ // 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G
    int i, j, k;
    VertexType va, vb;
    printf("请输入无向图G的顶点数,边数:");
    scanf("%d", &G.vexnum);
    scanf("%d", &G.arcnum);
    printf("\n请输入%d个顶点的值:\n", G.vexnum);
    for (i = 0; i < G.vexnum; ++i) // 构造顶点向量
        scanf(" %s", G.vexs[i]);
    for (i = 0; i < G.vexnum; ++i) // 初始化邻接矩阵
        for (j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = 0;
    printf("请输入%d条边的顶点1 顶点2:\n", G.arcnum);
    for (k = 0; k < G.arcnum; ++k)
    {
        scanf(" %s%s", va, vb);
        i = LocateVex(G, va);
        j = LocateVex(G, vb);
        G.arcs[i][j] = G.arcs[j][i] = 1; // 无向图
    }
    G.kind = AG;
    return OK;
}

void DestroyGraph(MGraph &G)
{ // 初始条件: 图G存在。操作结果: 销毁无向图G
    G.vexnum = 0;
    G.arcnum = 0;
}

Status PutVex(MGraph &G, VertexType v, VertexType value)
{ // 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value
    int k;
    k = LocateVex(G, v); // k为顶点v在图G中的序号
    if (k < 0)
        return ERROR;

    strcpy(G.vexs[k], value);
    return OK;
}

int FirstAdjVex(MGraph G, VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
    int i, j = 0, k;
    k = LocateVex(G, v); // k为顶点v在图G中的序号
    for (i = 0; i < G.vexnum; i++)
        if (G.arcs[k][i] != 0) //无向图
            return i;
    return -1;
}

int NextAdjVex(MGraph G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
    // 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号,
    //           若w是v的最后一个邻接顶点,则返回-1
    int i, j = 0, k1, k2;
    k1 = LocateVex(G, v); // k1为顶点v在图G中的序号
    k2 = LocateVex(G, w); // k2为顶点w在图G中的序号
    for (i = k2 + 1; i < G.vexnum; i++)
        if (G.arcs[i][k1] != 0)
            return i;
    return -1;
}

void InsertVex(MGraph &G, VertexType v)
{ // 初始条件: 图G存在,v和图G中顶点有相同特征
    // 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
    int i;
    strcpy(G.vexs[G.vexnum], v); // 构造新顶点向量
    for (i = 0; i <= G.vexnum; i++)
    {
        G.arcs[G.vexnum][i] = 0; // 初始化该行邻接矩阵的值(无边或弧)
        G.arcs[i][G.vexnum] = 0; // 初始化该列邻接矩阵的值(无边或弧)
    }

    G.vexnum++; // 图G的顶点数加1
}

Status DeleteVex(MGraph &G, VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧
    int i, j, k;
    k = LocateVex(G, v); // k为待删除顶点v的序号
    if (k < 0)           // v不是图G的顶点
        return ERROR;
    for (j = 0; j < G.vexnum; j++)
        if (G.arcs[j][k] != 0)         // 有边
            G.arcnum--;                // 修改边数
    for (j = k + 1; j < G.vexnum; j++) // 序号k后面的顶点向量依次前移
        strcpy(G.vexs[j - 1], G.vexs[j]);
    for (i = 0; i < G.vexnum; i++)
        for (j = k + 1; j < G.vexnum; j++)
            G.arcs[i][j - 1] = G.arcs[i][j]; // 移动待删除顶点之后的矩阵元素
    for (i = 0; i < G.vexnum; i++)
        for (j = k + 1; j < G.vexnum; j++)
            G.arcs[j - 1][i] = G.arcs[j][i]; // 移动待删除顶点之下的矩阵元素
    G.vexnum--;                              // 更新图的顶点数
    return OK;
}

Status InsertArc(MGraph &G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v和W是G中两个顶点
    // 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v>
    int i, l, v1, w1;
    v1 = LocateVex(G, v); // 尾
    w1 = LocateVex(G, w); // 头
    if (v1 < 0 || w1 < 0)
        return ERROR;

    G.arcnum++; // 弧或边数加1

    G.arcs[v1][w1] = 1, G.arcs[w1][v1] = 1;
    return OK;
}

Status DeleteArc(MGraph &G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v和w是G中两个顶点
    // 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v>
    int v1, w1;
    v1 = LocateVex(G, v); // 尾
    w1 = LocateVex(G, w); // 头
    if (v1 < 0 || w1 < 0) // v1、w1的值不合法
        return ERROR;

    G.arcs[v1][w1] = 0, G.arcs[w1][v1] = 0;

    G.arcnum--; //修改边数
    return OK;
}
void Display(MGraph G)
{ // 输出无向图G
    int i, j;
    printf("%d个顶点%d条边的无向图\n", G.vexnum, G.arcnum);
    for (i = 0; i < G.vexnum; ++i) // 输出G.vexs
        printf("G.vexs[%d]=%s\n", i, G.vexs[i]);
    printf("G.arcs:\n"); // 输出G.arcs.adj
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%2d", G.arcs[i][j]);
        printf("\n");
    }
}

int main()
{
    int i, j, k, n;
    VertexType v1, v2;
    MGraph g;
    CreateAG(g);
    Display(g);
    printf("修改顶点的值，请输入原值 新值: \n");
    scanf("%s%s", v1, v2);
    PutVex(g, v1, v2);
    printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：\n");
    scanf("%s%s", v1, v2);
    DeleteArc(g, v1, v2);
    Display(g);
    printf("插入新顶点，请输入顶点的值: ");
    scanf("%s", v1);
    InsertVex(g, v1);
    printf("\n插入与新顶点有关的边，请输入边数: ");
    scanf("%d", &n);
    for (k = 0; k < n; k++)
    {
        printf("\n请输入另一顶点的值: ");
        scanf("%s", v2);
        InsertArc(g, v1, v2);
    }
    printf("\n");
    Display(g);
    printf("删除顶点及相关边，请输入顶点的值: ");
    scanf("%s", v1);
    printf("\n");
    DeleteVex(g, v1);
    Display(g);
    DestroyGraph(g);
    return 0;
}