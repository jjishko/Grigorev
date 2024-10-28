#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "misc.h"
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
	cout << "������� ������������ ������� (��������): ";
	in >> std::ws;
	inputLine(p.kmMark, in);

	cout << "������� ����� �����: ";
	checkInput(p.length, float(0.1), FLT_MAX, in);

	cout << "������� ������� �����: ";
	checkInput(p.diameter, 1, INT_MAX, in);

	cout << "����� � �������? (1 - ��, 0 - ���): ";
	
	int isUnderRepair;
	checkInput(isUnderRepair, 0, 1, in);
	p.isUnderRepair = bool(isUnderRepair);

	cout << endl << "����� ����������������!" << endl;

	return in;
}

std::istream& operator>>(std::istream& in, CS& cs)
{
	cout << "������� �������� ��: ";
	cin >> std::ws;
	inputLine(cs.name, in);

	cout << "������� ���-�� �����: ";
	checkInput(cs.guildCount, 1, INT_MAX, in);

	cout << "������� ���-�� ����� � ������: ";
	checkInput(cs.guildCountInWork, 0, cs.guildCount, in);

	cout << "������� ����������� ������������� ��: ";
	checkInput(cs.efficiency, float(-100), float(100), in);

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

std::ifstream& operator>>(std::ifstream& in, Pipe& p)
{
	string kmMark;
	inputLine(kmMark, in);

	float length;
	int id, diameter;
	bool isUnderRepair;

	in >> id >> length >> diameter >> isUnderRepair;

	if (kmMark == "" || in.fail() || id < 0)
	{
		p.id = -1;
		return in;
	}

	p.id = id;
	p.kmMark = kmMark;
	p.length = length;
	p.diameter = diameter;
	p.isUnderRepair = isUnderRepair;

	return in;
}

std::ifstream& operator>>(std::ifstream& in, CS& cs)
{
	string name;
	inputLine(name, in);

	int guildCount, guildCountInWork, id;
	float efficiency;

	in >> id >> guildCount >> guildCountInWork >> efficiency;

	if (name == "" || in.fail() || id < 0
		|| guildCount < 0 || guildCountInWork < 0 ||
		guildCount < guildCountInWork)
	{
		cs.id = -1;
		return in;
	}

	cs.id = id;
	cs.name = name;
	cs.guildCount = guildCount;
	cs.guildCountInWork = guildCountInWork;
	cs.efficiency = efficiency;

	return in;
}

std::ofstream& operator<<(std::ofstream& out, const Pipe& p)
{
	if (p.kmMark == "")
	{
		return out;
	}

	out << 'P' << endl;
	out << p.kmMark << endl;
	out << p.id << " ";
	out << p.length << " ";
	out << p.diameter << " ";
	out << p.isUnderRepair << endl;

	return out;
}

std::ofstream& operator<<(std::ofstream& out, const CS& cs)
{
	if (cs.name == "")
	{
		return out;
	}

	out << 'C' << endl;
	out << cs.name << endl;
	out << cs.id << " ";
	out << cs.guildCount << " ";
	out << cs.guildCountInWork << " ";
	out << cs.efficiency << endl;

	return out;
}

Pipe::Pipe()
{
	this->id = this->idCount;
	++this->idCount;
}

CS::CS()
{
	this->id = this->idCount;
	++this->idCount;
}

int Pipe::getID()
{
	return id;
}

bool Pipe::getStatus() const
{
	return isUnderRepair;
}

std::string Pipe::getKmMark() const
{
	return kmMark;
}


int CS::getID()
{
	return id;
}

std::string CS::getName() const
{
	return name;
}

int CS::getGuildCount() const
{
	return guildCount;
}

int CS::getGuildCountInWork() const
{
	return guildCountInWork;
}

//std::vector<int> parseString(std::string str)
//{
//	int pos = str.find(' ');
//	std::vector<int> res;
//
//	if (str == "")
//	{
//		return res;
//	}
//
//	do
//	{
//		res.push_back(atoi(str.substr(0, pos).c_str()));
//
//		str = str.substr(pos + 1);
//		pos = str.find(' ');
//
//	} while (pos != std::string::npos);
//
//	return res;
//}

void editPipe(Pipe& p)
{
	p.isUnderRepair = !p.isUnderRepair;

	cout << "ID �����: " << p.id << endl;
	cout << "������� ������: "
		<< (p.isUnderRepair ? "� �������" : "��������") << endl;
}

void editCS(CS& cs)
{
	int increase;

	cout << "ID ��: " << cs.id << endl;
	cout << "���-�� �����: " << cs.guildCount << endl;
	cout << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
	cout << "�������� ��� - 1, ������ - 0" << endl;

	cout << "������� �����: ";
	checkInput(increase, 0, 1);

	if (increase)
	{
		if (cs.guildCount == cs.guildCountInWork)
		{
			cout << "���-�� ������� ����� ���������!" << endl << endl;
			return;
		}

		++cs.guildCountInWork;
	}
	else
	{
		if (cs.guildCountInWork == 0)
		{
			cout << "���-�� ������� ����� ����� ����!" << endl << endl;
			return;
		}

		--cs.guildCountInWork;
	}

	cout << "������� ���-�� ������� �����: " << cs.guildCountInWork
		<< endl << endl;
}

void saveObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS)
{
	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ���������� � ��������): ";
	char a = cin.get();
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ofstream f(fileName + ".txt");

	if (!f.is_open())
	{
		cout << "������: ���� ��� ���������� �� ������!" << endl;
		return;
	}

	for (const auto& p : mapPipe)
	{
		f << p.second;
	}

	for (const auto& cs : mapCS)
	{
		f << cs.second;
	}

	f.close();

	cout << "������!" << endl;
}

