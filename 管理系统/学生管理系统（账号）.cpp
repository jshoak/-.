#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define m 5     //�˺�����
struct
{
    char accnum[10];	//�˺�
    char code[7];	    //����
    int access;		    //Ȩ��
}account[m] = {
    {"root","000000",0},
    {"teacher","000000",1},
    {"student","000000",2},
};
typedef struct information
{
    char student_number[11];	//ѧ��
    char name[11];				//����
    char professional[11];		//רҵ
    double gra_c;               //c����
    double gra_puter;           //���������
    double gra_physics;         //��ѧ����
    double gra_atom;            //ԭ������
    double gra_optics;          //��ѧ
    struct information* next;
}stuin, * pstuin;
struct grades
{
    double average;             //ƽ����
    int pass;                   //����
    int excellent;              //����
};
struct 
{
    struct grades gra_c;               //c����
    struct grades gra_puter;           //���������
    struct grades gra_physics;         //��ѧ����
    struct grades gra_atom;            //ԭ������
    struct grades gra_optics;          //��ѧ
}statistics;
//��ӡ��Ϣ
void print_(pstuin head)
{
    printf("ѧ��        ����        רҵ        c����       ���������  ��ѧ����    ԭ������    ��ѧ\n");
    pstuin middle = head;
    while (middle != NULL)
    {
        printf("%-12s%-12s%-12s%-12lf%-12lf%-12lf%-12lf%-12lf\n", middle->student_number, middle->name, middle->professional, 
            middle->gra_c, middle->gra_puter, middle->gra_physics, middle->gra_atom, middle->gra_optics);
        printf("--------------------------------------------------------------------------------------------------------\n");
        middle = middle->next;					//ָ����һ��
    }
}
//ͳ��
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
//�����Ϣ
void addr_teacher(pstuin *head)
{
    pstuin middle;
    middle = (pstuin)malloc(sizeof(stuin));
    middle->next = NULL;
    printf("����ѧ�ţ�"); scanf("%s", middle->student_number); getchar();
    printf("����������"); scanf("%s", middle->name); getchar();
    printf("����רҵ��"); scanf("%s", middle->professional); getchar();
    printf("����c���Գɼ���"); scanf("%lf", &middle->gra_c); getchar();
    printf("������������ɼ���"); scanf("%lf", &middle->gra_puter); getchar();
    printf("�����ѧ����ɼ���"); scanf("%lf", &middle->gra_physics); getchar();
    printf("����ԭ������ɼ���"); scanf("%lf", &middle->gra_atom); getchar();
    printf("�����ѧ�ɼ���"); scanf("%lf", &middle->gra_optics); getchar();
    middle->next = (*head)->next;
    *head = middle;
}
//�޸���Ϣ
int modify_teacher(pstuin head)
{
    pstuin middle = head;
    char nu[11] = { 0 };
    printf("������Ҫ�޸�ѧ�ţ�");
    scanf("%s", nu); getchar();
    while (middle != NULL)
    {
        if (strcmp(middle->student_number, nu) == 0)
        {
            printf("����ѧ�ţ�"); scanf("%s", middle->student_number); getchar();
            printf("����������"); scanf("%s", middle->name); getchar();
            printf("����רҵ��"); scanf("%s", middle->professional); getchar();
            printf("����c���Գɼ���"); scanf("%lf", &middle->gra_c); getchar();
            printf("������������ɼ���"); scanf("%lf", &middle->gra_puter); getchar();
            printf("�����ѧ����ɼ���"); scanf("%lf", &middle->gra_physics); getchar();
            printf("����ԭ������ɼ���"); scanf("%lf", &middle->gra_atom); getchar();
            printf("�����ѧ�ɼ���"); scanf("%lf", &middle->gra_optics); getchar();
            return 1;
        }
        middle = middle->next;
    }
    return 0;
}
//ɾ����Ϣ
int delete_teacher(pstuin* head)
{
    pstuin middle;
    char nu[11] = { 0 };
    printf("������Ҫɾ��ѧ�ţ�");
    scanf("%s", nu);
    while ((*head) != NULL)
    {
        if (strcmp((*head)->student_number, nu) == 0)
        {
            middle = *head;
            *head = (*head)->next;
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
int enquiry_student(pstuin head)
{
    pstuin middle = head;
    char nu[11] = { 0 };
    printf("������Ҫ��ѯѧ�ţ�");
    scanf("%s", nu); getchar();
    while (middle != NULL)
    {
        if (strcmp(middle->student_number, nu) == 0)
        {
            printf("ѧ��        ����        רҵ        c����       ���������  ��ѧ����    ԭ������    ��ѧ\n");
            printf("%-12s%-12s%-12s%-12lf%-12lf%-12lf%-12lf%-12lf\n", middle->student_number, middle->name, middle->professional,
                middle->gra_c, middle->gra_puter, middle->gra_physics, middle->gra_atom, middle->gra_optics);
            printf("�ܳɼ���%lf\n", middle->gra_c + middle->gra_puter + middle->gra_physics + middle->gra_atom + middle->gra_optics);
            printf("--------------------------------------------------------------------------------------------------------\n");
            return 1;
        }
        middle = middle->next;
    }
    return 0;
}
//��ѯ��Ϣ
int enquiry_teacher(pstuin head,int n)
{
    int i = 0;
    pstuin middle;
    while (i != 10)
    {
        printf("     1.c����\n");
        printf("     2.���������\n");
        printf("     3.��ѧ����\n");
        printf("     4.ԭ������\n");
        printf("     5.��ѧ\n");
        printf("     6.��ӡ����ѧ��\n");
        printf("     7.��ѯָ��ѧ��\n");
        printf("     10.�˳�\n");
        printf("����ѡ�"); scanf("%d", &i); getchar();
        system("cls");
        switch (i)
        {
        case 1:
        {
            printf("c����\n");
            printf("ƽ���֣�%lf\n", statistics.gra_c.average / n);
            printf("�����ʣ�%d%%\n", (int)((double)statistics.gra_c.excellent / n * 100));
            printf("����������%d\n", statistics.gra_c.pass);
            printf("δ����������%d\n", n - statistics.gra_c.pass);
            printf("----------------��������----------------\n");
            printf("ѧ��        ����        רҵ        c����\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_c >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_c);
                middle = middle->next;
            }
            printf("----------------δ��������----------------\n");
            printf("ѧ��        ����        רҵ        c����\n");
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
            printf("���������\n");
            printf("ƽ���֣�%lf\n", statistics.gra_puter.average / n);
            printf("�����ʣ�%d%%\n", (int)((double)statistics.gra_puter.excellent / n * 100));
            printf("����������%d\n", statistics.gra_puter.pass);
            printf("δ����������%d\n", n - statistics.gra_puter.pass);
            printf("----------------��������----------------\n");
            printf("ѧ��        ����        רҵ        ���������\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_puter >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_puter);
                middle = middle->next;
            }
            printf("----------------δ��������----------------\n");
            printf("ѧ��        ����        רҵ        ���������\n");
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
            printf("��ѧ����\n");
            printf("ƽ���֣�%lf\n", statistics.gra_physics.average / n);
            printf("�����ʣ�%d%%\n", (int)((double)statistics.gra_physics.excellent / n * 100));
            printf("����������%d\n", statistics.gra_physics.pass);
            printf("δ����������%d\n", n - statistics.gra_physics.pass);
            printf("----------------��������----------------\n");
            printf("ѧ��        ����        רҵ        ��ѧ����\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_physics >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_physics);
                middle = middle->next;
            }
            printf("----------------δ��������----------------\n");
            printf("ѧ��        ����        רҵ        ��ѧ����\n");
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
            printf("ԭ������\n");
            printf("ƽ���֣�%lf\n", statistics.gra_atom.average / n);
            printf("�����ʣ�%d%%\n", (int)((double)statistics.gra_atom.excellent / n * 100));
            printf("����������%d\n", statistics.gra_atom.pass);
            printf("δ����������%d\n", n - statistics.gra_atom.pass);
            printf("----------------��������----------------\n");
            printf("ѧ��        ����        רҵ        ԭ������\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_atom >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_atom);
                middle = middle->next;
            }
            printf("----------------δ��������----------------\n");
            printf("ѧ��        ����        רҵ        ԭ������\n");
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
            printf("��ѧ\n");
            printf("ƽ���֣�%lf\n", statistics.gra_optics.average / n);
            printf("�����ʣ�%d%%\n", (int)((double)statistics.gra_optics.excellent / n * 100));
            printf("����������%d\n", statistics.gra_optics.pass);
            printf("δ����������%d\n", n - statistics.gra_optics.pass);
            printf("----------------��������----------------\n");
            printf("ѧ��        ����        רҵ        ��ѧ\n");
            middle = head;
            while (middle != NULL)
            {
                if (middle->gra_optics >= 80)
                    printf("%-12s%-12s%-12s%-12lf\n", middle->student_number, middle->name, middle->professional, middle->gra_optics);
                middle = middle->next;
            }
            printf("----------------δ��������----------------\n");
            printf("ѧ��        ����        רҵ        ��ѧ\n");
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
//��ȡ��Ϣ
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
void teacher(pstuin* head,int n)
{
    int i = 0;
    while (i != 5)
    {
        printf("     1.�����Ϣ\n");
        printf("     2.�޸���Ϣ\n");
        printf("     3.ɾ����Ϣ\n");
        printf("     4.��ѯ��Ϣ\n");
        printf("     5.�˳�\n");
        printf("����ѡ�"); scanf("%d", &i); getchar();
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
    char accnum[11] = { 0 };	//�˺�
    int i = 0, j = 0;
    while (i != 5)
    {
        memset(accnum, 0, 11);
        printf("     1.ɾ���˺�\n");
        printf("     2.�޸�����\n");
        printf("     3.����˺�\n");
        printf("     4.��ѯ�˺�\n");
        printf("     5.�˳�\n");
        printf("����ѡ�"); scanf("%d", &i); getchar();
        system("cls");
        switch (i)
        {
        case 1:
        {
            printf("�����˺ţ�"); scanf("%s", accnum); getchar();
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
            printf("�����˺ţ�"); scanf("%s", accnum); getchar();
            for (j = 0; j < m; j++)
            {
                if (strcmp(account[j].accnum, accnum) == 0)
                {
                    printf("�������룺"); scanf("%s", account[j].code); getchar();
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
                    printf("�����˺ţ�"); scanf("%s", account[j].accnum); getchar();
                    printf("�������룺"); scanf("%s", account[j].code); getchar();
                    printf("����Ȩ�ޣ�0��1��2����"); scanf("%d", &account[j].access); getchar();
                    break;
                }
            }
            break;
        }
        case 4:
        {
            for (j = 0; j < m; j++)
            {
                printf("�˺ţ�%s\n", account[j].accnum);
                printf("���룺%s\n", account[j].code);
                printf("Ȩ�ޣ�%d\n", account[j].access);
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
    /*��ʼ�˺�����
    root, 000000,0
    teacher,000000,1
    student,000000,2
    */
    pstuin head = NULL;
    char accnum[10] = { 0 };	//�˺�
    char code[7] = { 0 };	    //����
    int i = 0, k = 3, n = 0, j = 0;
    n = read_(&head);
    printf("�����˺ţ�"); scanf("%s", accnum); getchar();
    printf("�������룺"); scanf("%s", code); getchar();
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