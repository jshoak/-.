#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int ap(int* p1, double* p2)//重置入队概率
{
    int m = 0;
    for (int i = 0; i < 3; i++)
        m += p1[i];
    if (m == 0)
    {
        for (int i = 0; i < 3; i++)
            p2[i] = 1.0 / 3.0;
        return 0;
    }
    for (int i = 0; i < 3; i++)
        p2[i] = (1 - (double)p1[i] / m) / 2;
}

void queue(double oup, int k)
{
    int q[3] = { 10,13,16 };//队列人数
    double inp[3] = { 0 };//入队概率
    double a = 0;
    ap(q, inp);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < k; i++)
    {
        if (i % 5 == 0)//有人到达
        {
            a = rand() / (double)RAND_MAX;//范围0 - 1
            if (a <= inp[0])
                q[0]++;
            else
            {
                if (a <= inp[0] + inp[1])
                    q[1]++;
                else
                    q[2]++;
            }
            ap(q, inp);
        }
        if (i % 6 == 0)//有人离开
        {
            for (int j = 0; j < 3; j++)
            {
                if (q[j] == 0)continue;
                if (rand() / (double)RAND_MAX <= oup)
                    q[j]--;
            }
            ap(q, inp);
        }
    }
    printf("A剩余：%d人。入队概率：%f。\t", q[0], inp[0]);
    printf("B剩余：%d人。入队概率：%f。\t", q[1], inp[1]);
    printf("C剩余：%d人。入队概率：%f。\n", q[2], inp[2]);
    printf("---------------------------------------------\n");
}

int main()
{
    double oup[5] = { 0.45,0.2,0.4,0.6,0.8 };
    int k[6] = { 500,900,1500,1200,1900,2500 };
    for (int i = 0; i < 5; i++)
    {
        printf("离队概率：%f\n", oup[i]);
        for (int j = 0; j < 6; j++)
        {
            printf("%d秒内\n", k[j]);
            queue(oup[i], k[j]);
        }
        printf("********************************************\n");
    }
	return 0;
}