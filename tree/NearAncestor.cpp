#include <stdio.h>

int main()
{
    int Nodesum;
    int i, j, k;
    scanf(" %d", &Nodesum);
    int node[Nodesum + 1];
    for (k = 1; k <= Nodesum; k++)
        scanf(" %d", &node[k]);
    scanf(" %d %d", &i, &j);
    while (i > 0 && j > 0)
    {
        if (node[i] == 0)
        {
            printf("ERROR: T[%d] is NULL", i);
            return 0;
        }
        if (node[j] == 0)
        {
            printf("ERROR: T[%d] is NULL", j);
            return 0;
        }

        if (i == j)
        { /*至少有根结点为其共同祖先*/
            printf("%d %d", i, node[i]);
            break;
        }
        else if (i > j)
        {
            i /= 2;
        }
        else
        {
            j /= 2;
        }
    }
    return 0;
}