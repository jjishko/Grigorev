#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

/// <summary>
/// На вход дается ИНТЕРВАЛ, не отрезок
/// </summary>
template <typename T>
void checkInput(T& var, T left, T right,
	std::istream& in = std::cin)
{
	bool extraLine;
	bool notInInterval;
	std::string type;

	while (true)
	{
		in >> var;

		extraLine = (in.peek() != 10);
		type = typeid(T).name();

		if (type == "bool")
		{
			notInInterval = false;
		}
		else
		{
			notInInterval = (var <= left || var >= right);
		}

		if (extraLine || notInInterval)
		{
			std::cout << "Ошибка: кривые руки!" << std::endl;
			std::cout << "Попробуйте еще раз: ";

			in.clear();
			in.ignore(10000, '\n');
			continue;
		}

		std::cin.ignore(10000, '\n');
		break;
	}
}

class CS;

class Pipe
{
public:

	static int idCount;

	int getID();
	void redactPipe(Pipe& p);

	friend void saveObjects(const Pipe& p, const CS& cs);
	friend void loadObjects(Pipe& p, CS& cs);

	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);

private:
	
	int id;
	std::string kmMark;
	float length;
	int diameter;
	bool isUnderRepair;
};

class CS
{
public:
	static int idCount;

	int getID();
	void redactCS(CS& cs);

	friend void saveObjects(const Pipe& p, const CS& cs);
	friend void loadObjects(Pipe& p, CS& cs);

	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);

private:

	int id;
	std::string name;
	int guildCount;
	int guildCountInWork;
	float efficiency;
};

void saveObjects(const Pipe& p, const CS& cs);
void loadObjects(Pipe& p, CS& cs);


void addPipe(std::unordered_map<int, Pipe>& map);
void addCS(std::unordered_map<int, CS>& map);

void printObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS);


