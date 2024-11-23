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

	for (const auto& c : arrCon)
	{
		f << c;
	}

	f.close();

	cout << "Готово!" << endl;
}

void loadObjects(std::unordered_map<int, Pipe>& mapPipe,
	std::unordered_map<int, CS>& mapCS, std::vector<Connection>& arrCon)
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
		else if (type == 'C')
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
		else
		{
			f >> tmpConnection;

			if (tmpConnection.pipeId  == -1)
			{
				cout << "Ошибка: некорректное чтение файла!" << endl;

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

	cout << "Готово!" << endl;
}

void addConnection(std::vector<Connection>& arrCon, std::unordered_map<int, Pipe>& mapP,
	std::unordered_map<int, CS>& mapCS)
{
	if (mapCS.empty() || mapCS.size() < 2)
	{
		cout << "Нельзя создать соединение: недостаточно КС!" << endl;
		return;
	}

	Connection newC;
	int inputId, outputId, diameter;

	printCS(mapCS);
	cout << "Введите последовательно через Enter "
		<< "ID КС входа и ID КС выхода:" << endl;

	while (true)
	{
		checkInput(inputId, 0, INT_MAX);
		
		if (!mapCS.contains(inputId))
		{
			std::cout << "Нет КС с заданным id!" << std::endl
				<< "Попробуйте еще раз: ";
			continue;
		}

		break;
	}

	while (true)
	{
		checkInput(outputId, 0, INT_MAX);

		if (!mapCS.contains(outputId) || (outputId == inputId))
		{
			cout << "Неверный ввод!" << endl
				<< "Попробуйте еще раз: ";
			continue;
		}

		break;
	}

	newC.csInputId = inputId;
	newC.csOutputId = outputId;

	mapCS.at(inputId).isInConnection = true;
	mapCS.at(outputId).isInConnection = true;

	cout << "Выберите диаметр трубы: " << endl;
	cout << "1) 500 мм" << endl << "2) 700 мм" << endl
		<< "3) 1000 мм" << endl << "4) 1400 мм" << endl;
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

	cout << "Готово!" << endl;
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
		cout << "Соединения отсутствуют!" << endl;
		return;
	}

	cout << "Газопровод будет показан в формате (i -> d mm -> o), "
		<< "где i/o - ID КС входа/выхода, d - диаметр трубы между ними:"
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
		cout << "Соединения отсутствуют!" << endl;
		return;
	}

	printConnection(arrCon, mapP);

	cout << "Вводите номер соединения, которое хотите удалить: ";

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

	cout << "Готово!" << endl;
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
		cout << "Ну че, доигрался? Теперь иди цикл в графе ищи!" << endl;
		return;
	}

	cout << "Топологическая сортировка: " << endl;
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
		/*if (std::find(Connection::pipesInConnection.begin(),
			Connection::pipesInConnection.end(), id) == Connection::pipesInConnection.end())
		{
			cout << "Труба " << id << " находится в газопроводе!"
				<< " Сначала удалите соединение!" << endl;
			continue;
		}*/

		if (map.at(id).isInConnection)
		{
			cout << "Труба " << id << " находится в газопроводе!"
				<< " Сначала удалите соединение!" << endl;
			continue;
		}

		map.erase(id);
		cout << "Труба " << id << " удалена" << endl;
	}

	cout << endl;
}

void deleteObjects(std::unordered_map<int, CS>& map, std::unordered_set<int>& set)
{
	for (auto& id : set)
	{
		if (map.at(id).isInConnection)
		{
			cout << "КС " << id << " находится в газопроводе!"
				<< " Сначала удалите соединения!" << endl;
			continue;
		}

		map.erase(id);
		cout << "КС " << id << " удалена" << endl;
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





