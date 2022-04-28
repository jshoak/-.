#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
#define MAX 10

//设计联系人结构体
struct Person
{
	//姓名
	string m_Name;
	//性别  1 男  2 女
	int m_Sex = 0;
	//电话号码
	string m_Phone;
	//类别    1 同事类  2 朋友类  3 商务类  4 一般类
	int m_Group = 0;
	//电子邮件
	string m_Email;
};

//设计通讯录结构体
struct Addressbooks
{
	//通讯录中保存的联系人数组
	Person personArray[MAX];

	//通讯录中当前记录联系人个数
	int m_Size = 0;
};

//文件读写
int readPerson(Addressbooks* abs)
{
	int k = 0;
	ifstream srcFile("Person.txt", ios::in); //以文本模式打开读
	if (!srcFile)
	{
		cout << "读取失败" << endl;
		system("pause"); // 请按任意键继续
		system("cls"); // 清屏操作
		return 0;
	}
	srcFile >> k;
	for (int i = abs->m_Size; i < abs->m_Size + k; i++)
	{
		srcFile >> abs->personArray[i].m_Name;
		srcFile >> abs->personArray[i].m_Sex;
		srcFile >> abs->personArray[i].m_Phone;
		srcFile >> abs->personArray[i].m_Group;
		srcFile >> abs->personArray[i].m_Email;
	}
	abs->m_Size += k;
	srcFile.close();
	cout << "读取成功" << endl;
	system("pause"); // 请按任意键继续
	system("cls"); // 清屏操作
	return 1;
}
int writePerson(Addressbooks* abs)
{
	ofstream destFile("Person.txt", ios::out); //以文本模式打开写
	if (!destFile)
	{
		cout << "写入失败" << endl;
		system("pause"); // 请按任意键继续
		system("cls"); // 清屏操作
		return 0;
	}
	destFile << abs->m_Size << '\n';
	for (int i = 0; i < abs->m_Size; i++)
	{
		destFile << abs->personArray[i].m_Name << '\n';
		destFile << abs->personArray[i].m_Sex << '\n';
		destFile << abs->personArray[i].m_Phone << '\n';
		destFile << abs->personArray[i].m_Group << '\n';
		destFile << abs->personArray[i].m_Email << '\n';
	}
	destFile.close();
	cout << "写入成功" << endl;
	system("pause"); // 请按任意键继续
	system("cls"); // 清屏操作
	return 1;
}

//1、添加联系人
int inperson(Addressbooks* abs, int siz)
{
	//性别
	cout << "请输入性别： " << endl;
	cout << "1 --- 男" << endl;
	cout << "2 --- 女" << endl;
	int sex = 0;
	while (true)
	{
		//如果输入的是1 或者 2 可以退出循环，因为输入的是正确值
		//如果输入有误，重新输入
		cin >> sex;
		if (sex == 1 || sex == 2)
		{
			abs->personArray[siz].m_Sex = sex;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	//电话号码
	cout << "请输入联系电话： " << endl;
	string phone;
	cin >> phone;
	abs->personArray[siz].m_Phone = phone;
	//类别
	cout << "请输入类别：" << endl;
	cout << "1 --- 同事类" << endl;
	cout << "2 --- 朋友类" << endl;
	cout << "3 --- 商务类" << endl;
	cout << "4 --- 一般类" << endl;
	int group = 0;
	while (true)
	{
		//如果输入的是1 或者 2 或者 3 或者 4可以退出循环，因为输入的是正确值
		//如果输入有误，重新输入
		cin >> group;
		if (group == 1 || group == 2 || group == 3 || group == 4)
		{
			abs->personArray[siz].m_Group = group;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	//电子邮件
	cout << "请输入电子邮件：" << endl;
	string email;
	cin >> email;
	abs->personArray[siz].m_Email = email;
	return 1;
}
void addPerson(Addressbooks* abs)
{
	int k = 0;
	//判断通讯录是否已满，如果满了就不再添加
	if (abs->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
		//添加具体联系人

		//姓名
		string name;
		cout << "请输入姓名： " << endl;
		cin >> name;
		for (int i = 0; i < abs->m_Size; i++)
		{
			if (abs->personArray[i].m_Name == name)
			{
				cout << "记录已存在（1.增加   2.覆盖）" << endl;
				cin >> k;
				if (k == 1)break;
				if (k == 2)
				{
					abs->personArray[i].m_Name = name;
					inperson(abs, i);
					cout << "添加成功" << endl;
					system("pause"); // 请按任意键继续
					system("cls"); // 清屏操作
					return;
				}
			}
		}
		abs->personArray[abs->m_Size].m_Name = name;
		inperson(abs, abs->m_Size);
		/*
		//性别
		cout << "请输入性别： " << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex = 0;
		while (true)
		{
			//如果输入的是1 或者 2 可以退出循环，因为输入的是正确值
			//如果输入有误，重新输入
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}


		//电话号码
		cout << "请输入联系电话： " << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;
		//类别
		cout << "请输入类别：" << endl;
		cout << "1 --- 同事类" << endl;
		cout << "2 --- 朋友类" << endl;
		cout << "3 --- 商务类" << endl;
		cout << "4 --- 一般类" << endl;
		int group = 0;
		while (true)
		{
			//如果输入的是1 或者 2 或者 3 或者 4可以退出循环，因为输入的是正确值
			//如果输入有误，重新输入
			cin >> group;
			if (group == 1 || group == 2 || group == 3 || group == 4)
			{
				abs->personArray[abs->m_Size].m_Group = group;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}

		//电子邮件
		cout << "请输入电子邮件：" << endl;
		string email;
		cin >> email;
		abs->personArray[abs->m_Size].m_Email = email;
		/**/
		//更新通讯录人数
		abs->m_Size++;

		cout << "添加成功" << endl;

		system("pause"); // 请按任意键继续
		system("cls"); // 清屏操作
	}
}


//2、显示所有联系人
void showPerson(Addressbooks* abs)
{
	//判断通讯录中人数是否为0，如果为0，提示记录为空
	//如果不为0，显示记录的联系人信息
	if (abs->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "姓名： " << abs->personArray[i].m_Name << "\t";
			cout << "性别： " << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";//注意加括号
			cout << "电话号码： " << abs->personArray[i].m_Phone << "\t";
			if (abs->personArray[i].m_Group == 1)
			{
				cout << " 同事类" << endl;
			}
			else if (abs->personArray[i].m_Group == 2)
			{
				cout << " 朋友类" << endl;
			}
			else if (abs->personArray[i].m_Group == 3)
			{
				cout << " 商务类" << endl;
			}
			else
			{
				cout << " 一般类" << endl;
			}
			cout << "电子邮件： " << abs->personArray[i].m_Email << endl;
		}
	}

	system("pause"); //按任意键继续
	system("cls"); //清屏

}


//检测联系人是否存在，如果存在，返回联系人所在数组中的具体位置，不存在返回-1
//参数1  通讯录  参数2  对比姓名
int isExist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//找到用户输入的姓名了
		if (abs->personArray[i].m_Name == name)
		{
			return i;  //找到了，返回这个人在数组中的下标编号
		}
	}
	return -1;//如果遍历结束都没有找到，返回-1
}
int isExist(Addressbooks* abs, int group)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//找到用户输入的类别了
		if (abs->personArray[i].m_Group == group)
		{
			return i; //找到了，返回这个人在数组中的下标编号
		}
	}
	return -1; //如果遍历结束都没有找到，返回-1
}

