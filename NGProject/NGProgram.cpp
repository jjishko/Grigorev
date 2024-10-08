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

std::istream& operator>>(std::istream& in, Pipe& p)
{
	p.id = p.idCount;
	++p.idCount;

	cout << "������� ������������ ������� (��������): ";
	cin >> std::ws;
	std::getline(in, p.kmMark);

	cout << "������� ����� �����: ";
	checkInput(p.length, float(0), FLT_MAX, in);

	cout << "������� ������� �����: ";
	checkInput(p.diameter, 0, INT_MAX, in);

	cout << "����� � �������? (1 - ��, 0 - ���): ";
	checkInput(p.isUnderRepair, true, true, in);

	cout << endl << "����� ����������������!" << endl;

	return in;
}

std::istream& operator>>(std::istream& in, CS& cs)
{
	cs.id = cs.idCount;
	++cs.idCount;

	cout << "������� �������� ��: ";
	cin >> std::ws;
	std::getline(cin, cs.name);

	cout << "������� ���-�� �����: ";
	checkInput(cs.guildCount, 0, INT_MAX, in);

	cout << "������� ���-�� ����� � ������: ";
	checkInput(cs.guildCountInWork, 0, cs.guildCount + 1, in);

	cout << "������� ����������� ������������� ��: ";
	checkInput(cs.efficiency, float(- 101), float(101), in);

	cout << endl << "�� ����������������!" << endl;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Pipe& p)
{
	out << "ID �����: " << p.id << endl;
	out << "������������ ������� (��������) �����: " << p.kmMark << endl;
	out << "����� �����: " << p.length << endl;
	out << "������� �����: " << p.diameter << endl;
	out << "������: " << (p.isUnderRepair ? "� �������" : "��������") << endl;
	out << endl;

	return out;
}

std::ostream& operator<<(std::ostream& out, const CS& cs)
{
	out << "ID ��: " << cs.id << endl;
	out << "�������� ��: " << cs.name << endl;
	out << "���-�� �����: " << cs.guildCount << endl;
	out << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
	out << "����������� �������������: " << cs.efficiency << endl;
	out << endl;

	return out;
}

int Pipe::getID()
{
	return this->id;
}

int CS::getID()
{
	return this->id;
}

void Pipe::redactPipe(Pipe& p)
{
	cout << "����� � �������? (1 - ��, 0 - ���): ";
	checkInput(p.isUnderRepair, true, true, cin);

	cout << "������ �������!" << endl;
}

void CS::redactCS(CS& cs)
{
	bool increase;

	cout << "�������� ��� - 1, ������ - 0" << endl;

	cout << "������� �����: ";
	while (true)
	{
		checkInput(increase, true, true, cin);

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

//��������� id
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

void addPipe(std::unordered_map<int, Pipe>& map)
{
	Pipe p;
	cin >> p;

	map.insert({ p.getID(), p });
}

void addCS(std::unordered_map<int, CS>& map)
{
	CS cs;
	cin >> cs;

	map.insert({ cs.getID(), cs });
}

void printObjects(std::unordered_map<int, Pipe>& mapPipe, std::unordered_map<int, CS>& mapCS)
{
	cout << "�����:" << endl << endl;

	for(auto& p : mapPipe)
	{
		cout << p.second;
	}

	cout << endl << "��:" << endl << endl;

	for (auto& cs : mapCS)
	{
		cout << cs.second;
	}
}



