#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
#define MAX 10

//�����ϵ�˽ṹ��
struct Person
{
	//����
	string m_Name;
	//�Ա�  1 ��  2 Ů
	int m_Sex = 0;
	//�绰����
	string m_Phone;
	//���    1 ͬ����  2 ������  3 ������  4 һ����
	int m_Group = 0;
	//�����ʼ�
	string m_Email;
};

//���ͨѶ¼�ṹ��
struct Addressbooks
{
	//ͨѶ¼�б������ϵ������
	Person personArray[MAX];

	//ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_Size = 0;
};

//�ļ���д
int readPerson(Addressbooks* abs)
{
	int k = 0;
	ifstream srcFile("Person.txt", ios::in); //���ı�ģʽ�򿪶�
	if (!srcFile)
	{
		cout << "��ȡʧ��" << endl;
		system("pause"); // �밴���������
		system("cls"); // ��������
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
	cout << "��ȡ�ɹ�" << endl;
	system("pause"); // �밴���������
	system("cls"); // ��������
	return 1;
}
int writePerson(Addressbooks* abs)
{
	ofstream destFile("Person.txt", ios::out); //���ı�ģʽ��д
	if (!destFile)
	{
		cout << "д��ʧ��" << endl;
		system("pause"); // �밴���������
		system("cls"); // ��������
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
	cout << "д��ɹ�" << endl;
	system("pause"); // �밴���������
	system("cls"); // ��������
	return 1;
}

//1�������ϵ��
int inperson(Addressbooks* abs, int siz)
{
	//�Ա�
	cout << "�������Ա� " << endl;
	cout << "1 --- ��" << endl;
	cout << "2 --- Ů" << endl;
	int sex = 0;
	while (true)
	{
		//����������1 ���� 2 �����˳�ѭ������Ϊ���������ȷֵ
		//�������������������
		cin >> sex;
		if (sex == 1 || sex == 2)
		{
			abs->personArray[siz].m_Sex = sex;
			break;
		}
		cout << "������������������" << endl;
	}
	//�绰����
	cout << "��������ϵ�绰�� " << endl;
	string phone;
	cin >> phone;
	abs->personArray[siz].m_Phone = phone;
	//���
	cout << "���������" << endl;
	cout << "1 --- ͬ����" << endl;
	cout << "2 --- ������" << endl;
	cout << "3 --- ������" << endl;
	cout << "4 --- һ����" << endl;
	int group = 0;
	while (true)
	{
		//����������1 ���� 2 ���� 3 ���� 4�����˳�ѭ������Ϊ���������ȷֵ
		//�������������������
		cin >> group;
		if (group == 1 || group == 2 || group == 3 || group == 4)
		{
			abs->personArray[siz].m_Group = group;
			break;
		}
		cout << "������������������" << endl;
	}
	//�����ʼ�
	cout << "����������ʼ���" << endl;
	string email;
	cin >> email;
	abs->personArray[siz].m_Email = email;
	return 1;
}
void addPerson(Addressbooks* abs)
{
	int k = 0;
	//�ж�ͨѶ¼�Ƿ�������������˾Ͳ������
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
		//��Ӿ�����ϵ��

		//����
		string name;
		cout << "������������ " << endl;
		cin >> name;
		for (int i = 0; i < abs->m_Size; i++)
		{
			if (abs->personArray[i].m_Name == name)
			{
				cout << "��¼�Ѵ��ڣ�1.����   2.���ǣ�" << endl;
				cin >> k;
				if (k == 1)break;
				if (k == 2)
				{
					abs->personArray[i].m_Name = name;
					inperson(abs, i);
					cout << "��ӳɹ�" << endl;
					system("pause"); // �밴���������
					system("cls"); // ��������
					return;
				}
			}
		}
		abs->personArray[abs->m_Size].m_Name = name;
		inperson(abs, abs->m_Size);
		/*
		//�Ա�
		cout << "�������Ա� " << endl;
		cout << "1 --- ��" << endl;
		cout << "2 --- Ů" << endl;
		int sex = 0;
		while (true)
		{
			//����������1 ���� 2 �����˳�ѭ������Ϊ���������ȷֵ
			//�������������������
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}


		//�绰����
		cout << "��������ϵ�绰�� " << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;
		//���
		cout << "���������" << endl;
		cout << "1 --- ͬ����" << endl;
		cout << "2 --- ������" << endl;
		cout << "3 --- ������" << endl;
		cout << "4 --- һ����" << endl;
		int group = 0;
		while (true)
		{
			//����������1 ���� 2 ���� 3 ���� 4�����˳�ѭ������Ϊ���������ȷֵ
			//�������������������
			cin >> group;
			if (group == 1 || group == 2 || group == 3 || group == 4)
			{
				abs->personArray[abs->m_Size].m_Group = group;
				break;
			}
			cout << "������������������" << endl;
		}

		//�����ʼ�
		cout << "����������ʼ���" << endl;
		string email;
		cin >> email;
		abs->personArray[abs->m_Size].m_Email = email;
		/**/
		//����ͨѶ¼����
		abs->m_Size++;

		cout << "��ӳɹ�" << endl;

		system("pause"); // �밴���������
		system("cls"); // ��������
	}
}


//2����ʾ������ϵ��
void showPerson(Addressbooks* abs)
{
	//�ж�ͨѶ¼�������Ƿ�Ϊ0�����Ϊ0����ʾ��¼Ϊ��
	//�����Ϊ0����ʾ��¼����ϵ����Ϣ
	if (abs->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������ " << abs->personArray[i].m_Name << "\t";
			cout << "�Ա� " << (abs->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t";//ע�������
			cout << "�绰���룺 " << abs->personArray[i].m_Phone << "\t";
			if (abs->personArray[i].m_Group == 1)
			{
				cout << " ͬ����" << endl;
			}
			else if (abs->personArray[i].m_Group == 2)
			{
				cout << " ������" << endl;
			}
			else if (abs->personArray[i].m_Group == 3)
			{
				cout << " ������" << endl;
			}
			else
			{
				cout << " һ����" << endl;
			}
			cout << "�����ʼ��� " << abs->personArray[i].m_Email << endl;
		}
	}

	system("pause"); //�����������
	system("cls"); //����

}


//�����ϵ���Ƿ���ڣ�������ڣ�������ϵ�����������еľ���λ�ã������ڷ���-1
//����1  ͨѶ¼  ����2  �Ա�����
int isExist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//�ҵ��û������������
		if (abs->personArray[i].m_Name == name)
		{
			return i;  //�ҵ��ˣ�����������������е��±���
		}
	}
	return -1;//�������������û���ҵ�������-1
}
int isExist(Addressbooks* abs, int group)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//�ҵ��û�����������
		if (abs->personArray[i].m_Group == group)
		{
			return i; //�ҵ��ˣ�����������������е��±���
		}
	}
	return -1; //�������������û���ҵ�������-1
}

