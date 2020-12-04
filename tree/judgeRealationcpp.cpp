#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef char TElemType;
typedef int Status;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
int pathlen = 0; //用于储存两节点间的路径长度
Status CreatBiTree(BiTree &T)
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
            CreatBiTree(T->lchild);
            CreatBiTree(T->rchild);
        }
    }
    return OK;
}
BiTree Judge(BiTree T, char target, int depth)
{
    BiTree p;
    if (T) //树不空
    {
        if (T->data == target) //找到目标，调用结束返回相应节点
        {
            pathlen = depth;
            return T;
        }
        if (p = Judge(T->lchild, target, depth + 1)) //检查左节点
            return p;
        if (p = Judge(T->rchild, target, depth + 1)) //检查右节点
            return p;
    }
    return NULL;
}

int main()
{
    BiTree T, p;
    char ans, son;
    CreatBiTree(T);
    scanf(" %c%c", &ans, &son); //加一个空格防止输入字符被吞
    p = Judge(T, ans, 0);       //找到祖先
    if (Judge(p, son, 0))       //从祖先出发找孩子
        printf("%d", pathlen);
    else
        printf("NO");
    return 0;
}