#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
typedef struct information
{
	string name;//����
	int age = 0;//����
	char sex[3] = { 0 };//�Ա�
	string addres;//סַ
	double height = 0;//���
	double weight = 0;//����
	string parents_name;//��ĸ����
	char parents_telephone[11] = { 0 };	//��ĸ�绰
	string notes;//��ע
}stuin;
class Management
{
public:
	Management();
	~Management();
	void add();//����
	int del();//ɾ��
	int enquiry_parents();//��ѯ��ĸ��Ϣ
	int enquiry_addres();//��ѯѧ��סַ
	void statistics();//ͳ��
	void parin();//��ʾ
	vector<stuin> values;
private:
	stuin student;
	string name;
	int number;
	double boy;
	double girl;
};

bool cmp_height(stuin a, stuin b)//��߽���
{
	if (a.height > b.height)
		return true;
	else 
		return false;
}

bool cmp_weight(stuin a, stuin b)//���ؽ���
{
	if (a.weight > b.weight)
		return true;
	else 
		return false;
}

Management::Management():number(0),boy(0),girl(0)
{
	ifstream srcFile("�༶��Ϣ.txt", ios::in);
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
			if (strcmp(student.sex, "��") == 0)
				boy++;
			else
				girl++;
		}
		srcFile.close();
	}
}

Management::~Management()
{
	ofstream destFile("�༶��Ϣ.txt", ios::out);
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
	cout << "����������"; cin >> student.name;
	cout << "�������䣺"; cin >> student.age;
	cout << "�����Ա�"; cin >> student.sex;
	cout << "����סַ��"; cin >> student.addres;
	cout << "�������(cm)��"; cin >> student.height;
	cout << "��������(kg)��"; cin >> student.weight;
	cout << "���븸ĸ������"; cin >> student.parents_name;
	cout << "���븸ĸ�绰��"; cin >> student.parents_telephone;
	cout << "���뱸ע��"; cin >> student.notes;
	values.emplace_back(student);
	if (strcmp(student.sex, "��") == 0)
		boy++;
	else
		girl++;
}

int Management::enquiry_parents()
{
	cout << "������Ҫ��ѯ��ĸ��Ϣ��ѧ��������"; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			cout << "======================\n";
			cout << "��ĸ������" << values[i].parents_name << '\n';
			cout << "��ĸ�绰��" << values[i].parents_telephone << '\n';
			cout << "======================\n";
			return 1;
		}
	}
	cout << "δ�ҵ���ѧ��\n"; cin >> name;
	return 0;
}

int Management::enquiry_addres()
{
	cout << "������Ҫ��ѯסַ��ѧ��������"; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			cout << "======================\n";
			cout << "סַ��" << values[i].addres << '\n';
			cout << "======================\n";
			return 1;
		}
	}
	cout << "δ�ҵ���ѧ��\n"; cin >> name;
	return 0;
}

int Management::del()
{
	cout << "������Ҫɾ����ѧ��������"; cin >> name;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (name == values[i].name)
		{
			if (strcmp(values[i].sex, "��") == 0)
				boy--;
			else
				girl--;
			values.erase(values.begin() + i);
			cout << "ɾ���ɹ�\n";
			return 1;
		}
	}
	cout << "δ�ҵ���ѧ��\n"; cin >> name;
	return 0;
}

void Management::statistics()
{
	cout << "======================\n";
	cout << "������" << boy << "�ˣ�ռ" << boy / (boy + girl) * 100 << "%\n";
	cout << "Ů����" << girl << "�ˣ�ռ" << girl / (boy + girl) * 100 << "%\n";
	cout << "======================\n";
}

void Management::parin()
{
	for (unsigned int i = 0; i < values.size(); i++)
	{
		cout << "======================\n";
		cout << "������" << values[i].name << '\n';
		cout << "���䣺" << values[i].age << '\n';
		cout << "�Ա�" << values[i].sex << '\n';
		cout << "סַ��" << values[i].addres << '\n';
		cout << "��ߣ�" << values[i].height << '\n';
		cout << "���أ�" << values[i].weight << '\n';
		cout << "��ĸ������" << values[i].parents_name << '\n';
		cout << "��ĸ�绰��" << values[i].parents_telephone << '\n';
		cout << "��ע��" << values[i].notes << '\n';
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
		cout << "1.���ѧ��\n";
		cout << "2.ɾ��ѧ��\n";
		cout << "3.��ѯ��ĸ��Ϣ\n";
		cout << "4.��ѯѧ��סַ\n";
		cout << "5.��߽���\n";
		cout << "6.���ؽ���\n";
		cout << "7.ͳ��\n";
		cout << "8.��ʾ\n";
		cout << "9.�˳�\n";
		cout << "======================\n";
		cout << "���ѡ�"; cin >> choose;
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
			cout << "�������\n";
			break;
		case 6:sort(a.values.begin(), a.values.end(), cmp_weight);
			cout << "�������\n";
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