#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define   m   15
#define   infinity       99999
void aa(double(*matrix_distance)[m], char(*point)[30], int n,int start,int end,int middle);
void bb(double(*matrix_distance)[m], char(*point)[30], int n,int start,int end);
void aa1(double(*matrix_distance)[m], char(*point)[30], int n, int start, int end, int middle);
void bb1(double(*matrix_distance)[m], char(*point)[30], int n, int start, int end);
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
int dijkstra(double(*matrix)[m], int start, int* path, double* dist, int n, bool* visited)//查询两点间最短路径
{
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
    return 0;
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
            printf("%s(%d) --- > %s(%d)\n\n", point[path[i]], path[i], point[i], i) :0;
    }
}
//打印费用路径
void print_pathex(int start, int end, int* path_expe, double* expe, char(*point)[30])
{
    sp head = NULL;
    int i = end;
    while (path_expe[i] != start) {   //入桟
        push(&head, path_expe[i]);
        i = path_expe[i];
    }
    printf("费用：%f\n", expe[end]);
    printf("路径：%s", point[start]);
    while (head != NULL) {   //出桟
        printf(" -> %s", point[head->node]);
        pop(&head);
    }
    printf(" -> %s\n", point[end]);
}
//打印距离路径
void print_pathdi(int start, int end, int* path_dist, double* dist, char(*point)[30])
{
    sp head = NULL;
    int i = end;
    while (path_dist[i] != start) {   //入桟
        push(&head, path_dist[i]);
        i = path_dist[i];
    }
    printf("路径：%s", point[start]);
    while (head != NULL) {   //出桟
        printf(" -> %s", point[head->node]);
        pop(&head);
    }
    printf(" -> %s\n", point[end]);
    printf("距离：%f\n", dist[end]);
}
void print_pathdi1(int start, int end, int* path_dist, double* dist, char(*point)[30], bool* visited)
{
    sp head = NULL;
    int i = end;
    while (path_dist[i] != start) {   //入桟
        push(&head, path_dist[i]);
        i = path_dist[i];
    }
    printf("路径：%s", point[start]);
    visited[start] = 1;
    while (head != NULL) {   //出桟
        printf(" -> %s", point[head->node]);
        visited[head->node] = 1;
        pop(&head);
    }
}
void print_pathdi2(int start, int end, int* path_dist, double* dist, char(*point)[30])
{
    sp head = NULL;
    int i = end;
    while (path_dist[i] != start) {   //入桟
        push(&head, path_dist[i]);
        i = path_dist[i];
    }
    printf(" -> %s", point[start]);
    while (head != NULL) {   //出桟
        printf(" -> %s", point[head->node]);
        pop(&head);
    }
    printf(" -> %s\n", point[end]);
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
    bool visited[m + 1] = { 0 };//标记 
    int n = read(point, matrix_distance, matrix_expenses);
    int start = 0, end = 0, middle = 0;
    printf("输入起点："); scanf("%d", &start);
    printf("输入终点："); scanf("%d", &end);
    bb(matrix_distance, point,n, start, end);
    bb1(matrix_expenses, point, n, start, end);
    printf("输入起点："); scanf("%d", &start);
    prim(matrix_distance, start, n, point);
    prim(matrix_expenses, start, n, point);
    printf("输入起点："); scanf("%d", &start);
    printf("输入经过点："); scanf("%d", &middle);
    printf("输入终点："); scanf("%d", &end);
    aa(matrix_distance, point, n, start, end, middle);
    aa1(matrix_expenses, point, n, start, end, middle);
    return 0;
}
void aa(double(*matrix_distance)[m], char(*point)[30], int n,int start,int end,int middle )
{
    bool visited[m + 1] = { 0 };//标记 
    double expe[m + 1] = { 0 };          //费用表
    int path[m] = { 0 };            //路径费用表
    double t = 0;
    printf("输入起点："); scanf("%d", &start);
    printf("输入经过点："); scanf("%d", &middle);
    printf("输入终点："); scanf("%d", &end);
    visited[end] = 1;
    dijkstra(matrix_distance, start, path, expe, n, visited);
    for (int i = 0; i < m + 1; i++)
        visited[i] = 0;
    t += expe[middle];
    print_pathdi1(start, middle, path, expe, point, visited);
    dijkstra(matrix_distance, middle, path, expe, n, visited);
    t += expe[end];
    print_pathdi2(middle, end, path, expe, point);
    printf("距离：%f\n", t);
}
void bb(double(*matrix_distance)[m], char(*point)[30], int n,int start,int end)
{
    bool visited[m + 1] = { 0 };//标记 
    double expe[m + 1] = { 0 };          //费用表
    int path[m] = { 0 };            //路径费用表
    double t = 0;
    dijkstra(matrix_distance, start, path, expe, n, visited);
    print_pathdi(start, end, path, expe, point);
}
void bb1(double(*matrix_distance)[m], char(*point)[30], int n, int start, int end)
{
    bool visited[m + 1] = { 0 };//标记 
    double expe[m + 1] = { 0 };          //费用表
    int path[m] = { 0 };            //路径费用表
    double t = 0;
    dijkstra(matrix_distance, start, path, expe, n, visited);
    print_pathex(start, end, path, expe, point);
}
void aa(double(*matrix_distance)[m], char(*point)[30], int n, int start, int end, int middle)
{
    bool visited[m + 1] = { 0 };//标记 
    double expe[m + 1] = { 0 };          //费用表
    int path[m] = { 0 };            //路径费用表
    double t = 0;
    printf("输入起点："); scanf("%d", &start);
    printf("输入经过点："); scanf("%d", &middle);
    printf("输入终点："); scanf("%d", &end);
    visited[end] = 1;
    dijkstra(matrix_distance, start, path, expe, n, visited);
    for (int i = 0; i < m + 1; i++)
        visited[i] = 0;
    t += expe[middle];
    print_pathdi1(start, middle, path, expe, point, visited);
    dijkstra(matrix_distance, middle, path, expe, n, visited);
    t += expe[end];
    print_pathdi2(middle, end, path, expe, point);
    printf("费用：%f\n", t);
}

