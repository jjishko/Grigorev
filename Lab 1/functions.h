#pragma once
#include <string>

struct Pipe
{
	std::string kmMark;
	float length;
	int diameter;
	bool isUnderRepair;
};

struct CS
{
	std::string name;
	unsigned int guildCount;
	unsigned int guildCountInWork;
	float efficiency;
};

void flush();

void addPipe(Pipe& p);
void addCS(CS& cs);

void printObjects(Pipe& p, CS& cs);

void redactPipe(Pipe& p);
void redactCS(CS& cs);

void saveObjects(Pipe& p, CS& cs);
void loadObjects(Pipe& p, CS& cs);
