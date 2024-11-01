#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "misc.h"
#include "NGProgram.h"
#include "Pipe.h"
#include "CS.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void saveObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS)
{
	if (mapPipe.empty() && mapCS.empty())
	{
		cout << "Нет данных для сохранения!" << endl;
		return;
	}

	string fileName;

	cout << "Введите название файла или путь (без расширения и пробелов): ";
	char a = cin.get();
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ofstream f(fileName + ".txt");

	if (!f.is_open())
	{
		cout << "Ошибка: файл для сохранения не найден!" << endl;
		return;
	}

	for (const auto& p : mapPipe)
	{
		f << p.second;
	}

	for (const auto& cs : mapCS)
	{
		f << cs.second;
	}

	f.close();

	cout << "Готово!" << endl;
}

void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS)
{
	string fileName;

	cout << "Введите название файла или путь (без расширения и пробелов): ";
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ifstream f(fileName + ".txt");

	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "Ошибка: файл для загрузки не найден или пуст!" << endl;
		return;
	}

	int maxPipeId, maxCSId;

	maxPipeId = Pipe::idCount;
	Pipe::idCount = 0;
	maxCSId = CS::idCount;
	CS::idCount = 0;

	std::unordered_map<int, Pipe> newMapPipe;
	std::unordered_map<int, CS> newMapCS;

	Pipe tmpPipe;
	CS tmpCS;
	char type;

	while (f.peek() != EOF)
	{
		type = f.get();
		f.get();

		if (type != 'P' && type != 'C')
		{
			cout << "Ошибка: некорректное чтение файла!" << endl;

			Pipe::idCount = maxPipeId;
			CS::idCount = maxCSId;

			f.close();
			return;
		}

		if (type == 'P')
		{
			f >> tmpPipe;

			if (tmpPipe.getID() == -1)
			{
				cout << "Ошибка: некорректное чтение файла!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			Pipe::idCount = std::max(Pipe::idCount, tmpPipe.getID() + 1);
			newMapPipe.emplace(tmpPipe.getID(), tmpPipe);
		}
		else
		{
			f >> tmpCS;

			if (tmpCS.getID() == -1)
			{
				cout << "Ошибка: некорректное чтение файла!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			CS::idCount = std::max(CS::idCount, tmpCS.getID() + 1);
			newMapCS.emplace(tmpCS.getID(), tmpCS);
		}

		f.get();
	}

	mapPipe = newMapPipe;
	mapCS = newMapCS;

	f.close();

	cout << "Готово!" << endl;
}


void addPipe(std::unordered_map<int, Pipe>& map)
{
	Pipe p;
	cin >> p;

	map.emplace(p.getID(), p);
}

void addCS(std::unordered_map<int, CS>& map)
{
	CS cs;
	cin >> cs;

	map.emplace(cs.getID(), cs);
}

void printPipes(const std::unordered_map<int, Pipe>& map)
{
	cout << "Трубы:" << endl << endl;

	if (map.empty())
	{
		cout << "Трубы отсутствуют" << endl << endl;
	}
	else
	{
		for (const auto& p : map)
		{
			cout << p.second;
		}
	}

	cout << endl;
}

void printCS(const std::unordered_map<int, CS>& map)
{
	cout << "КС:" << endl << endl;

	if (map.empty())
	{
		cout << "КС отсутствуют" << endl << endl;
	}
	else
	{
		for (const auto& cs : map)
		{
			cout << cs.second;
		}
	}

	cout << endl;
}

void printAll(const std::unordered_map<int, Pipe>& mapPipe,
	 const std::unordered_map<int, CS>& mapCS)
{
	printPipes(mapPipe);
	printCS(mapCS);
}

void editObjects(std::unordered_map<int, Pipe>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		editPipe(map.at(id));
	}
}

void editObjects(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		editCS(map.at(id));
	}
}

