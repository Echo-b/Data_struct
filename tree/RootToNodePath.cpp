#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef char TElemType;
typedef int Status;
#define STACK_INIT_SIZE 100 //存储空间初始分配
#define STACKINCREMENT 10   //存储空间分配增量
typedef char SElemType;
typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status InitStack(SqStack &s)
{
    s.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s.base)
        exit(OVERFLOW); //存储分配失败
    s.top = s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack s, SElemType &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *(s.top - 1);
    return OK;
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
void CreatBinTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '*')
        T = NULL;
    else
    {
        if (!(T = (BiTree)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        else
        {
            T->data = ch;
            CreatBinTree(T->lchild);
            CreatBinTree(T->rchild);
        }
    }
}

Status Search(BiTree T, char ch, SqStack &s)
{
    SElemType e;
    int flag;
    if (!T)
        return ERROR;
    Push(s, T->data); //碰到节点则入栈（一直往左或往右）
    if (T->data == ch)
        return OK;
    flag = 0;
    if (T->lchild)
        flag = Search(T->lchild, ch, s); //判断左孩子是否等于所给节点
    if (!flag && T->rchild)
        flag = Search(T->rchild, ch, s); //左孩子不等判断右孩子是否相等
    if (!flag)                           //左右都不等，出栈根节点
        Pop(s, ch);
    return flag;
}
int main()
{
    char ch;
    SElemType e;
    SqStack s;
    InitStack(s);
    BiTree T;
    CreatBinTree(T);
    scanf(" %c", &ch);
    Search(T, ch, s);
    printf("the path is:");
    if (!StackEmpty(s)) //输出首节点
    {
        Pop(s, e);
        printf("%c", e);
    }
    while (!StackEmpty(s))
    {
        Pop(s, e);
        printf("<-%c", e);
    }
    return 0;
}