#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

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

std::ifstream& operator>>(std::ifstream& in, Connection& c)
{
	int inputCSId, outputCSId, pipeId;

	in >> inputCSId >> outputCSId >> pipeId;

	if (in.fail())
	{
		c.pipeId = 0;
		return in;
	}

	c.csInputId = inputCSId;
	c.csOutputId = outputCSId;
	c.pipeId = pipeId;

	return in;
}
std::ofstream& operator<<(std::ofstream& out, const Connection& c)
{
	out << 'G' << endl;
	out << c.csInputId << " ";
	out << c.csOutputId << " ";
	out << c.pipeId << endl;

	return out;
}

void saveObjects(const std::unordered_map<int, Pipe>& mapPipe,
	const std::unordered_map<int, CS>& mapCS, const std::vector<Connection>& arrCon)
{
	if (mapPipe.empty() && mapCS.empty())
	{
		cout << "��� ������ ��� ����������!" << endl;
		return;
	}

	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ���������� � ��������): ";
	char a = cin.get();
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ofstream f(fileName + ".txt");

	if (!f.is_open())
	{
		cout << "������: ���� ��� ���������� �� ������!" << endl;
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

	for (const auto& c : arrCon)
	{
		f << c;
	}

	f.close();

	cout << "������!" << endl;
}

void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS, std::vector<Connection>& arrCon)
{
	string fileName;

	cout << "������� �������� ����� ��� ���� (��� ���������� � ��������): ";
	cin >> std::ws;
	inputLine(fileName, cin);

	std::ifstream f(fileName + ".txt");

	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "������: ���� ��� �������� �� ������ ��� ����!" << endl;
		return;
	}

	int maxPipeId, maxCSId;

	maxPipeId = Pipe::idCount;
	Pipe::idCount = 0;
	maxCSId = CS::idCount;
	CS::idCount = 0;

	std::unordered_map<int, Pipe> newMapPipe;
	std::unordered_map<int, CS> newMapCS;
	std::vector<Connection> newArrCon;

	Pipe tmpPipe;
	CS tmpCS;
	Connection tmpConnection;
	char type;

	while (f.peek() != EOF)
	{
		type = f.get();
		f.get();

		if (type != 'P' && type != 'C' && type != 'G')
		{
			cout << "������: ������������ ������ �����!" << endl;

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
				cout << "������: ������������ ������ �����!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			Pipe::idCount = std::max(Pipe::idCount, tmpPipe.getID() + 1);
			newMapPipe.emplace(tmpPipe.getID(), tmpPipe);
		}
		else if (type == 'C')
		{
			f >> tmpCS;

			if (tmpCS.getID() == -1)
			{
				cout << "������: ������������ ������ �����!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			CS::idCount = std::max(CS::idCount, tmpCS.getID() + 1);
			newMapCS.emplace(tmpCS.getID(), tmpCS);
		}
		else
		{
			f >> tmpConnection;

			if (tmpConnection.pipeId  == -1)
			{
				cout << "������: ������������ ������ �����!" << endl;

				Pipe::idCount = maxPipeId;
				CS::idCount = maxCSId;

				f.close();
				return;
			}

			newArrCon.push_back(tmpConnection);
		}

		f.get();
	}

	mapPipe = newMapPipe;
	mapCS = newMapCS;
	arrCon = newArrCon;

	f.close();

	cout << "������!" << endl;
}

