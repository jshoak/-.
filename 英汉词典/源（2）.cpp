#include <iostream>
#include <fstream>
using namespace std;
typedef struct wor
{
    char* eng;
    char* chi;
    wor* next;
}*pword;

void free(pword *words)//�ͷ��ڴ�
{
    pword p = nullptr, mid = nullptr;
    for (int i = 0; i < 26; i++)
    {
        p = words[i];
        while (p != nullptr)
        {
            delete[] p->eng;
            delete[] p->chi;
            mid = p;
            p = p->next;
            delete[] mid;
        }
    }
}

void print(pword *words)
{
    pword p = nullptr;
    for (int i = 0; i < 26; i++)
    {
        p = words[i];
        while (p != nullptr)
        {
            cout << p->eng << "\n";
            cout << p->chi << "\n";
            p = p->next;
            cout << "-------------\n";
        }      
    }
}

int enquiry(pword* words, char* s)//��ѯ
{
    pword p = nullptr;
    p = words[s[0] - 97];
    while (p != nullptr)
    {
        if (strcmp(s, p->eng) == 0)
        {
            cout << "��ѯ����\n";
            cout << p->eng << "\n";
            cout << p->chi << "\n";
            cout << "-------------\n";
            return 1;
        }
        p = p->next;
    }
    cout << "δ�ҵ�\n";
    return 0;
}

int delet(pword* words, char* s)//ɾ��
{
    pword* p = nullptr;
    pword mid = nullptr;
    p = &words[s[0] - 97];
    while ((*p) != nullptr)
    {
        if (strcmp(s, (*p)->eng) == 0)
        {
            cout << "��ɾ��\n";
            mid = *p;
            *p = (*p)->next;
            delete[] mid->eng;
            delete[] mid->chi;
            delete[] mid;
            return 1;
        }
        p = &(*p)->next;
    }
    cout << "δ�ҵ�\n";
    return 0;
}

int insert(pword* words)
{
    pword* p = nullptr;
    pword mid = nullptr;
    char s[10] = { 0 };
    char c[10] = { 0 };
    cout << "����Ҫ����ĵ���\n";
    cin >> s;
    cout << "���뵥�ʵķ���\n";
    cin >> c;
    if (enquiry(words, s))return 0;
    p = &words[s[0] - 97];
    mid = new wor();
    mid->eng = new char[strlen(s) + 1]();
    mid->chi = new char[strlen(c) + 1]();
    memmove(mid->eng, s, strlen(s) + 1);
    memmove(mid->chi, c, strlen(c) + 1);
    mid->next = *p;
    *p = mid;
    cout << "�Ѳ���\n";
    return 1;
}

void write(pword* words)//д�ļ�
{
    char s[] = "�ʵ�\\a.txt";
    ofstream file; //���ı�ģʽ��
    pword p = nullptr;
    for (int i = 0; i < 26; i++)
    {
        file.open(s, ios::out);
        p = words[i];
        while (p != nullptr)
        {
            file << p->eng << ' ';
            file << p->chi << '\n';
            p = p->next;
        }
        file.close();
        s[5]++;
    }
}

void read(pword* words)//��ȡ�ļ�
{
    char s[] = "�ʵ�\\a.txt";
    char c[20] = { 0 };
    pword* p = nullptr;
    ifstream file; //���ı�ģʽ��in.txt����
    for (int i = 0; i < 26; i++)
    {
        file.open(s, ios::in);
        p = &words[i];
        while (file >> c)
        {
            *p = new wor();
            (*p)->eng = new char[strlen(c) + 1]();
            memcpy((*p)->eng, c, strlen(c) + 1);
            file >> c;
            (*p)->chi = new char[strlen(c) + 1]();
            memcpy((*p)->chi, c, strlen(c) + 1);
            (*p)->next = nullptr;
            p = &(*p)->next;
        }
        file.close();
        s[5]++;
    }
}

int main()
{
    pword words[26] = { 0 };//��ϣ����ַ��
    char s[10] = { 0 }, c = 0;
    read(words);
    int choose = 1;
    while (choose != 5)
    {
        cout << "------------------------------------------\n";
        cout << "1.��ѯ 2.ɾ�� 3.���� 4.��ӡ���е��� 5.�˳�\n";
        cout << "����ѡ��\n";
        cin >> choose; c = getchar();
        switch (choose)
        {
        case 1:
            memset(s, 0, 10);
            cout << "����Ҫ���ҵĵ���\n";
            cin >> s; c = getchar();
            enquiry(words, s);
            break;
        case 2:
            memset(s, 0, 10);
            cout << "����Ҫɾ���ĵ���\n";
            cin >> s; c = getchar();
            delet(words, s);
            break;
        case 3:
            insert(words);
            break;
        case 4:
            print(words);
            break;
        default:
            break;
        }
    }
    //write(words);
    free(words);/**/
    _CrtDumpMemoryLeaks();//Visual Studio �������ڴ�й¶���
    return 0;
}