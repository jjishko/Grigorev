#include <iostream>
#include <string>
#include <limits>

#include "functions.h"

#define FLUSH cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//while (cin.get() != '\n');


using std::string;
using std::cout;
using std::cin;
using std::endl;

void printHelp()
{
	cout << "Инструкции: " << endl;

	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить КС" << endl;
	cout << "3 - Просмотр всех объектов" << endl;
	cout << "4 - Редактировать трубу" << endl;
	cout << "5 - Редактировать КС" << endl;
	cout << "6 - Сохранить" << endl;
	cout << "7 - Загрузить" << endl;
	cout << "0 - Выход" << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Добро пожаловать в высокотехнологичный НГ-менеджер!" << endl;
	printHelp();

	unsigned short choice;
	Pipe p;
	CS cs;
	
	while (true)
	{
		cout << "Введите нoмер: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "Введите корректный номер!" << endl << endl;

			cin.clear();
			FLUSH
			continue;
		}

		FLUSH
		switch (choice)
		{
		case 1:
			system("cls");
			addPipe(p);

			cout << "\nГотово! Нажмите Enter...";
			cin.get();
			FLUSH

			system("cls");
			printHelp();

			break;
		case 2:
			system("cls");
			addCS(cs);

			cout << "\nГотово! Нажмите Enter...";
			cin.get();
			FLUSH

			system("cls");
			printHelp();

			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 0:
			cout << "До новых встреч!";
			return 0;
		default:
			cout << "Введите корректный номер!" << endl << endl;
			break;
		}

	}

	return 0;
}
