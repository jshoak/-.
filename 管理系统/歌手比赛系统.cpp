#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
typedef struct information
{
	int id;
	char name[10];//����
	double result[10];//�ɼ�
	double averesult;//ƽ���ɼ�
	double genresult;//�ܳɼ�
}player;


bool cmp_averesult(player a, player b)//ƽ���ɼ�����
{
	if (a.averesult > b.averesult)
		return true;
	else
		return false;
}

class Singer
{
public:
	Singer();
	~Singer();
	void addinform();//�����Ϣ
	int markgiven();//����
	int enquiry();//��ѯ��ĸ��Ϣ
	void parin();//��ʾ
	void readsinger();//��ȡ������Ϣ
	void savesinger();//���������Ϣ
	vector<player> values;
private:
	player singer;
	int number;
};

Singer::Singer() :number(0)
{
	memset(&singer, 0, sizeof(player));
}

Singer::~Singer()
{

}

void Singer::addinform()
{
	memset(&singer, 0, sizeof(player));
	cout << "�����ţ�"; cin >> singer.id;
	cout << "����������"; cin >> singer.name;
	values.emplace_back(singer);
}

int Singer::markgiven()
{
	int id = 0;
	double max = 999, min = 0;
	cout << "������Ҫ��ֱ�ţ�"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (id == values[i].id)
		{
			cout << "======================\n";
			for (int j = 0; j < 10; j++)
			{
				cout << "��ί��" << j + 1 << "����֣�";
				cin >> values[i].result[j];
				values[i].genresult += values[i].result[j];
				if (values[i].result[j] < max)
					max = values[i].result[j];
				if (values[i].result[j] > min)
					min = values[i].result[j];
			}
			values[i].averesult = (values[i].genresult - max - min) / 8;
			cout << "======================\n";
			return 1;
		}
	}
	return 0;
}

int Singer::enquiry()
{
	int id = 0;
	cout << "������Ҫ��ѯ��ţ�"; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (id == values[i].id)
		{
			cout << "======================\n";
			cout << "��ţ�" << values[i].id << '\n';
			cout << "������" << values[i].name << '\n';
			for (int j = 0; j < 10; j++)
				printf("��ί��%d�����֣�%f\t", j + 1, values[i].result[j]);
			cout << "\nƽ���֣�" << values[i].averesult << '\n';
			cout << "�ܷ֣�" << values[i].genresult << '\n';
			cout << "======================\n";
			return 1;
		}
	}
	return 0;
}

void Singer::parin()
{
	int j = 0;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		cout << "======================\n";
		cout << "��ţ�" << values[i].id << '\n';
		cout << "������" << values[i].name << '\n';
		for (j = 0; j < 10; j++)
			printf("��ί��%d����%f\t", j + 1, values[i].result[j]);
		cout << "\nƽ���֣�" << values[i].averesult << '\n';
		cout << "�ܷ֣�" << values[i].genresult << '\n';
		cout << "======================\n";
	}
}

void Singer::readsinger()
{
	int j = 0;
	ifstream srcFile("������Ϣ.txt", ios::in);
	if (srcFile)
	{
		srcFile >> number;
		for (int i = 0; i < number; i++)
		{
			srcFile >> singer.id;
			srcFile >> singer.name;
			for (j = 0; j < 10; j++)
				srcFile >> singer.result[j];
			srcFile >> singer.averesult;
			srcFile >> singer.genresult;
			values.emplace_back(singer);
		}
		srcFile.close();
	}
}

void Singer::savesinger()
{
	int j = 0;
	ofstream destFile("������Ϣ.txt", ios::out);
	destFile << values.size() << '\n';
	for (unsigned int i = 0; i < values.size(); i++)
	{
		destFile << values[i].id << '\n';
		destFile << values[i].name << '\n';
		for (j = 0; j < 10; j++)
			destFile << values[i].result[j] << '\t';
		destFile << '\n' << values[i].averesult << '\n';
		destFile << values[i].genresult << '\n';
	}
	destFile.close();
}


int main()
{
	Singer a;
	int choose = 0, i = 0;
	while (choose != 9)
	{
		cout << "======================\n";
		cout << "1.����ѡ������\n";
		cout << "2.��ί���\n";
		cout << "3.�ɼ����򣨰�ƽ���֣�\n";
		cout << "4.���ݲ�ѯ\n";
		cout << "5.׷��ѧ������\n";
		cout << "6.��ȡ�����ļ�\n";
		cout << "7.д�������ļ�\n";
		cout << "8.��ʾ����ѡ������\n";
		cout << "9.�˳�ϵͳ\n";
		cout << "======================\n";
		cout << "���ѡ�"; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			cout << "����ѡ��������"; cin >> i;
			while (i--)
				a.addinform();
			break;
		case 2:
			a.markgiven();
			break;
		case 3:
			sort(a.values.begin(), a.values.end(), cmp_averesult);
			cout << "�������\n";
			break;
		case 4:
			a.enquiry();
			break;
		case 5:
			a.addinform();
			break;
		case 6:
			a.readsinger();
			cout << "��ȡ���\n";
			break;
		case 7:
			a.savesinger();
			cout << "�������\n";
			break;
		case 8:
			a.parin();
			break;
		default:
			break;
		}
	}
	/**/
	return 0;
}