#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct teacher {
	unsigned int id;//��ʦ��
	char name[11];//����
	char sex[3];//�Ա�
	char background[11];//ѧ��
	unsigned int age;//����
	char phone[12];//�绰
	bool dist;//���
	struct teacher* next;
}tea, * ptea;

typedef struct course {
	unsigned int id;//�γ̺�
	char name[11];//�γ�����
	bool dist;//���
	struct course* next;
}cou, * pcou;

typedef struct tc {
	unsigned int id;//�̿κ�
	char time[11];//����ʱ��
	unsigned int tid;//��ʦ��
	unsigned int cid;//�γ̺�
	bool dist;//���
	struct tc* next;
}tc_, * ptc_;

typedef struct student {
	unsigned int id;//ѧ��
	char name[11];//����
	bool dist;//���
	struct student* next;
}stu, * pstu;

typedef struct sc{
	unsigned int id;//ѧ�κ�
	unsigned int sid;//ѧ��
	unsigned int tcid;//�̿κ�
	bool dist;//���
	struct sc* next;
}sc_, * psc_;

void show_teacher(ptea middle)
{
	printf("��ʦ�ţ�%d\n", middle->id);
	printf("������%s\n", middle->name);
	printf("�Ա�%s\n", middle->sex);
	printf("ѧ����%s\n", middle->background);
	printf("���䣺%d\n", middle->age);
	printf("�绰��%s\n", middle->phone);
	printf("---------------------------------------------\n");
}
void add_teacher(ptea* head)//��ӽ�ʦ��Ϣ
{
	ptea middle;
	middle = (ptea)malloc(sizeof(tea));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("�����ʦ�ţ�"); scanf("%d", &middle->id); getchar();
	printf("����������"); scanf("%s", middle->name); getchar();
	printf("�����Ա�"); scanf("%s", middle->sex); getchar();
	printf("����ѧ����"); scanf("%s", middle->background); getchar();
	printf("�������䣺"); scanf("%d", &middle->age); getchar();
	printf("����绰��"); scanf("%s", middle->phone); getchar();
}
int del_teacher(ptea head)//�߼�ɾ��
{
	unsigned int id;
	printf("������Ҫɾ����ʦ�ţ�");
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
	printf("δ�ҵ�\n");
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
void print_teacher(ptea head)//��ʾ��ʦ��Ϣ
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_teacher(head);
		head = head->next;//ָ����һ��
	}
}
int enquiry_teacher(ptea head, unsigned int id)//��ѯ��Ϣ
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
	printf("δ�ҵ�\n");
	return 0;
}
int fread_teacher(ptea *head)//��ȡ��ʦ��Ϣ
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
int fwrite_teacher(ptea head)//д���ʦ��Ϣ
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
		head = head->next;					//ָ����һ��
	}
	fclose(fp);
	return 1;
}

void show_course(pcou middle)
{
	printf("�γ̺ţ�%d\n", middle->id);
	printf("�γ����ƣ�%s\n", middle->name);
	printf("---------------------------------------------\n");
}
void add_course(pcou* head)//�����Ϣ
{
	pcou middle;
	middle = (pcou)malloc(sizeof(cou));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("����γ̺ţ�"); scanf("%d", &middle->id); getchar();
	printf("����γ����ƣ�"); scanf("%s", middle->name); getchar();
}
int del_course(pcou head)//�߼�ɾ��
{
	unsigned int id;
	printf("������Ҫɾ���γ̺ţ�");
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
	printf("δ�ҵ�\n");
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
void print_course(pcou head)//��ʾ��Ϣ
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_course(head);
		head = head->next;//ָ����һ��
	}
}
int enquiry_course(pcou head, unsigned int id)//��ѯ��Ϣ
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
	printf("δ�ҵ�\n");
	return 0;
}
int fread_course(pcou* head)//��ȡ��Ϣ
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
int fwrite_course(pcou head)//д����Ϣ
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
		head = head->next;					//ָ����һ��
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
		printf("����ʱ�䣺%s\n", head->time);
		enquiry_course(head1,head->cid);
		enquiry_teacher(head2, head->tid);
		head = head->next;//ָ����һ��
	}
}
void add_tc(ptc_* head)//�����Ϣ
{
	ptc_ middle;
	middle = (ptc_)malloc(sizeof(tc_));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("����̿κţ�"); scanf("%d", &middle->id); getchar();
	printf("���뿪��ʱ�䣺"); scanf("%s", middle->time); getchar();
	printf("�����ʦ�ţ�"); scanf("%d", &middle->tid); getchar();
	printf("����γ̺ţ�"); scanf("%d", &middle->cid); getchar();
}
int del_tc(ptc_ head)//�߼�ɾ��
{
	unsigned int id;
	printf("������Ҫɾ���̿κţ�");
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
	printf("δ�ҵ�\n");
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
int fread_tc(ptc_* head)//��ȡ��Ϣ
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
int fwrite_tc(ptc_ head)//д����Ϣ
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
		head = head->next;					//ָ����һ��
	}
	fclose(fp);
	return 1;
}

