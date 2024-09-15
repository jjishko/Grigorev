#pragma once
#include <string>

struct Pipe
{
	std::string kmMark = "Default";
	float length = 1;
	float diameter = 1;
	bool isUnderRepair = false;
};

struct CS
{
	std::string name = "Default";
	unsigned int guildCount = 10;
	unsigned int guildCountInWork = 5;
	float efficiency = 10;
};

void addPipe(Pipe& p);
void addCS(CS& cs);

void printObjects(Pipe& p, CS& cs);

void redactPipe(Pipe& p);
void redactCS(CS& cs);

void saveObjects(Pipe& p, CS& cs);
void loadObjects(Pipe& p, CS& cs);
