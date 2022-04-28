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
	int rpos[MAXRC + 1];//各行第一个非零元所在的位置
	int rows;
	int cols;
	int nums;
}RLSMatrix;
 
void CreateRLSM(RLSMatrix &M)
{
	int t;
	Triple T;
	bool k;
	cout << "请输入矩阵的行数,列数,非零元素数：";
	cin >> M.rows >> M.cols >> M.nums;
	M.data[0].i = 0; //为计算rpos[]做准备
	for (t = 1; t <= M.nums; ++t)
	{
		do
		{
			cout << "请按行序顺序输入第" << t << "个非零元素所在的行,列,元素值：";
			cin >> T.i >> T.j >> T.e;
			k = false;
			if (T.i<1 || T.i>M.rows || T.j<1 || T.j>M.cols)// 行、列超出范围
				k = true;
			if (T.i < M.data[t - 1].i || T.i == M.data[t - 1].i&&T.j <= M.data[t - 1].j)// 没有按顺序输入非零元素
				k = true;
		} while (k);
		M.data[t] = T;
	}
	for (t = 1; t <= M.nums; ++t)// 计算rpos[]
	{
		if (M.data[t].i > M.data[t - 1].i)
		{
			for (T.i = 0; T.i <M.data[t].i - M.data[t - 1].i; T.i++)
				M.rpos[M.data[t].i - T.i] = t;
		}
	}
	for (t = M.data[M.nums].i + 1; t <= M.rows; ++t) // 给最后没有非零元素的几行赋值
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
	M.rpos[M.rows + 1] = M.nums + 1;// 为方便后面的while循环临时设置
	N.rpos[N.rows + 1] = N.nums + 1;
	for (k = 1; k <= M.rows; ++k)// 对于每一行，k指示行号
	{
		Q.rpos[k] = Q.nums + 1;
		p = M.rpos[k];// p指示M矩阵第k行当前元素的序号
		q = N.rpos[k];// q指示N矩阵第k行当前元素的序号
		while (p < M.rpos[k + 1] && q < N.rpos[k + 1])
		{// M,N矩阵均有第k行元素未处理
			if (M.data[p].j == N.data[q].j)
			{// M矩阵当前元素和N矩阵当前元素的列相同
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
			{ // M矩阵当前元素的列<N矩阵当前元素的列
				++Q.nums;
				Q.data[Q.nums].e = M.data[p].e;
				Q.data[Q.nums].i = k;
				Q.data[Q.nums].j = M.data[p].j;
				++p;
			}
			else
			{// M矩阵当前元素的列>N矩阵当前元素的列
				++Q.nums;
				Q.data[Q.nums].e = N.data[q].e;
				Q.data[Q.nums].i = k;
				Q.data[Q.nums].j = N.data[q].j;
				++q;
			}
		}
		while (p < M.rpos[k + 1])
		{// M矩阵还有k行的元素未处理
			++Q.nums;
			Q.data[Q.nums].e = M.data[q].e;
			Q.data[Q.nums].i = k;
			Q.data[Q.nums].j = M.data[q].j;
			++p;
		}
		while (q < N.rpos[k + 1])
		{// N矩阵还有k行的元素未处理
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
	if (M.nums*N.nums)//M,N都是非零矩阵
	{
		for (arow = 1; arow <= M.rows; ++arow)
		{//从M的第一行开始到最后一行,arow是M的当前行
			for (ccol = 1; ccol <= Q.cols; ++ccol)
				ctemp[ccol] = 0; // Q的当前行的各列元素累加器清零
			Q.rpos[arow] = Q.nums + 1; // Q当前行的第1个元素位于上1行最后1个元素之后
			for (p = M.rpos[arow]; p < M.rpos[arow + 1]; ++p)
			{
				brow = M.data[p].j;// 找到对应元在N中的行号(M当前元的列号)
				for (q = N.rpos[brow]; q < N.rpos[brow + 1]; ++q)
				{
					ccol = N.data[q].j; // 乘积元素在Q中列号
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				}
			}// 求得Q中第arow行的非零元
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
{//打印矩阵
	int t;
	cout << "矩阵为:" << endl;
	cout << "元素的行数  " << "元素的列数  " << "内容" << endl;
	for (t = 1; t <= M.nums; ++t)
	{		
		cout << setw(8) << M.data[t].i << setw(8) << M.data[t].j
			<< setw(11) << M.data[t].e << endl;
	}
	for (t = 1; t <= M.rows; ++t)
		cout << "第" << t << "行的第一个非零元素是本矩阵第" << M.rpos[t] << "个元素"<<endl;
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