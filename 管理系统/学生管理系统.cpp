#ifndef STUDENT
#define STUDENT
#include<iostream>
#include<string>
#include <fstream>
#include <vector>
using namespace std;

const char* p = "ѧ��\t����\tϵ��\t�༶\t����\t�Ա�\t��ѧ����\t����ѧ��\t���ѧ��\n";

int tjudge(char* time)
{
	if (strlen(time) != 10 || time[4] != '-' || time[7] != '-')return 0;
	int year = 0, month = 0, day = 0;
	char s[5] = { 0 };

	memset(s, 0, sizeof(s));
	memcpy(s, time, 4);
	year = atoi(s);

	time += 5;
	memset(s, 0, sizeof(s));
	memcpy(s, time, 2);
	month = atoi(s);

	time += 3;
	memset(s, 0, sizeof(s));
	memcpy(s, time, 2);
	day = atoi(s);

	if (month < 1 || month >12)return 0;
	switch (month)
	{
	case 2:
		if (year % 4 == 0 && year % 100 != 0)
		{
			if (day < 1 || day > 29)return 0;
			else return 1;
		}
		else
		{
			if (day < 1 || day > 28)return 0;
			else return 1;
		}
	case 4:
	case 6:
	case 9:
	case 11:
		if (day < 1 || day > 30)return 0;
		else return 1;
	default:
		if (day < 1 || day > 31)return 0;
		else return 1;
	}
	return 1;
}

void rmenu()
{
	cout << "*********************************\n";
	cout << "1.�޸�ѧ��\n2.�޸�����\n3.�޸�ϵ��\n";
	cout << "4.�޸İ༶\n5.�޸�����\n6.�޸��Ա�\n";
	cout << "7.�޸���ѧ����\n8.�޸�����ѧ��\n9.�޸����ѧ��\n";
	cout << "10.�˳�\n";
	cout << "*********************************\n";
}

void qmenu()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.ѧ�Ų�ѯ" << '\n';
	std::cout << "2.�༶��ѯ" << '\n';
	std::cout << "3.δ���ѧ������" << '\n';
	std::cout << "4.�����ѧ������" << '\n';
	std::cout << "5.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}

class information
{
public:
	information();
	friend istream& operator>>(std::istream& in, information& a);
	friend ostream& operator<<(std::ostream& out, information& a);
	unsigned int id;//ѧ��
	char name[11];//����
	string college;//ϵ��
	string classes;//�༶
	unsigned int age;//����
	char sex[3];//�Ա�
	double credit;//��Ҫ���ѧ��
	double f_credit;//�����ѧ��
	char time[15];//��ѧʱ��
};

information::information() :id(0), age(0), credit(0), f_credit(0)
{
	memset(name, 0, sizeof(name));
	memset(sex, 0, sizeof(sex));
	memset(time, 0, sizeof(time));
}

istream& operator>>(std::istream& in, information& a)
{
	cout << "����ѧ�ţ�"; cin >> a.id;
	cout << "����������"; cin >> a.name;
	cout << "����ϵ��"; cin >> a.college;
	cout << "����༶��"; cin >> a.classes;
	cout << "�������䣺"; cin >> a.age;
	cout << "�����Ա�"; cin >> a.sex;
	while (true)
	{
		cout << "������ѧ���ڣ���ʽ��YYYY-MM-DD����"; cin >> a.time;
		if (tjudge(a.time))break;
		cout << "�������������������\n";
	}
	cout << "��������ѧ�֣�"; cin >> a.credit;
	cout << "���������ѧ�֣�"; cin >> a.f_credit;
	return in;
}
ostream& operator<<(std::ostream& out, information& a)
{
	cout << a.id << '\t' << a.name << '\t' << a.college << '\t' << a.classes << '\t' <<
		a.age << '\t' << a.sex << '\t' << a.time << '\t' << a.credit << '\t' << a.f_credit << '\n';
	return out;
}

class student
{
public:
	student();
	~student();
	void sprint();//��ʾ��Ϣ
	void sadd();//���ѧ��
	int sdel();//ɾ��ѧ��
	int squery();//��ѯѧ����Ϣ
	int srevise();//�޸���Ϣ
private:
	std::vector<information>values;
	information a;
	string class_;
	unsigned int id;
	int choose;
};

student::student() :id(0), choose(0)
{
	char str[60] = { 0 };
	int num = 0;
	ifstream sfread("student.txt", ios::in);
	sfread >> num;
	sfread >> str;
	sfread.getline(str, 60);
	for (int i = 0; i < num; i++)
	{
		sfread >> a.id >> a.name >> a.college >> a.classes >>
			a.age >> a.sex >> a.time >> a.credit >> a.f_credit;
		values.push_back(a);
	}
	sfread.close();
}

