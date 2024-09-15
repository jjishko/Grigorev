#include <iostream>
#include <string>
#include <fstream>

#include "functions.h"

#define FLUSH while (cin.get() != '\n');

using std::string;
using std::cout;
using std::cin;
using std::endl;

void resetInput()
{
	cout << "Введите корректное значение!" << endl << endl;

	cin.clear();
	FLUSH	
}

void addPipe(Pipe& p)
{
	while (true)
	{
		cout << "Введите километровую отметку (название): ";
		std::getline(cin, p.kmMark);

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

		FLUSH
		break;
	}
	

	while (true)
	{
		cout << "Введите диаметр трубы: ";
		cin >> p.diameter;

		if (p.diameter <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
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

		FLUSH
		break;
	}
	
}

void addCS(CS& cs)
{
	while (true)
	{
		cout << "Введите название КС: ";
		std::getline(cin, cs.name);

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

		FLUSH
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

		FLUSH
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

		FLUSH
		break;
	}

}

void printObjects(Pipe& p, CS& cs)
{
	cout << "Километровая отметка (название) трубы: " << p.kmMark << endl;
	cout << "Длина трубы: " << p.length << endl;
	cout << "Диаметр трубы: " << p.diameter << endl;
	cout << "Статус: " << (p.isUnderRepair ? "В ремонте" : "Работает") << endl;

	cout << endl;

	cout << "Название КС: " << cs.name << endl;
	cout << "Кол-во цехов: " << cs.guildCount << endl;
	cout << "Кол-во цехов в работе: " << cs.guildCountInWork << endl;
	cout << "Коэффициент эффективности: " << cs.efficiency << endl;
}

void redactPipe(Pipe& p)
{
	int choice;

	cout << "1) Изменить км-отметку (название) трубы" << endl;
	cout << "2) Изменить длину трубы" << endl;
	cout << "3) Изменить диаметр трубы" << endl;
	cout << "4) Изменить статус трубы" << endl;


	while (true)
	{
		cout << "Введите цифру: ";
		cin >> choice;

		if (choice < 1 && choice > 4 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}

	cout << endl;

	switch (choice)
	{
	case 1:

		while(true)
		{
			cout << "Введите километровую отметку (название): ";
			std::getline(cin, p.kmMark);

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			break;
		}

		break;

	case 2:

		while (true)
		{
			cout << "Введите длину трубы: ";
			cin >> p.length;

			if (p.length <= 0 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 3:

		while (true)
		{
			cout << "Введите диаметр трубы: ";
			cin >> p.diameter;

			if (p.diameter <= 0 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
				break;
		}

		break;

	case 4:

		while (true)
		{
			cout << "Труба в ремонте? (1 - да, 0 - нет): ";
			cin >> p.isUnderRepair;

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
				break;
		}
		
		break;
	}
		
}

void redactCS(CS& cs)
{
	int choice;

	cout << "1) Изменить название КС" << endl;
	cout << "2) Изменить кол-во цехов в КС" << endl;
	cout << "3) Изменить кол-во цехов в работе" << endl;
	cout << "4) Изменить коэффициент эффективности КС" << endl;


	while (true)
	{
		cout << "Введите цифру: ";
		cin >> choice;

		if (choice < 1 && choice > 4 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
			break;
	}

	cout << endl;

	switch (choice)
	{
	case 1:

		while (true)
		{
			cout << "Введите название КС: ";
			std::getline(cin, cs.name);

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			break;
		}


	case 2:

		while (true)
		{
			cout << "Введите кол-во цехов: ";
			cin >> cs.guildCount;

			if (cs.guildCount < 1 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 3:

		while (true)
		{
			cout << "Введите кол-во цехов в работе ";
			cout << "(всего цехов - " << cs.guildCount << "): ";
			cin >> cs.guildCountInWork;

			if (cs.guildCountInWork <= 0 || cs.guildCountInWork > cs.guildCount
				|| cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 4:

		while(true)
		{
			cout << "Введите коэффициент эффективности КС: ";
			cin >> cs.efficiency;

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;
	}
	
}

void saveObjects(Pipe& p, CS& cs)
{
	std::ofstream f("data.txt");

	if (!f.is_open())
	{
		cout << "Ошибка: файл для сохранения не найден!" << endl;
		return;
	}

	f << p.kmMark << endl;
	f << p.length << " ";
	f << p.diameter << " ";
	f << p.isUnderRepair << endl;

	f << cs.name << endl;
	f << cs.guildCount << " ";
	f << cs.guildCountInWork << " ";
	f << cs.efficiency;

	f.close();

	cout << "Данные сохранены! ";
}

void loadObjects(Pipe& p, CS& cs)
{
	std::ifstream f("data.txt");
	
	if (!f.is_open())
	{
		cout << "Ошибка: файл для сохранения не найден!" << endl;
		return;
	}

	std::getline(f, p.kmMark);
	f >> p.length >> p.diameter >> p.isUnderRepair;

	if (f.fail())
	{
		cout << "Ошибка: некорректное считывание из файла!" << endl;
		return;
	}

	f.get();

	std::getline(f, cs.name);
	f >> cs.guildCount >> cs.guildCountInWork 
		>> cs.efficiency;

	if (f.fail())
	{
		cout << "Ошибка: некорректное считывание из файла!" << endl;
		return;
	}

	f.close();

	cout << "Данные загружены! ";

}
