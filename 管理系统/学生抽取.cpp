#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct information
{
	char student_number[11];	//学号
	char name[21];				//名字
	float grades;				//成绩
	struct information* next;
}stuin, * pstuin;
//录入信息
pstuin inputting_student(int i)
{
	pstuin head, indirectly, *p;
	p = &head;
	while (i--)
	{
		indirectly = (pstuin)malloc(sizeof(stuin));
		indirectly->next = NULL;
		indirectly->grades = 0;
		memset(indirectly->student_number, 0, 11);
		memset(indirectly->name, 0, 21);
		*p = indirectly;
		p = &indirectly->next;
		printf("输入学号："); scanf("%s", indirectly->student_number); getchar();
		printf("输入姓名："); scanf("%s", indirectly->name); getchar();
		printf("----------------------------------\n");
	}
	return head;
}
//释放内存空间
void free_student(pstuin head)
{
	pstuin indirectly;
	while (head != NULL)
	{
		indirectly = head->next;
		free(head);
		head = indirectly;
	}
}
//打印信息
void print_student(pstuin head)
{
	pstuin indirectly = head;
	while (indirectly != NULL)
	{
		printf("学号：%s\n", indirectly->student_number);
		printf("姓名：%s\n", indirectly->name);
		printf("成绩：%f\n", indirectly->grades);
		printf("----------------------------------\n");
		indirectly = indirectly->next;		//指向下一个
	}
}
//评分
float scoring_student(int j)
{
	float a[10], max = 0, min = 100, s = 0;
	int i = 0;
	switch (j)
	{
	case 1:
		printf("输入评分：");
		scanf("%f", &s); getchar();
		return s;
	case 2:
		for (i = 0; i < 2; i++)
		{
			printf("%d输入评分：", i + 1);
			scanf("%f", &a[i]); getchar();
			s += a[i];
		}
		return s / 2;
	default:
		for (i = 0; i < j; i++)
		{
			printf("%d输入评分：", i + 1);
			scanf("%f", &a[i]); getchar();
			if (a[i] > max)max = a[i];
			if (a[i] < min)min = a[i];
			s += a[i];
		}
		s -= max;
		s -= min;
		return s / (j - 2);
	}
}
//抽取学生
void choose_student(int i, int n, pstuin* head, int j, pstuin* head_dy)
{
	while (j--)
		head_dy = &(*head_dy)->next;	//移动到末尾
	while (i--)
		head = &(*head)->next;		//选择第i个学生
	printf("抽中学号：%s\n", (*head)->student_number);
	(*head)->grades = scoring_student(n);
	printf("----------------------------------\n");
	*head_dy = *head;		//保存已抽取过学生
	*head = (*head)->next;		//去掉已抽取过学生
	(*head_dy)->next = NULL;
}
//排序
void sort_student(pstuin head)
{
	pstuin indirectly = head, middle;
	stuin a;
	while (indirectly != NULL)
	{
		middle = indirectly->next;
		while (middle != NULL)
		{
			if (middle->grades > indirectly->grades)	//交换信息
			{
				memcpy(&a, middle, sizeof(stuin) - sizeof(pstuin));
				memcpy(middle, indirectly, sizeof(stuin) - sizeof(pstuin));
				memcpy(indirectly, &a, sizeof(stuin) - sizeof(pstuin));
			}
			middle = middle->next;
		}
		indirectly = indirectly->next;
	}
}
//保存
void save_student(pstuin head, int i, pstuin head_dy, int j, int k)
{
	FILE* fp;
	pstuin indirectly = head;
	fp = fopen("demo.txt", "wt");
	fprintf(fp, "%d\n", k);		//评委数
	fprintf(fp, "%d\n", i);		//未抽取
	while (i--){
		fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
		indirectly = indirectly->next;
	}
	indirectly = head_dy;
	int n, m;
	for (m = 1; m < 4; m++)		//获奖
	{
		n = ceil(j * 0.1 * m);	//向上取整
		j -= n;
		fprintf(fp, "%d\n", n);
		while (n--) {
			fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
			indirectly = indirectly->next;
		}
	}
	fprintf(fp, "%d\n", j);		//未获奖
	while (j--) {
		fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
		indirectly = indirectly->next;
	}
	fclose(fp);
}
//读取
void derived_student(pstuin *head, pstuin* head_dy, int *i, int *j, int *n)
{
	FILE* fp;
	pstuin indirectly;
	fp = fopen("demo.txt", "rt");
	int k;
	fscanf(fp, "%d\n", n);	//评委数
	fscanf(fp, "%d\n", &k);	//未抽取
	*i = k;
	while (k--){
		indirectly = (pstuin)malloc(sizeof(stuin)); indirectly->next = NULL;
		fscanf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, &indirectly->grades);
		*head = indirectly;
		head = &indirectly->next;
	}
	int m;
	for (m = 0; m < 4; m++)		//已抽取
	{
		fscanf(fp, "%d\n", &k);
		*j += k;
		while (k--) {
			indirectly = (pstuin)malloc(sizeof(stuin)); indirectly->next = NULL;
			fscanf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, &indirectly->grades);
			*head_dy = indirectly;
			head_dy = &indirectly->next;
		}
	}
	fclose(fp);
}
//功能选项
void print()
{
	printf("     1.第一次使用\n");
	printf("     2.再次使用\n");
	printf("     3.列出未抽取学生\n");
	printf("     4.列出已抽取学生\n");
	printf("     5.退出\n");
}
int main()
{
	int i = 0, n = 0, j = 0, choice = 0;	//i：学生数 n：评委数 j：已抽取数
	char c = 0;
	pstuin head = NULL, head_dy = NULL;
	print();
	while (choice != 5)
	{
		printf("输入选项："); scanf("%d", &choice); getchar();
		system("cls");
		print();
		switch (choice)
		{
		case 1:
		{
			printf("输入学生数："); scanf("%d", &i); getchar();
			printf("输入评委数："); scanf("%d", &n); getchar();
			srand((unsigned)time(NULL));	//随机数种子
			head = inputting_student(i);
			for (j; j < i && c != 'q'; j++)
			{
				choose_student(rand() % (i - j), n, &head, j, &head_dy);
				printf("按回车继续，输入‘q’退出：");
				c = getchar();
			}
			sort_student(head_dy);					//排序后保存
			save_student(head, i - j, head_dy, j, n);
			break;
		}
		case 2:
		{
			free_student(head);
			free_student(head_dy);
			derived_student(&head, &head_dy, &i, &j, &n);
			i += j;
			srand((unsigned)time(NULL));	//随机数种子
			for (j; j < i && c != 'q'; j++)
			{
				choose_student(rand() % (i - j), n, &head, j, &head_dy);
				printf("按回车继续，输入‘q’退出：");
				c = getchar();
			}
			sort_student(head_dy);					//排序后保存
			save_student(head, i - j, head_dy, j, n);
			break;
		}
		case 3:
		{
			print_student(head);
			break;
		}
		case 4:
		{
			print_student(head_dy);
			break;
		}
		default:
			break;
		}
	}
	free_student(head);
	free_student(head_dy);
	printf("已退出");
	return 0;
}