void show_student(pstu middle)
{
	printf("ѧ�ţ�%d\n", middle->id);
	printf("������%s\n", middle->name);
	printf("---------------------------------------------\n");
}
void add_student(pstu* head)//�����Ϣ
{
	pstu middle;
	middle = (pstu)malloc(sizeof(stu));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("����ѧ�ţ�"); scanf("%d", &middle->id); getchar();
	printf("����������"); scanf("%s", middle->name); getchar();
}
int del_student(pstu head)//�߼�ɾ��
{
	unsigned int id;
	printf("������Ҫɾ��ѧ�ţ�");
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
	printf("δ�ҵ�\n");
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
void print_student(pstu head)//��ʾ��Ϣ
{
	while (head != NULL)
	{
		if (head->dist == 0)
		{
			head = head->next;
			continue;
		}
		show_student(head);
		head = head->next;//ָ����һ��
	}
}
int enquiry_student(pstu head, unsigned int id)//��ѯ��Ϣ
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
	printf("δ�ҵ�\n");
	return 0;
}
int fread_student(pstu* head)//��ȡ��Ϣ
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
int fwrite_student(pstu head)//д����Ϣ
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
		head = head->next;					//ָ����һ��
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
				printf("����ʱ�䣺%s\n", middle->time);
				enquiry_course(head3, middle->cid);
				enquiry_teacher(head4, middle->tid);
				head = head->next;
				break;
			}
			middle = middle->next;//ָ����һ��
		}
		middle = head2;
		head = head->next;//ָ����һ��
	}
}
void add_sc(psc_* head)//�����Ϣ
{
	psc_ middle;
	middle = (psc_)malloc(sizeof(sc_));
	middle->next = NULL;
	middle->dist = 1;
	middle->next = *head;
	*head = middle;
	printf("����ѧ�κţ�"); scanf("%d", &middle->id); getchar();
	printf("����ѧ�ţ�"); scanf("%d", &middle->sid); getchar();
	printf("����̿κţ�"); scanf("%d", &middle->tcid); getchar();
}
int del_sc(psc_ head)//�߼�ɾ��
{
	unsigned int id;
	printf("������Ҫɾ��ѧ�κţ�");
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
	printf("δ�ҵ�\n");
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
int fread_sc(psc_* head)//��ȡ��Ϣ
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
int fwrite_sc(psc_ head)//д����Ϣ
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
		head = head->next;					//ָ����һ��
	}
	fclose(fp);
	return 1;
}

void menu()
{
	printf("**********************************\n");
	printf("1.��Ϣ���\n");
	printf("2.��Ϣ���\n");
	printf("3.��Ϣɾ��\n");
	printf("4.��Ϣ��ѯ\n");
	printf("5.�˳�\n");
	printf("**********************************\n");
}
void menu1()
{
	printf("**********************************\n");
	printf("1.��ʦ��Ϣ���\n");
	printf("2.ѧ����Ϣ���\n");
	printf("3.�γ���Ϣ���\n");
	printf("4.��ʦ��γ̹�����Ϣ���\n");
	printf("5.ѧ����γ̹�����Ϣ���\n");
	printf("6.�˳�\n");
	printf("**********************************\n");
}
void menu2()
{
	printf("**********************************\n");
	printf("1.��ʦ��Ϣ���\n");
	printf("2.ѧ����Ϣ���\n");
	printf("3.�γ���Ϣ���\n");
	printf("4.��ʦ��γ̹�����Ϣ���\n");
	printf("5.ѧ����γ̹�����Ϣ���\n");
	printf("6.�˳�\n");
	printf("**********************************\n");
}
void menu3()
{
	printf("**********************************\n");
	printf("1.��ʦ��Ϣɾ��\n");
	printf("2.ѧ����Ϣɾ��\n");
	printf("3.�γ���Ϣɾ��\n");
	printf("4.��ʦ��γ̹�����Ϣɾ��\n");
	printf("5.ѧ����γ̹�����Ϣɾ��\n");
	printf("6.�˳�\n");
	printf("**********************************\n");
}
void menu4()
{
	printf("**********************************\n");
	printf("1.��ʦ��Ϣ��ѯ\n");
	printf("2.ѧ����Ϣ��ѯ\n");
	printf("3.�γ���Ϣ��ѯ\n");
	printf("4.��ʦ��γ̹�����Ϣ��ѯ\n");
	printf("5.ѧ����γ̹�����Ϣ��ѯ\n");
	printf("6.�˳�\n");
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
		printf("����ѡ�"); scanf("%d", &choose); getchar();
		system("cls");
		switch (choose)
		{
		case 1:
		{
			while (choose1 != 6)
			{
				menu1();
				printf("����ѡ�"); scanf("%d", &choose1); getchar();
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
				printf("����ѡ�"); scanf("%d", &choose2); getchar();
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
				printf("����ѡ�"); scanf("%d", &choose3); getchar();
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
				printf("����ѡ�"); scanf("%d", &choose4); getchar();
				system("cls");
				switch (choose4)
				{
				case 1:
					printf("������Ҫ��ѯID��");
					scanf("%d", &id); getchar();
					enquiry_teacher(teach, id);
					break;
				case 2:
					printf("������Ҫ��ѯID��");
					scanf("%d", &id); getchar();
					enquiry_student(stude, id);
					break;
				case 3:
					printf("������Ҫ��ѯID��");
					scanf("%d", &id); getchar();
					enquiry_course(cours, id);
					break;
				case 4:
					printf("������Ҫ��ѯ��ʦID��");
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
							printf("����ʱ�䣺%s\n", middle1->time);
							enquiry_course(cours, middle1->cid);
							enquiry_teacher(teach, middle1->tid);
						}
						middle1 = middle1->next;//ָ����һ��
					}
					break;
				case 5:
					printf("������Ҫ��ѯѧ��ID��");
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
									printf("����ʱ�䣺%s\n", middle1->time);
									enquiry_course(cours, middle1->cid);
									enquiry_teacher(teach, middle1->tid);
									middle1 = middle1->next;
									break;
								}
								middle1 = middle1->next;//ָ����һ��
							}
						}
						middle2 = middle2->next;//ָ����һ��
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