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

void printObjects(const Pipe& p, const CS& cs);

void redactPipe(Pipe& p);
void redactCS(CS& cs);

void saveObject(const Pipe& p, const CS& cs);
void loadObject(Pipe& p, CS& cs);
