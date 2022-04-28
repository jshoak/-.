#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
typedef struct information
{
	string name;//名字
	int age = 0;//年龄
	char sex[3] = { 0 };//性别
	string addres;//住址
	double height = 0;//身高
	double weight = 0;//体重
	string parents_name;//父母姓名
	char parents_telephone[11] = { 0 };	//父母电话
	string notes;//备注
}stuin;
class Management
{
public:
	Management();
	~Management();
	void add();//增加
	int del();//删除
	int enquiry_parents();//查询父母信息
	int enquiry_addres();//查询学生住址
	void statistics();//统计
	void parin();//显示
	vector<stuin> values;
private:
	stuin student;
	string name;
	int number;
	double boy;
	double girl;
};

bool cmp_height(stuin a, stuin b)//身高降序
{
	if (a.height > b.height)
		return true;
	else 
		return false;
}

bool cmp_weight(stuin a, stuin b)//体重降序
{
	if (a.weight > b.weight)
		return true;
	else 
		return false;
}

Management::Management():number(0),boy(0),girl(0)
{
	ifstream srcFile("班级信息.txt", ios::in);
	if (srcFile) 
	{
		srcFile >> number;
		for (int i = 0; i < number; i++)
		{
			srcFile >> student.name;
			srcFile >> student.age;
			srcFile >> student.sex;
			srcFile >> student.addres;
			srcFile >> student.height;
			srcFile >> student.weight;
			srcFile >> student.parents_name;
			srcFile >> student.parents_telephone;
			srcFile >> student.notes;
			values.emplace_back(student);
			if (strcmp(student.sex, "男") == 0)
				boy++;
			else
				girl++;
		}
		srcFile.close();
	}
}

Management::~Management()
{
	ofstream destFile("班级信息.txt", ios::out);
	destFile << values.size() << '\n';
	for (unsigned int i = 0; i < values.size(); i++)
	{
		destFile << values[i].name << '\n';
		destFile << values[i].age << '\n';
		destFile << values[i].sex << '\n';
		destFile << values[i].addres << '\n';
		destFile << values[i].height << '\n';
		destFile << values[i].weight << '\n';
		destFile << values[i].parents_name << '\n';
		destFile << values[i].parents_telephone << '\n';
		destFile << values[i].notes << '\n';
	}
	destFile.close();
}

void Management::add()
{
	cout << "输入姓名："; cin >> student.name;
	cout << "输入年龄："; cin >> student.age;
	cout << "输入性别："; cin >> student.sex;
	cout << "输入住址："; cin >> student.addres;
	cout << "输入身高(cm)："; cin >> student.height;
	cout << "输入体重(kg)："; cin >> student.weight;
	cout << "输入父母姓名："; cin >> student.parents_name;
	cout << "输入父母电话："; cin >> student.parents_telephone;
	cout << "输入备注："; cin >> student.notes;
	values.emplace_back(student);
	if (strcmp(student.sex, "男") == 0)
		boy++;
	else
		girl++;
}

int Management::enquiry_parents()
{
	cout << "输入需要查询父母信息的学生姓名："; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			cout << "======================\n";
			cout << "父母姓名：" << values[i].parents_name << '\n';
			cout << "父母电话：" << values[i].parents_telephone << '\n';
			cout << "======================\n";
			return 1;
		}
	}
	cout << "未找到该学生\n"; cin >> name;
	return 0;
}

int Management::enquiry_addres()
{
	cout << "输入需要查询住址的学生姓名："; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			cout << "======================\n";
			cout << "住址：" << values[i].addres << '\n';
			cout << "======================\n";
			return 1;
		}
	}
	cout << "未找到该学生\n"; cin >> name;
	return 0;
}

int Management::del()
{
	cout << "输入需要删除的学生姓名："; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			if (strcmp(values[i].sex, "男") == 0)
				boy--;
			else
				girl--;
			values.erase(values.begin() + i);
			cout << "删除成功\n";
			return 1;
		}
	}
	cout << "未找到该学生\n"; cin >> name;
	return 0;
}

void Management::statistics()
{
	cout << "======================\n";
	cout << "男生：" << boy << "人，占" << boy / (boy + girl) * 100 << "%\n";
	cout << "女生：" << girl << "人，占" << girl / (boy + girl) * 100 << "%\n";
	cout << "======================\n";
}

void Management::parin()
{
	for (unsigned int i = 0; i < values.size(); i++)
	{
		cout << "======================\n";
		cout << "姓名：" << values[i].name << '\n';
		cout << "年龄：" << values[i].age << '\n';
		cout << "性别：" << values[i].sex << '\n';
		cout << "住址：" << values[i].addres << '\n';
		cout << "身高：" << values[i].height << '\n';
		cout << "体重：" << values[i].weight << '\n';
		cout << "父母姓名：" << values[i].parents_name << '\n';
		cout << "父母电话：" << values[i].parents_telephone << '\n';
		cout << "备注：" << values[i].notes << '\n';
		cout << "======================\n";
	}
}
int main()
{
	Management a;
	int choose = 0;
	while (choose != 9)
	{
		cout << "======================\n";
		cout << "1.添加学生\n";
		cout << "2.删除学生\n";
		cout << "3.查询父母信息\n";
		cout << "4.查询学生住址\n";
		cout << "5.身高降序\n";
		cout << "6.体重降序\n";
		cout << "7.统计\n";
		cout << "8.显示\n";
		cout << "9.退出\n";
		cout << "======================\n";
		cout << "输出选项："; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:a.add();
			break;
		case 2:a.del();
			break;
		case 3:a.enquiry_parents();
			break;
		case 4:a.enquiry_addres();
			break;
		case 5:sort(a.values.begin(), a.values.end(), cmp_height);
			cout << "排序完成\n";
			break;
		case 6:sort(a.values.begin(), a.values.end(), cmp_weight);
			cout << "排序完成\n";
			break;
		case 7:a.statistics();
			break;
		case 8:a.parin();
			break;
		default:
			break;
		}
	}
    return 0;
}