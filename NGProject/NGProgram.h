#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <algorithm>

#include "misc.h"
#include "Pipe.h"
#include "CS.h"

using graphMatrix = std::unordered_map<int, std::unordered_map<int, int>>;

struct Connection
{
	int csInputId;
	int csOutputId;
	int pipeId;
	//static std::vector<int> pipesInConnection;
};

std::ifstream& operator >> (std::ifstream& in, Connection& c);
std::ofstream& operator << (std::ofstream& out, const Connection& c);

void addConnection(std::vector<Connection>& arrCon, std::unordered_map<int, Pipe>& mapP,
	std::unordered_map<int, CS>& mapCS);

void printConnection(const Connection& c,
	const std::unordered_map<int, Pipe>& mapP);
void printConnection(const std::vector<Connection> arrCon,
	const std::unordered_map<int, Pipe>& mapP);

void deleteConnection(std::vector<Connection>& arrCon, std::unordered_map<int, Pipe>& mapP,
	std::unordered_map<int, CS>& mapCS);

void findShortestPath(const std::vector<Connection>& arrCon,
	const std::unordered_map<int, Pipe>& mapPipe);
void topologicalSort(const std::vector<Connection>& arrCon,
	const std::unordered_map<int, Pipe>& mapPipe);

void addPipe(std::unordered_map<int, Pipe>& map);
void addCS(std::unordered_map<int, CS>& map);

void saveObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS, const std::vector<Connection>& arrCon);
void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS, std::vector<Connection>& arrCon);

void printPipes(const std::unordered_map<int, Pipe>& map);
void printCS(const std::unordered_map<int, CS>& map);
void printAll(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS);

void editObjects(std::unordered_map<int, Pipe>& map, 
	std::unordered_set<int>& set);
void editObjects(std::unordered_map<int, CS>& map,
	std::unordered_set<int>& set);

void deleteObjects(std::unordered_map<int, Pipe>& map,
  std::unordered_set<int>& set);
void deleteObjects(std::unordered_map<int, CS>& map,
  std::unordered_set<int>& set);

template <typename T1, typename T2>
using filter = bool(*)(const T1& obj, T2 param);

template <typename T1, typename T2>
void filtObjects(const std::unordered_map<int, T1>& map, 
	std::unordered_set<int>& set, filter<T1, T2> f, T2 param)
{
	for (const auto& [id, obj] : map)
	{
		if (f(obj, param))
		{
			set.insert(id);
		}
	}
}

std::unordered_set<int> filterIntersection(std::unordered_set<int>& oldSet,
	std::unordered_set<int>& newSet);

std::unordered_set<int> makeSetOfFilteredPipes(const std::unordered_map<int, Pipe>& map);
std::unordered_set<int> makeSetOfFilteredCS(const std::unordered_map<int, CS>& map);

template <typename T>
void selectById(const std::unordered_map<int, T>& map, std::unordered_set<int>& set)
{
	std::cout << "��� �������: " << std::endl << std::endl;

	for (const auto& obj : map)
	{
		std::cout << obj.second;
	}

	std::cout << std::endl;

	std::cout << "������� ID �������� ����� ������ (-1: ��������� ����):"
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
			std::cout << "��� ������� � �������� id!" << std::endl;
			continue;
		}

		set.emplace(id);
	}

	std::cout << std::endl << std::endl;
}

template <typename T>
void batchEditing(std::unordered_map<int, T>& map,
	void edit(std::unordered_map<int, T>& map, std::unordered_set<int>& set))
{
	int choice;
	std::unordered_set<int> set;

	if (map.empty())
	{
		std::cout << "���������� ������� ��� ������!" << std::endl;
		return;
	}

	std::cout << "������� 1, ����� ����� ������� �� �������, "
		<< "2, ����� ������� �� ID (��� ��� �����): ";
	checkInput(choice, 0, 2);
	system("cls");

	if (!choice)
	{
		std::cout << "������ ��������." << std::endl;
		return;
	}

	if (choice == 1)
	{
		if constexpr (std::is_same_v<T, Pipe>)
		{
			set = makeSetOfFilteredPipes(map);
		}
		else if constexpr (std::is_same_v<T, CS>)
		{
			set = makeSetOfFilteredCS(map);
		}
	}
	else if (choice == 2)
	{
		std::cout << "������� 1, ����� ������� ������� �� ID, "
			<< "2, ����� ������� ���: ";
		checkInput(choice, 0, 2);
		system("cls");

		if (!choice)
		{
			std::cout << "������ ��������." << std::endl;
			return;
		}

		if (choice == 1)
		{
			selectById(map, set);
		}
		else if (choice == 2)
		{
			for (const auto& el : map)
			{
				set.emplace(el.first);
			}
		}
	}

	if (set.empty())
	{
		std::cout << "�� ������� �� ������ �������!" << std::endl << std::endl;
		return;
	}

	edit(map, set);
	std::cout << std::endl << "������!" << std::endl;
}

template <typename T>
void chooseAction(std::unordered_map<int, T>& map)
{
	int actionType;

	std::cout << "������� 1, ���� ������ ������������� �������, 2, ���� ������ �������"
		<< " (0, ����� ��������): ";
	checkInput(actionType, 0, 2);
	system("cls");

	switch (actionType)
	{
	case 1:
		batchEditing(map, editObjects);
		break;

	case 2:
		batchEditing(map, deleteObjects);
		break;

	case 0:
		std::cout << "������ ��������." << std::endl;
		return;
	}

}

