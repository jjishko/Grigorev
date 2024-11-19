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

	cout << "������� ������������ ������� (��������): ";
	in >> std::ws;
	inputLine(p.kmMark, in);

	cout << "������� ����� �����: ";
	checkInput(p.length, float(0.1), FLT_MAX, in);

	int diameterInd;
	cout << "�������� ������� �����: " << endl;
	cout << "1) 500 ��" << endl << "2) 700 ��" << endl
		<< "3) 1000 ��" << endl << "4) 1400 ��" << endl;
	checkInput(diameterInd, 1, 4, in);
	p.diameter = pipeDiameters.at(diameterInd - 1);

	cout << "����� � �������? (1 - ��, 0 - ���): ";

	int isUnderRepair;
	checkInput(isUnderRepair, 0, 1, in);
	p.isUnderRepair = bool(isUnderRepair);

	cout << endl << "����� ����������������!" << endl;

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

std::ifstream& operator>>(std::ifstream& in, Pipe& p)
{
	string kmMark;
	in >> std::ws;
	std::getline(in, kmMark);

	float length;
	int id, diameter;
	bool isUnderRepair, isInConnection;

	in >> id >> length >> diameter >> isUnderRepair >> isInConnection;

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
	p.isInConnection = isInConnection;

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
	out << p.isUnderRepair << " ";
	out << p.isInConnection << endl;

	return out;
}

int Pipe::getID()
{
	return this->id;
}

int Pipe::getDiameter() const
{
	return this->diameter;
}

int Pipe::getStatus() const 
{
	return this->isUnderRepair;
}

void createPipeWithGivenDiameter(Pipe& p, int diameter)
{
	p.id = Pipe::idCount;
	++Pipe::idCount;

	p.kmMark = "New Pipe " + std::to_string(p.id);
	p.length = 500;
	p.diameter = diameter;
	p.isUnderRepair = false;
}

void editPipe(Pipe& p)
{
	if (p.isInConnection)
	{
		cout << "����� " << p.id << " ��������� � ������������!"
			<< " ������� ������� ����������!" << endl;
		return;
	}

	p.isUnderRepair = !p.isUnderRepair;

	cout << "ID �����: " << p.id << endl;
	cout << "������� ������: "
		<< (p.isUnderRepair ? "� �������" : "��������") << endl;
}

bool filtByName(const Pipe& p, std::string name)
{
	return p.kmMark.find(name) != string::npos;
}
bool filtByRepairingFlag(const Pipe& p, bool type)
{
	return p.isUnderRepair == type;
}
bool filtByDiameter(const Pipe& p, int d)
{
	return p.diameter == d;
}
