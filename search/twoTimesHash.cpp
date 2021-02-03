#include <stdio.h>
struct Twohash
{
    int key;      //关键字
    int position; //记录最后存放的位置
} Hash[100];

void hash_calculate(int deal_number)
{
    int i, count = 0, j;
    int hk;
    hk = deal_number % 17;
    int temp_hk = hk;
    if (Hash[hk].key == -2)
    {
        Hash[hk].key = deal_number;
        Hash[hk].position = hk;
    }
    else //处理冲突
    {
        count = 0;
        while (1)
        {
            count++;
            for (j = 0; j < 2; j++)
            {
                if (j == 1)
                    hk = temp_hk - (count * count);
                else
                    hk = temp_hk + (count * count);
                if (hk < 0)
                    hk += 180;
                hk = hk % 18;
                if (Hash[hk].key == -2)
                    break;
            }
            if (Hash[hk].key == -2)
            {
                Hash[hk].key = deal_number;
                Hash[hk].position = hk;
                break;
            }
        }
    }
}
int main()
{
    int total_length, i, j, count = 0;
    int deal_number;
    scanf("%d", &total_length);
    for (j = 0; j < 100; j++)
        Hash[j] = {-2, -2};
    for (i = 0; i < total_length; i++)
    {
        scanf("%d", &deal_number);
        hash_calculate(deal_number);
    }
    int search_number, search_number_position;
    scanf("%d", &search_number);
    int del_number1, del_number2;
    scanf("%d%d", &del_number1, &del_number2);
    int insert;
    scanf("%d", &insert);
    //查找
    for (i = 0; i < 18; i++)
    {
        if (Hash[i].key == search_number)
        {
            search_number_position = Hash[i].position;
            break;
        }
        else
            search_number_position = -1;
    }
    //删除
    for (i = 0; i < 18; i++)
    {
        if (Hash[i].key == del_number1 || Hash[i].key == del_number2)
        {
            Hash[i].position = -2;
            Hash[i].key = -2;
        }
    }
    //插入
    hash_calculate(insert);

    //输出
    printf("%d\n", search_number_position);
    for (i = 0; i < 18; i++)
    {
        if (Hash[i].key == -2)
            printf("****");
        else
            printf("%4d", Hash[i].key);
    }
    return 0;
}