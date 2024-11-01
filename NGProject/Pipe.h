#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "misc.h"

class Pipe
{
public:

	static int idCount;

	int getID();

	friend void editPipe(Pipe& p);
	friend bool filtByName(const Pipe& p, std::string name);
	friend bool filtByRepairingFlag(const Pipe& p, bool type);

	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);

private:

	int id;
	std::string kmMark;
	float length;
	int diameter;
	bool isUnderRepair;
};

void editPipe(Pipe& p);

bool filtByName(const Pipe& p, std::string name);
bool filtByRepairingFlag(const Pipe& p, bool type);