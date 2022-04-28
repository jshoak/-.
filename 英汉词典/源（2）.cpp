#include <iostream>
#include <fstream>
using namespace std;
typedef struct wor
{
    char* eng;
    char* chi;
    wor* next;
}*pword;

void free(pword *words)//释放内存
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

int enquiry(pword* words, char* s)//查询
{
    pword p = nullptr;
    p = words[s[0] - 97];
    while (p != nullptr)
    {
        if (strcmp(s, p->eng) == 0)
        {
            cout << "查询到：\n";
            cout << p->eng << "\n";
            cout << p->chi << "\n";
            cout << "-------------\n";
            return 1;
        }
        p = p->next;
    }
    cout << "未找到\n";
    return 0;
}

int delet(pword* words, char* s)//删除
{
    pword* p = nullptr;
    pword mid = nullptr;
    p = &words[s[0] - 97];
    while ((*p) != nullptr)
    {
        if (strcmp(s, (*p)->eng) == 0)
        {
            cout << "已删除\n";
            mid = *p;
            *p = (*p)->next;
            delete[] mid->eng;
            delete[] mid->chi;
            delete[] mid;
            return 1;
        }
        p = &(*p)->next;
    }
    cout << "未找到\n";
    return 0;
}

int insert(pword* words)
{
    pword* p = nullptr;
    pword mid = nullptr;
    char s[10] = { 0 };
    char c[10] = { 0 };
    cout << "输入要插入的单词\n";
    cin >> s;
    cout << "输入单词的翻译\n";
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
    cout << "已插入\n";
    return 1;
}

void write(pword* words)//写文件
{
    char s[] = "词典\\a.txt";
    ofstream file; //以文本模式打开
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

void read(pword* words)//读取文件
{
    char s[] = "词典\\a.txt";
    char c[20] = { 0 };
    pword* p = nullptr;
    ifstream file; //以文本模式打开in.txt备读
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
    pword words[26] = { 0 };//哈希链地址法
    char s[10] = { 0 }, c = 0;
    read(words);
    int choose = 1;
    while (choose != 5)
    {
        cout << "------------------------------------------\n";
        cout << "1.查询 2.删除 3.插入 4.打印所有单词 5.退出\n";
        cout << "输入选项\n";
        cin >> choose; c = getchar();
        switch (choose)
        {
        case 1:
            memset(s, 0, 10);
            cout << "输入要查找的单词\n";
            cin >> s; c = getchar();
            enquiry(words, s);
            break;
        case 2:
            memset(s, 0, 10);
            cout << "输入要删除的单词\n";
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
    _CrtDumpMemoryLeaks();//Visual Studio 调试器内存泄露检测
    return 0;
}