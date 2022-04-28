#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef struct information
{
	int coef;//系数
	int expn;//指数
	bool k;
	information* next;
}inf, * pinf;

void addr_informf(pinf* head, int coef, int expn)
{
	pinf middle;
	middle = new inf[sizeof(inf)]();
	middle->coef = coef;
	middle->expn = expn;
	middle->k = 1;
	middle->next = NULL;
	middle->next = *head;
	*head = middle;
}

void free_informf(pinf head)
{
	pinf middle = head, p;
	while (middle != NULL)
	{
		p = middle->next;
		delete middle;
		middle = p;
	}
}

void print_informf(pinf head)
{
	pinf middle = head;
	while (middle != NULL)
	{
		if (middle->coef > 0)
			printf("+");
		if (middle->coef == 0)
		{
			middle = middle->next;
			continue;
		}
		if (middle->expn == 0)
		{
			printf("%d ", middle->coef);
			middle = middle->next;
			continue;
		}
		printf("%dx^%d ", middle->coef, middle->expn);
		middle = middle->next;
	}
	printf("\n\n");
}

//重置标记
void res(pinf head)
{
	while (head != NULL)
	{
		head->k = 1;
		head = head->next;
	}
}

//合并
pinf mer(pinf nu)
{
	res(nu);
	pinf middle1 = nu, middle2 = nu;
	pinf head = NULL;
	while (middle2 != NULL)
	{
		if (middle2->k == 0)
		{
			middle2 = middle2->next;
			continue;
		}
		middle1 = middle2->next;
		while (middle1 != NULL)
		{
			if (middle1->k == 1 && middle2->expn == middle1->expn)
			{
				middle2->coef += middle1->coef;
				middle1->k = 0;
				middle2->k = 0;
			}
			middle1 = middle1->next;
		}
		if (middle2->k == 0)
			addr_informf(&head, middle2->coef, middle2->expn);		
		middle2 = middle2->next;
	}
	middle1 = nu;
	while (middle1 != NULL)
	{
		if (middle1->k == 1)
			addr_informf(&head, middle1->coef, middle1->expn);
		middle1 = middle1->next;
	}
	return head;
}

//加法
pinf add(pinf nu1, pinf nu2)
{
	res(nu1); res(nu2);
	pinf middle = nu2;
	pinf head = NULL;
	while (nu1 != NULL)
	{
		middle = nu2;
		while (middle != NULL)
		{
			if (middle->k == 1 && nu1->expn == middle->expn)
			{
				addr_informf(&head, nu1->coef + middle->coef, nu1->expn);
				middle->k = 0;
				nu1->k = 0;
				break;
			}
			middle = middle->next;
		}
		if (nu1->k == 1)
			addr_informf(&head, nu1->coef, nu1->expn);
		nu1 = nu1->next;
	}
	middle = nu2;
	while (middle != NULL)
	{
		if (middle->k == 1)
			addr_informf(&head, middle->coef, middle->expn);
		middle = middle->next;
	}
	return head;
}

//减法
pinf sub(pinf nu1, pinf nu2)
{
	res(nu1); res(nu2);
	pinf middle = nu2;
	pinf head = NULL;
	while (nu1 != NULL)
	{
		middle = nu2;
		while (middle != NULL)
		{
			if (middle->k == 1 && nu1->expn == middle->expn)
			{
				addr_informf(&head, nu1->coef - middle->coef, nu1->expn);
				middle->k = 0;
				nu1->k = 0;
				break;
			}
			middle = middle->next;
		}
		if (nu1->k == 1)
			addr_informf(&head, nu1->coef, nu1->expn);
		nu1 = nu1->next;
	}
	middle = nu2;
	while (middle != NULL)
	{
		if (middle->k == 1)
			addr_informf(&head, middle->coef * -1, middle->expn);
		middle = middle->next;
	}
	return head;
}

//乘法
pinf mul(pinf nu1, pinf nu2)
{
	pinf head1 = NULL;
	pinf middle = nu2;
	while (nu1 != NULL)
	{
		middle = nu2;
		while (middle != NULL)
		{
			addr_informf(&head1, middle->coef * nu1->coef, middle->expn + nu1->expn);
			middle = middle->next;
		}
		nu1 = nu1->next;
	}
	pinf head2 = mer(head1);
	free_informf(head1);
	return head2;
}

int main()
{
	pinf A = NULL;
	addr_informf(&A, 78, 300);
	addr_informf(&A, -102, 100);
	addr_informf(&A, 52, 70);
	addr_informf(&A, -73, 60);
	addr_informf(&A, 12, 20);
	addr_informf(&A, -8, 5);
	addr_informf(&A, 7, 0);
	printf("多项式A：");
	print_informf(A);

	pinf B = NULL;
	addr_informf(&B, 29, 400);
	addr_informf(&B, -46, 120);
	addr_informf(&B, -36, 70);
	addr_informf(&B, 73, 50);
	addr_informf(&B, -82, 30);
	addr_informf(&B, 15, 7);
	addr_informf(&B, 4, 0);
	printf("多项式B：");
	print_informf(B);

	pinf C = NULL;
	addr_informf(&C, -335, 700);
	addr_informf(&C, -246, 120);
	addr_informf(&C, -316, 100);
	addr_informf(&C, 513, 70);
	addr_informf(&C, -32, 40);
	addr_informf(&C, -25, 20);
	addr_informf(&C, -18, 7);
	addr_informf(&C, -7, 5);
	addr_informf(&C, 34, 0);
	printf("多项式C：\n");
	print_informf(C);

	printf("多项式A + B：\n");
	pinf head1 = add(A, B);
	print_informf(head1);

	printf("多项式A - B：\n");
	pinf head2 = sub(A, B);
	print_informf(head2);

	printf("多项式A * B：\n");
	pinf head3 = mul(A, B);
	print_informf(head3);

	printf("多项式A * B - C：\n");
	pinf head4 = sub(head3, C);
	print_informf(head4);

	free_informf(A);
	free_informf(B);
	free_informf(head1);
	free_informf(head2);
	free_informf(head3);
	free_informf(head4);
    return 0;
}