void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS)
{
	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ���������� � ��������): ";
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ifstream f(fileName + ".txt");

	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "������: ���� ��� �������� �� ������ ��� ����!" << endl;
		return;
	}

	int maxPipeId, maxCSId;

	maxPipeId = Pipe::idCount;
	Pipe::idCount = 0;
	maxCSId = CS::idCount;
	CS::idCount = 0;

	std::unordered_map<int, Pipe> newMapPipe;
	std::unordered_map<int, CS> newMapCS;

	Pipe tmpPipe;
	CS tmpCS;
	char type;

	while (f.peek() != EOF)
	{
		type = f.get();
		f.get();

		if (type != 'P' && type != 'C')
		{
			cout << "������: ������������ ������ �����!" << endl;

			Pipe::idCount = maxPipeId;
			CS::idCount = maxCSId;

			f.close();
			return;
		}

		if (type == 'P')
		{
			f >> tmpPipe;

			if (tmpPipe.getID() == -1)
			{
				cout << "������: ������������ ������ �����!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			Pipe::idCount = std::max(Pipe::idCount, tmpPipe.getID() + 1);
			newMapPipe.emplace(tmpPipe.getID(), tmpPipe);
		}
		else
		{
			f >> tmpCS;

			if (tmpCS.getID() == -1)
			{
				cout << "������: ������������ ������ �����!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			CS::idCount = std::max(CS::idCount, tmpCS.getID() + 1);
			newMapCS.emplace(tmpCS.getID(), tmpCS);
		}

		f.get();
	}

	mapPipe = newMapPipe;
	mapCS = newMapCS;

	f.close();

	cout << "������!" << endl;
}


void addPipe(std::unordered_map<int, Pipe>& map)
{
	Pipe p;
	cin >> p;

	map.emplace(p.getID(), p);
}

void addCS(std::unordered_map<int, CS>& map)
{
	CS cs;
	cin >> cs;

	map.emplace(cs.getID(), cs);
}

void printPipes(const std::unordered_map<int, Pipe>& map)
{
	cout << "�����:" << endl << endl;

	if (map.empty())
	{
		cout << "����� �����������" << endl << endl;
	}
	else
	{
		for (const auto& p : map)
		{
			cout << p.second;
		}
	}

	cout << endl;
}

void printCS(const std::unordered_map<int, CS>& map)
{
	cout << "��:" << endl << endl;

	if (map.empty())
	{
		cout << "�� �����������" << endl << endl;
	}
	else
	{
		for (const auto& cs : map)
		{
			cout << cs.second;
		}
	}

	cout << endl;
}

void printAll(const std::unordered_map<int, Pipe>& mapPipe,
	 const std::unordered_map<int, CS>& mapCS)
{
	printPipes(mapPipe);
	printCS(mapCS);
}

void editPipes(std::unordered_map<int, Pipe>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		editPipe(map.at(id));
	}
}

