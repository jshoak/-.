#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef struct teacher_information {
	unsigned int id;//��ʦ��
	char name[11];//����
	char sex[3];//�Ա�
	char background[11];//ѧ��
	unsigned int age;//����
	char phone[12];//�绰
} t_inf;

typedef struct course_information {
	unsigned int id;//�γ̺�
	char name[11];//�γ�����
} c_inf;

typedef struct tc_information {
	unsigned int id;//�̿κ�
	char time[11];//����ʱ��
	unsigned int tid;//��ʦ��
	unsigned int cid;//�γ̺�
} tc_inf;

typedef struct student_information {
	unsigned int id;//ѧ��
	char name[11];//����
} s_inf;

typedef struct sc_information {
	unsigned int id;//ѧ�κ�
	unsigned int sid;//ѧ��
	unsigned int tcid;//�̿κ�
} sc_inf;

std::istream& operator>>(std::istream& in, t_inf& a)
{
	std::cout << "�����ʦ�ţ�";
	in >> a.id;
	std::cout << "����������";
	in >> a.name;
	std::cout << "�����Ա�";
	in >> a.sex;
	std::cout << "����ѧ����";
	in >> a.background;
	std::cout << "�������䣺";
	in >> a.age;
	std::cout << "����绰��";
	in >> a.phone;
	return in;
}
std::ostream& operator<<(std::ostream& out, t_inf& a)
{
	out << "��ʦ�ţ�" << a.id << '\n';
	out << "������" << a.name << '\n';
	out << "�Ա�" << a.sex << '\n';
	out << "ѧ����" << a.background << '\n';
	out << "���䣺" << a.age << '\n';
	out << "�绰��" << a.phone << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, c_inf& a)
{
	std::cout << "����γ̺ţ�";
	in >> a.id;
	std::cout << "����γ����ƣ�";
	in >> a.name;
	return in;
}
std::ostream& operator<<(std::ostream& out, c_inf& a)
{
	out << "�γ̺ţ�" << a.id << '\n';
	out << "�����ƣ�" << a.name << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, tc_inf& a)
{
	std::cout << "����̿κţ�";
	in >> a.id;
	std::cout << "���뿪��ʱ�䣺";
	in >> a.time;
	std::cout << "�����ʦ�ţ�";
	in >> a.tid;
	std::cout << "����γ̺ţ�";
	in >> a.cid;
	return in;
}
std::ostream& operator<<(std::ostream& out, tc_inf& a)
{
	out << "�̿κţ�" << a.id << '\n';
	out << "����ʱ�䣺" << a.time << '\n';
	out << "��ʦ�ţ�" << a.tid << '\n';
	out << "�γ̺ţ�" << a.cid << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, s_inf& a)
{
	std::cout << "����ѧ�ţ�";
	in >> a.id;
	std::cout << "����������";
	in >> a.name;
	return in;
}
std::ostream& operator<<(std::ostream& out, s_inf& a)
{
	out << "ѧ�ţ�" << a.id << '\n';
	out << "������" << a.name << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, sc_inf& a)
{
	std::cout << "����ѧ�κţ�";
	in >> a.id;
	std::cout << "����ѧ�ţ�";
	in >> a.sid;
	std::cout << "����̿κţ�";
	in >> a.tcid;
	return in;
}
std::ostream& operator<<(std::ostream& out, sc_inf& a)
{
	out << "ѧ�κţ�" << a.id << '\n';
	out << "ѧ�ţ�" << a.sid << '\n';
	out << "�̿κţ�" << a.tcid << '\n';
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
	std::cout << "1.��Ϣ¼��" << '\n';
	std::cout << "2.��Ϣɾ��" << '\n';
	std::cout << "3.��Ϣ��ѯ" << '\n';
	std::cout << "4.��Ϣ���" << '\n';
	std::cout << "5.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_add()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.��ʦ��Ϣ¼��" << '\n';
	std::cout << "2.ѧ����Ϣ¼��" << '\n';
	std::cout << "3.�γ���Ϣ¼��" << '\n';
	std::cout << "4.��ʦ��γ̹�����Ϣ¼��" << '\n';
	std::cout << "5.ѧ����γ̹�����Ϣ¼��" << '\n';
	std::cout << "6.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_del()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.��ʦ��Ϣɾ��" << '\n';
	std::cout << "2.ѧ����Ϣɾ��" << '\n';
	std::cout << "3.�γ���Ϣɾ��" << '\n';
	std::cout << "4.��ʦ��γ̹�����Ϣɾ��" << '\n';
	std::cout << "5.ѧ����γ̹�����Ϣɾ��" << '\n';
	std::cout << "6.�˳�" << '\n';
	std::cout << "***********************" << '\n';
}

void menu_query()
{
	std::cout << "***********************" << '\n';
	std::cout << "1.��ʦ��Ϣ��ѯ" << '\n';
	std::cout << "2.ѧ����Ϣ��ѯ" << '\n';
	std::cout << "3.�γ���Ϣ��ѯ" << '\n';
	std::cout << "4.��ʦ��γ̹�����Ϣ��ѯ" << '\n';
	std::cout << "5.ѧ����γ̹�����Ϣ��ѯ" << '\n';
	std::cout << "6.�˳�" << '\n';
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
		std::cout << "����ѡ�\n";
		std::cin >> choose;
		system("cls");	
		switch (choose)
		{
		case 1:
		{
			while (choose1 != 6)
			{
				menu_add();
				std::cout << "����ѡ�\n";
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
				cout << "����ѡ�\n";
				cin >> choose2;
				system("cls");
				switch (choose1)
				{
				case 1:cout << "����ɾ��ID��\n"; cin >> id; teacher.del(id); break;
				case 2:cout << "����ɾ��ID��\n"; cin >> id; student.del(id); break;
				case 3:cout << "����ɾ��ID��\n"; cin >> id; course.del(id); break;
				case 4:cout << "����ɾ��ID��\n"; cin >> id; tc.del(id); break;
				case 5:cout << "����ɾ��ID��\n"; cin >> id; sc.del(id); break;
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
				cout << "����ѡ�\n";
				cin >> choose3;
				system("cls");
				switch (choose3)
				{
				case 1:cout << "�����ѯID��\n"; cin >> id; teacher.query(id); break;
				case 2:cout << "�����ѯID��\n"; cin >> id; student.query(id); break;
				case 3:cout << "�����ѯID��\n"; cin >> id; course.query(id); break;
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
			std::cout << "��������������ʦ��Ϣ������������\n";
			teacher.print();
			std::cout << "����������������������������������\n";
			std::cout << "������������ѧ����Ϣ������������\n";
			student.print();
			std::cout << "����������������������������������\n";
			std::cout << "�������������γ���Ϣ������������\n";
			course.print();
			std::cout << "����������������������������������\n";
			std::cout << "��������ʦ��γ̹�����Ϣ��Ϣ������\n";
			tc.print();
			std::cout << "����������������������������������\n";
			std::cout << "��������ѧ����γ̹�����Ϣ��������\n";
			sc.print();
			std::cout << "����������������������������������\n";
			break;
		}
		default:
			break;
		}
	}
	return 0;
}