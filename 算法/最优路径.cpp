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
//����·��
void dijkstra(double(*matrix)[m], int start,int *path, double *dist, int n)//��ѯ��������·��
{
    bool visited[m + 1] = { 0 };//���
    int k = start;
    for (int i = 0; i < m + 1; i++)
        dist[i] = infinity;//��ʼ������
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[j][k] != 0 && matrix[j][k] + dist[k] < dist[j] && visited[j] == 0) {//���¾���
                dist[j] = matrix[j][k] + dist[k];
                path[j] = k;
            }
        }
        visited[k] = 1;
        k = m;
        for (int t = 0; t < n; t++)
            if (visited[t] == 0 && dist[t] < dist[k])//�ҵ�δ������С�ڵ�
                k = t;
    }
}
//��ӡ����·��
void print_pathex(int start, int end, int* path_expe, double* expe, char(*point)[30])
{
    sp head = NULL;
    int i = end;
    while (path_expe[i] != start) {   //��C
        push(&head, path_expe[i]);
        i = path_expe[i];
    }
    printf("���ã�%f\n", expe[end]);
    printf("·����%s", point[start]);
    while (head != NULL) {   //���C
        printf(" -> %s", point[head->node]);
        pop(&head);
    }
    printf(" -> %s\n", point[end]);
}
//��ӡ����·��
void print_pathdi(int start, int end, int* path_dist, double* dist, char(*point)[30])
{
    sp head = NULL;
    int i = end;
    while ( path_dist[i] != start) {   //��C
        push(&head, path_dist[i]);
        i = path_dist[i];
    }
    printf("���룺%f\n", dist[end]);
    printf("·����%s", point[start]);
    while (head != NULL) {   //���C
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
    fscanf(fp, "%d\n", &k); printf("%d\n",k);
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
    int n = read(point, matrix_distance, matrix_expenses);
    printf("***********************************\n");
    int start = 0, end = 0;
    printf("������㣺"); scanf("%d", &start);
    dijkstra(matrix_distance, start, path_dist, dist, n);
    dijkstra(matrix_expenses, start, path_expe, expe, n);
    int i;
    for (i = 0; i < n; i++)
    {
        print_pathdi(start, i, path_dist, dist, point);
        printf("-----------------------------------\n");
        print_pathex(start, i, path_expe, expe, point);
        printf("===================================\n");
    }
    printf("***********************************\n");
    printf("�����յ㣺"); scanf("%d", &end);
    print_pathdi(start, end, path_dist, dist, point);
    printf("-----------------------------------\n");
    print_pathex(start, end, path_expe, expe, point);
    printf("===================================\n");
	return 0;
}