//3��ɾ��ָ����ϵ��
void deletePerson(Addressbooks* abs)
{
	cout << "��������Ҫɾ������ϵ��" << endl;

	string name;
	cin >> name;

	//ret == -1  δ�鵽
	//ret != -1  �鵽��
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		//���ҵ��ˣ�Ҫ����ɾ������
		for (int i = ret; i < abs->m_Size; i++)
		{
			//����ǰ��
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--; //����ͨѶ¼�е���Ա��
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}

	system("pause");
	system("cls");
}

//4������ָ����ϵ����Ϣ
void findPerson(Addressbooks* abs)
{
	cout << "�������������: " << "\t";
	cout << "1---����������  " << endl;
	cout << "2---��������  " << endl;
	int input;
	scanf_s("%d", &input);
	switch (input)
	{
	case 1:
	{
		cout << "���������֣� " << "\t";
		string name;
		cin >> name;

		//�ж�ָ������ϵ���Ƿ����ͨѶ¼��
		int ret = isExist(abs, name);


		if (ret != -1) //�ҵ���ϵ��
		{
			cout << "������ " << abs->personArray[ret].m_Name << "\t";
			cout << "�Ա� " << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t";//ע�������
			cout << "�绰���룺 " << abs->personArray[ret].m_Phone << "\t";
			if (abs->personArray[ret].m_Group == 1)
			{
				cout << " ͬ����" << endl;
			}
			else if (abs->personArray[ret].m_Group == 2)
			{
				cout << " ������" << endl;
			}
			else if (abs->personArray[ret].m_Group == 3)
			{
				cout << " ������" << endl;
			}
			else
			{
				cout << " һ����" << endl;
			}
			cout << "�����ʼ��� " << abs->personArray[ret].m_Email << endl;
		}
		else  //δ�ҵ���ϵ��
		{
			cout << "���޴���" << endl;
		}
		//��������º� ����
		system("pause");
		system("cls");
		break;
	}

	case 2:
	{
		cout << "��������� " << "\t";
		int group;
		cin >> group;

		int ret = isExist(abs, group);
		if (ret != -1) //�ҵ���ϵ��
		{
			cout << "������ " << abs->personArray[ret].m_Name << "\t";
			cout << "�Ա� " << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t";//ע�������
			cout << "�绰���룺 " << abs->personArray[ret].m_Phone << "\t";
			if (abs->personArray[ret].m_Group == 1)
			{
				cout << " ͬ����" << endl;
			}
			else if (abs->personArray[ret].m_Group == 2)
			{
				cout << " ������" << endl;
			}
			else if (abs->personArray[ret].m_Group == 3)
			{
				cout << " ������" << endl;
			}
			else
			{
				cout << " һ����" << endl;
			}
			cout << "�����ʼ��� " << abs->personArray[ret].m_Email << endl;
		}
		else  //δ�ҵ���ϵ��
		{
			cout << "���޴���" << endl;
		}
	}
	//��������º� ����
	system("pause");
	system("cls");
	break;
	}
}

//�˵�����
void showMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1�������ϵ��  *****" << endl;
	cout << "*****  2����ʾ��ϵ��  *****" << endl;
	cout << "*****  3��ɾ����ϵ��  *****" << endl;
	cout << "*****  4��������ϵ��  *****" << endl;
	cout << "*****  5�����ļ���ȡ  *****" << endl;
	cout << "*****  6�����뵽�ļ�  *****" << endl;
	cout << "*****  0���˳�ͨѶ¼  *****" << endl;
	cout << "***************************" << endl;
}


int main()
{

	//����ͨѶ¼�ṹ�����
	Addressbooks abs;
	//��ʼ��ͨѶ¼�е�ǰ��Ա����
	abs.m_Size = 0;

	int select = 0; // �����û�ѡ������ı���

	while (true)
	{
		//�˵�����
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1: // 1�������ϵ��
			addPerson(&abs); //���õ�ַ���ݣ���������ʵ��
			break;
		case 2: // 2����ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3: // 3��ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4: // 4��������ϵ��
			findPerson(&abs);
			break;
		case 5: // 5��������ϵ��
			readPerson(&abs);
			break;
		case 6: // 6��д����ϵ��
			writePerson(&abs);
			break;
		case 0: // 0���˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;
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