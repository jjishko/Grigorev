#pragma once
#include <string>

struct pipe
{
	std::string kmMark = "Mimi 36";
	unsigned int length = 1;
	unsigned int diameter = 1;
	bool isUnderRepair = false;
};

struct CS
{
	std::string name = "CS 1";
	unsigned int guildCount = 10;
	unsigned int guildCountInWork = 5;
	int efficiency = 10;
};
