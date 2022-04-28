#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
typedef struct information
{
	int id;
	char name[10];//名字
	double result[10];//成绩
	double averesult;//平均成绩
	double genresult;//总成绩
}player;


bool cmp_averesult(player a, player b)//平均成绩降序
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
	void addinform();//添加信息
	int markgiven();//评分
	int enquiry();//查询父母信息
	void parin();//显示
	void readsinger();//读取歌手信息
	void savesinger();//保存歌手信息
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
	cout << "输入编号："; cin >> singer.id;
	cout << "输入姓名："; cin >> singer.name;
	values.emplace_back(singer);
}

int Singer::markgiven()
{
	int id = 0;
	double max = 999, min = 0;
	cout << "输入需要打分编号："; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (id == values[i].id)
		{
			cout << "======================\n";
			for (int j = 0; j < 10; j++)
			{
				cout << "评委【" << j + 1 << "】打分：";
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
	cout << "输入需要查询编号："; cin >> id;
	for (unsigned int i = 0; i < values.size(); i++)
	{
		if (id == values[i].id)
		{
			cout << "======================\n";
			cout << "编号：" << values[i].id << '\n';
			cout << "姓名：" << values[i].name << '\n';
			for (int j = 0; j < 10; j++)
				printf("评委【%d】评分：%f\t", j + 1, values[i].result[j]);
			cout << "\n平均分：" << values[i].averesult << '\n';
			cout << "总分：" << values[i].genresult << '\n';
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
		cout << "编号：" << values[i].id << '\n';
		cout << "姓名：" << values[i].name << '\n';
		for (j = 0; j < 10; j++)
			printf("评委【%d】：%f\t", j + 1, values[i].result[j]);
		cout << "\n平均分：" << values[i].averesult << '\n';
		cout << "总分：" << values[i].genresult << '\n';
		cout << "======================\n";
	}
}

void Singer::readsinger()
{
	int j = 0;
	ifstream srcFile("歌手信息.txt", ios::in);
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
	ofstream destFile("歌手信息.txt", ios::out);
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
		cout << "1.输入选手数据\n";
		cout << "2.评委打分\n";
		cout << "3.成绩排序（按平均分）\n";
		cout << "4.数据查询\n";
		cout << "5.追加学生数据\n";
		cout << "6.读取数据文件\n";
		cout << "7.写入数据文件\n";
		cout << "8.显示所有选手数据\n";
		cout << "9.退出系统\n";
		cout << "======================\n";
		cout << "输出选项："; cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			cout << "输入选手人数："; cin >> i;
			while (i--)
				a.addinform();
			break;
		case 2:
			a.markgiven();
			break;
		case 3:
			sort(a.values.begin(), a.values.end(), cmp_averesult);
			cout << "排序完成\n";
			break;
		case 4:
			a.enquiry();
			break;
		case 5:
			a.addinform();
			break;
		case 6:
			a.readsinger();
			cout << "读取完成\n";
			break;
		case 7:
			a.savesinger();
			cout << "保存完成\n";
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