#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "misc.h"
#include "NGProgram.h"
#include "CS.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int CS::idCount = 0;

std::istream& operator>>(std::istream& in, CS& cs)
{
	cs.id = CS::idCount;
	++CS::idCount;

	cout << "Введите название КС: ";
	cin >> std::ws;
	inputLine(cs.name, in);

	cout << "Введите кол-во цехов: ";
	checkInput(cs.guildCount, 1, INT_MAX, in);

	cout << "Введите кол-во цехов в работе: ";
	checkInput(cs.guildCountInWork, 0, cs.guildCount, in);

	cout << "Введите коэффициент эффективности КС: ";
	checkInput(cs.efficiency, float(-100), float(100), in);

	cout << endl << "КС инициализирована!" << endl;

	return in;
}

std::ostream& operator<<(std::ostream& out, const CS& cs)
{
	out << "ID КС: " << cs.id << endl;
	out << "Название КС: " << cs.name << endl;
	out << "Кол-во цехов: " << cs.guildCount << endl;
	out << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
	out << "Коэффициент эффективности: " << cs.efficiency << endl;
	out << endl;

	return out;
}

std::ifstream& operator>>(std::ifstream& in, CS& cs)
{
	string name;
	in >> std::ws;
	std::getline(in, name);

	int guildCount, guildCountInWork, id;
	float efficiency;
	bool isInConnection;

	in >> id >> guildCount >> guildCountInWork >> efficiency >> isInConnection;

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
	cs.isInConnection = isInConnection;

	return in;
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
	out << cs.efficiency << " ";
	out << cs.isInConnection << endl;

	return out;
}

int CS::getID()
{
	return id;
}

void editCS(CS& cs)
{
	int increase;

	cout << "ID КС: " << cs.id << endl;
	cout << "Кол-во цехов: " << cs.guildCount << endl;
	cout << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
	cout << "Добавить цех - 1, убрать - 0" << endl;

	cout << "Введите номер: ";
	checkInput(increase, 0, 1);

	if (increase)
	{
		if (cs.guildCount == cs.guildCountInWork)
		{
			cout << "Кол-во рабочих цехов превышено!" << endl << endl;
			return;
		}

		++cs.guildCountInWork;
	}
	else
	{
		if (cs.guildCountInWork == 0)
		{
			cout << "Кол-во рабочих цехов равно нулю!" << endl << endl;
			return;
		}

		--cs.guildCountInWork;
	}

	cout << "Текущее кол-во рабочих цехов: " << cs.guildCountInWork
		<< endl << endl;
}

bool filtByName(const CS& cs, std::string name)
{
	return cs.name.find(name) != string::npos;
}
bool filtByGuildUpperPercent(const CS& cs, int percent)
{
	return float(cs.guildCount - cs.guildCountInWork)
		/ cs.guildCount * 100 > percent;
}
bool filtByGuildEqualPercent(const CS& cs, int percent)
{
	return float(cs.guildCount - cs.guildCountInWork)
		/ cs.guildCount * 100 == percent;
}
bool filtByGuildLowerPercent(const CS& cs, int percent)
{
	return float(cs.guildCount - cs.guildCountInWork)
		/ cs.guildCount * 100 < percent;
}