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
    char number[11];	//���
    char name[11];		//����
    char sex[3];		//�Ա�
    char phone[15];     //�绰����
    char unit[20];      //��־��λ
    int quantity;       //������
    char date[11];      //��������
}inf;
class mag
{
public:
	mag();
    int time_(char date[11]);
    void addr();//���
    int enquiry();//��ѯ
    void show();//��ʾ
    int modifies();//�޸�
    int dele();//ɾ��
    int quantity;
    int male;
    int female;
    int da;
private:
    vector<inf> users;
    int date;//����

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
            break;//��
    c[4] = ss1[date - 1][0]; c[5] = ss1[date - 1][1];
    c[6] = s[8]; c[7] = s[9];
    date = atoi(c);//��
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
    cout << "��ţ�"; cin >> a.number;
    cout << "������"; cin >> a.name;
    cout << "�Ա�"; cin >> a.sex;
    cout << "�绰���룺"; cin >> a.phone;
    cout << "��־��λ��"; cin >> a.unit;
    cout << "��������"; cin >> a.quantity;
    cout << "��������(��ʽ0000.00.00)��"; cin >> a.date;
    quantity += a.quantity;
    if (strcmp(a.sex, "��") == 0)
        male++;
    else female++;
    if (date > time_(a.date))
        da++;
    users.push_back(a);
}
int mag::enquiry()
{
    char name[11];		//����
    char sex[3];		//�Ա�
    char unit[20];      //��־��λ
    int j = users.size(), i;
    cout << "��ѯ������"; cin >> name;
    cout << "��ѯ�Ա�"; cin >> sex;
    cout << "��ѯ��־��λ��"; cin >> unit;
    for (i = 0; i < j; i++)
    {
        if (strcmp(name, users[i].name) == 0 && strcmp(sex, users[i].sex) == 0 && strcmp(unit, users[i].unit) == 0)
        {
            cout << "��ţ�" << users[i].number << '\n';
            cout << "������" << users[i].name << '\n';
            cout << "�Ա�" << users[i].sex << '\n';
            cout << "�绰���룺" << users[i].phone << '\n';
            cout << "��־��λ��" << users[i].unit << '\n';
            cout << "��������" << users[i].quantity << '\n';
            cout << "�������ޣ�" << users[i].date << '\n';
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
        cout << "��ţ�" << users[i].number << '|';
        cout << "������" << users[i].name << '|';
        cout << "�Ա�" << users[i].sex << '|';
        cout << "�绰���룺" << users[i].phone << '|';
        cout << "��־��λ��" << users[i].unit << '|';
        cout << "��������" << users[i].quantity << '|';
        cout << "�������ޣ�" << users[i].date << '\n';
    }
}
int mag::modifies()
{
    char name[11];		//����
    char sex[3];		//�Ա�
    char unit[20];      //��־��λ
    int j = users.size(), i;
    cout << "������"; cin >> name;
    cout << "�Ա�"; cin >> sex;
    cout << "��־��λ��"; cin >> unit;
    for (i = 0; i < j; i++)
    {
        if (strcmp(name, users[i].name) == 0 && strcmp(sex, users[i].sex) == 0 && strcmp(unit, users[i].unit) == 0)
        {
            cout << "��ţ�"; cin >> users[i].number;
            cout << "������"; cin >> users[i].name;
            cout << "�Ա�"; cin >> users[i].sex;
            cout << "�绰���룺"; cin >> users[i].phone;
            cout << "��־��λ��"; cin >> users[i].unit;
            cout << "��������"; cin >> users[i].quantity;
            cout << "�������ޣ�"; cin >> users[i].date;;
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
            cout << "��ţ�" << users[i].number << "�ѹ��ڣ��Ƿ�ɾ����1�ǣ�0�񣩣�"; cin >> k;
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
        cout << "1.���\n"; 
        cout << "2.��ѯ\n";
        cout << "3.��ʾ\n";
        cout << "4.�޸�\n";
        cout << "5.ɾ��\n";
        cout << "6.ͳ��\n";
        cout << "7.�˳�\n"; 
        cout << "ѡ�"; cin >> choose;
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
            cout << "����������" << a.quantity << '\n';
            cout << "�У�" << a.male << '\n';
            cout << "Ů��" << a.female << '\n';
            cout << "���Ĺ�������" << a.da << '\n';
            break;
        }
        default:
            break;
        }
    }
	return 0;
}