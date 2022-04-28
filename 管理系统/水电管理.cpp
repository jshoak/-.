#include <iostream>
using namespace std;
#define m 15//最多人数
typedef struct information
{
	double dosage;//用量
	double charges;//收费
	char id[10];//ID
	char this_time[10];//本次抄表时间
	char last_time[10];//上次抄表时间
	bool mark;//缴费标记
}inf;
class expenses//收费
{
public:
	inf water;
	inf electricity;
	inf gas;
	expenses(double exwa, double exel, double exga);
	virtual int exed() = 0;
	friend istream& operator>>(istream& in, expenses& a);
	friend ostream& operator<<(ostream& out, expenses& a);
private:
};
istream& operator>>(istream& in, expenses& a)
{
	cout << "水用量："; in >> a.water.dosage;
	cout << "表号："; in >> a.water.id;
	cout << "本次抄表时间："; in >> a.water.this_time;
	cout << "上次抄表时间："; in >> a.water.last_time;
	cout << "是否缴费（1已缴，0未缴）："; in >> a.water.mark;
	cout << "--------------------------------\n";

	cout << "电用量："; in >> a.electricity.dosage;
	cout << "表号："; in >> a.electricity.id;
	cout << "本次抄表时间："; in >> a.electricity.this_time;
	cout << "上次抄表时间："; in >> a.electricity.last_time;
	cout << "是否缴费（1已缴，0未缴）："; in >> a.electricity.mark;
	cout << "--------------------------------\n";

	cout << "煤气用量："; in >> a.gas.dosage;
	cout << "表号："; in >> a.gas.id;
	cout << "本次抄表时间："; in >> a.gas.this_time;
	cout << "上次抄表时间："; in >> a.gas.last_time;
	cout << "是否缴费（1已缴，0未缴）："; in >> a.gas.mark;
	cout << "--------------------------------\n";
	a.exed();
	return in;
}
ostream& operator<<(ostream& out, expenses& a)
{
	out << "水费：(" << a.water.charges << (a.water.mark ? ")已缴" : ")未缴")
		<< "\n表号：" << a.water.id << "  本次抄表时间：" << a.water.this_time << '\n'
		<< "电费：(" << a.electricity.charges << (a.electricity.mark ? ")已缴" : ")未缴")
		<< "\n表号：" << a.electricity.id << "  本次抄表时间：" << a.electricity.this_time << '\n'
		<< "煤气费：(" << a.gas.charges << (a.gas.mark ? ")已缴" : ")未缴")
		<< "\n表号：" << a.gas.id << "  本次抄表时间：" << a.gas.this_time << "\n";
	return out;
}
expenses::expenses(double exwa, double exel, double exga)
{
	memset(&water, 0, sizeof(water));
	memset(&electricity, 0, sizeof(electricity));
	memset(&gas, 0, sizeof(gas));
	water.charges = exwa;
	electricity.charges = exel;
	gas.charges = exga;
}

