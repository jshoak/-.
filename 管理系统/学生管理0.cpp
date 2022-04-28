#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
typedef struct student_information {
	unsigned int id;//ѧ��
	char name[11];//����
	char college[20];//ϵ��
	char classes[20];//�༶
	unsigned int age;//����
	char sex[3];//�Ա�
	double credit[2];//��Ҫ���ѧ��
	double f_credit[2];//�����ѧ��
	char time[15];//��ѧʱ��
} s_inf;

void str_num(char* time, int& year,int& month,int& day)
{
	char s[5] = { 0 }, * p = time;
	memset(s, 0, sizeof(s));
	memcpy(s, p, 4); s[4] = '\0';
	year = atoi(s);
	p += 5;
	memset(s, 0, sizeof(s));
	memcpy(s, p, 2); s[2] = '\0';
	month = atoi(s);
	p += 3;
	memset(s, 0, sizeof(s));
	memcpy(s, p, 2); s[2] = '\0';
	day = atoi(s);
}
int judge_time(char* time)
{
	if (strlen(time) != 10 || time[4] != '-' || time[7] != '-')return 0;
	int year = 0, month = 0, day = 0;
	str_num(time, year, month, day);
	if (month > 12 || month < 1)return 0;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day < 1 || day > 31)return 0;
		else return 1;
	case 2:
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			if (day < 1 || day > 29)return 0;
			else return 1;
		}
		else
		{
			if (day < 1 || day > 28)return 0;
			else return 1;
		}
	default:
		if (day < 1 || day > 30)return 0;
		else return 1;
	}
	return 1;
}
void print_inf(s_inf& inf)
{
		cout << "ѧ�ţ�" << inf.id << '\n';
		cout << "������" << inf.name << '\n';
		cout << "ϵ��" << inf.college << '\n';
		cout << "�༶��" << inf.classes << '\n';
		cout << "���䣺" << inf.age << '\n';
		cout << "�Ա�" << inf.sex << '\n';
		cout << "��һѧ������ѧ�֣�" << inf.credit[0] << '\n';
		cout << "�ڶ�ѧ������ѧ�֣�" << inf.credit[1] << '\n';
		cout << "��һѧ�������ѧ�֣�" << inf.f_credit[0] << '\n';
		cout << "�ڶ�ѧ�������ѧ�֣�" << inf.f_credit[0] << '\n';
		cout << "��ѧ����" << inf.time << '\n';
		cout << "----------------------------\n";
}

class student
{
public:
	student();
	~student();
	void add_student();//���
	int del_student(unsigned int id);//ɾ��
	int rev_student(unsigned int id);//�޸�
	int que_student_id(unsigned int id);//��ѯ
	int que_student_classes(char* classes);//��ѯ
	int que_student_1(unsigned int choose);//��ѯ
	int que_student_2(unsigned int choose);//��ѯ
	void pri_student();//��ӡ
private:
	std::vector<s_inf>inf;
	s_inf a;
};

student::student()
{
	memset(&a, 0, sizeof(s_inf));
	ifstream inFile("student.dat", ios::in | ios::binary);
	while (inFile.read((char*)&a, sizeof(s_inf)))
		inf.push_back(a);
	inFile.close();
}

student::~student()
{
	ofstream outFile("student.dat", ios::out | ios::binary);
	for (unsigned int i = 0; i < inf.size(); i++)
		outFile.write((char*)&inf[i], sizeof(s_inf));
	outFile.close();
}

void student::add_student()
{
	cout << "����ѧ�ţ�"; cin >> a.id;
	cout << "����������"; cin >> a.name;
	cout << "����ϵ��"; cin >> a.college;
	cout << "����༶��"; cin >> a.classes;
	cout << "�������䣺"; cin >> a.age;
	cout << "�����Ա�"; cin >> a.sex;
	cout << "�����һѧ������ѧ�֣�"; cin >> a.credit[0];
	cout << "����ڶ�ѧ������ѧ�֣�"; cin >> a.credit[1];
	cout << "�����һѧ�������ѧ�֣�"; cin >> a.f_credit[0];
	cout << "����ڶ�ѧ�������ѧ�֣�"; cin >> a.f_credit[0];
	while (true)
	{
		cout << "������ѧ���ڣ���ʽ��YYYY-MM-DD����"; cin >> a.time;
		if (judge_time(a.time))break;
		cout << "�������������������\n";
	}
	inf.push_back(a);
}
/**/
int student::del_student(unsigned int id)
{
	for (unsigned int i = 0; i < inf.size(); i++)
		if (id == inf[i].id)
		{
			inf.erase(inf.begin() + i);
			return 1;
		}
	return 0;
}

