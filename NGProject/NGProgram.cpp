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

Pipe::Pipe()
{
	id = idCount;
	++idCount;

	cout << "Введите километровую отметку (название): ";
	while (true)
	{
		std::getline(cin, kmMark);

		if (kmMark == "null")
		{
			cout << "null незя, ты давай еще подумай!" << endl;
			continue;
		}

		break;
	}

	cout << "Введите длину трубы: ";
	while (true)
	{
		checkInput(length);

		if (length <= 0)
		{
			cout << "Длина должна быть больше нуля!" << endl;
			continue;
		}

		break;
	}

	cout << "Введите диаметр трубы: ";
	while (true)
	{
		checkInput(diameter);

		if (diameter < 1)
		{
			cout << "Диаметр не может быть меньше 1!" << endl;
			continue;
		}

		break;
	}

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	checkInput(isUnderRepair);

	cout << endl << "Труба инициализирована!" << endl;
}

CS::CS()
{
	id = idCount;
	++idCount;

	cout << "Введите название КС: ";
	while (true)
	{
		std::getline(cin, name);

		if (name == "null")
		{
			cout << "null незя, ты давай еще подумай!" << endl;
			continue;
		}

		break;
	}

	cout << "Введите кол-во цехов: ";
	while (true)
	{
		checkInput(guildCount);

		if (guildCount < 1)
		{
			cout << "Кол-во цехов должно быть больше нуля!" << endl;
			continue;
		}

		break;
	}

	cout << "Введите кол-во цехов в работе: ";
	while (true)
	{
		checkInput(guildCountInWork);

		if (guildCountInWork < 0)
		{
			cout << "Кол-во цехов в работе должно быть положительным!" << endl;
			continue;
		}

		if (guildCountInWork > guildCount)
		{
			cout << "Кол-во рабочих цехов должно быть меньше общего!" << endl;
		}

		break;
	}

	cout << "Введите коэффициент эффективности КС: ";
	checkInput(efficiency);

	cout << endl << "КС инициализирована!" << endl;
}

void Pipe::printPipe(const Pipe& p)
{
	if (p.kmMark == "null")
	{
		cout << "Данные трубы отсутствуют!" << endl;
	}
	else
	{
		cout << "Километровая отметка (название) трубы: " << p.kmMark << endl;
		cout << "Длина трубы: " << p.length << endl;
		cout << "Диаметр трубы: " << p.diameter << endl;
		cout << "Статус: " << (p.isUnderRepair ? "В ремонте" : "Работает") << endl;
	}

	cout << endl;
}

void CS::printCS(const CS& cs)
{
	if (cs.name == "null")
	{
		cout << "Данные КС отсутствуют!" << endl << endl;

	}
	else
	{
		cout << "Название КС: " << cs.name << endl;
		cout << "Кол-во цехов: " << cs.guildCount << endl;
		cout << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
		cout << "Коэффициент эффективности: " << cs.efficiency << endl;
	}

	cout << endl;
}

void Pipe::redactPipe(Pipe& p)
{
	if (p.kmMark == "null")
	{
		cout << "Ошибка: Данные трубы отсутствуют!" << endl;
		return;
	}

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	checkInput(p.isUnderRepair);

	cout << "Статус изменен!" << endl;
}

void CS::redactCS(CS& cs)
{
	if (cs.name == "null")
	{
		cout << "Ошбика: Данные КС отсутствуют!" << endl;
		return;
	}

	bool increase;

	cout << "Добавить цех - 1, убрать - 0" << endl;

	cout << "Введите номер: ";
	while (true)
	{
		checkInput(increase);

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