void deleteObjects(std::unordered_map<int, Pipe>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		map.erase(id);
		cout << "Труба " << id << " удалена" << endl;
	}

	cout << endl;
}

void deleteObjects(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		map.erase(id);
		cout << "КС " << id << " удалена" << endl;
	}
}


std::unordered_set<int> filterIntersection(std::unordered_set<int>& oldSet,
	std::unordered_set<int>& newSet)
{
	std::unordered_set<int> set;

	if (oldSet.empty())
	{
		set = newSet;
	}
	else
	{
		std::set_intersection(oldSet.begin(), oldSet.end(), newSet.begin(), newSet.end(),
			std::inserter(set, set.begin()));
	}

	if (set.empty())
	{
		std::cout << "Не найдено объектов, подходящих по фильтру!"
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "ID найденных элементов: ";

		for (int id : set)
		{
			std::cout << id << " ";
		}

		std::cout << std::endl << std::endl;
	}

	oldSet.clear();
	newSet.clear();

	return set;
}

std::unordered_set<int> makeSetOfFilteredPipes(const std::unordered_map<int, Pipe>& map)
{
	int filtType;
	std::unordered_set<int> set, oldSet, newSet;

	std::string name;
	int status;

	printPipes(map);

	cout << endl;
	cout << "Перечень фильтров: " << endl;
	cout << "1 - фильтр по названию" << endl 
		<< "2 - по признаку \"в ремонте\"" << endl << endl;

	while (true)
	{
		cout << "Введите номер фильтра (0, если хотите закончить фильтрацию): ";

		checkInput(filtType, -1, 1);

		if (!filtType)
		{
			cout << endl;
			break;
		}

		if (filtType == 1)
		{
			cout << "Введите строку для фильтра: ";
			cin >> std::ws;
			inputLine(name, cin);

			filtObjects(map, newSet, filtByName, name);
		}
		else if (filtType == 2)
		{
			cout << "Введите статус (0 - статус \"в ремонте\", 1 - статус \"работает\"): ";
			checkInput(status, 0, 1);

			filtObjects(map, newSet, filtByRepairingFlag, !bool(status));
		}

		oldSet.insert(set.begin(), set.end());
		set.clear();
		set = filterIntersection(oldSet, newSet);
	}

	return set;
}

std::unordered_set<int> makeSetOfFilteredCS(const std::unordered_map<int, CS>& map)
{
	int filtType;
	std::unordered_set<int> set, oldSet, newSet;

	std::string name;
	int percent;
	int comparePercent;

	printCS(map);

	cout << endl;
	cout << "Перечень фильтров: " << endl;
	cout << "1 - фильтр по названию" << endl
		<< "2 - по проценту незайдействованных цехов" << endl << endl;

	while (true)
	{
		cout << "Введите номер фильтра (0, если хотите закончить фильтрацию): ";
		checkInput(filtType, 0, 2);

		if (!filtType)
		{
			cout << endl;
			break;
		}

		if (filtType == 1)
		{
			cout << "Введите строку для фильтра: ";
			cin >> std::ws;
			inputLine(name, cin);

			filtObjects(map, newSet, filtByName, name);
		}
		else if (filtType == 2)
		{
			cout << "Введите процент незадействованных цехов: ";
			checkInput(percent, 0, 100);

			cout << "Введите 1, чтобы найти КС с процентом, больше введенного, "
				<< "2 - меньше введенного, 3 - равным введенному: ";
			checkInput(comparePercent, 1, 3);

			if (comparePercent == 1)
			{
				filtObjects(map, newSet, filtByGuildUpperPercent, percent);
			}
			else if (comparePercent == 2)
			{
				filtObjects(map, newSet, filtByGuildLowerPercent, percent);
			}
			else if (comparePercent == 3)
			{
				filtObjects(map, newSet, filtByGuildEqualPercent, percent);
			}
		}

		oldSet.insert(set.begin(), set.end());
		set.clear();
		set = filterIntersection(oldSet, newSet);
	}

	return set;
}





