#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
void CreatBiTree(BiTree &T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == '*' || ch == 0)
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
}
void Visit(BiTree p)
{
    printf("%c", p->data);
}
void PostTraverse(BiTree T)
{
    if (T)
    {
        PostTraverse(T->lchild);
        PostTraverse(T->rchild);
        Visit(T);
    }
}
int LeafNode(BiTree T)
{
    int lnum = 0, rnum = 0;
    if (!T)
        return 0;
    else if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    else
    {
        lnum = LeafNode(T->lchild);
        rnum = LeafNode(T->rchild);
        return lnum + rnum;
    }
}
int DepthTree(BiTree T)
{
    int llength, rlength;
    if (!T)
        return 0;
    else
    {
        llength = DepthTree(T->lchild);
        rlength = DepthTree(T->rchild);
        return llength > rlength ? llength + 1 : rlength + 1;
    }
}
int main()
{
    BiTree T;
    CreatBiTree(T);
    PostTraverse(T);
    int length;
    length = DepthTree(T);
    int num;
    num = LeafNode(T);
    printf("\n");
    printf("%d%d", length, num);
    return 0;
}