void addConnection(std::vector<Connection>& arrCon, std::unordered_map<int, Pipe>& mapP,
	std::unordered_map<int, CS>& mapCS)
{
	if (mapCS.empty() || mapCS.size() < 2)
	{
		cout << "������ ������� ����������: ������������ ��!" << endl;
		return;
	}

	Connection newC;
	int inputId, outputId, diameter;

	printCS(mapCS);
	cout << "������� ��������������� ����� Enter "
		<< "ID �� ����� � ID �� ������:" << endl;

	while (true)
	{
		checkInput(inputId, 0, INT_MAX);
		
		if (!mapCS.contains(inputId))
		{
			std::cout << "��� �� � �������� id!" << std::endl
				<< "���������� ��� ���: ";
			continue;
		}

		break;
	}

	while (true)
	{
		checkInput(outputId, 0, INT_MAX);

		if (!mapCS.contains(outputId) || (outputId == inputId))
		{
			cout << "�������� ����!" << endl
				<< "���������� ��� ���: ";
			continue;
		}

		break;
	}

	newC.csInputId = inputId;
	newC.csOutputId = outputId;

	mapCS.at(inputId).isInConnection = true;
	mapCS.at(outputId).isInConnection = true;

	cout << "�������� ������� �����: " << endl;
	cout << "1) 500 ��" << endl << "2) 700 ��" << endl
		<< "3) 1000 ��" << endl << "4) 1400 ��" << endl;
	checkInput(diameter, 1, 4);
	diameter = pipeDiameters.at(diameter - 1);

	newC.pipeId = -1;

	for (const auto& [id, p] : mapP)
	{
		if (filtByDiameter(p, diameter))
		{
			if (p.getStatus() || p.isInConnection)
			{
				continue;
			}

			newC.pipeId = id;
			break;		
		}
	}

	if (newC.pipeId == -1)
	{
		Pipe p;
		createPipeWithGivenDiameter(p, diameter);
		mapP.emplace(p.getID(), p);
		newC.pipeId = p.getID();
	}

	arrCon.push_back(newC);
	mapP.at(newC.pipeId).isInConnection = true;

	cout << "������!" << endl;
}

void printConnection(const Connection& c,
	const std::unordered_map<int, Pipe>& mapP)
{
	std::cout << c.csInputId << " -> "
		<< mapP.find(c.pipeId)->second.getDiameter()
		<< " mm -> " << c.csOutputId << endl;
}

void printConnection(const std::vector<Connection> arrCon,
	const std::unordered_map<int, Pipe>& mapP)
{
	if (arrCon.empty())
	{
		cout << "���������� �����������!" << endl;
		return;
	}

	cout << "���������� ����� ������� � ������� (i -> d mm -> o), "
		<< "��� i/o - ID �� �����/������, d - ������� ����� ����� ����:"
		<< endl << endl;

	for (int i = 0; i < arrCon.size(); ++i)
	{
		cout << i + 1 << ") ";
		printConnection(arrCon.at(i), mapP);
	}

	cout << endl;
}

void deleteConnection(std::vector<Connection>& arrCon, std::unordered_map<int, Pipe>& mapP,
	std::unordered_map<int, CS>& mapCS)
{
	if (arrCon.empty())
	{
		cout << "���������� �����������!" << endl;
		return;
	}

	printConnection(arrCon, mapP);

	cout << "������� ����� ����������, ������� ������ �������: ";

	int indToDelete;
	checkInput(indToDelete, 1, int(arrCon.size()));
	--indToDelete;
	
	mapP.at(arrCon.at(indToDelete).pipeId).isInConnection = false;

	bool inputCSHaveConnections = false;
	bool outputCSHaveConnections = false;

	for (int i = 0; i < arrCon.size(); ++i)
	{
		if ((arrCon.at(i).csInputId == arrCon.at(indToDelete).csInputId ||
			arrCon.at(i).csOutputId == arrCon.at(indToDelete).csInputId) && i != indToDelete)
		{
			inputCSHaveConnections = true;
		}

		if ((arrCon.at(i).csInputId == arrCon.at(indToDelete).csOutputId ||
			arrCon.at(i).csOutputId == arrCon.at(indToDelete).csOutputId) && i != indToDelete)
		{
			outputCSHaveConnections = true;
		}

		if (inputCSHaveConnections && outputCSHaveConnections)
			break;
	}

	if (!inputCSHaveConnections)
	{
		mapCS.at(arrCon.at(indToDelete).csInputId).isInConnection = false;
	}

	if (!outputCSHaveConnections)
	{
		mapCS.at(arrCon.at(indToDelete).csOutputId).isInConnection = false;

	}

	arrCon.erase(arrCon.begin() + indToDelete);

	cout << "������!" << endl;
}

void convertToAdjacencyMatrix(const std::vector<Connection>& arrCon,
	std::unordered_map<int, std::vector<int>>& graph)
{
	if (arrCon.empty())
	{
		return;
	}

	for (auto& con : arrCon)
	{
		if (!graph.contains(con.csInputId))
		{
			graph.emplace(con.csInputId, std::vector<int> ());
		}

		if (!graph.contains(con.csOutputId))
		{
			graph.emplace(con.csOutputId, std::vector<int>());
		}

		graph.at(con.csInputId).push_back(con.csOutputId);
	}

	/*for (auto& [in, out] : graph)
	{
		cout << in << " ";

		for (auto& v : out)
		{
			cout << v << " ";
		}

		cout << endl;
	}*/
}

