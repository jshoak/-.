// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
typedef struct information
{
	char student_number[11];	//学号
	char name[21];				//名字
	char sex[2];				//性别
	int age;					//年龄
	char college[20];			//学院
	char professional[20];		//专业
	char telephone[11];			//电话
	float grades;				//成绩
	struct information* next;
}stuin, * pstuin;
pstuin head = NULL, * p = &head;
int boy = 0, girl = 0;
int nine = 0, eight = 0, seven = 0, six = 0, zero = 0;
void scan(pstuin middle)//输入信息
{
	printf("输入学号："); scanf("%s", middle->student_number);
	printf("输入姓名："); scanf("%s", middle->name);
	printf("输入性别："); scanf("%s", middle->sex);
	if (strcmp(middle->sex, "男") == 0)boy++; 
	else girl++;
	printf("输入年龄："); scanf("%d", &middle->age);
	printf("输入学院："); scanf("%s", middle->college);
	printf("输入专业："); scanf("%s", middle->professional);
	printf("输入电话："); scanf("%s", middle->telephone);
	printf("输入成绩："); scanf("%f", &middle->grades);
	int grades = middle->grades / 10;
	switch (grades)
	{
	case 10:nine++;
		break;
	case 9:nine++;
		break;
	case 8:eight++;
		break;
	case 7:seven++;
		break;
	case 6:six++;
		break;
	default:zero++;
		break;
	}
}
void print(pstuin indirectly)//打印信息
{
	printf("学号：%s\n", indirectly->student_number);
	printf("姓名：%s\n", indirectly->name);
	printf("性别：%s\n", indirectly->sex);
	printf("年龄：%d\n", indirectly->age);
	printf("学院：%s\n", indirectly->college);
	printf("专业：%s\n", indirectly->professional);
	printf("电话：%s\n", indirectly->telephone);
	printf("成绩：%f\n", indirectly->grades);
}
void free_singer()//释放内存空间
{
	pstuin indirectly;
	while (head!=NULL)
	{
		indirectly = head->next;
		free(head);
		head = indirectly;
	}
}
void inputting_singer(int i)//录入信息
{
	pstuin middle;
	while (i--)
	{
		middle = (pstuin)malloc(sizeof(stuin));
		middle->next = NULL;
		*p = middle;
		p = &middle->next;
		scan(middle);
		printf("----------------------------------\n");
	}
}
int addr_singer()//添加信息
{
	pstuin indirectly = head, middle;
	char nu[11] = { 0 };
	printf("输入插入位置前学号（第一位学号0）：");
	scanf("%s", nu);
	if (nu[0] == 48)
	{
		middle = (pstuin)malloc(sizeof(stuin));
		scan(middle);
		middle->next = head;
		head = middle;
		printf("插入成功\n");
		return 1;
	}
	while (indirectly != NULL)
	{
		if (strcmp(indirectly->student_number, nu) == 0)//比较学号是否一样
		{		
			middle = (pstuin)malloc(sizeof(stuin));
			scan(middle);
			middle->next = indirectly->next;			//连接下一个学生信息
			indirectly->next = middle;					//连接下一个学生信息
			printf("插入成功\n");
			return 1;
		}
		indirectly = indirectly->next;
	}
	printf("插入失败\n");
	return 0;
}
void print_singer()//打印信息
{
	pstuin indirectly = head;
	while (indirectly != NULL)
	{
		print(indirectly);
		printf("----------------------------------\n");
		indirectly = indirectly->next;					//指向下一个
	}
}
int enquiry_singer()//查询信息
{
	pstuin indirectly = head;
	char nu[21] = { 0 };
	printf("输入需要查询学号或姓名：");
	scanf("%s", nu);
	while (indirectly != NULL)
	{
		if (strcmp(indirectly->student_number, nu) == 0|| strcmp(indirectly->name, nu) == 0)
		{
			print(indirectly);
			printf("----------------------------------\n");
			return 1;
		}
		indirectly = indirectly->next;
	}
	cout << "查询失败" << endl;
	return 0;
}
int modify_singer()//修改
{
	pstuin indirectly = head;
	char nu[21] = { 0 };
	printf("输入需要修改学号或姓名：");
	scanf("%s", nu);
	while (indirectly != NULL)
	{
		if (strcmp(indirectly->student_number, nu) == 0 || strcmp(indirectly->name, nu) == 0)
		{
			scan(indirectly);
			return 1;
		}
		indirectly = indirectly->next;
	}
	cout << "修改失败" << endl;
	return 0;
}
int delete_singer()//删除信息
{
	pstuin indirectly = head, middle;
	char nu[11] = { 0 };
	printf("输入需要删除学号：");
	scanf("%s", nu);
	if (strcmp(head->student_number, nu) == 0)
	{
		int grades = indirectly->grades / 10;
		switch (grades)
		{
		case 10:nine--;
			break;
		case 9:nine--;
			break;
		case 8:eight--;
			break;
		case 7:seven--;
			break;
		case 6:six--;
			break;
		default:zero--;
			break;
		}
		indirectly = head->next;
		free(head);
		head = indirectly;
		printf("删除成功\n");
		return 1;
	}
	indirectly = head;
	while (indirectly->next != NULL)
	{
		if (strcmp(indirectly->next->student_number, nu) == 0)
		{
			int grades = indirectly->next->grades / 10;
			switch (grades)
			{
			case 10:nine--;
				break;
			case 9:nine--;
				break;
			case 8:eight--;
				break;
			case 7:seven--;
				break;
			case 6:six--;
				break;
			default:zero--;
				break;
			}
			middle = indirectly->next->next;
			free(indirectly->next);
			indirectly->next = middle;
			printf("删除成功\n");
			return 1;
		}
		indirectly = indirectly->next;
	}
	printf("删除失败\n");
	return 0;
}
void save_singer()//保存
{
	FILE* fp;
	fp = fopen("demo.txt", "wt");
	pstuin indirectly = head;
	char nu[27] = { 0 };
	int i = 0, j = 0;
	while (indirectly != NULL)
	{
		fprintf(fp, "%s\n", indirectly->student_number);
		fprintf(fp, "%s\n", indirectly->name);
		fprintf(fp, "%s\n", indirectly->sex);
		fprintf(fp, "%d\n", indirectly->age);
		fprintf(fp, "%s\n", indirectly->college);
		fprintf(fp, "%s\n", indirectly->professional);
		fprintf(fp, "%s\n", indirectly->telephone);
		fprintf(fp, "%f\n", indirectly->grades);
		indirectly = indirectly->next;
	}
	fclose(fp);
}
void derived_singer()//读取
{
	FILE* fp;
	stuin a;
	fp = fopen("demo.txt", "rt");
	while (fscanf(fp, "%s", a.student_number) > 0)
	{
		printf("学号：%s\n", a.student_number);	
		fscanf(fp, "%s", a.name); printf("名字：%s\n", a.name);
		fscanf(fp, "%s", a.sex); printf("性别：%s\n", a.sex);
		fscanf(fp, "%d", &a.age); printf("年龄：%d\n", a.age);
		fscanf(fp, "%s", a.college); printf("学院：%s\n", a.college);
		fscanf(fp, "%s", a.professional); printf("专业：%s\n", a.professional);
		fscanf(fp, "%s", a.telephone); printf("电话：%s\n", a.telephone);
		fscanf(fp, "%f", &a.grades); printf("成绩：%f\n", a.grades);
	}
	fclose(fp);
}
void statistics_singer()//统计
{
	printf("男歌手有：%d人\n", boy);
	printf("女歌手有：%d人\n", girl);
	printf("90--100：%d人\n", nine);
	printf("80--89：%d人\n", eight);
	printf("70--79：%d人\n", seven);
	printf("60--69：%d人\n", six);
	printf("60一下：%d人\n", zero);
}
void sort_singer()//排序
{
	pstuin indirectly = head, middle;
	stuin a;
	while (indirectly != NULL)
	{
		middle = indirectly->next;
		while (middle != NULL)
		{
			if (middle->grades > indirectly->grades)
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
void winning_singer()//获奖
{
	pstuin indirectly = head;
	int i = 2;
	while (i--)
	{
		printf("一等奖姓名：%s\n", indirectly->name);
		indirectly = indirectly->next;
	}
	i = 3;
	while (i--)
	{
		printf("二等奖姓名：%s\n", indirectly->name);
		indirectly = indirectly->next;
	}
	i = 4;
	while (i--)
	{
		printf("三等奖姓名：%s\n", indirectly->name);
		indirectly = indirectly->next;
	}

}
void print()
{
	printf("*****校园歌手比赛信息管理系统*****\n");
	printf("     0.打印名单\n");
	printf("     1.录入功能\n");
	printf("     2.添加功能\n");
	printf("     3.保存功能\n");
	printf("     4.读取功能\n");
	printf("     5.删除功能\n");
	printf("     6.修改功能\n");
	printf("     7.查询功能\n");
	printf("     8.统计功能\n");
	printf("     9.排序功能\n");
	printf("     10.获奖名单\n");
	printf("     11.退出系统\n");
	cout << "**************************" << endl;
}
int main()
{
	print();
	int choice = 0;
	int i = 0;
	while (choice != 11)
	{	
		printf("输入选项：");
		scanf("%d", &choice);
		system("cls");
		print();
		switch (choice)
		{
		case 0:print_singer();
			break;
		case 1:
			printf("输入需要录入人数：");
			scanf("%d", &i);
			inputting_singer(i);
			break;
		case 2:addr_singer();
			break;
		case 3:save_singer();
			break;
		case 4:derived_singer();
			break;
		case 5:delete_singer();
			break;
		case 6:modify_singer();
			break;
		case 7:enquiry_singer();
			break;
		case 8:statistics_singer();
			break;
		case 9:sort_singer();
			break;
		case 10:winning_singer();
			break;
		default:
			break;
		}
	}
	free_singer();
	printf("退出系统\n");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