//3、删除指定联系人
void deletePerson(Addressbooks* abs)
{
	cout << "请输入您要删除的联系人" << endl;

	string name;
	cin >> name;

	//ret == -1  未查到
	//ret != -1  查到了
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		//查找到人，要进行删除操作
		for (int i = ret; i < abs->m_Size; i++)
		{
			//数据前移
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--; //更新通讯录中的人员数
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}

//4、查找指定联系人信息
void findPerson(Addressbooks* abs)
{
	cout << "请输入查找类型: " << "\t";
	cout << "1---按姓名查找  " << endl;
	cout << "2---按类别查找  " << endl;
	int input;
	scanf_s("%d", &input);
	switch (input)
	{
	case 1:
	{
		cout << "请输入名字： " << "\t";
		string name;
		cin >> name;

		//判断指定的联系人是否存在通讯录中
		int ret = isExist(abs, name);


		if (ret != -1) //找到联系人
		{
			cout << "姓名： " << abs->personArray[ret].m_Name << "\t";
			cout << "性别： " << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";//注意加括号
			cout << "电话号码： " << abs->personArray[ret].m_Phone << "\t";
			if (abs->personArray[ret].m_Group == 1)
			{
				cout << " 同事类" << endl;
			}
			else if (abs->personArray[ret].m_Group == 2)
			{
				cout << " 朋友类" << endl;
			}
			else if (abs->personArray[ret].m_Group == 3)
			{
				cout << " 商务类" << endl;
			}
			else
			{
				cout << " 一般类" << endl;
			}
			cout << "电子邮件： " << abs->personArray[ret].m_Email << endl;
		}
		else  //未找到联系人
		{
			cout << "查无此人" << endl;
		}
		//任意键按下后 清屏
		system("pause");
		system("cls");
		break;
	}

	case 2:
	{
		cout << "请输入类别： " << "\t";
		int group;
		cin >> group;

		int ret = isExist(abs, group);
		if (ret != -1) //找到联系人
		{
			cout << "姓名： " << abs->personArray[ret].m_Name << "\t";
			cout << "性别： " << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";//注意加括号
			cout << "电话号码： " << abs->personArray[ret].m_Phone << "\t";
			if (abs->personArray[ret].m_Group == 1)
			{
				cout << " 同事类" << endl;
			}
			else if (abs->personArray[ret].m_Group == 2)
			{
				cout << " 朋友类" << endl;
			}
			else if (abs->personArray[ret].m_Group == 3)
			{
				cout << " 商务类" << endl;
			}
			else
			{
				cout << " 一般类" << endl;
			}
			cout << "电子邮件： " << abs->personArray[ret].m_Email << endl;
		}
		else  //未找到联系人
		{
			cout << "查无此人" << endl;
		}
	}
	//任意键按下后 清屏
	system("pause");
	system("cls");
	break;
	}
}

//菜单界面
void showMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、从文件读取  *****" << endl;
	cout << "*****  6、输入到文件  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}


int main()
{

	//创建通讯录结构体变量
	Addressbooks abs;
	//初始化通讯录中当前人员个数
	abs.m_Size = 0;

	int select = 0; // 创建用户选择输入的变量

	while (true)
	{
		//菜单调用
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1: // 1、添加联系人
			addPerson(&abs); //利用地址传递，可以修饰实参
			break;
		case 2: // 2、显示联系人
			showPerson(&abs);
			break;
		case 3: // 3、删除联系人
			deletePerson(&abs);
			break;
		case 4: // 4、查找联系人
			findPerson(&abs);
			break;
		case 5: // 5、读入联系人
			readPerson(&abs);
			break;
		case 6: // 6、写入联系人
			writePerson(&abs);
			break;
		case 0: // 0、退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}

	}

	system("pause");
	return 0;
}