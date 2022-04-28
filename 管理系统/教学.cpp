#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct teacher {
	unsigned int id;//教师号
	char name[11];//姓名
	char sex[3];//性别
	char background[11];//学历
	unsigned int age;//年龄
	char phone[12];//电话
	bool dist;//标记
	struct teacher* next;
}tea, * ptea;

typedef struct course {
	unsigned int id;//课程号
	char name[11];//课程名称
	bool dist;//标记
	struct course* next;
}cou, * pcou;

typedef struct tc {
	unsigned int id;//教课号
	char time[11];//开课时间
	unsigned int tid;//教师号
	unsigned int cid;//课程号
	bool dist;//标记
	struct tc* next;
}tc_, * ptc_;

typedef struct student {
	unsigned int id;//学号
	char name[11];//姓名
	bool dist;//标记
	struct student* next;
}stu, * pstu;

typedef struct sc{
	unsigned int id;//学课号
	unsigned int sid;//学号
	unsigned int tcid;//教课号
	bool dist;//标记
	struct sc* next;
}sc_, * psc_;

void show_teacher(ptea middle)
{
	printf("教师号：%d\n", middle->id);
	printf("姓名：%s\n", middle->name);
	printf("性别：%s\n", middle->sex);
	printf("学历：%s\n", middle->background);
	printf("年龄：%d\n", middle->age);
	printf("电话：%s\n", middle->phone);
	printf("---------------------------------------------\n");
}
void add_teacher(ptea* head)//添加教师信息
{
	ptea middle;
	middle = (ptea)malloc(sizeof(tea));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("输入教师号："); scanf("%d", &middle->id); getchar();
	printf("输入姓名："); scanf("%s", middle->name); getchar();
	printf("输入性别："); scanf("%s", middle->sex); getchar();
	printf("输入学历："); scanf("%s", middle->background); getchar();
	printf("输入年龄："); scanf("%d", &middle->age); getchar();
	printf("输入电话："); scanf("%s", middle->phone); getchar();
}
int del_teacher(ptea head)//逻辑删除
{
	unsigned int id;
	printf("输入需要删除教师号：");
	scanf("%d", &id); getchar();
	while (head != NULL)
	{
		if (head->id == id)
		{
			head->dist = 0;
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
void free_teacher(ptea head)
{
	ptea middle = NULL;
	while (head != NULL)
	{
		middle = head->next;
		free(head);
		head = middle;
	}
}
void print_teacher(ptea head)//显示教师信息
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_teacher(head);
		head = head->next;//指向下一个
	}
}
int enquiry_teacher(ptea head, unsigned int id)//查询信息
{
	while (head != NULL)
	{
		if (head->id == id)
		{
			show_teacher(head);
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
int fread_teacher(ptea *head)//读取教师信息
{
	FILE* fp;
	ptea middle;
	fopen_s(&fp, "teacher.dat", "rb");
	if (fp == NULL)return 0;
	while (true)
	{
		middle = (ptea)malloc(sizeof(tea));
		middle->next = NULL;
		if (!fread(middle, sizeof(tea), 1, fp))
			break;
		middle->next = *head;
		*head = middle;
	};
	free(middle);
	fclose(fp);
	return 1;
}
int fwrite_teacher(ptea head)//写入教师信息
{
	FILE* fp;
	fopen_s(&fp, "teacher.dat", "wb");
	if (fp == NULL)return 0;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		fwrite(head, sizeof(tea), 1, fp);
		head = head->next;					//指向下一个
	}
	fclose(fp);
	return 1;
}

void show_course(pcou middle)
{
	printf("课程号：%d\n", middle->id);
	printf("课程名称：%s\n", middle->name);
	printf("---------------------------------------------\n");
}
void add_course(pcou* head)//添加信息
{
	pcou middle;
	middle = (pcou)malloc(sizeof(cou));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("输入课程号："); scanf("%d", &middle->id); getchar();
	printf("输入课程名称："); scanf("%s", middle->name); getchar();
}
int del_course(pcou head)//逻辑删除
{
	unsigned int id;
	printf("输入需要删除课程号：");
	scanf("%d", &id); getchar();
	while (head != NULL)
	{
		if (head->id == id)
		{
			head->dist = 0;
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
void free_course(pcou head)
{
	pcou middle = NULL;
	while (head != NULL)
	{
		middle = head->next;
		free(head);
		head = middle;
	}
}
void print_course(pcou head)//显示信息
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_course(head);
		head = head->next;//指向下一个
	}
}
int enquiry_course(pcou head, unsigned int id)//查询信息
{
	while (head != NULL)
	{
		if (head->id == id)
		{
			show_course(head);
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
int fread_course(pcou* head)//读取信息
{
	FILE* fp;
	pcou middle;
	fopen_s(&fp, "course.dat", "rb");
	if (fp == NULL)return 0;
	while (true)
	{
		middle = (pcou)malloc(sizeof(cou));
		middle->next = NULL;
		if (!fread(middle, sizeof(cou), 1, fp))
			break;
		middle->next = *head;
		*head = middle;
	};
	free(middle);
	fclose(fp);
	return 1;
}
int fwrite_course(pcou head)//写入信息
{
	FILE* fp;
	fopen_s(&fp, "course.dat", "wb");
	if (fp == NULL)return 0;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		fwrite(head, sizeof(cou), 1, fp);
		head = head->next;					//指向下一个
	}
	fclose(fp);
	return 1;
}

void print_tc(ptc_ head, pcou head1, ptea head2)
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		printf("开课时间：%s\n", head->time);
		enquiry_course(head1,head->cid);
		enquiry_teacher(head2, head->tid);
		head = head->next;//指向下一个
	}
}
void add_tc(ptc_* head)//添加信息
{
	ptc_ middle;
	middle = (ptc_)malloc(sizeof(tc_));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("输入教课号："); scanf("%d", &middle->id); getchar();
	printf("输入开课时间："); scanf("%s", middle->time); getchar();
	printf("输入教师号："); scanf("%d", &middle->tid); getchar();
	printf("输入课程号："); scanf("%d", &middle->cid); getchar();
}
int del_tc(ptc_ head)//逻辑删除
{
	unsigned int id;
	printf("输入需要删除教课号：");
	scanf("%d", &id); getchar();
	while (head != NULL)
	{
		if (head->id == id)
		{
			head->dist = 0;
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
void free_tc(ptc_ head)
{
	ptc_ middle = NULL;
	while (head != NULL)
	{
		middle = head->next;
		free(head);
		head = middle;
	}
}
int fread_tc(ptc_* head)//读取信息
{
	FILE* fp;
	ptc_ middle;
	fopen_s(&fp, "tc.dat", "rb");
	if (fp == NULL)return 0;
	while (true)
	{
		middle = (ptc_)malloc(sizeof(tc_));
		middle->next = NULL;
		if (!fread(middle, sizeof(tc_), 1, fp))
			break;
		middle->next = *head;
		*head = middle;
	};
	free(middle);
	fclose(fp);
	return 1;
}
int fwrite_tc(ptc_ head)//写入信息
{
	FILE* fp;
	fopen_s(&fp, "tc.dat", "wb");
	if (fp == NULL)return 0;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		fwrite(head, sizeof(tc_), 1, fp);
		head = head->next;					//指向下一个
	}
	fclose(fp);
	return 1;
}

void show_student(pstu middle)
{
	printf("学号：%d\n", middle->id);
	printf("姓名：%s\n", middle->name);
	printf("---------------------------------------------\n");
}
void add_student(pstu* head)//添加信息
{
	pstu middle;
	middle = (pstu)malloc(sizeof(stu));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("输入学号："); scanf("%d", &middle->id); getchar();
	printf("输入姓名："); scanf("%s", middle->name); getchar();
}
int del_student(pstu head)//逻辑删除
{
	unsigned int id;
	printf("输入需要删除学号：");
	scanf("%d", &id); getchar();
	while (head != NULL)
	{
		if (head->id == id)
		{
			head->dist = 0;
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
void free_student(pstu head)
{
	pstu middle = NULL;
	while (head != NULL)
	{
		middle = head->next;
		free(head);
		head = middle;
	}
}
void print_student(pstu head)//显示信息
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_student(head);
		head = head->next;//指向下一个
	}
}
int enquiry_student(pstu head, unsigned int id)//查询信息
{
	while (head != NULL)
	{
		if (head->id == id)
		{
			show_student(head);
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
int fread_student(pstu* head)//读取信息
{
	FILE* fp;
	pstu middle;
	fopen_s(&fp, "student.dat", "rb");
	if (fp == NULL)return 0;
	while (true)
	{
		middle = (pstu)malloc(sizeof(stu));
		middle->next = NULL;
		if (!fread(middle, sizeof(stu), 1, fp))
			break;
		middle->next = *head;
		*head = middle;
	};
	free(middle);
	fclose(fp);
	return 1;
}
int fwrite_student(pstu head)//写入信息
{
	FILE* fp;
	fopen_s(&fp, "student.dat", "wb");
	if (fp == NULL)return 0;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		fwrite(head, sizeof(stu), 1, fp);
		head = head->next;					//指向下一个
	}
	fclose(fp);
	return 1;
}

void print_sc(psc_ head, pstu head1, ptc_ head2, pcou head3, ptea head4)
{
	ptc_ middle = head2;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		enquiry_student(head1, head->sid);
		while (middle != NULL)
		{
			if (middle->dist == 0)
			{
				head = head->next;
				continue;
			}
			if (middle->id == head->tcid)
			{
				printf("开课时间：%s\n", middle->time);
				enquiry_course(head3, middle->cid);
				enquiry_teacher(head4, middle->tid);
				head = head->next;
				break;
			}
			middle = middle->next;//指向下一个
		}
		middle = head2;
		head = head->next;//指向下一个
	}
}
void add_sc(psc_* head)//添加信息
{
	psc_ middle;
	middle = (psc_)malloc(sizeof(sc_));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("输入学课号："); scanf("%d", &middle->id); getchar();
	printf("输入学号："); scanf("%d", &middle->sid); getchar();
	printf("输入教课号："); scanf("%d", &middle->tcid); getchar();
}
int del_sc(psc_ head)//逻辑删除
{
	unsigned int id;
	printf("输入需要删除学课号：");
	scanf("%d", &id); getchar();
	while (head != NULL)
	{
		if (head->id == id)
		{
			head->dist = 0;
			return 1;
		}
		head = head->next;
	}
	printf("未找到\n");
	return 0;
}
void free_sc(psc_ head)
{
	psc_ middle = NULL;
	while (head != NULL)
	{
		middle = head->next;
		free(head);
		head = middle;
	}
}
int fread_sc(psc_* head)//读取信息
{
	FILE* fp;
	psc_ middle;
	fopen_s(&fp, "sc.dat", "rb");
	if (fp == NULL)return 0;
	while (true)
	{
		middle = (psc_)malloc(sizeof(sc_));
		middle->next = NULL;
		if (!fread(middle, sizeof(sc_), 1, fp))
			break;
		middle->next = *head;
		*head = middle;
	};
	free(middle);
	fclose(fp);
	return 1;
}
int fwrite_sc(psc_ head)//写入信息
{
	FILE* fp;
	fopen_s(&fp, "sc.dat", "wb");
	if (fp == NULL)return 0;
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		fwrite(head, sizeof(sc_), 1, fp);
		head = head->next;					//指向下一个
	}
	fclose(fp);
	return 1;
}

void menu()
{
	printf("**********************************\n");
	printf("1.信息浏览\n");
	printf("2.信息添加\n");
	printf("3.信息删除\n");
	printf("4.信息查询\n");
	printf("5.退出\n");
	printf("**********************************\n");
}
void menu1()
{
	printf("**********************************\n");
	printf("1.教师信息浏览\n");
	printf("2.学生信息浏览\n");
	printf("3.课程信息浏览\n");
	printf("4.教师与课程关联信息浏览\n");
	printf("5.学生与课程关联信息浏览\n");
	printf("6.退出\n");
	printf("**********************************\n");
}
void menu2()
{
	printf("**********************************\n");
	printf("1.教师信息添加\n");
	printf("2.学生信息添加\n");
	printf("3.课程信息添加\n");
	printf("4.教师与课程关联信息添加\n");
	printf("5.学生与课程关联信息添加\n");
	printf("6.退出\n");
	printf("**********************************\n");
}
void menu3()
{
	printf("**********************************\n");
	printf("1.教师信息删除\n");
	printf("2.学生信息删除\n");
	printf("3.课程信息删除\n");
	printf("4.教师与课程关联信息删除\n");
	printf("5.学生与课程关联信息删除\n");
	printf("6.退出\n");
	printf("**********************************\n");
}
void menu4()
{
	printf("**********************************\n");
	printf("1.教师信息查询\n");
	printf("2.学生信息查询\n");
	printf("3.课程信息查询\n");
	printf("4.教师与课程关联信息查询\n");
	printf("5.学生与课程关联信息查询\n");
	printf("6.退出\n");
	printf("**********************************\n");
}

int main()
{
	ptea teach = NULL;
	pcou cours = NULL;
	ptc_ t = NULL;
	pstu stude = NULL;
	psc_ s = NULL;
	int choose = 0, choose1 = 0, choose2 = 0, choose3 = 0, choose4 = 0;
	unsigned int id = 0;
	ptc_ middle1 = t;
	psc_ middle2 = s;
	fread_teacher(&teach); fread_course(&cours); fread_student(&stude); fread_tc(&t); fread_sc(&s);
	while (choose != 5)
	{
		menu();
		printf("输入选项："); scanf("%d", &choose); getchar();
		system("cls");
		switch (choose)
		{
		case 1:
		{
			while (choose1 != 6)
			{
				menu1();
				printf("输入选项："); scanf("%d", &choose1); getchar();
				system("cls");
				switch (choose1)
				{
				case 1:
					print_teacher(teach);
					break;
				case 2:
					print_student(stude);
					break;
				case 3:
					print_course(cours);
					break;
				case 4:
					print_tc(t, cours, teach);
					break;
				case 5:
					print_sc(s, stude, t, cours, teach);
					break;
				default:
					break;
				}
			}
			choose1 = 0;
			break;
		}
		case 2:
		{
			while (choose2 != 6)
			{	
				menu2();
				printf("输入选项："); scanf("%d", &choose2); getchar();
				system("cls");
				switch (choose2)
				{
				case 1:
					add_teacher(&teach);
					break;
				case 2:
					add_student(&stude);
					break;
				case 3:
					add_course(&cours);
					break;
				case 4:
					add_tc(&t);
					break;
				case 5:
					add_sc(&s);
					break;
				default:
					break;
				}
			}
			choose2 = 0;
			break;
		}
		case 3:
		{
			while (choose3 != 6)
			{
				menu3();
				printf("输入选项："); scanf("%d", &choose3); getchar();
				system("cls");
				switch (choose3)
				{
				case 1:
					del_teacher(teach);
					break;
				case 2:
					del_student(stude);
					break;
				case 3:
					del_course(cours);
					break;
				case 4:
					del_tc(t);
					break;
				case 5:
					del_sc(s);
					break;
				default:
					break;
				}
			}
			choose3 = 0;
			break;
		}
		case 4:
		{
			while (choose4 != 6)
			{
				menu4();
				printf("输入选项："); scanf("%d", &choose4); getchar();
				system("cls");
				switch (choose4)
				{
				case 1:
					printf("输入需要查询ID：");
					scanf("%d", &id); getchar();
					enquiry_teacher(teach, id);
					break;
				case 2:
					printf("输入需要查询ID：");
					scanf("%d", &id); getchar();
					enquiry_student(stude, id);
					break;
				case 3:
					printf("输入需要查询ID：");
					scanf("%d", &id); getchar();
					enquiry_course(cours, id);
					break;
				case 4:
					printf("输入需要查询教师ID：");
					scanf("%d", &id); getchar();
					middle1 = t;
					while (middle1 != NULL)
					{
						if (middle1->dist == 0)
						{
							middle1 = middle1->next;
							continue;
						}
						if (middle1->tid == id)
						{
							printf("开课时间：%s\n", middle1->time);
							enquiry_course(cours, middle1->cid);
							enquiry_teacher(teach, middle1->tid);
						}
						middle1 = middle1->next;//指向下一个
					}
					break;
				case 5:
					printf("输入需要查询学生ID：");
					scanf("%d", &id); getchar();
					middle2 = s;
					middle1 = t;
					while (middle2 != NULL)
					{
						if (middle2->dist == 0)
						{
							middle2 = middle2->next;
							continue;
						}
						if (middle2->sid == id)
						{
							enquiry_student(stude, middle2->sid);
							while (middle1 != NULL)
							{
								if (middle1->dist == 0)
								{
									middle1 = middle1->next;
									continue;
								}
								if (middle2->tcid == middle1->id)
								{
									printf("开课时间：%s\n", middle1->time);
									enquiry_course(cours, middle1->cid);
									enquiry_teacher(teach, middle1->tid);
									middle1 = middle1->next;
									break;
								}
								middle1 = middle1->next;//指向下一个
							}
						}
						middle2 = middle2->next;//指向下一个
					}
					break;
				default:
					break;
				}
			}
			choose4 = 0;
			break;
		}
		default:
			break;
		}
	}
	fwrite_teacher(teach); fwrite_course(cours); fwrite_student(stude); fwrite_tc(t); fwrite_sc(s);
	return 0;
}