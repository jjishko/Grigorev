#include <iostream>
#include <string>
#include <fstream>

#include "NGProgram.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int Pipe::idCount = 0;
int CS::idCount = 0;

std::istream& operator>>(std::istream& in, Pipe& p)
{
	p.id = p.idCount;
	++p.idCount;

	cout << "Введите километровую отметку (название): ";
	cin >> std::ws;
	std::getline(in, p.kmMark);

	cout << "Введите длину трубы: ";
	checkInput(p.length, float(0), FLT_MAX, in);

	cout << "Введите диаметр трубы: ";
	checkInput(p.diameter, 0, INT_MAX, in);

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	checkInput(p.isUnderRepair, true, true, in);

	cout << endl << "Труба инициализирована!" << endl;

	return in;
}

std::istream& operator>>(std::istream& in, CS& cs)
{
	cs.id = cs.idCount;
	++cs.idCount;

	cout << "Введите название КС: ";
	cin >> std::ws;
	std::getline(cin, cs.name);

	cout << "Введите кол-во цехов: ";
	checkInput(cs.guildCount, 0, INT_MAX, in);

	cout << "Введите кол-во цехов в работе: ";
	checkInput(cs.guildCountInWork, 0, cs.guildCount + 1, in);

	cout << "Введите коэффициент эффективности КС: ";
	checkInput(cs.efficiency, float(- 101), float(101), in);

	cout << endl << "КС инициализирована!" << endl;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Pipe& p)
{
	out << "ID трубы: " << p.id << endl;
	out << "Километровая отметка (название) трубы: " << p.kmMark << endl;
	out << "Длина трубы: " << p.length << endl;
	out << "Диаметр трубы: " << p.diameter << endl;
	out << "Статус: " << (p.isUnderRepair ? "В ремонте" : "Работает") << endl;
	out << endl;

	return out;
}

std::ostream& operator<<(std::ostream& out, const CS& cs)
{
	out << "ID КС: " << cs.id << endl;
	out << "Название КС: " << cs.name << endl;
	out << "Кол-во цехов: " << cs.guildCount << endl;
	out << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
	out << "Коэффициент эффективности: " << cs.efficiency << endl;
	out << endl;

	return out;
}

int Pipe::getID()
{
	return this->id;
}

int CS::getID()
{
	return this->id;
}

void Pipe::redactPipe(Pipe& p)
{
	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	checkInput(p.isUnderRepair, true, true, cin);

	cout << "Статус изменен!" << endl;
}

void CS::redactCS(CS& cs)
{
	bool increase;

	cout << "Добавить цех - 1, убрать - 0" << endl;

	cout << "Введите номер: ";
	while (true)
	{
		checkInput(increase, true, true, cin);

		if (increase)
		{
			if (cs.guildCount == cs.guildCountInWork)
			{
				cout << "Кол-во рабочих цехов превышено!" << endl;
				return;
			}

			++cs.guildCountInWork;
		}
		else
		{
			if (cs.guildCountInWork == 0)
			{
				cout << "Кол-во рабочих цехов равно нулю!" << endl;
				return;
			}

			--cs.guildCountInWork;
		}

		break;
	}

	cout << "Готово!" << endl;
}

//сохранять id
void saveObjects(const Pipe& p, const CS& cs)
{
	string fileName;

	cout << "Введите название файла или путь (без расширения): ";
	std::getline(cin, fileName);

	std::ofstream f(fileName + ".txt");
	//std::ofstream f(fileName, std::ios::app);

	if (!f.is_open())
	{
		cout << "Ошибка: файл для сохранения недоступен!" << endl;
		return;
	}

	if (cs.name == "" && p.kmMark == "")
	{
		cout << "Ошбика: Данные отсутствуют!" << endl;

		f.close();
		return;
	}

	if (p.kmMark == "")
	{
		cout << "Данные трубы отсутствуют!" << endl;
	}
	else
	{
		f << 'P' << endl;
		f << p.kmMark << endl;
		f << p.length << " ";
		f << p.diameter << " ";
		f << p.isUnderRepair << endl;

		cout << "Данные трубы сохранены! ";
	}

	if (cs.name == "")
	{
		cout << "Данные КС отсутствуют!" << endl;
	}
	else
	{
		f << 'C' << endl;
		f << cs.name << endl;
		f << cs.guildCount << " ";
		f << cs.guildCountInWork << " ";
		f << cs.efficiency;

		cout << "Данные КС сохранены! " << endl;
	}

	f.close();

}

void loadObjects(Pipe& p, CS& cs)
{
	string fileName;

	cout << "Введите название файла или путь (без расширения): ";
	std::getline(cin, fileName);

	std::ifstream f(fileName + ".txt");

	if (!f.is_open() || f.peek() == EOF)
	{
		cout << "Ошибка: файл для сохранения не найден или пуст!" << endl;
		return;
	}

	char type;


	while (f.peek() != EOF)
	{
		type = f.get();
		f.get();

		if (type != 'P' && type != 'C')
		{
			cout << "Ошибка: некорректное чтение файла!" << endl;

			f.close();
			return;
		}

		if (type == 'P')
		{
			std::getline(f, p.kmMark);
			f >> p.length >> p.diameter >> p.isUnderRepair;

			if (p.kmMark == "" || f.fail())
			{
				cout << "Ошибка: некорректное считывание из файла!" << endl;

				f.close();
				return;
			}

			cout << "Труба загружена!" << endl;
		}
		else
		{
			std::getline(f, cs.name);
			f >> cs.guildCount >> cs.guildCountInWork
				>> cs.efficiency;

			if (cs.name == "" || f.fail())
			{
				cout << "Ошибка: некорректное считывание из файла!" << endl;
				return;
			}

			cout << "КС загружена!" << endl;
		}

		f.get();
	}


	f.close();
}

void addPipe(std::unordered_map<int, Pipe>& map)
{
	Pipe p;
	cin >> p;

	map.insert({ p.getID(), p });
}

void addCS(std::unordered_map<int, CS>& map)
{
	CS cs;
	cin >> cs;

	map.insert({ cs.getID(), cs });
}

void printObjects(std::unordered_map<int, Pipe>& mapPipe, std::unordered_map<int, CS>& mapCS)
{
	cout << "Трубы:" << endl << endl;

	for(auto& p : mapPipe)
	{
		cout << p.second;
	}

	cout << endl << "КС:" << endl << endl;

	for (auto& cs : mapCS)
	{
		cout << cs.second;
	}
}



