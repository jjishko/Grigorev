#include <iostream>
#include <string>
#include <fstream>

#include "NGProgram.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int Pipe::idCount = 0;
int CS::idCount = 0;

Pipe::Pipe()
{
	id = idCount;
	++idCount;

	cout << "������� ������������ ������� (��������): ";
	while (true)
	{
		std::getline(cin, kmMark);

		if (kmMark == "null")
		{
			cout << "null ����, �� ����� ��� �������!" << endl;
			continue;
		}

		break;
	}

	cout << "������� ����� �����: ";
	while (true)
	{
		checkInput(length);

		if (length <= 0)
		{
			cout << "����� ������ ���� ������ ����!" << endl;
			continue;
		}

		break;
	}

	cout << "������� ������� �����: ";
	while (true)
	{
		checkInput(diameter);

		if (diameter < 1)
		{
			cout << "������� �� ����� ���� ������ 1!" << endl;
			continue;
		}

		break;
	}

	cout << "����� � �������? (1 - ��, 0 - ���): ";
	checkInput(isUnderRepair);

	cout << endl << "����� ����������������!" << endl;
}

CS::CS()
{
	id = idCount;
	++idCount;

	cout << "������� �������� ��: ";
	while (true)
	{
		std::getline(cin, name);

		if (name == "null")
		{
			cout << "null ����, �� ����� ��� �������!" << endl;
			continue;
		}

		break;
	}

	cout << "������� ���-�� �����: ";
	while (true)
	{
		checkInput(guildCount);

		if (guildCount < 1)
		{
			cout << "���-�� ����� ������ ���� ������ ����!" << endl;
			continue;
		}

		break;
	}

	cout << "������� ���-�� ����� � ������: ";
	while (true)
	{
		checkInput(guildCountInWork);

		if (guildCountInWork < 0)
		{
			cout << "���-�� ����� � ������ ������ ���� �������������!" << endl;
			continue;
		}

		if (guildCountInWork > guildCount)
		{
			cout << "���-�� ������� ����� ������ ���� ������ ������!" << endl;
		}

		break;
	}

	cout << "������� ����������� ������������� ��: ";
	checkInput(efficiency);

	cout << endl << "�� ����������������!" << endl;
}

void Pipe::printPipe(const Pipe& p)
{
	if (p.kmMark == "null")
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
}

void CS::printCS(const CS& cs)
{
	if (cs.name == "null")
	{
		cout << "������ �� �����������!" << endl << endl;

	}
	else
	{
		cout << "�������� ��: " << cs.name << endl;
		cout << "���-�� �����: " << cs.guildCount << endl;
		cout << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
		cout << "����������� �������������: " << cs.efficiency << endl;
	}

	cout << endl;
}

void Pipe::redactPipe(Pipe& p)
{
	if (p.kmMark == "null")
	{
		cout << "������: ������ ����� �����������!" << endl;
		return;
	}

	cout << "����� � �������? (1 - ��, 0 - ���): ";
	checkInput(p.isUnderRepair);

	cout << "������ �������!" << endl;
}

void CS::redactCS(CS& cs)
{
	if (cs.name == "null")
	{
		cout << "������: ������ �� �����������!" << endl;
		return;
	}

	bool increase;

	cout << "�������� ��� - 1, ������ - 0" << endl;

	cout << "������� �����: ";
	while (true)
	{
		checkInput(increase);

		if (increase)
		{
			if (cs.guildCount == cs.guildCountInWork)
			{
				cout << "���-�� ������� ����� ���������!" << endl;
				return;
			}

			++cs.guildCountInWork;
		}
		else
		{
			if (cs.guildCountInWork == 0)
			{
				cout << "���-�� ������� ����� ����� ����!" << endl;
				return;
			}

			--cs.guildCountInWork;
		}

		break;
	}

	cout << "������!" << endl;
}


void saveObjects(const Pipe& p, const CS& cs)
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

void loadObjects(Pipe& p, CS& cs)
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