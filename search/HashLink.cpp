#include <stdlib.h>
#include <stdio.h>
struct HashNode
{
    int data;
    struct HashNode *next;
};
typedef HashNode HashList[10];
int main()
{
    int number;
    HashNode *q, *p;
    HashList Hash;
    scanf("%d", &number);
    int i, j, hk, array;
    int del, insert;
    for (j = 0; j < 10; j++)
    {
        Hash[j].data = j;
        Hash[j].next = NULL;
    }
    for (i = 0; i < number; i++)
    {
        scanf("%d", &array);
        hk = array % 10;
        q = (HashNode *)malloc(sizeof(HashNode));
        q->data = array;
        q->next = Hash[hk].next;
        Hash[hk].next = q;
    }

    //删除
    scanf("%d", &del);
    hk = del % 10;
    p = &Hash[hk];
    while (p->next)
    {
        if (p->next->data == del)
        {
            q = p->next;
            p->next = q->next;
            break;
        }
        p = p->next;
    }
    //插入
    scanf("%d", &insert);
    hk = insert % 10;
    q = (HashNode *)malloc(sizeof(HashNode));
    q->data = insert;
    q->next = Hash[hk].next;
    Hash[hk].next = q;

    //输出
    for (i = 0; i < 10; i++)
    {
        q = Hash[i].next;
        printf("%d", Hash[i].data);
        while (q)
        {
            printf("->%d", q->data);
            q = q->next;
        }
        printf("^\n");
    }
    return 0;
}