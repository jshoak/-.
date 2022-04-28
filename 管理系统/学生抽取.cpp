#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct information
{
	char student_number[11];	//ѧ��
	char name[21];				//����
	float grades;				//�ɼ�
	struct information* next;
}stuin, * pstuin;
//¼����Ϣ
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
		printf("����ѧ�ţ�"); scanf("%s", indirectly->student_number); getchar();
		printf("����������"); scanf("%s", indirectly->name); getchar();
		printf("----------------------------------\n");
	}
	return head;
}
//�ͷ��ڴ�ռ�
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
//��ӡ��Ϣ
void print_student(pstuin head)
{
	pstuin indirectly = head;
	while (indirectly != NULL)
	{
		printf("ѧ�ţ�%s\n", indirectly->student_number);
		printf("������%s\n", indirectly->name);
		printf("�ɼ���%f\n", indirectly->grades);
		printf("----------------------------------\n");
		indirectly = indirectly->next;		//ָ����һ��
	}
}
//����
float scoring_student(int j)
{
	float a[10], max = 0, min = 100, s = 0;
	int i = 0;
	switch (j)
	{
	case 1:
		printf("�������֣�");
		scanf("%f", &s); getchar();
		return s;
	case 2:
		for (i = 0; i < 2; i++)
		{
			printf("%d�������֣�", i + 1);
			scanf("%f", &a[i]); getchar();
			s += a[i];
		}
		return s / 2;
	default:
		for (i = 0; i < j; i++)
		{
			printf("%d�������֣�", i + 1);
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
//��ȡѧ��
void choose_student(int i, int n, pstuin* head, int j, pstuin* head_dy)
{
	while (j--)
		head_dy = &(*head_dy)->next;	//�ƶ���ĩβ
	while (i--)
		head = &(*head)->next;		//ѡ���i��ѧ��
	printf("����ѧ�ţ�%s\n", (*head)->student_number);
	(*head)->grades = scoring_student(n);
	printf("----------------------------------\n");
	*head_dy = *head;		//�����ѳ�ȡ��ѧ��
	*head = (*head)->next;		//ȥ���ѳ�ȡ��ѧ��
	(*head_dy)->next = NULL;
}
//����
void sort_student(pstuin head)
{
	pstuin indirectly = head, middle;
	stuin a;
	while (indirectly != NULL)
	{
		middle = indirectly->next;
		while (middle != NULL)
		{
			if (middle->grades > indirectly->grades)	//������Ϣ
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
//����
void save_student(pstuin head, int i, pstuin head_dy, int j, int k)
{
	FILE* fp;
	pstuin indirectly = head;
	fp = fopen("demo.txt", "wt");
	fprintf(fp, "%d\n", k);		//��ί��
	fprintf(fp, "%d\n", i);		//δ��ȡ
	while (i--){
		fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
		indirectly = indirectly->next;
	}
	indirectly = head_dy;
	int n, m;
	for (m = 1; m < 4; m++)		//��
	{
		n = ceil(j * 0.1 * m);	//����ȡ��
		j -= n;
		fprintf(fp, "%d\n", n);
		while (n--) {
			fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
			indirectly = indirectly->next;
		}
	}
	fprintf(fp, "%d\n", j);		//δ��
	while (j--) {
		fprintf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, indirectly->grades);
		indirectly = indirectly->next;
	}
	fclose(fp);
}
//��ȡ
void derived_student(pstuin *head, pstuin* head_dy, int *i, int *j, int *n)
{
	FILE* fp;
	pstuin indirectly;
	fp = fopen("demo.txt", "rt");
	int k;
	fscanf(fp, "%d\n", n);	//��ί��
	fscanf(fp, "%d\n", &k);	//δ��ȡ
	*i = k;
	while (k--){
		indirectly = (pstuin)malloc(sizeof(stuin)); indirectly->next = NULL;
		fscanf(fp, "%s\n%s\n%f\n", indirectly->student_number, indirectly->name, &indirectly->grades);
		*head = indirectly;
		head = &indirectly->next;
	}
	int m;
	for (m = 0; m < 4; m++)		//�ѳ�ȡ
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
//����ѡ��
void print()
{
	printf("     1.��һ��ʹ��\n");
	printf("     2.�ٴ�ʹ��\n");
	printf("     3.�г�δ��ȡѧ��\n");
	printf("     4.�г��ѳ�ȡѧ��\n");
	printf("     5.�˳�\n");
}
int main()
{
	int i = 0, n = 0, j = 0, choice = 0;	//i��ѧ���� n����ί�� j���ѳ�ȡ��
	char c = 0;
	pstuin head = NULL, head_dy = NULL;
	print();
	while (choice != 5)
	{
		printf("����ѡ�"); scanf("%d", &choice); getchar();
		system("cls");
		print();
		switch (choice)
		{
		case 1:
		{
			printf("����ѧ������"); scanf("%d", &i); getchar();
			printf("������ί����"); scanf("%d", &n); getchar();
			srand((unsigned)time(NULL));	//���������
			head = inputting_student(i);
			for (j; j < i && c != 'q'; j++)
			{
				choose_student(rand() % (i - j), n, &head, j, &head_dy);
				printf("���س����������롮q���˳���");
				c = getchar();
			}
			sort_student(head_dy);					//����󱣴�
			save_student(head, i - j, head_dy, j, n);
			break;
		}
		case 2:
		{
			free_student(head);
			free_student(head_dy);
			derived_student(&head, &head_dy, &i, &j, &n);
			i += j;
			srand((unsigned)time(NULL));	//���������
			for (j; j < i && c != 'q'; j++)
			{
				choose_student(rand() % (i - j), n, &head, j, &head_dy);
				printf("���س����������롮q���˳���");
				c = getchar();
			}
			sort_student(head_dy);					//����󱣴�
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
	printf("���˳�");
	return 0;
}