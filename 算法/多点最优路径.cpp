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
void push(sp* head, int i)   //��C
{
    sp p;
    p = (sp)calloc(1, sizeof(st));
    p->node = i;
    p->next = *head;
    *head = p;
}
void pop(sp* head)//���C
{
    sp p;
    p = *head;
    *head = (*head)->next;
    free(p);
}
//�㵽������·��
int dijkstra(double(*matrix)[m], int start, int* path, double* expend, int n)//��ѯ��������·��
{
    bool visited[m + 1] = { 0 };//��� 
    int k = start;
    for (int i = 0; i < m + 1; i++)
        expend[i] = infinity;//��ʼ������
    expend[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] != 0 && matrix[j][k] + expend[k] < expend[j] && visited[j] == 0) {//���¾���
                expend[j] = matrix[j][k] + expend[k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (visited[t] == 0 && expend[t] < expend[k])//�ҵ�δ������С�ڵ�
                k = t;
    }
    return 0;
}
//�㵽�㵽������·��
double dijkstra_p(double(*matrix)[m], int start, int middle, int end, int n, int* path)//��ѯ��������·��
{
    bool visited[m + 1] = { 0 };//��� 
    double expend[m + 1] = { 0 };//�����
    int i = 0, j = 0, k = 0, t = 0;
    visited[end] = 1;//����յ�
    double s = 0;
    k = start;
    for (i = 0; i < m + 1; i++)
        expend[i] = infinity;//��ʼ������
    expend[start] = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[j][k] && matrix[j][k] + expend[k] < expend[j] && !visited[j]) {//���¾���
                expend[j] = matrix[j][k] + expend[k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (t = 0; t < n; t++)
            if (visited[t] == 0 && expend[t] < expend[k])//�ҵ�δ������С�ڵ�
                k = t;
        if (k == middle)//�����յ�
        {
            s = expend[middle];
            memset(visited, 0, m + 1);
            for (i = 0; i < m + 1; i++)
                expend[i] = infinity;
            expend[middle] = 0;
            i = 0;
            while (middle != start) {
                middle = path[middle];
                visited[middle] = 1;
                i++;
            }
        }
    }
    return s + expend[end];
}
//��ѯ��ĳ������������ͨ·��
void prim(double(*matrix)[m], int start, int n, char(*point)[30])//��ѯ��ĳ������������ͨ·��
{
    int path[m] = { 0 };
    double dist[m + 1] = { 0 };
    bool visited[m + 1] = { 0 };//���
    int k = start;
    for (int i = 0; i < m + 1; i++)
        dist[i] = infinity;//��ʼ������
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] && !visited[j] && matrix[j][k] < dist[j]) {//���¾���
                dist[j] = matrix[j][k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (!visited[t] && dist[t] < dist[k])//�ҵ�δ������С�ڵ�
                k = t;
    }
    for (int i = 0; i < n; i++)
    {
        i!= start?
            printf("%s(%d) --- > %s(%d)\n\n", point[path[i]], path[i], point[i], i) :0;
    }
}
//��ӡ·����1���룬0���ã�
void print_path(int start, int end, int* path, double expend, char(*point)[30], bool choose)
{
    choose ? printf("���룺%f\n", expend) : printf("���ã�%f\n", expend);
    sp head = NULL;
    int i = end;
    while (path[i] != start) {   //��C
        push(&head, path[i]);
        i = path[i];
    }
    printf("·����%s(%d)", point[start], start);
    while (head != NULL) {   //���C
        printf(" -> %s(%d)", point[head->node], head->node);
        pop(&head);
    }
    printf(" -> %s(%d)\n", point[end], end);
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
    char point[m][30] = { 0 };           //����
    double matrix_distance[m][m] = { 0 };//����
    double matrix_expenses[m][m] = { 0 };//����
    double dist[m + 1] = { 0 };          //�����
    double expe[m + 1] = { 0 };          //���ñ�
    int path_dist[m] = { 0 };            //·�������
    int path_expe[m] = { 0 };            //·�����ñ�
    int pathd[m + 1] = { 0 };             //·��
    int pathe[m + 1] = { 0 };             //·��
    int n = read(point, matrix_distance, matrix_expenses);
    int start = 0, end = 0, middle = 0;
    double s = 0;
    printf("������㣺"); scanf("%d", &start);
    printf("�����յ㣺"); scanf("%d", &end);
    dijkstra(matrix_distance, start, path_dist, dist, n);
    s = dist[end];
    print_path(start, end, path_dist, s, point, 1);
    dijkstra(matrix_expenses, start, path_expe, expe, n);
    s = expe[end];
    print_path(start, end, path_expe, s, point, 0);

    printf("������㣺"); scanf("%d", &start);
    printf("���뾭���㣺"); scanf("%d", &middle);
    printf("�����յ㣺"); scanf("%d", &end);
    s = dijkstra_p(matrix_distance, start, middle, end, n, pathd);
    print_path(start, end, pathd, s, point, 1);
    s = dijkstra_p(matrix_expenses, start, middle, end, n, pathe);
    print_path(start, end, pathe, s, point, 0);

    printf("������㣺"); scanf("%d", &start);
    printf("���룺\n");
    prim(matrix_distance, start, n, point);
    printf("���ã�\n");
    prim(matrix_expenses, start, n, point);
    return 0;
}

