#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define   m   22
#define   infinity       99999
//�㵽������·��
int dijkstra_max(double(*matrix)[m], int start, int(*path)[m+1], double(*expend)[m + 1], int n)//��ѯ��������·��
{
    bool visited[m + 1] = { 0 };//��� 
    int k = start;
    for (int i = 0; i < m + 1; i++)
        expend[start][i] = infinity;//��ʼ������
    expend[start][start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] != 0 && matrix[j][k] + expend[start][k] < expend[start][j] && visited[j] == 0) {//���¾���
                expend[start][j] = matrix[j][k] + expend[start][k];
                path[start][j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (visited[t] == 0 && expend[start][t] < expend[start][k])//�ҵ�δ������С�ڵ�
                k = t;
    }
    return 0;
}
int r = 0;
int print_max(int start, int end, int(*path)[m + 1], double(*expend)[m + 1], int k)
{
    int i = end, j = 0;
    if (start != end && expend[start][end] != infinity)
    {
        if (start == k || end == k)j++;
        while (path[start][i] != start) {
            if (path[start][i] == k)j++;
            i = path[start][i];
        }
        r++;
    }
    return j;
}
int read(char(*point)[30], double(*matrix)[m])
{
    double dist;
    int n, k;
    FILE* fp;
    fp = fopen("b.txt", "rt");
    fscanf(fp, "%d\n", &k);
    for (int i = 0; i < k; i++)
    {
        fscanf(fp, "%s\n", point[i]);
        while (fscanf(fp, "%d %lf\n", &n, &dist) > 0)
            matrix[n][i] = dist;
    }
    fclose(fp);
    return k;
}
int main(int argc, char const* argv[])
{
    char point[m][30] = { 0 };           //����
    double matrix[m][m] = { 0 };         //����
    int n = read(point, matrix);
    int path_max[m][m + 1] = { 0 };            //·��
    double dist_max[m][m + 1] = { 0 };          //�����
    int s = 0;
    for (int i = 0; i < m; i++)
        dijkstra_max(matrix, i, path_max, dist_max, n);
    printf("�ڵ�   �ڵ����\n");
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s += print_max(i, j, path_max, dist_max, k);
            }
        }
        printf(" %-5d %d\n", k, s);
        s = 0;
    }
    printf("·������%d\n",r/m);
    return 0;
}