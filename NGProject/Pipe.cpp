#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "misc.h"
#include "NGProgram.h"
#include "Pipe.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int Pipe::idCount = 0;

std::istream& operator>>(std::istream& in, Pipe& p)
{
	p.id = Pipe::idCount;
	++Pipe::idCount;

	cout << "Введите километровую отметку (название): ";
	in >> std::ws;
	inputLine(p.kmMark, in);

	cout << "Введите длину трубы: ";
	checkInput(p.length, float(0.1), FLT_MAX, in);

	cout << "Введите диаметр трубы: ";
	checkInput(p.diameter, 1, INT_MAX, in);

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";

	int isUnderRepair;
	checkInput(isUnderRepair, 0, 1, in);
	p.isUnderRepair = bool(isUnderRepair);

	cout << endl << "Труба инициализирована!" << endl;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Pipe& p)
{
	out << "ID трубы: " << p.id << endl;
	out << "Километровая отметка (название) трубы: " << p.kmMark << endl;
	out << "Длина трубы: " << p.length << endl;
	out << "Диаметр трубы: " << p.diameter << endl;
	out << "Статус: " << (p.isUnderRepair ? "В ремонте" : "Работает") << endl;
	out << endl;

	return out;
}

std::ifstream& operator>>(std::ifstream& in, Pipe& p)
{
	string kmMark;
	std::cin >> std::ws;
	std::getline(in, kmMark);

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

int Pipe::getID()
{
	return id;
}

void editPipe(Pipe& p)
{
	p.isUnderRepair = !p.isUnderRepair;

	cout << "ID трубы: " << p.id << endl;
	cout << "Текущий статус: "
		<< (p.isUnderRepair ? "В ремонте" : "Работает") << endl;
}

bool filtByName(const Pipe& p, std::string name)
{
	return p.kmMark.find(name) != string::npos;
}
bool filtByRepairingFlag(const Pipe& p, bool type)
{
	return p.isUnderRepair == type;
}