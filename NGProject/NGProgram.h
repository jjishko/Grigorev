#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

#include "misc.h"

//std::vector<int> parseString(std::string str);

class CS;

class Pipe
{
public:

	static int idCount;

	Pipe();
	int getID();

	friend void editPipe(Pipe& p);

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

class CS
{
public:
	static int idCount;

	CS();
	int getID();

	friend void editCS(CS& cs);

	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);
	friend std::ifstream& operator >> (std::ifstream& in, CS& cs);
	friend std::ofstream& operator << (std::ofstream& out, const CS& cs);

private:

	int id;
	std::string name;
	int guildCount;
	int guildCountInWork;
	float efficiency;
};

void addPipe(std::unordered_map<int, Pipe>& map);
void addCS(std::unordered_map<int, CS>& map);

void editPipe(Pipe& p);
void editCS(CS& cs);

void saveObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS);
void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS);

void printObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS);


void editPipes(std::unordered_map<int, Pipe>& map, 
	std::unordered_set<int>& set);
void editCS(std::unordered_map<int, CS>& map,
	std::unordered_set<int>& set);

void deletePipes(std::unordered_map<int, Pipe>& map,
  std::unordered_set<int>& set);
void deleteCS(std::unordered_map<int, CS>& map,
  std::unordered_set<int>& set);

//часть->фильтр или по id
//все 
template <typename T>
void batchRedacting(std::unordered_map<int, T>& map, 
	void edit(std::unordered_map<int, T>& map, std::unordered_set<int>& set))
{
	int choice;
	std::unordered_set<int> set;

	std::cout << "Введите 1, чтобы работать с выбранными объектами, "
		<< "0, чтобы работать со всеми: ";
	checkInput(choice, 0, 1);
	system("cls");

	if (choice)
	{
		std::cout << "Введите 1, чтобы выбрать объекты по фильтру, "
			<< "0, чтобы выбрать по ID: ";
		checkInput(choice, 0, 1);
		system("cls");

		if (choice)
		{
			for (const auto& [id, el] : map)
			{
				//if (/*сравнить по фильтру*/)
				//{
				//	set.emplace(id);
				//}
			}
		}
		else
		{
			std::cout << "Все объекты: " << std::endl << std::endl;

			for (const auto& obj : map)
			{
				std::cout << obj.second;
			}

			std::cout << std::endl;

			std::cout << "Вводите ID объектов через пробел (-1: закончить ввод):" 
				<< std::endl;

			int id;

			while (true)
			{
				checkInput(id, -1, INT_MAX);

				if (id == -1)
				{
					break;
				}

				if (!map.contains(id))
				{
					std::cout << "Нет объекта с заданным id!" << std::endl;
					continue;
				}

				set.emplace(id);
			}
		}

		std::cout << std::endl << std::endl;
	}
	else
	{
		for (const auto& el : map)
		{
			set.emplace(el.first);
		}
	}

	if (set.empty())
	{
		std::cout << "Не найдено ни одного объекта!" << std::endl << std::endl;
		return;
	}

	edit(map, set);
	std::cout << std::endl << "Готово!" << std::endl;
}


