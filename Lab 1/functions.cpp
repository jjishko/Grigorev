#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "functions.h"

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

//ofstream& operator << (ofstream & out, const Pipe & p)
//{
//	out << "Километровая отметка (название) трубы: " << p.kmMark << endl;
//	out << "Длина трубы: " << p.length << endl;
//	out << "Диаметр трубы: " << p.diameter << endl;
//	out << "Статус: " << (p.isUnderRepair ? "В ремонте" : "Работает") << endl;
//
//	return out;
//}

void flush()
{
	cin.ignore(10000, '\n');
}

void resetInput()
{
	cout << "Введите корректное значение!" << endl << endl;

	cin.clear();
	flush();	
}

void addPipe(Pipe& p)
{
	while (true)
	{
		cout << "Введите километровую отметку (название): ";
		std::getline(cin, p.kmMark);

		if (p.kmMark == "")
		{
			cout << "Название обязательно!" << endl << endl;
			continue;
		}

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}
	

	while (true)
	{
		cout << "Введите длину трубы: ";
		cin >> p.length;

		if (p.length <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}
	

	while (true)
	{
		cout << "Введите диаметр трубы: ";
		cin >> p.diameter;

		if (p.diameter < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}
	

	while (true)
	{
		cout << "Труба в ремонте? (1 - да, 0 - нет): ";
		cin >> p.isUnderRepair;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}

	cout << endl << "Труба инициализирована!" << endl;
	
}

void addCS(CS& cs)
{
	while (true)
	{
		cout << "Введите название КС: ";
		std::getline(cin, cs.name);

		if (cs.name == "")
		{
			cout << "Название обязательно!" << endl << endl;
			continue;
		}

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}


	while (true)
	{
		cout << "Введите кол-во цехов: ";
		cin >> cs.guildCount;

		if (cs.guildCount < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}


	while (true)
	{
		cout << "Введите кол-во цехов в работе: ";
		cin >> cs.guildCountInWork;

		if (cs.guildCountInWork <= 0 || cs.guildCountInWork > cs.guildCount
			|| cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}


	while (true)
	{
		cout << "Введите коэффициент эффективности КС: ";
		cin >> cs.efficiency;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		flush();
		break;
	}

	cout << endl << "КС инициализирована!" << endl;
}

void printObjects(const Pipe& p, const CS& cs)
{
	if (p.kmMark == "")
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

	if (cs.name == "")
	{
		cout << "Данные КС отсутствуют!" << endl << endl;

	}
	else
	{
		cout << "Название КС: " << cs.name << endl;
		cout << "Кол-во цехов: " << cs.guildCount << endl;
		cout << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
		cout << "Коэффициент эффективности: " << cs.efficiency << endl << endl;
	}
	
	cout << "Готово!" << endl;

}

void redactPipe(Pipe& p)
{
	if (p.kmMark == "")
	{
		cout << "Ошибка: Данные трубы отсутствуют!" << endl;
		return;
	}

	cout << "Труба в ремонте? (1 - да, 0 - нет): ";
	cin >> p.isUnderRepair;

	if (cin.fail())
	{
		resetInput();
	}

	flush();	

	cout << "Статус изменен!" << endl;

}

void redactCS(CS& cs)
{
	if (cs.name == "")
	{
		cout << "Ошбика: Данные КС отсутствуют!" << endl;
		return;
	}

	int increase;

	cout << "Добавить цех - 1, убрать - 0" << endl;

	while (true)
	{
		cout << "Введите номер: ";
		cin >> increase;

		if (increase < 0 || increase > 1 || cin.fail())
		{
			resetInput();
		}

		flush();

		if (increase)
		{
			if (cs.guildCount == cs.guildCountInWork)
			{
				cout << "Ошибка: Кол-во рабочих цехов превышено!" << endl;
				return;
			}

			++cs.guildCountInWork;
		}
		else
		{
			if (cs.guildCountInWork == 0)
			{
				cout << "Ошибка: Кол-во рабочих цехов равно нулю!" << endl;
				return;
			}

			--cs.guildCountInWork;
		}

		break;
	}
	
	cout << "Готово!" << endl;
}

void saveObject(const Pipe& p, const CS& cs)
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

void loadObject(Pipe& p, CS& cs)
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