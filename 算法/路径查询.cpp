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
int push(sp* head, int i)   //��C
{
    sp p = NULL;
    p = (sp)calloc(1, sizeof(st));
    if (p == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return 0;
    }
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
//��ӡ·��
int print_path(int start, int end, int* path, double expend, char(*point)[30])
{
    printf("���룺%f\n", expend);
    sp head = NULL;
    int i = end;
    while (path[i] != start) {   //��C
        if (push(&head, path[i]) == 0)return 0;
        i = path[i];
    }
    printf("·����%s(%d)", point[start], start);
    while (head != NULL) {   //���C
        printf(" -> %s(%d)", point[head->node], head->node);
        pop(&head);
    }
    printf(" -> %s(%d)\n", point[end], end);
    return 1;
}
//��ȡ�ļ�
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
    char point[m][30] = { 0 };           //����
    double matrix_distance[m][m] = { 0 };//����
    double dist[m + 1] = { 0 };          //�����
    int path_dist[m] = { 0 };            //·�������
    int n = read(point, matrix_distance);
    int start = 0, end = 0, middle = 0;
    double s = 0;
    char c;
    printf("������㣺"); scanf_s("%d", &start); c = getchar();
    printf("�����յ㣺"); scanf_s("%d", &end); c = getchar();
    dijkstra(matrix_distance, start, path_dist, dist, n);
    s = dist[end];
    print_path(start, end, path_dist, s, point);
    printf("��������رմ˴���");
    c = getchar();
    return 0;
}

