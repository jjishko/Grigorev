#include <iostream>
#include <string>
#include <fstream>

#include "functions.h"

#define FLUSH while (cin.get() != '\n');

using std::string;
using std::cout;
using std::cin;
using std::endl;

void resetInput()
{
	cout << "������� ���������� ��������!" << endl << endl;

	cin.clear();
	FLUSH	
}

void addPipe(Pipe& p)
{
	while (true)
	{
		cout << "������� ������������ ������� (��������): ";
		std::getline(cin, p.kmMark);

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

		FLUSH
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

		FLUSH
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

		FLUSH
		break;
	}
	
}

void addCS(CS& cs)
{
	while (true)
	{
		cout << "������� �������� ��: ";
		std::getline(cin, cs.name);

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

		FLUSH
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

		FLUSH
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

		FLUSH
		break;
	}

}

void printObjects(Pipe& p, CS& cs)
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
		cout << "������ �� �����������!" << endl;

	}
	else
	{
		cout << "�������� ��: " << cs.name << endl;
		cout << "���-�� �����: " << cs.guildCount << endl;
		cout << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
		cout << "����������� �������������: " << cs.efficiency << endl;
	}
	
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

	FLUSH		
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

		FLUSH

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
	
}

void saveObjects(Pipe& p, CS& cs)
{
	if (cs.name == "" && p.kmMark == "")
	{
		cout << "������: ������ �����������!" << endl;
		return;
	}

	std::ofstream f("data.txt");

	if (!f.is_open())
	{
		cout << "������: ���� ��� ���������� �� ������!" << endl;
		return;
	}

	if (p.kmMark == "")
	{
		cout << "������ ����� �����������!" << endl;
	}
	else
	{
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
		f << cs.name << endl;
		f << cs.guildCount << " ";
		f << cs.guildCountInWork << " ";
		f << cs.efficiency;

		cout << "������ �� ���������! " << endl;
	}

	f.close();

}

void loadObjects(Pipe& p, CS& cs)
{
	std::ifstream f("data.txt");
	
	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "������: ���� ��� ���������� �� ������ ��� ����!" << endl;
		return;
	}

	std::getline(f, p.kmMark);
	f >> p.length >> p.diameter >> p.isUnderRepair;

	if (f.fail())
	{
		cout << "������: ������������ ���������� �� �����!" << endl;
		return;
	}

	cout << "����� ���������!" << endl;

	f.get();

	std::getline(f, cs.name);
	f >> cs.guildCount >> cs.guildCountInWork 
		>> cs.efficiency;

	if (f.fail())
	{
		cout << "������: ������������ ���������� �� �����!" << endl;
		return;
	}

	cout << "�� ���������!" << endl;

	f.close();

}
