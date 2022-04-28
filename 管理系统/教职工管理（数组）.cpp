#include <iostream>
#include <fstream>
using namespace std;
#define m 3         //��ְ������
#define k "     "
typedef struct information
{
    int title_number;	    //ְ����
    char name[10];			//����
    char title[20];		    //ְ��
    char sex[3];            //�Ա�
    char courses1[10];      //�γ�1
    char courses2[10];      //�γ�2
    char courses3[10];      //�γ�3
    double scoring;         //����
}teacher, * pteacher;
//д���ļ�
void infile(pteacher tea)
{
    ofstream destFile("out.txt", ios::out);
    destFile << "ְ����" << k << "����" << k << "ְ��" << k << "�γ�1" << k << "�γ�2" << k << "�γ�3" << k << "����\n";
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
//��ȡ�ļ�
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
        srcFile >> a.title_number; cout << "ְ���ţ�" << a.title_number << '\n';
        srcFile >> a.name; cout << "������" << a.name << '\n';
        srcFile >> a.title; cout << "ְ�ƣ�" << a.title << '\n';
        srcFile >> a.sex; cout << "�Ա�" << a.sex << '\n';
        srcFile >> a.courses1; cout << "�γ�1��" << a.courses1 << '\n';
        srcFile >> a.courses2; cout << "�γ�2��" << a.courses2 << '\n';
        srcFile >> a.courses3; cout << "�γ�2��" << a.courses3 << '\n';
        srcFile >> a.scoring; cout << "���֣�" << a.scoring << '\n';
        cout << "*************************" << '\n';
    }
    srcFile.close();
}
//������Ϣ
void inputting(pteacher tea)
{
    for (int i = 0; i < m; i++)
    {
        cout << "ְ���ţ�"; cin >> tea[i].title_number;
        cout << "������"; cin >> tea[i].name;
        cout << "ְ�ƣ�"; cin >> tea[i].title;
        cout << "�Ա�"; cin >> tea[i].sex;
        cout << "�γ�1��"; cin >> tea[i].courses1;
        cout << "�γ�2��"; cin >> tea[i].courses2;
        cout << "�γ�3��"; cin >> tea[i].courses3;
        cout << "���֣�"; cin >> tea[i].scoring;
    }
}
///��������
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
///����ְ����
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
//��ӡ��Ϣ
void print(pteacher tea)
{
    for (int i = 0; i < m; i++)
    {
        cout << "ְ���ţ�" << tea[i].title_number << '\n';
        cout << "������" << tea[i].name << '\n';
        cout << "ְ�ƣ�" << tea[i].title << '\n';
        cout << "�Ա�" << tea[i].sex << '\n';
        cout << "�γ�1��" << tea[i].courses1 << '\n';
        cout << "�γ�2��" << tea[i].courses2 << '\n';
        cout << "�γ�2��" << tea[i].courses3 << '\n';
        cout << "���֣�" << tea[i].scoring << '\n';
        cout << "*************************" << '\n';
    }
}
//��ѯ
int enquiry_student(pteacher tea)
{
    char nu[20] = { 0 };
    cout << "������Ҫ��ѯ������ѧ�ţ�"; cin >> nu;
    for (int i = 0; i < m; i++)
    {
        if (!strcmp(tea[i].name, nu) || !strcmp(tea[i].courses1, nu) || !strcmp(tea[i].courses2, nu) || !strcmp(tea[i].courses3, nu))
        {
            cout << "ְ���ţ�" << tea[i].title_number << '\n';
            cout << "������" << tea[i].name << '\n';
            cout << "ְ�ƣ�" << tea[i].title << '\n';
            cout << "�Ա�" << tea[i].sex << '\n';
            cout << "�γ�1��" << tea[i].courses1 << '\n';
            cout << "�γ�2��" << tea[i].courses2 << '\n';
            cout << "�γ�2��" << tea[i].courses3 << '\n';
            cout << "���֣�" << tea[i].scoring << '\n';
            cout << '\n';
            return 1;
        }
    }
    return 0;
}
//����
void interface()
{
    cout << "1.������Ϣ"<<'\n';
    cout << "2.��Ϣд���ļ�" << '\n';
    cout << "3.��ȡ�ļ�" << '\n';
    cout << "4.���򣨰����֣�" << '\n';
    cout << "5.���򣨰�ְ���ţ�" << '\n';
    cout << "6.��ѯ��" << '\n';
    cout << "7.��ӡ��Ϣ" << '\n';
    cout << "8.�˳�" << '\n';
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