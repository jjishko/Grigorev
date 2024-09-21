#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

#include "functions.h"

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

		if (cin.fail() || choice > 7 || choice < 0)
		{
			cout << "Введите корректный номер!" << endl << endl;

			cin.clear();
			flush();
			continue;
		}

		flush();
		system("cls");

		switch (choice)
		{
		case 1:
			addPipe(p);
			break;

		case 2:
			addCS(cs);
			break;

		case 3:
			printObjects(p, cs);
			break;

		case 4:
			redactPipe(p);
			break;

		case 5:
			redactCS(cs);
			break;

		case 6:
			saveObjects(p, cs);
			break;

		case 7:
			loadObjects(p, cs);
			break;

		case 0:
			cout << "До новых встреч!" << endl;
			return 0;
		}

		cout << "Нажмите Enter...";
		flush();
		system("cls");
		printHelp();
	}

	return 0;
}
