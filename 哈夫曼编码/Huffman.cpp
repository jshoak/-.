// ConsoleApplication6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
using namespace std;
#define   infinity       10
//哈夫曼树结点结构
typedef struct 
{
    int weight;//结点权重
    int parent, left, right;//父结点、左孩子、右孩子在数组中的位置下标
}HTNode, * HuffmanTree;

int min(HuffmanTree p, int parent)
{
    int j = 99999, k = 0;
    for (int i = 0; p[i].weight != 0; i++)
    {
        if (p[i].weight < j && p[i].parent == 0)
        {
            j = p[i].weight;
            k = i;
        }
    }
    p[k].parent = parent;
    return k;
}

void hfmtree(HuffmanTree p, int n/*叶子数*/, int m/*总节点数*/)
{
    for (int i = n; i < m; i++)
    {
        p[i].left = min(p, i);
        p[i].right = min(p, i);
        p[i].weight = p[p[i].left].weight + p[p[i].right].weight;
    }
}

void table(HuffmanTree p, int n, char** t)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < n; i++)
    {
        j = i;
        for (k = infinity - 1; p[j].parent != 0; k--)
        {
            if (p[p[j].parent].left == j)//子节点与父节点比较判断左右
                t[i][k] = 0;
            else
                t[i][k] = 1;
            j = p[j].parent;
        }
        t[i][k] = infinity - k - 1;
    }
}

void print(int* alphabet,/*实际存在多少种字母*/ char** t, int m)//打印编码
{
    printf("哈弗曼编码：\n");
    int i = 0, j = 0, k = 0;
    for (i = 0; i < m; i++)
    {
        printf("(%c)", alphabet[i] + 65);
        for (j = 0; t[i][j] == 0; j++); j += 1;
        printf("%d)", t[i][j - 1]);
        for (k = j; k < infinity; k++)
            printf("%d", t[i][k]);
        printf("\n");
    }
}

int charnumber(int* alphabet, char c, int n)
{
    for (int i = 0; i < n; i++)
        if (alphabet[i] == c - 65)return i;
    return -1;
}

int quan(int* alphabet, int n, char* in, int number, char** t)
{
    int mm = 0, num = 0;
    int i = 0, j = 0;
    for (i = 0; i < number; i++)
    {
        num = charnumber(alphabet, in[i], n);
        for (j = 0; t[num][j] == 0; j++);
        mm += t[num][j];
    }
    return mm;
}

void t(int* alphabet, int n, char* in, int number, char* out, char** t)//编码
{
    int mm = 0, num = 0;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < number; i++)
    {
        num = charnumber(alphabet, in[i], n);
        for (j = 0; t[num][j] == 0; j++); j += 1;
        for (k = j; k < infinity; k++)
            out[mm++] = t[num][k];
    }
}

void ft(int* alphabet, int n, char* in, int number, char* out, char** t)//解码
{
    int mm = 0, num = 0;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < number;)
    {
        for (k = 0; k < n; k++)
        {
            for (j = 0; t[k][j] == 0; j++); j += 1;
            num = memcmp(&in[i], &t[k][j], t[k][j - 1]);
            if (num == 0)
            {
                i += t[k][j - 1];
                out[mm++] = alphabet[k] + 65;
            }
        }   
    }
}

unsigned ezs(char* s)//二转十
{
    unsigned char mm = 0;
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        mm += s[i] * (unsigned char)pow(2, 7 - i);
    }
    return mm;
}

void sze(unsigned char n, char* s)//十转二
{
    int i = 0;
    for (i = 7; i > -1; i--)
    {
        s[i] = n % 2;
        n = n / 2;
    }
}

int readtxt(char** s, int* alphabet)
{
    ifstream srcFile("hfm.txt", ios::in); //以文本模式打开in.txt备读
    int i = 0;
    srcFile >> i;
    *s = new char[i];
    for (int j = 0; j < i; j++)
    {
        srcFile >> (*s)[j];
        alphabet[(*s)[j] - 65]++;
    }
    srcFile.close();
    return i;
}

void writedat(char* ss, int m)
{

    char n[8] = { 0 };
    int nu = m / 8;
    unsigned char c = m % 8;
    ofstream outFile("hfm.dat", ios::out | ios::binary);
    outFile.write((char*)&nu, sizeof(int));
    outFile.write((char*)&c, sizeof(char));
    int i = 0;
    for (i = 0; i < (m / 8) * 8; i += 8)
    {
        c = ezs(&ss[i]);
        outFile.write((char*)&c, sizeof(char));
    }
    if (m % 8 != 0)
    {
        memmove(n, &ss[i], m % 8);
        c = ezs(n);
        outFile.write((char*)&c, sizeof(char));
    }
    outFile.close();
}

void readdata(char *ss)
{
    printf("读取二进制文件\n");
    int i = 0, nu = 0;;
    char n[8] = { 0 };
    unsigned char c = 0, c1 = 0;
    ifstream inFile("hfm.dat", ios::in | ios::binary); //二进制读方式打开
    inFile.read((char*)&nu, sizeof(int));
    inFile.read((char*)&c1, sizeof(char));
    while (nu--)
    {
        inFile.read((char*)&c, sizeof(char));
        sze(c, n);
        for (int j = 0; j < 8; j++)
        {
            ss[i++] = n[j];
            printf("%d", n[j]);
        }
    }
    inFile.read((char*)&c, sizeof(char));
    sze(c, n);
    for (int j = 0; j < c1; j++)
    {
        ss[i++] = n[j];
        printf("%d", n[j]);
    }
    printf("\n--------------\n");
}

int main()
{
    char *s = NULL;//文本
    int alphabet[26] = { 0 };
    int number = readtxt(&s, alphabet);
    int n = 0;////实际存在多少种字母
    for (int i = 0; i < 26; i++)
        if (alphabet[i] != 0)n++;

    char** tab = new char* [n]();//编码表
    for (int i = 0; i < n; i++)
        tab[i] = new char[infinity]();

    int* c = new int[n]();//实际存在多少种字母
    for (int i = 0, j = 0; i < 26; i++)
        if (alphabet[i] != 0)c[j++] = i;

    HuffmanTree p = new HTNode[n * 2 - 1]();
    for (int i = 0; i < n; i++)
    {
        p[i].weight = alphabet[c[i]];
        p[i].left = -1;
        p[i].right = -1;
    }

    printf("编码前文本：\n");
    for (int i = 0; i < number; i++)
        printf("%c", s[i]);
    printf("\n--------------\n");
    hfmtree(p, n, n * 2 - 1);
    table(p, n, tab);
    print(c, tab, n);
    printf("--------------\n");

    int m = quan(c, n, s, number, tab);
    char* ss = new char[m]();//编码后
    char* ss1 = new char[number]();//解码后

    t(c, n, s, number, ss, tab);
    printf("编码后文本：\n");
    for (int i = 0; i < m; i++)
        printf("%d", ss[i]);
    printf("\n--------------\n");
    writedat(ss, m);//生成二进制文件

    memset(ss, 0, m);//编码清零
    readdata(ss);

    ft(c, n, ss, m, ss1, tab);
    printf("解码后文本：\n");
    for (int i = 0; i < number; i++)
        printf("%c", ss1[i]);
    printf("\n");

    delete[] p;
    for (int i = 0; i < n; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
    delete[] c;
    delete[] ss;
    delete[] ss1;
    delete[] s;
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
