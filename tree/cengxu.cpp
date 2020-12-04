#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXQSIZE 100 //最大队列长度
typedef char TElemType;
typedef int Status;
typedef struct BiTNode
{ //树的节点
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct
{
    BiTree *base; //初始化的动态分配存储空间
    int front;    //头指针,若队列不空,指向队列头元
    int rear;     //尾指针,若队列不空,指向队列尾元素的下一个位置
} SqQueue;
Status InitQueue(SqQueue &Q)
{ //  构造一个空队列Q
    Q.base = (BiTree *)malloc(sizeof(BiTree) * MAXQSIZE);
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
Status EnQueue(SqQueue &Q, BiTree e)
{                                           // 插入元素e为Q的新的队尾元素
    if ((Q.rear + 1) % MAXQSIZE == Q.front) //队列满
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}
Status DeQueue(SqQueue &Q, BiTree &e)
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

void CreatBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '*' || ch == 0)
        T = NULL;
    else
    {
        if (!(T = (BiTree)malloc(sizeof(BiTree))))
            exit(OVERFLOW);
        else
        {
            T->data = ch;
            CreatBiTree(T->lchild);
            CreatBiTree(T->rchild);
        }
    }
}
void cengxuTraverse(BiTree T)
{
    SqQueue p;
    InitQueue(p);
    if (T == NULL)
        return;
    EnQueue(p, T);
    while (!QueueEmpty(p))
    {
        T = p.base[p.front];
        DeQueue(p, T);
        if (T->lchild)
            EnQueue(p, T->lchild);
        if (T->rchild)
            EnQueue(p, T->rchild);
        printf("%c", T->data);
    }
}
int main()
{
    BiTree T;
    CreatBiTree(T);
    cengxuTraverse(T);
    return 0;
}