#include <iostream>
using namespace std;
#define m 15//�������
typedef struct information
{
	double dosage;//����
	double charges;//�շ�
	char id[10];//ID
	char this_time[10];//���γ���ʱ��
	char last_time[10];//�ϴγ���ʱ��
	bool mark;//�ɷѱ��
}inf;
class expenses//�շ�
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
	cout << "ˮ������"; in >> a.water.dosage;
	cout << "��ţ�"; in >> a.water.id;
	cout << "���γ���ʱ�䣺"; in >> a.water.this_time;
	cout << "�ϴγ���ʱ�䣺"; in >> a.water.last_time;
	cout << "�Ƿ�ɷѣ�1�ѽɣ�0δ�ɣ���"; in >> a.water.mark;
	cout << "--------------------------------\n";

	cout << "��������"; in >> a.electricity.dosage;
	cout << "��ţ�"; in >> a.electricity.id;
	cout << "���γ���ʱ�䣺"; in >> a.electricity.this_time;
	cout << "�ϴγ���ʱ�䣺"; in >> a.electricity.last_time;
	cout << "�Ƿ�ɷѣ�1�ѽɣ�0δ�ɣ���"; in >> a.electricity.mark;
	cout << "--------------------------------\n";

	cout << "ú��������"; in >> a.gas.dosage;
	cout << "��ţ�"; in >> a.gas.id;
	cout << "���γ���ʱ�䣺"; in >> a.gas.this_time;
	cout << "�ϴγ���ʱ�䣺"; in >> a.gas.last_time;
	cout << "�Ƿ�ɷѣ�1�ѽɣ�0δ�ɣ���"; in >> a.gas.mark;
	cout << "--------------------------------\n";
	a.exed();
	return in;
}
ostream& operator<<(ostream& out, expenses& a)
{
	out << "ˮ�ѣ�(" << a.water.charges << (a.water.mark ? ")�ѽ�" : ")δ��")
		<< "\n��ţ�" << a.water.id << "  ���γ���ʱ�䣺" << a.water.this_time << '\n'
		<< "��ѣ�(" << a.electricity.charges << (a.electricity.mark ? ")�ѽ�" : ")δ��")
		<< "\n��ţ�" << a.electricity.id << "  ���γ���ʱ�䣺" << a.electricity.this_time << '\n'
		<< "ú���ѣ�(" << a.gas.charges << (a.gas.mark ? ")�ѽ�" : ")δ��")
		<< "\n��ţ�" << a.gas.id << "  ���γ���ʱ�䣺" << a.gas.this_time << "\n";
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

/*----------------------����------------------------*/
class resident :virtual public expenses
{
public:
	char name[10];//����
	char address[10];//��ַ
	char contact[10];//��ϵ��ʽ
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
/*----------------------��ʦ------------------------*/
class teacher :public resident
{
public:
	char teacher_number[10];//ְ����
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
/*--------------------ѧ��--------------------------*/
class student
{
public:
	char name[10];//����
	char address[10];//��ַ
	char contact[10];//��ϵ��ʽ
	char student_number[10];//ѧ��
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
	cout << "ˮ������"; in >> a.water;
	cout << "�Ƿ�ɷѣ�1�ѽɣ�0δ�ɣ���"; in >> a.w;
	cout << "--------------------------------\n";

	cout << "��������"; in >> a.electricity;
	cout << "�Ƿ�ɷѣ�1�ѽɣ�0δ�ɣ���"; in >> a.e;
	cout << "--------------------------------\n";
	a.exed();
	return in;
}
ostream& operator<<(ostream& out, student& a)
{
	out << "ˮ�ѣ�(" << a.exwater << (a.w ? ")�ѽ�" : ")δ��")
		<< "��ѣ�(" << a.exelectricity << (a.e ? ")�ѽ�" : ")δ��") << '\n';
	return out;
}
/*--------------------------------------------------*/
/*-------------------------------------------------*/
void interface()
{
	cout << "1.�������¼��" << '\n';
	cout << "2.��ʦ����¼��" << '\n';
	cout << "3.ѧ������¼��" << '\n';
	cout << "4.��ѯ" << '\n';
	cout << "5.δ�ɷ�����" << '\n';
	cout << "6.�˳���" << '\n';
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
			cout << "������Ҫ¼��������" ;
			cin >> j;
			for (i = a1; i < j; i++)
			{
				cout << "������";
				cin >> a[i].name;
				cout << "��ַ��";
				cin >> a[i].address;
				cout << "��ϵ��ʽ��";
				cin >> a[i].contact;
				cin >> a[i];
				cout << a[i] << '\n';
				a1++;
			}
			break;
		}
		case 2:
		{
			cout << "������Ҫ¼��������";
			cin >> j;
			for (i = b1; i < j; i++)
			{
				cout << "������";
				cin >> b[i].name;
				cout << "��ַ��";
				cin >> b[i].address;
				cout << "��ϵ��ʽ��";
				cin >> b[i].contact;
				cout << "ְ���ţ�";
				cin >> b[i].teacher_number;
				cin >> b[i];
				cout << b[i] << '\n';
				b1++;
			}
			break;
		}
		case 3:
		{
			cout << "������Ҫ¼��������";
			cin >> j;
			for (i = c1; i < j; i++)
			{
				cout << "������";
				cin >> c[i].name;
				cout << "��ַ��";
				cin >> c[i].address;
				cout << "��ϵ��ʽ��";
				cin >> c[i].contact;
				cout << "ѧ�ţ�";
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
			cout << "�����ѯ������" << '\n';
			cin >> nu;
			for (i = 0; i < a1; i++)
			{
				if (!strcmp(a[i].name, nu))
				{
					cout << "������" << a[i].name << '\n';
					cout << "��ַ��" << a[i].address << '\n';
					cout << "��ϵ��ʽ��" << a[i].contact << '\n';
					cout << a[i];
				}
			}
			for (i = 0; i < b1; i++)
			{
				if (!strcmp(b[i].name, nu))
				{
					cout << "������" << b[i].name << '\n';
					cout << "��ַ��" << b[i].address << '\n';
					cout << "��ϵ��ʽ��" << b[i].contact << '\n';
					cout << "ְ���ţ�" << b[i].teacher_number << '\n';
					cout << b[i];
				}
			}
			for (i = 0; i < c1; i++)
			{
				if (!strcmp(c[i].name, nu))
				{
					cout << "������" << c[i].name << '\n';
					cout << "��ַ��" << c[i].address << '\n';
					cout << "��ϵ��ʽ��" << c[i].contact << '\n';
					cout << "ѧ�ţ�" << c[i].student_number << '\n';
					cout << c[i];
				}
			}
			break;
		}
		case 5:
		{
			cout << "=====����δ�ɷ�����=====" << '\n';
			for (i = 0; i < a1; i++)
			{
				if (!a[i].water.mark || !a[i].electricity.mark || !a[i].gas.mark)
				{
					cout << "������" << a[i].name << '\n';
					cout << "��ַ��" << a[i].address << '\n';
					cout << "��ϵ��ʽ��" << a[i].contact << '\n';
					cout << a[i];
				}
			}
			cout << "=====��ʦδ�ɷ�����=====" << '\n';
			for (i = 0; i < b1; i++)
			{
				if (!b[i].water.mark || !b[i].electricity.mark || !b[i].gas.mark)
				{
					cout << "������" << b[i].name << '\n';
					cout << "��ַ��" << b[i].address << '\n';
					cout << "��ϵ��ʽ��" << b[i].contact << '\n';
					cout << "ְ���ţ�" << b[i].teacher_number << '\n';
					cout << b[i];
				}
			}
			cout << "=====ѧ��δ�ɷ�����=====" << '\n';
			for (i = 0; i < c1; i++)
			{
				if (!c[i].w || !c[i].e)
				{
					cout << "������" << c[i].name << '\n';
					cout << "��ַ��" << c[i].address << '\n';
					cout << "��ϵ��ʽ��" << c[i].contact << '\n';
					cout << "ѧ�ţ�" << c[i].student_number << '\n';
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