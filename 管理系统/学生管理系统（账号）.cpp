#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define m 5     //账号数量
struct
{
    char accnum[10];	//账号
    char code[7];	    //密码
    int access;		    //权限
}account[m] = {
    {"root","000000",0},
    {"teacher","000000",1},
    {"student","000000",2},
};
typedef struct information
{
    char student_number[11];	//学号
    char name[11];				//姓名
    char professional[11];		//专业
    double gra_c;               //c语言
    double gra_puter;           //计算机物理
    double gra_physics;         //大学物理
    double gra_atom;            //原子物理
    double gra_optics;          //光学
    struct information* next;
}stuin, * pstuin;
struct grades
{
    double average;             //平均分
    int pass;                   //及格
    int excellent;              //优秀
};
struct 
{
    struct grades gra_c;               //c语言
    struct grades gra_puter;           //计算机物理
    struct grades gra_physics;         //大学物理
    struct grades gra_atom;            //原子物理
    struct grades gra_optics;          //光学
}statistics;
//打印信息
void print_(pstuin head)
{
    printf("学号        姓名        专业        c语言       计算机物理  大学物理    原子物理    光学\n");
    pstuin middle = head;
    while (middle != NULL)
    {
        printf("%-12s%-12s%-12s%-12lf%-12lf%-12lf%-12lf%-12lf\n", middle->student_number, middle->name, middle->professional, 
            middle->gra_c, middle->gra_puter, middle->gra_physics, middle->gra_atom, middle->gra_optics);
        printf("--------------------------------------------------------------------------------------------------------\n");
        middle = middle->next;					//指向下一个
    }
}
//统计
void statistics_(pstuin middle)
{
    statistics.gra_c.average += middle->gra_c;
    if (middle->gra_c >= 60)statistics.gra_c.pass++;
    if (middle->gra_c >= 80)statistics.gra_c.excellent++;

    statistics.gra_puter.average += middle->gra_puter;
    if (middle->gra_puter >= 60)statistics.gra_puter.pass++;
    if (middle->gra_puter >= 80)statistics.gra_puter.excellent++;

    statistics.gra_physics.average += middle->gra_physics;
    if (middle->gra_physics >= 60)statistics.gra_physics.pass++;
    if (middle->gra_physics >= 80)statistics.gra_physics.excellent++;

    statistics.gra_atom.average += middle->gra_atom;
    if (middle->gra_atom >= 60)statistics.gra_atom.pass++;
    if (middle->gra_atom >= 80)statistics.gra_atom.excellent++;

    statistics.gra_optics.average += middle->gra_optics;
    if (middle->gra_optics >= 60)statistics.gra_optics.pass++;
    if (middle->gra_optics >= 80)statistics.gra_optics.excellent++;
}
//添加信息
void addr_teacher(pstuin *head)
{
    pstuin middle;
    middle = (pstuin)malloc(sizeof(stuin));
    middle->next = NULL;
    printf("输入学号："); scanf("%s", middle->student_number); getchar();
    printf("输入姓名："); scanf("%s", middle->name); getchar();
    printf("输入专业："); scanf("%s", middle->professional); getchar();
    printf("输入c语言成绩："); scanf("%lf", &middle->gra_c); getchar();
    printf("输入计算机物理成绩："); scanf("%lf", &middle->gra_puter); getchar();
    printf("输入大学物理成绩："); scanf("%lf", &middle->gra_physics); getchar();
    printf("输入原子物理成绩："); scanf("%lf", &middle->gra_atom); getchar();
    printf("输入光学成绩："); scanf("%lf", &middle->gra_optics); getchar();
    middle->next = (*head)->next;
    *head = middle;
}
//修改信息
int modify_teacher(pstuin head)
{
    pstuin middle = head;
    char nu[11] = { 0 };
    printf("输入需要修改学号：");
    scanf("%s", nu); getchar();
    while (middle != NULL)
    {
        if (strcmp(middle->student_number, nu) == 0)
        {
            printf("输入学号："); scanf("%s", middle->student_number); getchar();
            printf("输入姓名："); scanf("%s", middle->name); getchar();
            printf("输入专业："); scanf("%s", middle->professional); getchar();
            printf("输入c语言成绩："); scanf("%lf", &middle->gra_c); getchar();
            printf("输入计算机物理成绩："); scanf("%lf", &middle->gra_puter); getchar();
            printf("输入大学物理成绩："); scanf("%lf", &middle->gra_physics); getchar();
            printf("输入原子物理成绩："); scanf("%lf", &middle->gra_atom); getchar();
            printf("输入光学成绩："); scanf("%lf", &middle->gra_optics); getchar();
            return 1;
        }
        middle = middle->next;
    }
    return 0;
}
//删除信息
int delete_teacher(pstuin* head)
{
    pstuin middle;
    char nu[11] = { 0 };
    printf("输入需要删除学号：");
    scanf("%s", nu);
    while ((*head) != NULL)
    {
        if (strcmp((*head)->student_number, nu) == 0)
        {
            middle = *head;
            *head = (*head)->next;
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
int enquiry_student(pstuin head)
{
    pstuin middle = head;
    char nu[11] = { 0 };
    printf("输入需要查询学号：");
    scanf("%s", nu); getchar();
    while (middle != NULL)
    {
        if (strcmp(middle->student_number, nu) == 0)
        {
            printf("学号        姓名        专业        c语言       计算机物理  大学物理    原子物理    光学\n");
            printf("%-12s%-12s%-12s%-12lf%-12lf%-12lf%-12lf%-12lf\n", middle->student_number, middle->name, middle->professional,
                middle->gra_c, middle->gra_puter, middle->gra_physics, middle->gra_atom, middle->gra_optics);
            printf("总成绩：%lf\n", middle->gra_c + middle->gra_puter + middle->gra_physics + middle->gra_atom + middle->gra_optics);
            printf("--------------------------------------------------------------------------------------------------------\n");
            return 1;
        }
        middle = middle->next;
    }
    return 0;
}
//查询信息
int enquiry_teacher(pstuin head,int n)
{
    int i = 0;
    pstuin middle;
    while (i != 10)
    {
        printf("     1.c语言\n");
        printf("     2.计算机物理\n");
        printf("     3.大学物理\n");
        printf("     4.原子物理\n");
        printf("     5.光学\n");
        printf("     6.打印所有学生\n");
        printf("     7.查询指定学生\n");
        printf("     10.退出\n");
        printf("输入选项："); scanf("%d", &i); getchar();
        system("cls");
        switch (i)
        {
        case 1:
        {
            printf("c语言\n");
            printf("平均分：%lf\n", statistics.gra_c.average / n);
            printf("优秀率：%d%%\n", (int)((double)statistics.gra_c.excellent / n * 100));
            printf("及格人数：%d\n", statistics.gra_c.pass);
            printf("未及格人数：%d\n", n - statistics.gra_c.pass);
            printf("----------------优秀名单----------------\n");
            printf("学号        姓名        专业        c语言\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_c >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_c);
                middle = middle->next;
            }
            printf("----------------未及格名单----------------\n");
            printf("学号        姓名        专业        c语言\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_c < 60)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_c);
                middle = middle->next;
            }
            break;
        }
        case 2:
        {
            printf("计算机物理\n");
            printf("平均分：%lf\n", statistics.gra_puter.average / n);
            printf("优秀率：%d%%\n", (int)((double)statistics.gra_puter.excellent / n * 100));
            printf("及格人数：%d\n", statistics.gra_puter.pass);
            printf("未及格人数：%d\n", n - statistics.gra_puter.pass);
            printf("----------------优秀名单----------------\n");
            printf("学号        姓名        专业        计算机物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_puter >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_puter);
                middle = middle->next;
            }
            printf("----------------未及格名单----------------\n");
            printf("学号        姓名        专业        计算机物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_puter < 60)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_puter);
                middle = middle->next;
            }
            break;
        }
        case 3:
        {
            printf("大学物理\n");
            printf("平均分：%lf\n", statistics.gra_physics.average / n);
            printf("优秀率：%d%%\n", (int)((double)statistics.gra_physics.excellent / n * 100));
            printf("及格人数：%d\n", statistics.gra_physics.pass);
            printf("未及格人数：%d\n", n - statistics.gra_physics.pass);
            printf("----------------优秀名单----------------\n");
            printf("学号        姓名        专业        大学物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_physics >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_physics);
                middle = middle->next;
            }
            printf("----------------未及格名单----------------\n");
            printf("学号        姓名        专业        大学物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_physics < 60)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_physics);
                middle = middle->next;
            }
            break;
        }
        case 4:
        {
            printf("原子物理\n");
            printf("平均分：%lf\n", statistics.gra_atom.average / n);
            printf("优秀率：%d%%\n", (int)((double)statistics.gra_atom.excellent / n * 100));
            printf("及格人数：%d\n", statistics.gra_atom.pass);
            printf("未及格人数：%d\n", n - statistics.gra_atom.pass);
            printf("----------------优秀名单----------------\n");
            printf("学号        姓名        专业        原子物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_atom >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_atom);
                middle = middle->next;
            }
            printf("----------------未及格名单----------------\n");
            printf("学号        姓名        专业        原子物理\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_atom < 60)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_atom);
                middle = middle->next;
            }
            break;
        }
        case 5:
        {
            printf("光学\n");
            printf("平均分：%lf\n", statistics.gra_optics.average / n);
            printf("优秀率：%d%%\n", (int)((double)statistics.gra_optics.excellent / n * 100));
            printf("及格人数：%d\n", statistics.gra_optics.pass);
            printf("未及格人数：%d\n", n - statistics.gra_optics.pass);
            printf("----------------优秀名单----------------\n");
            printf("学号        姓名        专业        光学\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_optics >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_optics);
                middle = middle->next;
            }
            printf("----------------未及格名单----------------\n");
            printf("学号        姓名        专业        光学\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_optics < 60)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_optics);
                middle = middle->next;
            }
            break;
        }
            break;
        case 6:
            print_(head);
            break;
        case 7:
            enquiry_student(head);
            break;
        default:
            break;
        }
        printf("==============================\n");
    }    
    return 0;
}
//读取信息
int read_(pstuin* head)
{
    int n = 0, k = 0;
    pstuin middle;
    char s[20];
    FILE* fp;
    memset(&statistics, 0, sizeof(statistics));
    fp = fopen("13.txt", "rt");
    for (int i = 0; i < 8; i++)
        fscanf(fp, "%s\n", s);
    while (1)
    {
        middle = (pstuin)malloc(sizeof(stuin));
        middle->next = NULL;
        k = fscanf(fp, "%s %s %s %lf %lf %lf %lf %lf\n", middle->student_number, middle->name, middle->professional, 
            &middle->gra_c, &middle->gra_puter, &middle->gra_physics, &middle->gra_atom, &middle->gra_optics);
        if (k == EOF)
        {
            free(middle);
            break;
        }
        statistics_(middle);
        *head = middle;
        head = &middle->next;
        n++;
    }
    fclose(fp);
    return n;
}
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
void teacher(pstuin* head,int n)
{
    int i = 0;
    while (i != 5)
    {
        printf("     1.添加信息\n");
        printf("     2.修改信息\n");
        printf("     3.删除信息\n");
        printf("     4.查询信息\n");
        printf("     5.退出\n");
        printf("输入选项："); scanf("%d", &i); getchar();
        system("cls");
        switch (i)
        {
        case 1:
        {
            addr_teacher(head);
            break;
        }
        case 2:
        {
            modify_teacher(*head);
            break;
        }
        case 3:
        {
            delete_teacher(head);
            break;
        }
        case 4:
        {
            enquiry_teacher(*head, n);
            break;
        }
        default:
            break;
        }
    }
}
void root()
{
    char accnum[11] = { 0 };	//账号
    int i = 0, j = 0;
    while (i != 5)
    {
        memset(accnum, 0, 11);
        printf("     1.删除账号\n");
        printf("     2.修改密码\n");
        printf("     3.添加账号\n");
        printf("     4.查询账号\n");
        printf("     5.退出\n");
        printf("输入选项："); scanf("%d", &i); getchar();
        system("cls");
        switch (i)
        {
        case 1:
        {
            printf("输入账号："); scanf("%s", accnum); getchar();
            for (j = 0; j < m; j++)
            {
                if (strcmp(account[j].accnum, accnum) == 0)
                {
                    memset(account[j].accnum, 0, 11);
                    memset(account[j].code, 0, 11);
                    account[j].access = 3;
                    break;
                }
            }
            break;
        }
        case 2:
        {
            printf("输入账号："); scanf("%s", accnum); getchar();
            for (j = 0; j < m; j++)
            {
                if (strcmp(account[j].accnum, accnum) == 0)
                {
                    printf("输入密码："); scanf("%s", account[j].code); getchar();
                    break;
                }
            }
            break;
        }
        case 3:
        {
            for (j = 0; j < m; j++)
            {
                if (strcmp(account[j].accnum, accnum) == 0)
                {
                    printf("输入账号："); scanf("%s", account[j].accnum); getchar();
                    printf("输入密码："); scanf("%s", account[j].code); getchar();
                    printf("输入权限（0，1，2）："); scanf("%d", &account[j].access); getchar();
                    break;
                }
            }
            break;
        }
        case 4:
        {
            for (j = 0; j < m; j++)
            {
                printf("账号：%s\n", account[j].accnum);
                printf("密码：%s\n", account[j].code);
                printf("权限：%d\n", account[j].access);
                printf("-----------------------------\n");
            }
            break;
        }
        default:
            break;
        }
    }
}
int main(int argc, char const* argv[])
{
    /*初始账号密码
    root, 000000,0
    teacher,000000,1
    student,000000,2
    */
    pstuin head = NULL;
    char accnum[10] = { 0 };	//账号
    char code[7] = { 0 };	    //密码
    int i = 0, k = 3, n = 0, j = 0;
    n = read_(&head);
    printf("输入账号："); scanf("%s", accnum); getchar();
    printf("输入密码："); scanf("%s", code); getchar();
    for (i = 0; i < m; i++)
    {
        if (strcmp(account[i].accnum, accnum) == 0 && strcmp(account[i].code, code) == 0)
        {
            k = account[i].access;
            break;
        }
    }
    switch (k)
    {
    case 0:
    {
        root();
        break;
    }
    case 1:
    {
        teacher(&head, n);
        break;
    }
    case 2:
    {
        enquiry_student(head);
        break;
    }
    default:
        break;
    }
    free_(head);
    return 0;
}