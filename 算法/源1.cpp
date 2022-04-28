#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define   m   15
#define   infinity       99999
typedef struct stack
{
    int node;
    struct stack* next;
}st, * sp;
void push(sp* head, int i)   //入桟
{
    sp p;
    p = (sp)calloc(1, sizeof(st));
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
//最忧路径
void dijkstra(double(*matrix)[m], int start, int* path, double* dist, int n)//查询两点间最短路径
{
    bool visited[m + 1] = { 0 };//标记
    int k = start;
    for (int i = 0; i < m + 1; i++)
        dist[i] = infinity;//初始化距离
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] != 0 && matrix[j][k] + dist[k] < dist[j] && visited[j] == 0) {//更新距离
                dist[j] = matrix[j][k] + dist[k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (visited[t] == 0 && dist[t] < dist[k])//找到未访问最小节点
                k = t;
    }
}
//查询从某点出发的最短连通路径
void prim(double(*matrix)[m], int start, int n, char(*point)[30])//查询从某点出发的最短连通路径
{
    int path[m] = { 0 };
    double dist[m + 1] = { 0 };
    bool visited[m + 1] = { 0 };//标记
    int k = start;
    for (int i = 0; i < m + 1; i++)
        dist[i] = infinity;//初始化距离
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] && !visited[j] && matrix[j][k] < dist[j]) {//更新距离
                dist[j] = matrix[j][k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (!visited[t] && dist[t] < dist[k])//找到未访问最小节点
                k = t;
    }
    for (int i = 0; i < n; i++)
    {
        i!= start?
            printf("%s(%d) --- > %+20s(%d)\n\n", point[path[i]], path[i], point[i], i) :0;
    }
}
//打印费用路径
int print_pathex(int end, int start, int j, int* path_expe, double* expe, char(*point)[30])
{
    sp head = NULL;
    bool k = 0;
    int i = j;
    if (i == end)k = 1;
    while (path_expe[i] != start) {   //入桟
        if (i == end)k = 1;
        push(&head, path_expe[i]);
        i = path_expe[i];
    }
    if (!k)return 0;
    printf("费用：%f\n", expe[j]);
    printf("路径：%s(%d)", point[start], start);
    while (head != NULL) {   //出桟
        printf(" -> %s(%d)", point[head->node], head->node);
        pop(&head);
    }
    printf(" -> %s(%d)\n", point[j], j);
    printf("===============================================\n");
    return 1;
}
//打印距离路径
int print_pathdi(int end, int start, int j, int* path_dist, double* dist, char(*point)[30])
{
    sp head = NULL;
    bool k = 0;
    int i = j;
    if (i == end)k = 1;
    while (path_dist[i] != start) {   //入桟
        if (i == end)k = 1;
        push(&head, path_dist[i]);
        i = path_dist[i];
    }
    if(!k)return 0;
    printf("距离：%f\n", dist[j]);
    printf("路径：%s(%d)", point[start], start);
    while (head != NULL) {   //出桟
        printf(" -> %s(%d)", point[head->node], head->node);
        pop(&head);
    }
    printf(" -> %s(%d)\n", point[j], j);
    printf("-----------------------------------------------\n");
    return 1;
}
int read(char(*point)[30], double(*matrix_distance)[m], double(*matrix_expenses)[m])
{
    double dist, expe;
    int n, k;
    FILE* fp;
    fp = fopen("b.txt", "rt");
    fscanf(fp, "%d\n", &k); printf("%d\n", k);
    for (int i = 0; i < k; i++)
    {
        fscanf(fp, "%s\n", point[i]); printf("%s\n", point[i]);
        while (fscanf(fp, "%d %lf %lf\n", &n, &dist, &expe) > 0)
        {
            matrix_distance[n][i] = dist;
            matrix_expenses[n][i] = expe;
            printf("%d %lf %lf\n", n, matrix_distance[n][i], matrix_expenses[n][i]);
        }
    }
    fclose(fp);
    return k;
}
int main(int argc, char const* argv[])
{

    char point[m][30] = { 0 };           //名称
    double matrix_distance[m][m] = { 0 };//距离
    double matrix_expenses[m][m] = { 0 };//费用
    double dist[m + 1] = { 0 };          //距离表
    double expe[m + 1] = { 0 };          //费用表
    int path_dist[m] = { 0 };            //路径距离表
    int path_expe[m] = { 0 };            //路径费用表
    int n = read(point, matrix_distance, matrix_expenses);
    printf("***********************************\n");
    int start = 0, end = 0;
    printf("输入起点："); scanf("%d", &start);
    prim(matrix_distance, start, n, point);
    printf("***********************************\n");
    printf("输入经过点："); scanf("%d", &end);
    dijkstra(matrix_distance, start, path_dist, dist, n);
    dijkstra(matrix_expenses, start, path_expe, expe, n);
    for (int i = 0; i < n; i++)
    {
        print_pathdi(end, start, i, path_dist, dist, point);
        print_pathex(end, start, i, path_expe, expe, point);
    }
    return 0;
}