/*----------------------居民------------------------*/
class resident :virtual public expenses
{
public:
	char name[10];//姓名
	char address[10];//地址
	char contact[10];//联系方式
	resident();
	virtual int exed();
};
resident::resident():expenses(1,1,1)
{
	memset(name,0,sizeof(name));
	memset(address, 0, sizeof(address));
	memset(contact, 0, sizeof(contact));
}
int resident::exed()
{
	water.charges = water.dosage * water.charges;
	electricity.charges = electricity.dosage * electricity.charges;
	gas.charges = gas.dosage * gas.charges;
	return 0;
}
/*--------------------------------------------------*/
/*----------------------教师------------------------*/
class teacher :public resident
{
public:
	char teacher_number[10];//职工号
	teacher();
	virtual int exed();
};
int k = 0;
teacher::teacher() :resident(), expenses(0.8, 0.8, 0.8)
{
	memset(teacher_number, 0, sizeof(teacher_number));
}
int teacher::exed()
{
	water.charges = water.dosage * water.charges;
	electricity.charges = electricity.dosage * electricity.charges;
	gas.charges = gas.dosage * gas.charges;
	return 0;
}
/*--------------------------------------------------*/
/*--------------------学生--------------------------*/
class student
{
public:
	char name[10];//姓名
	char address[10];//地址
	char contact[10];//联系方式
	char student_number[10];//学号
	double water;
	double electricity;
	double exwater;
	double exelectricity;
	bool w;
	bool e;
	student();
	int exed();
	friend istream& operator>>(istream& in, expenses& a);
	friend ostream& operator<<(ostream& out, expenses& a);
};
student::student() :exwater(1.2), exelectricity(1.2), e(0), w(0), water(0), electricity(0)
{
	memset(name, 0, sizeof(name));
	memset(address, 0, sizeof(address));
	memset(contact, 0, sizeof(contact));
	memset(student_number, 0, sizeof(student_number));
}
int student::exed()
{
	if (water > 5.0)exwater = (water - 5.0) * exwater;
	else
	{
		exwater = 0;
		w = 1;
	}
	if (electricity > 5.0)exelectricity = (electricity - 5.0) * exelectricity;
	else
	{
		exelectricity = 0;
		w = 1;
	}
	return 0;
}
istream& operator>>(istream& in, student& a)
{
	cout << "水用量："; in >> a.water;
	cout << "是否缴费（1已缴，0未缴）："; in >> a.w;
	cout << "--------------------------------\n";

	cout << "电用量："; in >> a.electricity;
	cout << "是否缴费（1已缴，0未缴）："; in >> a.e;
	cout << "--------------------------------\n";
	a.exed();
	return in;
}
ostream& operator<<(ostream& out, student& a)
{
	out << "水费：(" << a.exwater << (a.w ? ")已缴" : ")未缴")
		<< "电费：(" << a.exelectricity << (a.e ? ")已缴" : ")未缴") << '\n';
	return out;
}
/*--------------------------------------------------*/
/*-------------------------------------------------*/
void interface()
{
	cout << "1.居民费用录入" << '\n';
	cout << "2.教师费用录入" << '\n';
	cout << "3.学生费用录入" << '\n';
	cout << "4.查询" << '\n';
	cout << "5.未缴费名单" << '\n';
	cout << "6.退出：" << '\n';
}
int main()
{
	resident a[m];
	teacher b[m];
	student c[m];
	expenses* p = NULL;
	int a1 = 0, b1 = 0, c1 = 0, j = 0, i = 0;
	char nu[10] = { 0 };
	int choose = 0;
	while (choose!=6)
	{
		interface();
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			cout << "输入需要录入人数：" ;
			cin >> j;
			for (i = a1; i < j; i++)
			{
				cout << "姓名：";
				cin >> a[i].name;
				cout << "地址：";
				cin >> a[i].address;
				cout << "联系方式：";
				cin >> a[i].contact;
				cin >> a[i];
				cout << a[i] << '\n';
				a1++;
			}
			break;
		}
		case 2:
		{
			cout << "输入需要录入人数：";
			cin >> j;
			for (i = b1; i < j; i++)
			{
				cout << "姓名：";
				cin >> b[i].name;
				cout << "地址：";
				cin >> b[i].address;
				cout << "联系方式：";
				cin >> b[i].contact;
				cout << "职工号：";
				cin >> b[i].teacher_number;
				cin >> b[i];
				cout << b[i] << '\n';
				b1++;
			}
			break;
		}
		case 3:
		{
			cout << "输入需要录入人数：";
			cin >> j;
			for (i = c1; i < j; i++)
			{
				cout << "姓名：";
				cin >> c[i].name;
				cout << "地址：";
				cin >> c[i].address;
				cout << "联系方式：";
				cin >> c[i].contact;
				cout << "学号：";
				cin >> c[i].student_number;
				cin >> c[i];
				cout << c[i] << '\n';
				c1++;
			}
			break;
		}
		case 4:
		{
			memset(nu, 0, sizeof(nu));
			cout << "输入查询姓名：" << '\n';
			cin >> nu;
			for (i = 0; i < a1; i++)
			{
				if (!strcmp(a[i].name, nu))
				{
					cout << "姓名：" << a[i].name << '\n';
					cout << "地址：" << a[i].address << '\n';
					cout << "联系方式：" << a[i].contact << '\n';
					cout << a[i];
				}
			}
			for (i = 0; i < b1; i++)
			{
				if (!strcmp(b[i].name, nu))
				{
					cout << "姓名：" << b[i].name << '\n';
					cout << "地址：" << b[i].address << '\n';
					cout << "联系方式：" << b[i].contact << '\n';
					cout << "职工号：" << b[i].teacher_number << '\n';
					cout << b[i];
				}
			}
			for (i = 0; i < c1; i++)
			{
				if (!strcmp(c[i].name, nu))
				{
					cout << "姓名：" << c[i].name << '\n';
					cout << "地址：" << c[i].address << '\n';
					cout << "联系方式：" << c[i].contact << '\n';
					cout << "学号：" << c[i].student_number << '\n';
					cout << c[i];
				}
			}
			break;
		}
		case 5:
		{
			cout << "=====居民未缴费名单=====" << '\n';
			for (i = 0; i < a1; i++)
			{
				if (!a[i].water.mark || !a[i].electricity.mark || !a[i].gas.mark)
				{
					cout << "姓名：" << a[i].name << '\n';
					cout << "地址：" << a[i].address << '\n';
					cout << "联系方式：" << a[i].contact << '\n';
					cout << a[i];
				}
			}
			cout << "=====教师未缴费名单=====" << '\n';
			for (i = 0; i < b1; i++)
			{
				if (!b[i].water.mark || !b[i].electricity.mark || !b[i].gas.mark)
				{
					cout << "姓名：" << b[i].name << '\n';
					cout << "地址：" << b[i].address << '\n';
					cout << "联系方式：" << b[i].contact << '\n';
					cout << "职工号：" << b[i].teacher_number << '\n';
					cout << b[i];
				}
			}
			cout << "=====学生未缴费名单=====" << '\n';
			for (i = 0; i < c1; i++)
			{
				if (!c[i].w || !c[i].e)
				{
					cout << "姓名：" << c[i].name << '\n';
					cout << "地址：" << c[i].address << '\n';
					cout << "联系方式：" << c[i].contact << '\n';
					cout << "学号：" << c[i].student_number << '\n';
					cout << c[i];
				}
			}
			break;
		}
		default:
			break;
		}
	}
    return 0;
}