void editCS(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		editCS(map.at(id));
	}
}

void deletePipes(std::unordered_map<int, Pipe>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		map.erase(id);
		cout << "����� " << id << " �������" << endl;
	}

	cout << endl;
}

void deleteCS(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		map.erase(id);
		cout << "�� " << id << " �������" << endl;
	}
}

inline bool filtByName(const Pipe& p, std::string name)
{
	return p.getKmMark().find(name) != string::npos;
}
inline bool filtByRepairingFlag(const Pipe& p, bool type)
{
	return p.getStatus() == type;
}
inline bool filtByName(const CS& cs, std::string name)
{
	return cs.getName().find(name) != string::npos;
}
inline bool filtByGuildUpperPercentage(const CS& cs, int percent)
{
	return float(cs.getGuildCount() - cs.getGuildCountInWork())
		/cs.getGuildCount() * 100 > percent;
}
inline bool filtByGuildLowerPercentage(const CS& cs, int percent)
{
	return float(cs.getGuildCount() - cs.getGuildCountInWork())
		/ cs.getGuildCount() * 100 < percent;
}


std::unordered_set<int> makeSetOfFilteredPipes(const std::unordered_map<int, Pipe>& map)
{
	int filtType;
	std::unordered_set<int> set;

	std::string name;
	int status;

	printPipes(map);

	std::cout << std::endl;
	std::cout << "�������� �������� (������� -1, ����� ���������): " << std::endl;
	std::cout << "0 - ������ �� ��������, 1 - �� �������� \"� �������\"" << std::endl;

	while (true)
	{
		std::cout << "������� �����: ";
		checkInput(filtType, -1, 1);

		if (filtType == -1)
			break;

		if (filtType == 0)
		{
			std::cout << "������� ������ ��� �������: ";
			std::cin >> std::ws;
			inputLine(name, std::cin);

			filtObjects(map, set, filtByName, name);
		}
		else if (filtType == 1)
		{
			std::cout << "������� ������ (1 - ������ \"� �������\", 0 - ������ \"��������\"): ";
			checkInput(status, 0, 1);

			filtObjects(map, set, filtByRepairingFlag, bool(status));
		}

		if (set.empty())
		{
			std::cout << "�� ������� ����, ���������� �� �������!"
				<< std::endl << std::endl;
		}
		else
		{
			std::cout << "ID ��������� ���������: ";

			for (int id : set)
			{
				std::cout << id << " ";
			}

			std::cout << std::endl << std::endl;
		}
	}

	return set;
}

std::unordered_set<int> makeSetOfFilteredCS(const std::unordered_map<int, CS>& map)
{
	int filtType;
	std::unordered_set<int> set;

	std::string name;
	int percent;
	int upperThanPercent;

	printCS(map);

	std::cout << std::endl;
	std::cout << "�������� �������� (������� -1, ����� ���������): " << std::endl;
	std::cout << "0 - ������ �� ��������, 1 - �� �������� ������������������ �����" << std::endl;

	while (true)
	{
		std::cout << "������� �����: ";
		checkInput(filtType, -1, 1);

		if (filtType == -1)
			break;

		if (filtType == 0)
		{
			std::cout << "������� ������ ��� �������: ";
			std::cin >> std::ws;
			inputLine(name, std::cin);

			filtObjects(map, set, filtByName, name);
		}
		else if (filtType == 1)
		{
			std::cout << "������� ������� ����������������� �����: ";
			checkInput(percent, 0, 100);

			std::cout << "������� 1, ����� ����� �� � ���������, ������ ����������, "
				<< "0 - ����� ����� ������: ";
			checkInput(upperThanPercent, 0, 1);

			upperThanPercent ? filtObjects(map, set, filtByGuildUpperPercentage, percent)
				: filtObjects(map, set, filtByGuildLowerPercentage, percent);
		}

		if (set.empty())
		{
			std::cout << "�� ������� ��, ���������� �� �������!"
				<< std::endl << std::endl;
		}
		else
		{
			std::cout << "ID ��������� ���������: ";

			for (int id : set)
			{
				std::cout << id << " ";
			}

			std::cout << std::endl << std::endl;
		}
	}

	return set;
}





