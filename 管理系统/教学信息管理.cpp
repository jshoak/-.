#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef struct teacher_information {
	unsigned int id;//教师号
	char name[11];//姓名
	char sex[3];//性别
	char background[11];//学历
	unsigned int age;//年龄
	char phone[12];//电话
} t_inf;

typedef struct course_information {
	unsigned int id;//课程号
	char name[11];//课程名称
} c_inf;

typedef struct tc_information {
	unsigned int id;//教课号
	char time[11];//开课时间
	unsigned int tid;//教师号
	unsigned int cid;//课程号
} tc_inf;

typedef struct student_information {
	unsigned int id;//学号
	char name[11];//姓名
} s_inf;

typedef struct sc_information {
	unsigned int id;//学课号
	unsigned int sid;//学号
	unsigned int tcid;//教课号
} sc_inf;

std::istream& operator>>(std::istream& in, t_inf& a)
{
	std::cout << "输入教师号：";
	in >> a.id;
	std::cout << "输入姓名：";
	in >> a.name;
	std::cout << "输入性别：";
	in >> a.sex;
	std::cout << "输入学历：";
	in >> a.background;
	std::cout << "输入年龄：";
	in >> a.age;
	std::cout << "输入电话：";
	in >> a.phone;
	return in;
}
std::ostream& operator<<(std::ostream& out, t_inf& a)
{
	out << "教师号：" << a.id << '\n';
	out << "姓名：" << a.name << '\n';
	out << "性别：" << a.sex << '\n';
	out << "学历：" << a.background << '\n';
	out << "年龄：" << a.age << '\n';
	out << "电话：" << a.phone << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, c_inf& a)
{
	std::cout << "输入课程号：";
	in >> a.id;
	std::cout << "输入课程名称：";
	in >> a.name;
	return in;
}
std::ostream& operator<<(std::ostream& out, c_inf& a)
{
	out << "课程号：" << a.id << '\n';
	out << "程名称：" << a.name << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, tc_inf& a)
{
	std::cout << "输入教课号：";
	in >> a.id;
	std::cout << "输入开课时间：";
	in >> a.time;
	std::cout << "输入教师号：";
	in >> a.tid;
	std::cout << "输入课程号：";
	in >> a.cid;
	return in;
}
std::ostream& operator<<(std::ostream& out, tc_inf& a)
{
	out << "教课号：" << a.id << '\n';
	out << "开课时间：" << a.time << '\n';
	out << "教师号：" << a.tid << '\n';
	out << "课程号：" << a.cid << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, s_inf& a)
{
	std::cout << "输入学号：";
	in >> a.id;
	std::cout << "输入姓名：";
	in >> a.name;
	return in;
}
std::ostream& operator<<(std::ostream& out, s_inf& a)
{
	out << "学号：" << a.id << '\n';
	out << "姓名：" << a.name << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, sc_inf& a)
{
	std::cout << "输入学课号：";
	in >> a.id;
	std::cout << "输入学号：";
	in >> a.sid;
	std::cout << "输入教课号：";
	in >> a.tcid;
	return in;
}
std::ostream& operator<<(std::ostream& out, sc_inf& a)
{
	out << "学课号：" << a.id << '\n';
	out << "学号：" << a.sid << '\n';
	out << "教课号：" << a.tcid << '\n';
	return out;
}

template<typename T>
class MyClass
{
public:
	MyClass(const char* s);
	~MyClass();
	void add();
	bool del(unsigned int id);
	void print();
	int query(unsigned int id);
	std::vector<T>inf;
private:
	T values;
	char str[20];
};

template<typename T>
MyClass<T>::MyClass(const char* s)
{
	memset(&values, 0, sizeof(T));
	memset(str, 0, sizeof(str));
	memcpy(str, s, strlen(s));
	ifstream inFile(str, ios::in | ios::binary);
	while (inFile.read((char*)&values, sizeof(T)))
		inf.push_back(values);
	inFile.close();
}

template<typename T>
MyClass<T>::~MyClass()
{
	ofstream outFile(str, ios::out | ios::binary);
	for (unsigned int i = 0; i < inf.size(); i++)
		outFile.write((char*)&inf[i], sizeof(T));
	outFile.close();
}

template<typename T>
void MyClass<T>::add()
{
	cin >> values;
	inf.push_back(values);
}

template<typename T>
bool MyClass<T>::del(unsigned int id)
{
	for (unsigned int i = 0; i < inf.size(); i++)
		if (id == inf[i].id)
		{
			inf.erase(inf.begin() + i);
			return true;
		}				
	return false;
}

template<typename T>
void MyClass<T>::print()
{
	for (unsigned int i = 0; i < inf.size(); i++)
		cout << inf[i] << endl;
}

