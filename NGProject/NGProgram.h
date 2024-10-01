#pragma once
#include <string>
#include <iostream>

template <typename T>
void checkInput(T& var)
{
	while (!(std::cin >> var) || cin.peek() == '\n')
	{
		std::cout << "¬ведите корректное значение!"  << std::endl;

		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
}


class CS;

class Pipe
{
public:

	static int idCount;

	void printPipe(const Pipe& p);
	void redactPipe(Pipe& p);

	friend void saveObjects(const Pipe& p, const CS& cs);
	friend void loadObjects(Pipe& p, CS& cs);

	/*friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);*/

private:
	
	int id;
	std::string kmMark = "null";
	float length;
	int diameter;
	bool isUnderRepair;
};


class CS
{
public:
	static int idCount;

	void printCS(const CS& cs);
	void redactCS(CS& cs);

	friend void saveObjects(const Pipe& p, const CS& cs);
	friend void loadObjects(Pipe& p, CS& cs);

	//friend std::istream& operator >> (std::istream& in, CS& cs);
	//friend std::ostream& operator << (std::ostream& out, const CS& cs);

private:

	int id;
	std::string name;
	int guildCount;
	int guildCountInWork;
	float efficiency;
};

void saveObjects(const Pipe& p, const CS& cs);
void loadObjects(Pipe& p, CS& cs);


