#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int left;
    int right;
} Tree[20];

int main()
{
    int i, j = 1;
    int Nodesum;
    int root;
    scanf("%d", &Nodesum);
    int flag[20] = {0};  //用于寻找树根
    int serch[20] = {0}; //用于存储遍历结果
    char Tl, Tr;
    //标记
    for (i = 0; i < Nodesum; i++)
    {
        scanf(" %c %c", &Tl, &Tr);
        if (Tl != '-')
            flag[Tl - '0'] = 1;
        if (Tr != '-')
            flag[Tr - '0'] = 1;
        Tree[i].left = Tl - '0';
        Tree[i].right = Tr - '0';
    }
    //找出树根
    for (i = 0; i < Nodesum; i++)
    {
        if (flag[i] == 0)
        {
            root = i;
            break;
        }
    }

    //广度遍历树
    int count = 0;
    serch[0] = root;
    while (count < Nodesum)
    {
        if (Tree[serch[count]].left != -3)
        {
            serch[j] = Tree[serch[count]].left;
            j++;
        }
        if (Tree[serch[count]].right != -3)
        {
            serch[j] = Tree[serch[count]].right;
            j++;
        }
        count++;
    }
    j = 0;
    for (i = 0; i < Nodesum; i++)
    {
        if (Tree[serch[i]].left == -3 && Tree[serch[i]].right == -3)
        {
            flag[j] = serch[i];
            j++;
        }
    }
    //格式控制
    for (i = 0; i < j - 1; i++)
        printf("%d ", flag[i]);
    printf("%d", flag[j - 1]);
    return 0;
}
