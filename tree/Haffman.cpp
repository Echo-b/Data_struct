#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef struct
{
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
typedef int Status;
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int i;
    int min = 100, min1 = 100;
    for (i = 1; i <= n; i++) //找第一个小的数
    {
        if (HT[i].parent != 0)
            continue; //跳过已加入的节点
        if (HT[i].weight < min)
        {
            s1 = i;
            min = HT[i].weight;
        }
    }
    for (i = 1; i <= n; i++) //找第二个小的数
    {
        if (HT[i].parent != 0)
            continue; //跳过已加入的节点
        if (HT[i].weight < min1 && i != s1)
        {
            s2 = i;
            min1 = HT[i].weight;
        }
    }
    if (s1 > s2)
    {
        s1 = temp;
        s1 = s2;
        s2 = temp;
    }
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n, char *s)
{
    if (n <= 1)
        return;
    int m = 2 * n - 1;
    HuffmanTree p;
    int i, j;
    int s1, s2;
    int f, c, start; //编码变量
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    HT[0].weight = n;
    for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w) //初始化表的前几列，相当于建立的一个索引，每一个p对应着它的权值，父母，左孩子，右孩子
        *p = {*w, 0, 0, 0};
    for (; i <= m; ++i, ++p) //初始化除原有点之外的表，具体同上
        *p = {0, 0, 0, 0};
    for (i = n + 1; i <= m; ++i) //建立表格
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    //逐个字符求哈夫曼编码
    for (i = 1; i <= n; ++i)
    {
        start = n - 1; //编码结束的位置

        //从叶子到根逆向求编码
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char *)malloc((n - start) * sizeof(char)); //为每个哈夫曼编码结果分配存储空间
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
    //输出编码结果
    for (i = 1; i <= strlen(s); i++)
    {
        printf("%c:%s\n", s[i - 1], HC[i]);
    }
}

int main()
{
    int number, i;
    scanf("%d", &number);
    int w[100];
    char str[100];
    HuffmanCode HC;
    HuffmanTree HT;
    for (i = 0; i <= number; i++)
        scanf("%d", &w[i]);
    scanf("%s", str);
    HuffmanCoding(HT, HC, w, number, str);
    return 0;
}