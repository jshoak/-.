#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct information
{
    char name[16];//����11
    double grades;//�ɼ�8
    struct information* next;//4
}stuin, * pstuin;
//�ͷ��ڴ�
void free_(pstuin head)
{
    pstuin middle = head, p;
    while (middle != NULL)
    {
        p = middle->next;
        free(middle);
        middle = p;
    }
}
//�����Ϣ
void addr_(pstuin* head)
{
    pstuin middle;
    middle = (pstuin)malloc(sizeof(stuin));
    middle->next = NULL;
    printf("����������"); scanf("%s", middle->name); getchar();
    printf("����ɼ���"); scanf("%lf", &middle->grades); getchar();
    middle->next = (*head);//ָ��ͷָ��
    *head = middle;
}
//ɾ����Ϣ
int delete_(pstuin* head)
{
    pstuin middle;
    char nu[11] = { 0 };
    printf("������Ҫɾ��������");
    scanf("%s", nu); getchar();
    while ((*head) != NULL)
    {
        if (strcmp((*head)->name, nu) == 0)//�����Ա�
        {
            middle = *head;
            *head = (*head)->next;//�����ڵ�
            free(middle);
            printf("ɾ���ɹ�\n");
            return 1;
        }
        head = &(*head)->next;
    }
    printf("ɾ��ʧ��\n");
    return 0;
}
//��ѯ��Ϣ
int enquiry_n(pstuin head)
{
    char nu[11] = { 0 };
    printf("������Ҫ��ѯ������");
    scanf("%s", nu); getchar();
    while (head != NULL)
    {
        if (strcmp(head->name, nu) == 0)
        {
            printf("������%-10s�ɼ���%lf\n", head->name, head->grades);
            return 1;
        }
        head = head->next;
    }
    printf("û�и�ѧ��");
    return 0;
}
int enquiry_g(pstuin head)
{
    double nu = 0;
    printf("������Ҫ��ѯ������");
    scanf("%lf", &nu); getchar();
    while (head != NULL)
    {
        if (head->grades == nu)
        {
            printf("������%-10s�ɼ���%lf\n", head->name, head->grades);
            return 1;
        }
        head = head->next;
    }
    printf("û�и�ѧ��");
    return 0;
}
//��ӡ��Ϣ
void print_(pstuin head)
{
    while (head != NULL)
    {
        printf("������%-10s�ɼ���%lf\n", head->name, head->grades);
        head = head->next;					//ָ����һ��
    }
}
void print_m(pstuin head, double g)
{
    while (head != NULL)
    {
        if (head->grades >= g)
        printf("������%-10s�ɼ���%lf\n", head->name, head->grades);
        head = head->next;					//ָ����һ��
    }
}
void print_n(pstuin head, double g)
{
    while (head != NULL)
    {
        if (head->grades <= g)
            printf("������%-10s�ɼ���%lf\n", head->name, head->grades);
        head = head->next;					//ָ����һ��
    }
}
//����
void sort_max(pstuin head)
{
    pstuin middle;
    stuin a;
    while (head != NULL)
    {
        middle = head->next;
        while (middle != NULL)
        {
            if (middle->grades > head->grades)
            {
                memcpy(&a, middle, 24);//�ڴ����
                memcpy(middle, head, 24);
                memcpy(head, &a, 24);
            }
            middle = middle->next;
        }
        head = head->next;
    }
}
void sort_min(pstuin head)
{
    pstuin middle;
    stuin a;
    while (head != NULL)
    {
        middle = head->next;
        while (middle != NULL)
        {
            if (middle->grades < head->grades)
            {
                memcpy(&a, middle, 24);//�ڴ����
                memcpy(middle, head, 24);
                memcpy(head, &a, 24);
            }
            middle = middle->next;
        }
        head = head->next;
    }
}
void print()
{
    printf("******ѧ����Ϣ����ϵͳ******\n");
    printf("     0.��ӡ����\n");
    printf("     1.���ѧ��\n");
    printf("     2.ɾ��ѧ��\n");
    printf("     3.��������ѯ\n");
    printf("     4.��������ѯ\n");
    printf("     5.������߷�\n");
    printf("     6.������ͷ�\n");
    printf("     7.���ĳ����������ѧ��\n");
    printf("     8.���ĳ����������ѧ��\n");
    printf("     9.�������Ӹߵ������ѧ��\n");
    printf("     10.�˳�ϵͳ\n");
    printf("****************************\n");
}
int main(int argc, char const* argv[])
{
    pstuin head = NULL;
    int choose = 0, i = 0;
    double g = 0;
    while (choose!=10)
    {
        print();
        printf("����ѡ�");
        scanf("%d", &choose); getchar();
        system("cls");
        switch (choose)
        {
        case 0:
        {
            print_(head);
            break;
        }
        case 1:
        {
            printf("��Ҫ��Ӽ����ˣ�");
            scanf("%d", &i); getchar();
            while (i--)
            {
                addr_(&head);
                printf("---------------------------\n");
            }
            break;
        }
        case 2:
        {
            delete_(&head);
            printf("---------------------------\n");
            break;
        }
        case 3:
        {
            enquiry_n(head);
            printf("---------------------------\n");
            break;
        }
        case 4:
        {
            enquiry_g(head);
            printf("---------------------------\n");
            break;
        }
        case 5:
        {
            sort_max(head);
            print_m(head, head->grades);
            printf("---------------------------\n");
            break;
        }
        case 6:
        {
            sort_min(head);
            print_n(head, head->grades);
            printf("---------------------------\n");
            break;
        }
        case 7:
        {
            printf("�������");
            scanf("%lf", &g); getchar();
            sort_max(head);
            print_m(head, g);
            printf("---------------------------\n");
            break;
        }
        case 8:
        {
            printf("�������");
            scanf("%lf", &g); getchar();
            sort_min(head);
            print_n(head, g);
            printf("---------------------------\n");
            break;
        }
        case 9:
        {
            sort_max(head);
            print_(head);
            printf("---------------------------\n");
            break;
        }
        default:
            break;
        }
    }
    free_(head);//*/
    return 0;
}