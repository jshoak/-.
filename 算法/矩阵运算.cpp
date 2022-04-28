#include<iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 100
#define MAXRC 20
typedef int ElemType;
typedef struct Triple
{
	int i;
	int j;
	ElemType e;
}Triple;
typedef struct RLSMatrix
{
	Triple data[MAXSIZE];
	int rpos[MAXRC + 1];//���е�һ������Ԫ���ڵ�λ��
	int rows;
	int cols;
	int nums;
}RLSMatrix;
 
void CreateRLSM(RLSMatrix &M)
{
	int t;
	Triple T;
	bool k;
	cout << "��������������,����,����Ԫ������";
	cin >> M.rows >> M.cols >> M.nums;
	M.data[0].i = 0; //Ϊ����rpos[]��׼��
	for (t = 1; t <= M.nums; ++t)
	{
		do
		{
			cout << "�밴����˳�������" << t << "������Ԫ�����ڵ���,��,Ԫ��ֵ��";
			cin >> T.i >> T.j >> T.e;
			k = false;
			if (T.i<1 || T.i>M.rows || T.j<1 || T.j>M.cols)// �С��г�����Χ
				k = true;
			if (T.i < M.data[t - 1].i || T.i == M.data[t - 1].i&&T.j <= M.data[t - 1].j)// û�а�˳���������Ԫ��
				k = true;
		} while (k);
		M.data[t] = T;
	}
	for (t = 1; t <= M.nums; ++t)// ����rpos[]
	{
		if (M.data[t].i > M.data[t - 1].i)
		{
			for (T.i = 0; T.i <M.data[t].i - M.data[t - 1].i; T.i++)
				M.rpos[M.data[t].i - T.i] = t;
		}
	}
	for (t = M.data[M.nums].i + 1; t <= M.rows; ++t) // �����û�з���Ԫ�صļ��и�ֵ
		M.rpos[t] = M.nums + 1;
}
 
void DestroyRLSM(RLSMatrix &M)
{
	M.rows = 0;
	M.cols = 0;
	M.nums = 0;
}
 
void CopyRLSM(RLSMatrix M, RLSMatrix &N)
{
	N = M;
}
 
void TransRLSM(RLSMatrix M, RLSMatrix &N)
{
	int p, q, t, col, *num;
	num = new int[M.cols + 1];
	N.cols = M.rows;
	N.rows = M.cols;
	N.nums = M.nums;
	if (N.nums)
	{
		for (col = 1; col <= M.cols; ++col)
			num[col] = 0;
		for (t = 1; t <= M.nums; ++t)
			++num[M.data[t].j];
		N.rpos[1] = 1;
		for (col = 2; col <= M.cols; ++col)
			N.rpos[col] = N.rpos[col - 1] + num[col - 1];
		for (col = 1; col <= M.cols; ++col)
			num[col] = N.rpos[col];
		for (p = 1; p <= M.nums; ++p)
		{
			col = M.data[p].j;
			q = num[col];
			N.data[q].i = M.data[p].j;
			N.data[q].j = M.data[p].i;
			N.data[q].e = M.data[p].e;
			++num[col];
		}
	}
	delete[]num;
}
 
