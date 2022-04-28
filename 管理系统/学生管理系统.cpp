#ifndef STUDENT
#define STUDENT
#include<iostream>
#include<string>
#include <fstream>
#include <vector>
using namespace std;

const char* p = "学号\t姓名\t系别\t班级\t年龄\t性别\t入学日期\t所需学分\t完成学分\n";

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
	cout << "1.修改学号\n2.修改姓名\n3.修改系别\n";
	cout << "4.修改班级\n5.修改年龄\n6.修改性别\n";
	cout << "7.修改入学日期\n8.修改所需学分\n9.修改完成学分\n";
	cout << "10.退出\n";
	cout << "*********************************\n";
}

void qmenu()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.学号查询" << '\n';
	std::cout << "2.班级查询" << '\n';
	std::cout << "3.未完成学分名单" << '\n';
	std::cout << "4.已完成学分名单" << '\n';
	std::cout << "5.退出" << '\n';
	std::cout << "***********************" << '\n';
}

class information
{
public:
	information();
	friend istream& operator>>(std::istream& in, information& a);
	friend ostream& operator<<(std::ostream& out, information& a);
	unsigned int id;//学号
	char name[11];//姓名
	string college;//系别
	string classes;//班级
	unsigned int age;//年龄
	char sex[3];//性别
	double credit;//需要完成学分
	double f_credit;//已完成学分
	char time[15];//入学时间
};

information::information() :id(0), age(0), credit(0), f_credit(0)
{
	memset(name, 0, sizeof(name));
	memset(sex, 0, sizeof(sex));
	memset(time, 0, sizeof(time));
}

istream& operator>>(std::istream& in, information& a)
{
	cout << "输入学号："; cin >> a.id;
	cout << "输入姓名："; cin >> a.name;
	cout << "输入系别："; cin >> a.college;
	cout << "输入班级："; cin >> a.classes;
	cout << "输入年龄："; cin >> a.age;
	cout << "输入性别："; cin >> a.sex;
	while (true)
	{
		cout << "输入入学日期（格式：YYYY-MM-DD）："; cin >> a.time;
		if (tjudge(a.time))break;
		cout << "日期输入错误，重新输入\n";
	}
	cout << "输入所需学分："; cin >> a.credit;
	cout << "输入已完成学分："; cin >> a.f_credit;
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
	void sprint();//显示信息
	void sadd();//添加学生
	int sdel();//删除学生
	int squery();//查询学生信息
	int srevise();//修改信息
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
	swrite << "学号\t姓名\t系别\t班级\t年龄\t性别\t入学日期\t所需学分\t完成学分\n";
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
	cout << "已添加\n";
}

int student::sdel()
{
	cout << "输入需要删除学号：\n"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
		if (id == values[i].id)
		{
			values.erase(values.begin() + i);
			cout << "已删除\n";
			return 1;
		}
	cout << "未找到该学生\n";
	return 0;
}

int student::squery()
{
	choose = 0;
	while (choose != 5)
	{
		qmenu();
		cout << "输入选项："; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			cout << "输入需要查询学生的学号：\n"; cin >> id;
			for (unsigned int i = 0; i < values.size(); i++)
				if (id == values[i].id)
				{
					cout << p;
					cout << values[i];
					break;
				}
			break;
		case 2:
			cout << "输入需要查询的班级：\n"; cin >> class_;
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
	cout << "输入需要修改学生的学号：\n"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
		if (id == values[i].id)
		{
			while (choose != 10)
			{
				rmenu();
				cout << "输入选项："; cin >> choose;
				system("cls");
				switch (choose)
				{
				case 1:cout << "输入学号："; cin >> values[i].id; break;
				case 2:cout << "输入姓名："; cin >> values[i].name; break;
				case 3:cout << "输入系别："; cin >> values[i].college; break;
				case 4:cout << "输入班级："; cin >> values[i].classes; break;
				case 5:cout << "输入年龄："; cin >> values[i].age; break;
				case 6:cout << "输入性别："; cin >> values[i].sex;
				case 7:
					while (true)
					{
						cout << "输入入学日期（格式：YYYY-MM-DD）："; cin >> values[i].time;
						if (tjudge(values[i].time))break;
						cout << "日期输入错误，重新输入\n";
					}
					break;
				case 8:cout << "输入所需学分："; cin >> values[i].credit; break;
				case 9:cout << "输入完成学分："; cin >> values[i].f_credit; break;
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
	std::cout << "1.添加学生信息" << '\n';
	std::cout << "2.删除学生信息" << '\n';
	std::cout << "3.查询学生信息" << '\n';
	std::cout << "4.修改学生信息" << '\n';
	std::cout << "5.显示所有学生" << '\n';
	std::cout << "6.退出" << '\n';
	std::cout << "***********************" << '\n';
}
int main()
{
	student a;
	int choose = 0;
	while (choose != 6)
	{
		menu();
		cout << "输入选项：\n"; cin >> choose;
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