#pragma once
#include <string>

struct Pipe
{
	std::string kmMark = "Mimi 36";
	float length = 1;
	float diameter = 1;
	bool isUnderRepair = false;
};

struct CS
{
	std::string name = "CS 1";
	unsigned int guildCount = 10;
	unsigned int guildCountInWork = 5;
	float efficiency = 10;
};

int addPipe(Pipe& p);
int addCS(CS& cs);
