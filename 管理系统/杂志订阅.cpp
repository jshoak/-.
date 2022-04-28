#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string.h>
#include <ctime>
using namespace std;
const char ss[12][4] = { {"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"} };
const char ss1[12][3] = { {"01"},{"02"},{"03"},{"04"},{"05"},{"06"},{"07"},{"08"},{"09"},{"10"},{"11"},{"12"} };
typedef struct information
{
    char number[11];	//编号
    char name[11];		//姓名
    char sex[3];		//性别
    char phone[15];     //电话号码
    char unit[20];      //杂志单位
    int quantity;       //订阅数
    char date[11];      //订阅期限
}inf;
class mag
{
public:
	mag();
    int time_(char date[11]);
    void addr();//添加
    int enquiry();//查询
    void show();//显示
    int modifies();//修改
    int dele();//删除
    int quantity;
    int male;
    int female;
    int da;
private:
    vector<inf> users;
    int date;//日期

};
mag::mag():quantity(0), male(0), female(0),da(0)
{
    date = 0;
    time_t curtime = time(0);
    char* s = ctime(&curtime);
    char c[10] = { 0 }, cc[5] = { 0 };
    c[0] = s[20]; c[1] = s[21]; c[2] = s[22]; c[3] = s[23];
    cc[0] = s[4]; cc[1] = s[5]; cc[2] = s[6];
    for (date = 1; date <= 12; date++)
        if (strcmp(&ss[date - 1][0], cc) == 0)
            break;//月
    c[4] = ss1[date - 1][0]; c[5] = ss1[date - 1][1];
    c[6] = s[8]; c[7] = s[9];
    date = atoi(c);//日
}
int mag::time_(char date[11])
{
    int j = 0;
    char c[10] = { 0 };
    c[0] = date[0]; c[1] = date[1]; c[2] = date[2]; c[3] = date[3];
    c[4] = date[5]; c[5] = date[6];
    c[6] = date[8]; c[7] = date[9];
    j = atoi(c);
    return j;
}
void mag::addr()
{
    inf a;
    memset(&a, 0, sizeof(a));
    cout << "编号："; cin >> a.number;
    cout << "姓名："; cin >> a.name;
    cout << "性别："; cin >> a.sex;
    cout << "电话号码："; cin >> a.phone;
    cout << "杂志单位："; cin >> a.unit;
    cout << "订阅数："; cin >> a.quantity;
    cout << "订阅期限(格式0000.00.00)："; cin >> a.date;
    quantity += a.quantity;
    if (strcmp(a.sex, "男") == 0)
        male++;
    else female++;
    if (date > time_(a.date))
        da++;
    users.push_back(a);
}
int mag::enquiry()
{
    char name[11];		//姓名
    char sex[3];		//性别
    char unit[20];      //杂志单位
    int j = users.size(), i;
    cout << "查询姓名："; cin >> name;
    cout << "查询性别："; cin >> sex;
    cout << "查询杂志单位："; cin >> unit;
    for (i = 0; i < j; i++)
    {
        if (strcmp(name, users[i].name) == 0 && strcmp(sex, users[i].sex) == 0 && strcmp(unit, users[i].unit) == 0)
        {
            cout << "编号：" << users[i].number << '\n';
            cout << "姓名：" << users[i].name << '\n';
            cout << "性别：" << users[i].sex << '\n';
            cout << "电话号码：" << users[i].phone << '\n';
            cout << "杂志单位：" << users[i].unit << '\n';
            cout << "订阅数：" << users[i].quantity << '\n';
            cout << "订阅期限：" << users[i].date << '\n';
            return 1;
        }
    }
    return 0;
}
void mag::show()
{
    int j = users.size(), i;
    for (i = 0; i < j; i++)
    {
        cout << "编号：" << users[i].number << '|';
        cout << "姓名：" << users[i].name << '|';
        cout << "性别：" << users[i].sex << '|';
        cout << "电话号码：" << users[i].phone << '|';
        cout << "杂志单位：" << users[i].unit << '|';
        cout << "订阅数：" << users[i].quantity << '|';
        cout << "订阅期限：" << users[i].date << '\n';
    }
}
int mag::modifies()
{
    char name[11];		//姓名
    char sex[3];		//性别
    char unit[20];      //杂志单位
    int j = users.size(), i;
    cout << "姓名："; cin >> name;
    cout << "性别："; cin >> sex;
    cout << "杂志单位："; cin >> unit;
    for (i = 0; i < j; i++)
    {
        if (strcmp(name, users[i].name) == 0 && strcmp(sex, users[i].sex) == 0 && strcmp(unit, users[i].unit) == 0)
        {
            cout << "编号："; cin >> users[i].number;
            cout << "姓名："; cin >> users[i].name;
            cout << "性别："; cin >> users[i].sex;
            cout << "电话号码："; cin >> users[i].phone;
            cout << "杂志单位："; cin >> users[i].unit;
            cout << "订阅数："; cin >> users[i].quantity;
            cout << "订阅期限："; cin >> users[i].date;;
            return 1;
        }
    }
    return 0;
}
int mag::dele()
{
    int j = users.size(), i, k;
    for (i = 0; i < j; i++)
    {
        if (date > time_(users[i].date))
        {
            cout << "编号：" << users[i].number << "已过期，是否删除（1是，0否）："; cin >> k;
            if (k == 1)
            {
                users.erase(users.begin() + i);
                j--;
            }
        }
    }
    return 0;
}
int main()
{
    mag a;
    int choose = 0;
    while (choose!=7)
    {
        cout << "****************\n";
        cout << "1.添加\n"; 
        cout << "2.查询\n";
        cout << "3.显示\n";
        cout << "4.修改\n";
        cout << "5.删除\n";
        cout << "6.统计\n";
        cout << "7.退出\n"; 
        cout << "选项："; cin >> choose;
        switch (choose)
        {
        case 1:
        {
            a.addr();
            break;
        }
        case 2:
        {
            a.enquiry();
            break;
        }
        case 3:
        {
            a.show();
            break;
        }
        case 4:
        {
            a.modifies();
            break;
        }
        case 5:
        {
            a.dele();
            break;
        }
        case 6:
        {
            cout << "订阅总数：" << a.quantity << '\n';
            cout << "男：" << a.male << '\n';
            cout << "女：" << a.female << '\n';
            cout << "订阅过期数：" << a.da << '\n';
            break;
        }
        default:
            break;
        }
    }
	return 0;
}