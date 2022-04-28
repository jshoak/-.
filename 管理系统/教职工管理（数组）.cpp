#include <iostream>
#include <fstream>
using namespace std;
#define m 3         //教职工人数
#define k "     "
typedef struct information
{
    int title_number;	    //职工号
    char name[10];			//姓名
    char title[20];		    //职称
    char sex[3];            //性别
    char courses1[10];      //课程1
    char courses2[10];      //课程2
    char courses3[10];      //课程3
    double scoring;         //评分
}teacher, * pteacher;
//写入文件
void infile(pteacher tea)
{
    ofstream destFile("out.txt", ios::out);
    destFile << "职工号" << k << "姓名" << k << "职称" << k << "课程1" << k << "课程2" << k << "课程3" << k << "评分\n";
    for (int i = 0; i < m; i++)
    {
        destFile << tea[i].title_number << ' ';
        destFile << tea[i].name << ' ';
        destFile << tea[i].title << ' ';
        destFile << tea[i].sex << ' ';
        destFile << tea[i].courses1 << ' ';
        destFile << tea[i].courses2 << ' ';
        destFile << tea[i].courses3 << ' ';
        destFile << tea[i].scoring << '\n';
    }
    destFile.close();
}
//读取文件
void oufile(pteacher tea)
{
    char s[50] = { 0 };
    teacher a;
    ifstream srcFile("out.txt", ios::in);
    for (int i = 0; i < 7; i++)
        srcFile >> s;
    for (int i = 0; i < m; i++)
    {
        memset(&a, 0, sizeof(a));
        srcFile >> a.title_number; cout << "职工号：" << a.title_number << '\n';
        srcFile >> a.name; cout << "姓名：" << a.name << '\n';
        srcFile >> a.title; cout << "职称：" << a.title << '\n';
        srcFile >> a.sex; cout << "性别：" << a.sex << '\n';
        srcFile >> a.courses1; cout << "课程1：" << a.courses1 << '\n';
        srcFile >> a.courses2; cout << "课程2：" << a.courses2 << '\n';
        srcFile >> a.courses3; cout << "课程2：" << a.courses3 << '\n';
        srcFile >> a.scoring; cout << "评分：" << a.scoring << '\n';
        cout << "*************************" << '\n';
    }
    srcFile.close();
}
//输入信息
void inputting(pteacher tea)
{
    for (int i = 0; i < m; i++)
    {
        cout << "职工号："; cin >> tea[i].title_number;
        cout << "姓名："; cin >> tea[i].name;
        cout << "职称："; cin >> tea[i].title;
        cout << "性别："; cin >> tea[i].sex;
        cout << "课程1："; cin >> tea[i].courses1;
        cout << "课程2："; cin >> tea[i].courses2;
        cout << "课程3："; cin >> tea[i].courses3;
        cout << "评分："; cin >> tea[i].scoring;
    }
}
///排序评分
void sort_scoring(pteacher tea)
{
    teacher a;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            if (tea[i].scoring < tea[j].scoring)
            {
                a = tea[i];
                tea[i] = tea[j];
                tea[j] = a;
            }
        }
    }
}
///排序职工号
void sort_number(pteacher tea)
{
    teacher a;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            if (tea[i].title_number < tea[j].title_number)
            {
                a = tea[i];
                tea[i] = tea[j];
                tea[j] = a;
            }
        }
    }
}
//打印信息
void print(pteacher tea)
{
    for (int i = 0; i < m; i++)
    {
        cout << "职工号：" << tea[i].title_number << '\n';
        cout << "姓名：" << tea[i].name << '\n';
        cout << "职称：" << tea[i].title << '\n';
        cout << "性别：" << tea[i].sex << '\n';
        cout << "课程1：" << tea[i].courses1 << '\n';
        cout << "课程2：" << tea[i].courses2 << '\n';
        cout << "课程2：" << tea[i].courses3 << '\n';
        cout << "评分：" << tea[i].scoring << '\n';
        cout << "*************************" << '\n';
    }
}
//查询
int enquiry_student(pteacher tea)
{
    char nu[20] = { 0 };
    cout << "输入需要查询姓名或学号："; cin >> nu;
    for (int i = 0; i < m; i++)
    {
        if (!strcmp(tea[i].name, nu) || !strcmp(tea[i].courses1, nu) || !strcmp(tea[i].courses2, nu) || !strcmp(tea[i].courses3, nu))
        {
            cout << "职工号：" << tea[i].title_number << '\n';
            cout << "姓名：" << tea[i].name << '\n';
            cout << "职称：" << tea[i].title << '\n';
            cout << "性别：" << tea[i].sex << '\n';
            cout << "课程1：" << tea[i].courses1 << '\n';
            cout << "课程2：" << tea[i].courses2 << '\n';
            cout << "课程2：" << tea[i].courses3 << '\n';
            cout << "评分：" << tea[i].scoring << '\n';
            cout << '\n';
            return 1;
        }
    }
    return 0;
}
//界面
void interface()
{
    cout << "1.输入信息"<<'\n';
    cout << "2.信息写入文件" << '\n';
    cout << "3.读取文件" << '\n';
    cout << "4.排序（按评分）" << '\n';
    cout << "5.排序（按职工号）" << '\n';
    cout << "6.查询：" << '\n';
    cout << "7.打印信息" << '\n';
    cout << "8.退出" << '\n';
}
int main()
{
    teacher tea[m] = { 0 };
    int choose = 0; 
    while (choose != 8)
    {
        interface();
        cin >> choose;
        system("cls");
        switch (choose)
        {
        case 1:
            inputting(tea);
            cout << "--------------------" << '\n';
            break;
        case 2:
            infile(tea);
            cout << "--------------------" << '\n';
            break;
        case 3:
            oufile(tea);
            cout << "--------------------" << '\n';
            break;
        case 4:
            sort_scoring(tea);
            cout << "--------------------" << '\n';
            break;
        case 5:
            sort_number(tea);
            cout << "--------------------" << '\n';
            break;
        case 6:
            enquiry_student(tea);
            cout << "--------------------" << '\n';
            break;
        case 7:
            print(tea);
            cout << "--------------------" << '\n';
            break;
        default:
            break;
        }
    }
    return 0;
}