void topologicalSort(std::vector<Connection>& arrCon)
{
	if (arrCon.empty())
	{
		return;
	}

	std::unordered_map<int, std::vector<int>> graph;
	std::vector<int> result;

	convertToAdjacencyMatrix(arrCon, graph);

	int n = graph.size();

	std::vector<int> inCount(n, 0);

	for (auto& [thisVert, verts] : graph) 
	{
		for (int vert : verts) {
			inCount[vert]++;
		}
	}

	std::queue<int> usedVerts;

	for (int i = 0; i < n; ++i) 
	{
		if (inCount[i] == 0) 
		{
			usedVerts.push(i);
		}
	}

	while (!usedVerts.empty()) {
		int noInVert = usedVerts.front();
		usedVerts.pop();

		result.push_back(noInVert);

		for (int vert : graph.at(noInVert)) {
			inCount[vert]--;

			if (inCount[vert] == 0) {
				usedVerts.push(vert);
			}
		}
	}

	if (result.empty())
	{
		cout << "�� ��, ���������? ������ ��� ���� � ����� ���!" << endl;
		return;
	}

	cout << "�������������� ����������: " << endl;
	for (int v : result) 
	{
		cout << v << " ";
	}
	cout << endl;
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
	cout << "�����:" << endl << endl;

	if (map.empty())
	{
		cout << "����� �����������" << endl << endl;
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
	cout << "��:" << endl << endl;

	if (map.empty())
	{
		cout << "�� �����������" << endl << endl;
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
		/*if (std::find(Connection::pipesInConnection.begin(),
			Connection::pipesInConnection.end(), id) == Connection::pipesInConnection.end())
		{
			cout << "����� " << id << " ��������� � �����������!"
				<< " ������� ������� ����������!" << endl;
			continue;
		}*/

		if (map.at(id).isInConnection)
		{
			cout << "����� " << id << " ��������� � �����������!"
				<< " ������� ������� ����������!" << endl;
			continue;
		}

		map.erase(id);
		cout << "����� " << id << " �������" << endl;
	}

	cout << endl;
}

void deleteObjects(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		if (map.at(id).isInConnection)
		{
			cout << "�� " << id << " ��������� � �����������!"
				<< " ������� ������� ����������!" << endl;
			continue;
		}

		map.erase(id);
		cout << "�� " << id << " �������" << endl;
	}

	cout << endl;
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
		std::cout << "�� ������� ��������, ���������� �� �������!"
			<< std::endl << std::endl;
	}
	else
	{
		std::cout << "ID ��������� ���������: ";

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
	cout << "�������� ��������: " << endl;
	cout << "1 - ������ �� ��������" << endl 
		<< "2 - �� �������� \"� �������\"" << endl << endl;

	while (true)
	{
		cout << "������� ����� ������� (0, ���� ������ ��������� ����������): ";

		checkInput(filtType, 0, 2);

		if (!filtType)
		{
			cout << endl;
			break;
		}

		if (filtType == 1)
		{
			cout << "������� ������ ��� �������: ";
			cin >> std::ws;
			inputLine(name, cin);

			filtObjects(map, newSet, filtByName, name);
		}
		else if (filtType == 2)
		{
			cout << "������� ������ (0 - ������ \"� �������\", 1 - ������ \"��������\"): ";
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
	cout << "�������� ��������: " << endl;
	cout << "1 - ������ �� ��������" << endl
		<< "2 - �� �������� ������������������ �����" << endl << endl;

	while (true)
	{
		cout << "������� ����� ������� (0, ���� ������ ��������� ����������): ";
		checkInput(filtType, 0, 2);

		if (!filtType)
		{
			cout << endl;
			break;
		}

		if (filtType == 1)
		{
			cout << "������� ������ ��� �������: ";
			cin >> std::ws;
			inputLine(name, cin);

			filtObjects(map, newSet, filtByName, name);
		}
		else if (filtType == 2)
		{
			cout << "������� ������� ����������������� �����: ";
			checkInput(percent, 0, 100);

			cout << "������� 1, ����� ����� �� � ���������, ������ ����������, "
				<< "2 - ������ ����������, 3 - ������ ����������: ";
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