template<typename T>
int MyClass<T>::query(unsigned int id)
{
	for (unsigned int i = 0; i < inf.size(); i++)
		if (id == inf[i].id)
		{
			cout << inf[i] << endl;
			return i;
		}
	return 0;
}

void menu()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.信息录入" << '\n';
	std::cout << "2.信息删除" << '\n';
	std::cout << "3.信息查询" << '\n';
	std::cout << "4.信息浏览" << '\n';
	std::cout << "5.退出" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_add()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.教师信息录入" << '\n';
	std::cout << "2.学生信息录入" << '\n';
	std::cout << "3.课程信息录入" << '\n';
	std::cout << "4.教师与课程关联信息录入" << '\n';
	std::cout << "5.学生与课程关联信息录入" << '\n';
	std::cout << "6.退出" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_del()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.教师信息删除" << '\n';
	std::cout << "2.学生信息删除" << '\n';
	std::cout << "3.课程信息删除" << '\n';
	std::cout << "4.教师与课程关联信息删除" << '\n';
	std::cout << "5.学生与课程关联信息删除" << '\n';
	std::cout << "6.退出" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_query()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.教师信息查询" << '\n';
	std::cout << "2.学生信息查询" << '\n';
	std::cout << "3.课程信息查询" << '\n';
	std::cout << "4.教师与课程关联信息查询" << '\n';
	std::cout << "5.学生与课程关联信息查询" << '\n';
	std::cout << "6.退出" << '\n';
	std::cout << "***********************" << '\n';
}


int main()
{
	MyClass<t_inf> teacher("teacher.dat");
	MyClass<s_inf> student("student.dat");
	MyClass<c_inf> course("course.dat");
	MyClass<tc_inf> tc("tc.dat");
	MyClass<sc_inf> sc("sc.dat");
	int choose = 0, choose1 = 0, choose2 = 0, choose3 = 0;
	unsigned int id = 0, j = 0;;
	while (choose != 5)
	{
		menu();
		std::cout << "输入选项：\n";
		std::cin >> choose;
		system("cls");	
		switch (choose)
		{
		case 1:
		{
			while (choose1 != 6)
			{
				menu_add();
				std::cout << "输入选项：\n";
				std::cin >> choose1;
				system("cls");
				switch (choose1)
				{
				case 1:teacher.add(); break;
				case 2:student.add(); break;
				case 3:course.add(); break;
				case 4:tc.add(); break;
				case 5:sc.add(); break;
				default:break;
				}
			}
			choose1 = 0;
			break;
		}
		case 2:
		{
			while (choose2 != 6)
			{
				menu_del();
				cout << "输入选项：\n";
				cin >> choose2;
				system("cls");
				switch (choose1)
				{
				case 1:cout << "输入删除ID：\n"; cin >> id; teacher.del(id); break;
				case 2:cout << "输入删除ID：\n"; cin >> id; student.del(id); break;
				case 3:cout << "输入删除ID：\n"; cin >> id; course.del(id); break;
				case 4:cout << "输入删除ID：\n"; cin >> id; tc.del(id); break;
				case 5:cout << "输入删除ID：\n"; cin >> id; sc.del(id); break;
				default:break;
				}
			}
			choose2 = 0;
			break;
		}
		case 3:
		{
			while (choose3 != 6)
			{
				menu_query();
				cout << "输入选项：\n";
				cin >> choose3;
				system("cls");
				switch (choose3)
				{
				case 1:cout << "输入查询ID：\n"; cin >> id; teacher.query(id); break;
				case 2:cout << "输入查询ID：\n"; cin >> id; student.query(id); break;
				case 3:cout << "输入查询ID：\n"; cin >> id; course.query(id); break;
				case 4:
				{
					for (unsigned int i = 0; i < tc.inf.size(); i++)
					{
						teacher.query(tc.inf[i].tid);
						course.query(tc.inf[i].cid);
					}
					break;
				}
				case 5:
				{
					for (unsigned int i = 0; i < sc.inf.size(); i++)
					{
						student.query(sc.inf[i].sid);
						j = tc.query(sc.inf[i].tcid);
						course.query(tc.inf[j].cid);
					}
					break;
				}
				default:break;
				}
			}
			choose3 = 0;
			break;
		}			
		case 4:
		{
			std::cout << "——————教师信息——————\n";
			teacher.print();
			std::cout << "—————————————————\n";
			std::cout << "——————学生信息——————\n";
			student.print();
			std::cout << "—————————————————\n";
			std::cout << "——————课程信息——————\n";
			course.print();
			std::cout << "—————————————————\n";
			std::cout << "———教师与课程关联信息信息———\n";
			tc.print();
			std::cout << "—————————————————\n";
			std::cout << "————学生与课程关联信息————\n";
			sc.print();
			std::cout << "—————————————————\n";
			break;
		}
		default:
			break;
		}
	}
	return 0;
}