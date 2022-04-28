#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
typedef struct student_information {
	unsigned int id;//学号
	char name[11];//姓名
	char college[20];//系别
	char classes[20];//班级
	unsigned int age;//年龄
	char sex[3];//性别
	double credit[2];//需要完成学分
	double f_credit[2];//已完成学分
	char time[15];//入学时间
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
		cout << "学号：" << inf.id << '\n';
		cout << "姓名：" << inf.name << '\n';
		cout << "系别：" << inf.college << '\n';
		cout << "班级：" << inf.classes << '\n';
		cout << "年龄：" << inf.age << '\n';
		cout << "性别：" << inf.sex << '\n';
		cout << "第一学期所需学分：" << inf.credit[0] << '\n';
		cout << "第二学期所需学分：" << inf.credit[1] << '\n';
		cout << "第一学期已完成学分：" << inf.f_credit[0] << '\n';
		cout << "第二学期已完成学分：" << inf.f_credit[0] << '\n';
		cout << "入学日期" << inf.time << '\n';
		cout << "----------------------------\n";
}

class student
{
public:
	student();
	~student();
	void add_student();//添加
	int del_student(unsigned int id);//删除
	int rev_student(unsigned int id);//修改
	int que_student_id(unsigned int id);//查询
	int que_student_classes(char* classes);//查询
	int que_student_1(unsigned int choose);//查询
	int que_student_2(unsigned int choose);//查询
	void pri_student();//打印
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
	cout << "输入学号："; cin >> a.id;
	cout << "输入姓名："; cin >> a.name;
	cout << "输入系别："; cin >> a.college;
	cout << "输入班级："; cin >> a.classes;
	cout << "输入年龄："; cin >> a.age;
	cout << "输入性别："; cin >> a.sex;
	cout << "输入第一学期所需学分："; cin >> a.credit[0];
	cout << "输入第二学期所需学分："; cin >> a.credit[1];
	cout << "输入第一学期已完成学分："; cin >> a.f_credit[0];
	cout << "输入第二学期已完成学分："; cin >> a.f_credit[0];
	while (true)
	{
		cout << "输入入学日期（格式：YYYY-MM-DD）："; cin >> a.time;
		if (judge_time(a.time))break;
		cout << "日期输入错误，重新输入\n";
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
			cout << "1.修改学号\n2.修改姓名\n3.修改系别\n";
			cout << "4.修改班级\n5.修改年龄\n6.修改性别\n";
			cout << "7.修改第一学期所需学分\n";
			cout << "8.修改第二学期所需学分\n";
			cout << "9.修改第一学期已完成学分\n";
			cout << "10.修改第二学期已完成学分\n";
			cout << "11.修改入学日期\n";
			cout << "*********************************\n";
			cout << "输入选项："; cin >> choose;
			switch (choose)
			{
			case 1:cout << "输入学号："; cin >> inf[i].id;
				break;
			case 2:cout << "输入姓名："; cin >> inf[i].name;
				break;
			case 3:cout << "输入系别："; cin >> inf[i].college;
				break;
			case 4:cout << "输入班级："; cin >> inf[i].classes;
				break;
			case 5:cout << "输入年龄："; cin >> inf[i].age;
				break;
			case 6:cout << "输入性别："; cin >> inf[i].sex;
				break;
			case 7:cout << "输入第一学期所需学分："; cin >> inf[i].credit[0];
				break;
			case 8:cout << "输入第二学期所需学分："; cin >> inf[i].credit[1];
				break;
			case 9:cout << "输入第一学期已完成学分："; cin >> inf[i].f_credit[0];
				break;
			case 10:cout << "输入第二学期已完成学分："; cin >> inf[i].f_credit[0];
				break;
			case 11:
				while (true)
				{
					cout << "输入入学日期（格式：YYYY-MM-DD）："; cin >> inf[i].time;
					if (judge_time(inf[i].time))break;
					cout << "日期输入错误，重新输入\n";
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
	std::cout << "1.信息录入" << '\n';
	std::cout << "2.信息删除" << '\n';
	std::cout << "3.信息查询" << '\n';
	std::cout << "4.信息修改" << '\n';
	std::cout << "5.信息浏览" << '\n';
	std::cout << "6.退出" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_query()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.学号查询" << '\n';
	std::cout << "2.班级查询" << '\n';
	std::cout << "3.第一学期未完成学分查询" << '\n';
	std::cout << "4.第二学期未完成学分查询" << '\n';
	std::cout << "5.第一学期完成学分查询" << '\n';
	std::cout << "6.第二学期完成学分查询" << '\n';
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
		cout << "输入选项：\n";cin >> choose;
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
			cout << "输入需要删除学号：\n"; cin >> id;
			if (stu.del_student(id) == 0)
				cout << "未找到该学生\n";
			break;
		}
		case 3:
		{
			menu_query();
			cout << "输入选项：\n";cin >> choose1;
			switch (choose1)
			{
			case 1:
				cout << "输入需要查询学号：\n"; cin >> id;
				if (stu.que_student_id(id) == 0)
					cout << "未找到该学生\n";
				break;
			case 2:
				memset(&classes, 0, 20);
				cout << "输入需要查询班级：\n"; cin >> classes;
				if (stu.que_student_classes(classes) == 0)
					cout << "未找到该学生\n";
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
			cout << "输入需要修改学号：\n"; cin >> id;
			if (stu.rev_student(id) == 0)
				cout << "未找到该学生\n";
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