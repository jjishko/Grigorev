#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "functions.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

//ofstream& operator << (ofstream & out, const Pipe & p)
//{
//	out << "������������ ������� (��������) �����: " << p.kmMark << endl;
//	out << "����� �����: " << p.length << endl;
//	out << "������� �����: " << p.diameter << endl;
//	out << "������: " << (p.isUnderRepair ? "� �������" : "��������") << endl;
//
//	return out;
//}

void flush()
{
	cin.ignore(10000, '\n');
}

void resetInput()
{
	cout << "������� ���������� ��������!" << endl << endl;

	cin.clear();
	flush();	
}

void addPipe(Pipe& p)
{
	while (true)
	{
		cout << "������� ������������ ������� (��������): ";
		std::getline(cin, p.kmMark);

		if (p.kmMark == "")
		{
			cout << "�������� �����������!" << endl << endl;
			continue;
		}

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}
	

	while (true)
	{
		cout << "������� ����� �����: ";
		cin >> p.length;

		if (p.length <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}
	

	while (true)
	{
		cout << "������� ������� �����: ";
		cin >> p.diameter;

		if (p.diameter < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}
	

	while (true)
	{
		cout << "����� � �������? (1 - ��, 0 - ���): ";
		cin >> p.isUnderRepair;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}

	cout << endl << "����� ����������������!" << endl;
	
}

void addCS(CS& cs)
{
	while (true)
	{
		cout << "������� �������� ��: ";
		std::getline(cin, cs.name);

		if (cs.name == "")
		{
			cout << "�������� �����������!" << endl << endl;
			continue;
		}

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}


	while (true)
	{
		cout << "������� ���-�� �����: ";
		cin >> cs.guildCount;

		if (cs.guildCount < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}


	while (true)
	{
		cout << "������� ���-�� ����� � ������: ";
		cin >> cs.guildCountInWork;

		if (cs.guildCountInWork <= 0 || cs.guildCountInWork > cs.guildCount
			|| cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}


	while (true)
	{
		cout << "������� ����������� ������������� ��: ";
		cin >> cs.efficiency;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}

	cout << endl << "�� ����������������!" << endl;
}

void printObjects(const Pipe& p, const CS& cs)
{
	if (p.kmMark == "")
	{
		cout << "������ ����� �����������!" << endl;
	}
	else
	{
		cout << "������������ ������� (��������) �����: " << p.kmMark << endl;
		cout << "����� �����: " << p.length << endl;
		cout << "������� �����: " << p.diameter << endl;
		cout << "������: " << (p.isUnderRepair ? "� �������" : "��������") << endl;
	}
	
	cout << endl;

	if (cs.name == "")
	{
		cout << "������ �� �����������!" << endl << endl;

	}
	else
	{
		cout << "�������� ��: " << cs.name << endl;
		cout << "���-�� �����: " << cs.guildCount << endl;
		cout << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
		cout << "����������� �������������: " << cs.efficiency << endl << endl;
	}
	
	cout << "������!" << endl;

}

void redactPipe(Pipe& p)
{
	if (p.kmMark == "")
	{
		cout << "������: ������ ����� �����������!" << endl;
		return;
	}

	cout << "����� � �������? (1 - ��, 0 - ���): ";
	cin >> p.isUnderRepair;

	if (cin.fail())
	{
		resetInput();
	}

	flush();	

	cout << "������ �������!" << endl;

}

void redactCS(CS& cs)
{
	if (cs.name == "")
	{
		cout << "������: ������ �� �����������!" << endl;
		return;
	}

	int increase;

	cout << "�������� ��� - 1, ������ - 0" << endl;

	while (true)
	{
		cout << "������� �����: ";
		cin >> increase;

		if (increase < 0 || increase > 1 || cin.fail())
		{
			resetInput();
		}

		flush();

		if (increase)
		{
			if (cs.guildCount == cs.guildCountInWork)
			{
				cout << "������: ���-�� ������� ����� ���������!" << endl;
				return;
			}

			++cs.guildCountInWork;
		}
		else
		{
			if (cs.guildCountInWork == 0)
			{
				cout << "������: ���-�� ������� ����� ����� ����!" << endl;
				return;
			}

			--cs.guildCountInWork;
		}

		break;
	}
	
	cout << "������!" << endl;
}

void saveObject(const Pipe& p, const CS& cs)
{
	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ����������): ";
	std::getline(cin, fileName);

	std::ofstream f(fileName + ".txt");
	//std::ofstream f(fileName, std::ios::app);

	if (!f.is_open())
	{
		cout << "������: ���� ��� ���������� ����������!" << endl;
		return;
	}

	if (cs.name == "" && p.kmMark == "")
	{
		cout << "������: ������ �����������!" << endl;

		f.close();
		return;
	}

	if (p.kmMark == "")
	{
		cout << "������ ����� �����������!" << endl;
	}
	else
	{
		f << 'P' << endl;
		f << p.kmMark << endl;
		f << p.length << " ";
		f << p.diameter << " ";
		f << p.isUnderRepair << endl;

		cout << "������ ����� ���������! ";
	}
	
	if (cs.name == "")
	{
		cout << "������ �� �����������!" << endl;
	}
	else
	{
		f << 'C' << endl;
		f << cs.name << endl;
		f << cs.guildCount << " ";
		f << cs.guildCountInWork << " ";
		f << cs.efficiency;

		cout << "������ �� ���������! " << endl;
	}

	f.close();

}

void loadObject(Pipe& p, CS& cs)
{
	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ����������): ";
	std::getline(cin, fileName);

	std::ifstream f(fileName + ".txt");

	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "������: ���� ��� ���������� �� ������ ��� ����!" << endl;
		return;
	}

	char type;


	while (f.peek() != EOF)
	{
		type = f.get();
		f.get();

		if (type != 'P' && type != 'C')
		{
			cout << "������: ������������ ������ �����!" << endl;

			f.close();
			return;
		}

		if (type == 'P')
		{
			std::getline(f, p.kmMark);
			f >> p.length >> p.diameter >> p.isUnderRepair;

			if (p.kmMark == "" || f.fail())
			{
				cout << "������: ������������ ���������� �� �����!" << endl;

				f.close();
				return;
			}

			cout << "����� ���������!" << endl;
		}
		else
		{
			std::getline(f, cs.name);
			f >> cs.guildCount >> cs.guildCountInWork
				>> cs.efficiency;

			if (cs.name == "" || f.fail())
			{
				cout << "������: ������������ ���������� �� �����!" << endl;
				return;
			}

			cout << "�� ���������!" << endl;
		}

		f.get();
	}
	

	f.close();
}