bool AddRLSM(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
	int k, p, q;
	if (M.rows != N.rows || M.cols != N.cols)
		return false;
	Q.rows = M.rows;
	Q.cols = M.cols;
	Q.nums = 0;
	M.rpos[M.rows + 1] = M.nums + 1;// Ϊ��������whileѭ����ʱ����
	N.rpos[N.rows + 1] = N.nums + 1;
	for (k = 1; k <= M.rows; ++k)// ����ÿһ�У�kָʾ�к�
	{
		Q.rpos[k] = Q.nums + 1;
		p = M.rpos[k];// pָʾM�����k�е�ǰԪ�ص����
		q = N.rpos[k];// qָʾN�����k�е�ǰԪ�ص����
		while (p < M.rpos[k + 1] && q < N.rpos[k + 1])
		{// M,N������е�k��Ԫ��δ����
			if (M.data[p].j == N.data[q].j)
			{// M����ǰԪ�غ�N����ǰԪ�ص�����ͬ
				Q.data[Q.nums + 1].e = M.data[p].e + N.data[q].e;
				if (Q.data[Q.nums + 1].e)
				{
					++Q.nums;
					Q.data[Q.nums].i = k;
					Q.data[Q.nums].j = M.data[p].j;
				}
				++p;
				++q;
			}
			else if (M.data[p].j < N.data[q].j)
			{ // M����ǰԪ�ص���<N����ǰԪ�ص���
				++Q.nums;
				Q.data[Q.nums].e = M.data[p].e;
				Q.data[Q.nums].i = k;
				Q.data[Q.nums].j = M.data[p].j;
				++p;
			}
			else
			{// M����ǰԪ�ص���>N����ǰԪ�ص���
				++Q.nums;
				Q.data[Q.nums].e = N.data[q].e;
				Q.data[Q.nums].i = k;
				Q.data[Q.nums].j = N.data[q].j;
				++q;
			}
		}
		while (p < M.rpos[k + 1])
		{// M������k�е�Ԫ��δ����
			++Q.nums;
			Q.data[Q.nums].e = M.data[q].e;
			Q.data[Q.nums].i = k;
			Q.data[Q.nums].j = M.data[q].j;
			++p;
		}
		while (q < N.rpos[k + 1])
		{// N������k�е�Ԫ��δ����
			++Q.nums;
			Q.data[Q.nums].e = N.data[q].e;
			Q.data[Q.nums].i = k;
			Q.data[Q.nums].j = N.data[q].j;
			++q;
		}
	}
	return true;
}
 
bool SubtractRLSM(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
	int t;
	if (M.rows != N.rows || M.cols != N.cols)
		return false;
	for (t = 1; t <= N.nums; ++t)
		N.data[t].e *= -1;
	AddRLSM(M, N, Q);
	return true;
}
 
bool MultiplyRLSM(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
	int arow, brow, p, q, ccol, ctemp[MAXRC + 1];
	if (M.cols != N.rows)
		return false;
	Q.rows = M.rows;
	Q.cols = N.cols;
	Q.nums = 0;
	M.rpos[M.rows + 1] = M.nums + 1;
	N.rpos[N.rows + 1] = N.nums + 1;
	if (M.nums*N.nums)//M,N���Ƿ������
	{
		for (arow = 1; arow <= M.rows; ++arow)
		{//��M�ĵ�һ�п�ʼ�����һ��,arow��M�ĵ�ǰ��
			for (ccol = 1; ccol <= Q.cols; ++ccol)
				ctemp[ccol] = 0; // Q�ĵ�ǰ�еĸ���Ԫ���ۼ�������
			Q.rpos[arow] = Q.nums + 1; // Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮��
			for (p = M.rpos[arow]; p < M.rpos[arow + 1]; ++p)
			{
				brow = M.data[p].j;// �ҵ���ӦԪ��N�е��к�(M��ǰԪ���к�)
				for (q = N.rpos[brow]; q < N.rpos[brow + 1]; ++q)
				{
					ccol = N.data[q].j; // �˻�Ԫ����Q���к�
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				}
			}// ���Q�е�arow�еķ���Ԫ
			for (ccol = 1; ccol <= Q.cols; ++ccol)
			{
				if (ctemp[ccol])
				{
					if (++Q.nums > MAXSIZE)
						return false;
					Q.data[Q.nums].i = arow;
					Q.data[Q.nums].j = ccol;
					Q.data[Q.nums].e = ctemp[ccol];
				}
			}
		}
	}
	return true;
}
 
void PrintRLSM(RLSMatrix M)
{//��ӡ����
	int t;
	cout << "����Ϊ:" << endl;
	cout << "Ԫ�ص�����  " << "Ԫ�ص�����  " << "����" << endl;
	for (t = 1; t <= M.nums; ++t)
	{		
		cout << setw(8) << M.data[t].i << setw(8) << M.data[t].j
			<< setw(11) << M.data[t].e << endl;
	}
	for (t = 1; t <= M.rows; ++t)
		cout << "��" << t << "�еĵ�һ������Ԫ���Ǳ������" << M.rpos[t] << "��Ԫ��"<<endl;
}
 
int main(void)
{
	RLSMatrix M,N,Q;
	CreateRLSM(M);
	PrintRLSM(M);
	CreateRLSM(N);
	PrintRLSM(N);
	SubtractRLSM(M, N, Q);
	PrintRLSM(Q);
	return(0);
}