int student::rev_student(unsigned int id)
{
	int choose = 0;
	for (unsigned int i = 0; i < inf.size(); i++)
		if (id == inf[i].id)
		{	
			cout << "*********************************\n";
			cout << "1.�޸�ѧ��\n2.�޸�����\n3.�޸�ϵ��\n";
			cout << "4.�޸İ༶\n5.�޸�����\n6.�޸��Ա�\n";
			cout << "7.�޸ĵ�һѧ������ѧ��\n";
			cout << "8.�޸ĵڶ�ѧ������ѧ��\n";
			cout << "9.�޸ĵ�һѧ�������ѧ��\n";
			cout << "10.�޸ĵڶ�ѧ�������ѧ��\n";
			cout << "11.�޸���ѧ����\n";
			cout << "*********************************\n";
			cout << "����ѡ�"; cin >> choose;
			switch (choose)
			{
			case 1:cout << "����ѧ�ţ�"; cin >> inf[i].id;
				break;
			case 2:cout << "����������"; cin >> inf[i].name;
				break;
			case 3:cout << "����ϵ��"; cin >> inf[i].college;
				break;
			case 4:cout << "����༶��"; cin >> inf[i].classes;
				break;
			case 5:cout << "�������䣺"; cin >> inf[i].age;
				break;
			case 6:cout << "�����Ա�"; cin >> inf[i].sex;
				break;
			case 7:cout << "�����һѧ������ѧ�֣�"; cin >> inf[i].credit[0];
				break;
			case 8:cout << "����ڶ�ѧ������ѧ�֣�"; cin >> inf[i].credit[1];
				break;
			case 9:cout << "�����һѧ�������ѧ�֣�"; cin >> inf[i].f_credit[0];
				break;
			case 10:cout << "����ڶ�ѧ�������ѧ�֣�"; cin >> inf[i].f_credit[0];
				break;
			case 11:
				while (true)
				{
					cout << "������ѧ���ڣ���ʽ��YYYY-MM-DD����"; cin >> inf[i].time;
					if (judge_time(inf[i].time))break;
					cout << "�������������������\n";
				}
				break;
			default:
				break;
			}
			return 1;
		}
	return 0;
}

int student::que_student_id(unsigned int id)
{
	for (unsigned int i = 0; i < inf.size(); i++)
		if (id == inf[i].id)
		{
			print_inf(inf[i]);
			return 1;
		}
	return 0;
}

int student::que_student_classes(char* classes)
{
	for (unsigned int i = 0; i < inf.size(); i++)
		if (strcmp(inf[i].classes, classes) == 0)
			print_inf(inf[i]);
	return 0;
}

int student::que_student_1(unsigned int choose)
{
	switch (choose)
	{
	case 1:
		for (unsigned int i = 0; i < inf.size(); i++)
			if (inf[i].f_credit[0] < inf[i].credit[0])
				print_inf(inf[i]);
		break;
	case 2:
		for (unsigned int i = 0; i < inf.size(); i++)
			if (inf[i].f_credit[0] >= inf[i].credit[0])
				print_inf(inf[i]);
		break;
	default:
		break;
	}
	return 0;
}

int student::que_student_2(unsigned int choose)
{
	switch (choose)
	{
	case 1:
		for (unsigned int i = 0; i < inf.size(); i++)
			if (inf[i].f_credit[0] < inf[i].credit[0])
				print_inf(inf[i]);
		break;
	case 2:
		for (unsigned int i = 0; i < inf.size(); i++)
			if (inf[i].f_credit[0] >= inf[i].credit[0])
				print_inf(inf[i]);
		break;
	default:
		break;
	}
	return 0;
}

void student::pri_student()
{
	for (unsigned int i = 0; i < inf.size(); i++)
		print_inf(inf[i]);	
}

void menu()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.��Ϣ¼��" << '\n';
	std::cout << "2.��Ϣɾ��" << '\n';
	std::cout << "3.��Ϣ��ѯ" << '\n';
	std::cout << "4.��Ϣ�޸�" << '\n';
	std::cout << "5.��Ϣ���" << '\n';
	std::cout << "6.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_query()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.ѧ�Ų�ѯ" << '\n';
	std::cout << "2.�༶��ѯ" << '\n';
	std::cout << "3.��һѧ��δ���ѧ�ֲ�ѯ" << '\n';
	std::cout << "4.�ڶ�ѧ��δ���ѧ�ֲ�ѯ" << '\n';
	std::cout << "5.��һѧ�����ѧ�ֲ�ѯ" << '\n';
	std::cout << "6.�ڶ�ѧ�����ѧ�ֲ�ѯ" << '\n';
	std::cout << "***********************" << '\n';
}

int main()
{
	student stu;
	int choose = 0, choose1 = 0;
	unsigned int id = 0, j = 0;
	char classes[20] = { 0 };
	while (choose != 6)
	{
		menu();
		cout << "����ѡ�\n";cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			stu.add_student();
			break;
		}
		case 2:
		{
			cout << "������Ҫɾ��ѧ�ţ�\n"; cin >> id;
			if (stu.del_student(id) == 0)
				cout << "δ�ҵ���ѧ��\n";
			break;
		}
		case 3:
		{
			menu_query();
			cout << "����ѡ�\n";cin >> choose1;
			switch (choose1)
			{
			case 1:
				cout << "������Ҫ��ѯѧ�ţ�\n"; cin >> id;
				if (stu.que_student_id(id) == 0)
					cout << "δ�ҵ���ѧ��\n";
				break;
			case 2:
				memset(&classes, 0, 20);
				cout << "������Ҫ��ѯ�༶��\n"; cin >> classes;
				if (stu.que_student_classes(classes) == 0)
					cout << "δ�ҵ���ѧ��\n";
				break;
			case 3:stu.que_student_1(1);
				break;
			case 4:stu.que_student_2(1);
				break;
			case 5:stu.que_student_1(2);
				break;
			case 6:stu.que_student_2(2);
				break;
			default:
				break;
			}
			break;
		}
		case 4:
		{
			cout << "������Ҫ�޸�ѧ�ţ�\n"; cin >> id;
			if (stu.rev_student(id) == 0)
				cout << "δ�ҵ���ѧ��\n";
			break;
		}
		case 5:stu.pri_student();
			break;
		default:
			break;
		}
	}
	return 0;
}