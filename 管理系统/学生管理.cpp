#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct information
{
    char name[16];//姓名11
    double grades;//成绩8
    struct information* next;//4
}stuin, * pstuin;
//释放内存
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
//添加信息
void addr_(pstuin* head)
{
    pstuin middle;
    middle = (pstuin)malloc(sizeof(stuin));
    middle->next = NULL;
    printf("输入姓名："); scanf("%s", middle->name); getchar();
    printf("输入成绩："); scanf("%lf", &middle->grades); getchar();
    middle->next = (*head);//指向头指针
    *head = middle;
}
//删除信息
int delete_(pstuin* head)
{
    pstuin middle;
    char nu[11] = { 0 };
    printf("输入需要删除姓名：");
    scanf("%s", nu); getchar();
    while ((*head) != NULL)
    {
        if (strcmp((*head)->name, nu) == 0)//遍历对比
        {
            middle = *head;
            *head = (*head)->next;//跳过节点
            free(middle);
            printf("删除成功\n");
            return 1;
        }
        head = &(*head)->next;
    }
    printf("删除失败\n");
    return 0;
}
//查询信息
int enquiry_n(pstuin head)
{
    char nu[11] = { 0 };
    printf("输入需要查询姓名：");
    scanf("%s", nu); getchar();
    while (head != NULL)
    {
        if (strcmp(head->name, nu) == 0)
        {
            printf("姓名：%-10s成绩：%lf\n", head->name, head->grades);
            return 1;
        }
        head = head->next;
    }
    printf("没有该学生");
    return 0;
}
int enquiry_g(pstuin head)
{
    double nu = 0;
    printf("输入需要查询分数：");
    scanf("%lf", &nu); getchar();
    while (head != NULL)
    {
        if (head->grades == nu)
        {
            printf("姓名：%-10s成绩：%lf\n", head->name, head->grades);
            return 1;
        }
        head = head->next;
    }
    printf("没有该学生");
    return 0;
}
//打印信息
void print_(pstuin head)
{
    while (head != NULL)
    {
        printf("姓名：%-10s成绩：%lf\n", head->name, head->grades);
        head = head->next;					//指向下一个
    }
}
void print_m(pstuin head, double g)
{
    while (head != NULL)
    {
        if (head->grades >= g)
        printf("姓名：%-10s成绩：%lf\n", head->name, head->grades);
        head = head->next;					//指向下一个
    }
}
void print_n(pstuin head, double g)
{
    while (head != NULL)
    {
        if (head->grades <= g)
            printf("姓名：%-10s成绩：%lf\n", head->name, head->grades);
        head = head->next;					//指向下一个
    }
}
//排序
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
                memcpy(&a, middle, 24);//内存对齐
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
                memcpy(&a, middle, 24);//内存对齐
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
    printf("******学生信息管理系统******\n");
    printf("     0.打印名单\n");
    printf("     1.添加学生\n");
    printf("     2.删除学生\n");
    printf("     3.按姓名查询\n");
    printf("     4.按分数查询\n");
    printf("     5.查找最高分\n");
    printf("     6.查找最低分\n");
    printf("     7.输出某个分数以上学生\n");
    printf("     8.输出某个分数以下学生\n");
    printf("     9.按分数从高到低输出学生\n");
    printf("     10.退出系统\n");
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
        printf("输入选项：");
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
            printf("需要添加几个人：");
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
            printf("输入分数");
            scanf("%lf", &g); getchar();
            sort_max(head);
            print_m(head, g);
            printf("---------------------------\n");
            break;
        }
        case 8:
        {
            printf("输入分数");
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