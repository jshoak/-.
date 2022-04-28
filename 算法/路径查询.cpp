#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define   m   30
#define   infinity       99999
typedef struct stack
{
    int node;
    struct stack* next;
}st, * sp;
int push(sp* head, int i)   //入桟
{
    sp p = NULL;
    p = (sp)calloc(1, sizeof(st));
    if (p == NULL)
    {
        printf("内存分配失败\n");
        return 0;
    }
    p->node = i;
    p->next = *head;
    *head = p;
}
void pop(sp* head)//出桟
{
    sp p;
    p = *head;
    *head = (*head)->next;
    free(p);
}
//点到点最忧路径
int dijkstra(double(*matrix)[m], int start, int* path, double* expend, int n)//查询两点间最短路径
{
    bool visited[m + 1] = { 0 };//标记 
    int k = start;
    for (int i = 0; i < m + 1; i++)
        expend[i] = infinity;//初始化距离
    expend[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] != 0 && matrix[j][k] + expend[k] < expend[j] && visited[j] == 0) {//更新距离
                expend[j] = matrix[j][k] + expend[k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (visited[t] == 0 && expend[t] < expend[k])//找到未访问最小节点
                k = t;
    }
    return 0;
}
//打印路径
int print_path(int start, int end, int* path, double expend, char(*point)[30])
{
    printf("距离：%f\n", expend);
    sp head = NULL;
    int i = end;
    while (path[i] != start) {   //入桟
        if (push(&head, path[i]) == 0)return 0;
        i = path[i];
    }
    printf("路径：%s(%d)", point[start], start);
    while (head != NULL) {   //出桟
        printf(" -> %s(%d)", point[head->node], head->node);
        pop(&head);
    }
    printf(" -> %s(%d)\n", point[end], end);
    return 1;
}
//读取文件
int read(char(*point)[30], double(*matrix_distance)[m])
{
    double dist;
    int n, k, j = 0;
    FILE* fp;
    fp = fopen("b.txt", "rt");
    fscanf_s(fp, "%d\n", &k); printf("%d\n", k);
    for (int i = 0; i < k; i++)
    {
        fscanf_s(fp, "%s\n", point[i],30); printf("%s\n", point[i]);
        while (fscanf_s(fp, "%d %lf\n", &n, &dist) > 0)
        {
            matrix_distance[n][i] = dist;
            printf("%d %lf\n", n, matrix_distance[n][i]);
        }
    }
    fclose(fp);
    return k;
}
int main(int argc, char const* argv[])
{
    char point[m][30] = { 0 };           //名称
    double matrix_distance[m][m] = { 0 };//距离
    double dist[m + 1] = { 0 };          //距离表
    int path_dist[m] = { 0 };            //路径距离表
    int n = read(point, matrix_distance);
    int start = 0, end = 0, middle = 0;
    double s = 0;
    char c;
    printf("输入起点："); scanf_s("%d", &start); c = getchar();
    printf("输入终点："); scanf_s("%d", &end); c = getchar();
    dijkstra(matrix_distance, start, path_dist, dist, n);
    s = dist[end];
    print_path(start, end, path_dist, s, point);
    printf("按任意键关闭此窗口");
    c = getchar();
    return 0;
}