student::~student()
{
	ofstream swrite("student.txt", ios::out);
	swrite << values.size() << '\n';
	swrite << "ѧ��\t����\tϵ��\t�༶\t����\t�Ա�\t��ѧ����\t����ѧ��\t���ѧ��\n";
	for (unsigned int i = 0; i < values.size(); i++)
	{
		swrite << values[i].id << '\t';
		swrite << values[i].name << '\t';
		swrite << values[i].college << '\t';
		swrite << values[i].classes << '\t';
		swrite << values[i].age << '\t';
		swrite << values[i].sex << '\t';
		swrite << values[i].time << '\t';
		swrite << values[i].credit << '\t';
		swrite << values[i].f_credit << '\n';
	}
	swrite.close();
}

void student::sprint()
{
	cout << p;
	for (unsigned int i = 0; i < values.size(); i++)
		cout << values[i];
}

void student::sadd()
{
	cin >> a;
	values.push_back(a);
	cout << "�����\n";
}

int student::sdel()
{
	cout << "������Ҫɾ��ѧ�ţ�\n"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
		if (id == values[i].id)
		{
			values.erase(values.begin() + i);
			cout << "��ɾ��\n";
			return 1;
		}
	cout << "δ�ҵ���ѧ��\n";
	return 0;
}

int student::squery()
{
	choose = 0;
	while (choose != 5)
	{
		qmenu();
		cout << "����ѡ�"; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			cout << "������Ҫ��ѯѧ����ѧ�ţ�\n"; cin >> id;
			for (unsigned int i = 0; i < values.size(); i++)
				if (id == values[i].id)
				{
					cout << p;
					cout << values[i];
					break;
				}
			break;
		case 2:
			cout << "������Ҫ��ѯ�İ༶��\n"; cin >> class_;
			cout << p;
			for (unsigned int i = 0; i < values.size(); i++)
				if (values[i].classes == class_)
					cout << values[i];
			break;
		case 3:
			cout << p;
			for (unsigned int i = 0; i < values.size(); i++)
				if (values[i].f_credit < values[i].credit)
					cout << values[i];
			break;
		case 4:
			cout << p;
			for (unsigned int i = 0; i < values.size(); i++)
				if (values[i].f_credit >= values[i].credit)
					cout << values[i];
			break;
		default:
			break;
		}
	}
	return 1;

}

int student::srevise()
{
	choose = 0;
	cout << "������Ҫ�޸�ѧ����ѧ�ţ�\n"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
		if (id == values[i].id)
		{
			while (choose != 10)
			{
				rmenu();
				cout << "����ѡ�"; cin >> choose;
				system("cls");
				switch (choose)
				{
				case 1:cout << "����ѧ�ţ�"; cin >> values[i].id; break;
				case 2:cout << "����������"; cin >> values[i].name; break;
				case 3:cout << "����ϵ��"; cin >> values[i].college; break;
				case 4:cout << "����༶��"; cin >> values[i].classes; break;
				case 5:cout << "�������䣺"; cin >> values[i].age; break;
				case 6:cout << "�����Ա�"; cin >> values[i].sex;
				case 7:
					while (true)
					{
						cout << "������ѧ���ڣ���ʽ��YYYY-MM-DD����"; cin >> values[i].time;
						if (tjudge(values[i].time))break;
						cout << "�������������������\n";
					}
					break;
				case 8:cout << "��������ѧ�֣�"; cin >> values[i].credit; break;
				case 9:cout << "�������ѧ�֣�"; cin >> values[i].f_credit; break;
				default:
					break;
				}
			}
			return 1;
		}
	return 0;
}

#endif#pragma once

void menu()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.���ѧ����Ϣ" << '\n';
	std::cout << "2.ɾ��ѧ����Ϣ" << '\n';
	std::cout << "3.��ѯѧ����Ϣ" << '\n';
	std::cout << "4.�޸�ѧ����Ϣ" << '\n';
	std::cout << "5.��ʾ����ѧ��" << '\n';
	std::cout << "6.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}
int main()
{
	student a;
	int choose = 0;
	while (choose != 6)
	{
		menu();
		cout << "����ѡ�\n"; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:a.sadd();break;
		case 2:a.sdel();break;
		case 3:a.squery();break;
		case 4:a.srevise();break;
		case 5:a.sprint();break;
		default:
			break;
		}
	}
	return 0;
}