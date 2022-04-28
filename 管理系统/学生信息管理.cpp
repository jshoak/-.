// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Student
{
private:
	typedef struct information {
		char student_number[11];	//学号
		char name[21];		//名字
		char sex;			//m（男),f（女）
		double grades;		//成绩
		struct information* next;
	}stuin, *pstuin;
	pstuin head, middle, indirectly;
	int number;
public:
	Student();
	~Student();
	int addr_student();//添加
	void print_student();//打印
	int enquiry_student();//查询
	int delete_student();//删除
	void save_student();//保存
	void derived_student();//导出
};
Student::Student():middle(NULL),number(0)
{
	head = new stuin{ 0 };
	head->student_number[0] = '0';
	head->next = NULL;
	indirectly = NULL;
}
Student::~Student()
{
	while (head!=NULL)
	{
		indirectly = head->next;
		delete head;
		head = indirectly;
	}
}
int Student::addr_student()
{
	indirectly = head;
	char nu[11] = {0};
	cout << "输入插入位置前学号（初始学号0）：";
	cin.getline(nu, 11);
	while (indirectly != NULL)
	{
		if (strcmp(indirectly->student_number, nu) == 0)//比较学号是否一样
		{		
			cout << "基本信息" << endl;
			middle = new stuin{ 0 };
			cout << "输入学号：";
			cin.getline(middle->student_number, 11);	//输入学号
			cout << "输入姓名：";
			cin.getline(middle->name, 21);				//输入姓名
			cout << "输入性别【m（男),f（女)】：";
			cin >> middle->sex;							//输入性别
			cout << "输入成绩：";
			cin >> middle->grades;						//输入成绩
			cin.get();									//吃掉回车
			middle->next = indirectly->next;			//连接下一个学生信息
			indirectly->next = middle;					//连接下一个学生信息
			cout << "插入成功" << endl;
			number++;									//学生信息数量
			return 1;
		}
		indirectly = indirectly->next;
	}
	cout << "插入失败" << endl;
	return 0;
}
void Student::print_student()//打印
{
	cout << "已有学生" << number << "个" <<endl;
	indirectly = head->next;
	while (indirectly != NULL)
	{
		cout << "学号：" << indirectly->student_number << endl;
		cout << "姓名：" << indirectly->name << endl;
		cout << "性别【m（男),f（女)】：" << indirectly->sex << endl;
		cout << "成绩：" << indirectly->grades << endl;
		indirectly = indirectly->next;					//指向下一个
	}
}
int Student::enquiry_student()
{
	indirectly = head;
	char nu[11] = { 0 };
	cout << "输入需要查询学号：";
	cin.getline(nu, 11);
	while (indirectly != NULL)
	{
		if (strcmp(indirectly->student_number, nu) == 0)
		{
			cout << "学号：" << indirectly->student_number << endl;
			cout << "姓名：" << indirectly->name << endl;
			cout << "性别【m（男),f（女)】：" << indirectly->sex << endl;
			cout << "成绩：" << indirectly->grades << endl;
			return 1;
		}
		indirectly = indirectly->next;
	}
	cout << "查询失败" << endl;
	return 0;
}
int Student::delete_student()
{
	indirectly = head;
	char nu[11] = { 0 };
	cout << "输入需要删除学号：";
	cin.getline(nu, 11);
	while (indirectly->next != NULL)
	{
		if (strcmp(indirectly->next->student_number, nu) == 0)
		{
			middle = indirectly->next->next;
			delete indirectly->next;
			indirectly->next = middle;
			cout << "删除成功" << endl;
			number--;
			return 1;
		}
		indirectly = indirectly->next;
	}
	cout << "删除失败" << endl;
	return 0;
}
void Student::save_student()
{
	indirectly = head->next;
	char nu[27] = { 0 };
	int i = 0, j = 0;
	while (indirectly != NULL)
	{
		i = strlen(indirectly->name);
		j = strlen(indirectly->student_number);
		memset(nu, 0, 23);
		memcpy(nu, indirectly->name, i);								   //学生姓名
		nu[i] = indirectly->student_number[j-2];						   //学号
		nu[i + 1] = indirectly->student_number[j - 1];					   //
		nu[i + 2] = '.'; nu[i + 3] = 't'; nu[i + 4] = 'x'; nu[i + 5] = 't';//文件后缀
		ofstream outfile;
		outfile.open(nu);
		outfile << indirectly->student_number << endl;
		outfile << indirectly->name << endl;
		outfile << indirectly->sex << endl;
		outfile << indirectly->grades << endl;
		outfile.close();
		indirectly = indirectly->next;
	}
}
void Student::derived_student()
{
	char nu[27] = { 0 };
	ifstream infile;
	stuin a;
	cout << "输入文件名：";
	cin.getline(nu, 27);
	int i = strlen(nu);
	nu[i] = '.'; nu[i + 1] = 't'; nu[i + 2] = 'x'; nu[i + 3] = 't';
	infile.open(nu);
	infile >> a.student_number;
	infile >> a.name;
	infile >> a.sex;
	infile >> a.grades;
	cout << "学号：" << a.student_number << endl;
	cout << "姓名：" << a.name << endl;
	cout << "性别【m（男),f（女)】：" << a.sex << endl;
	cout << "成绩：" << a.grades << endl;
}
void print()
{
	cout << "*****学生成绩管理系统*****" << endl;
	cout << "     1.添加学生记录" << endl;
	cout << "     2.显示学生记录" << endl;
	cout << "     3.查找学生记录" << endl;
	cout << "     4.删除学生记录" << endl;
	cout << "     5.保存学生记录" << endl;
	cout << "     6.导出学生记录" << endl;
	cout << "     7.退出系统" << endl;
	cout << "**************************" << endl;
}
int main()
{
	print();
	Student a;
	int i = 0;
	while (i != 7)
	{	
		cout << "输入选项：";
		cin >> i;
		cin.get();
		system("cls");
		print();
		switch (i)
		{
		case 1:
			a.addr_student();
			break;
		case 2:
			a.print_student();
			break;
		case 3:
			a.enquiry_student();
			break;
		case 4:
			a.delete_student();
			break;
		case 5:
			a.save_student();
			break;
		case 6:
			a.derived_student();
			break;
		default:
			break;
		}
	}
	cout << "退出系统" << endl;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
