#include <iostream>
#include <string>
#include <limits>
#include <conio.h>
#include <vector>
#include <unordered_map>

#include "NGProgram.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::unordered_map;


/*
Несколько объектов (Добавление, удаление, редактирование)
Фильтры
Ограничения в checkInput
*/

void printHelp()
{
	cout << "Инструкции: " << endl;

	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить КС" << endl;
	cout << "3 - Удалить трубу" << endl;
	cout << "4 - Удалить КС" << endl;
	cout << "5 - Просмотр всех объектов" << endl;
	cout << "6 - Редактировать трубу" << endl;
	cout << "7 - Редактировать КС" << endl;
	cout << "8 - Сохранить" << endl;
	cout << "9 - Загрузить" << endl;
	cout << "0 - Выход" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Добро пожаловать в высокотехнологичный НГ-менеджер!" << endl;
	printHelp();

	int choice;

	unordered_map<int, Pipe> mapPipe;
	unordered_map<int, CS> mapCS;

	while (true)
	{
		cout << "Введите нoмер: ";
		checkInput(choice, -1, 10);

		system("cls");

		switch (choice)
		{
		case 1:
			addPipe(mapPipe);
			break;

		case 2:
			addCS(mapCS);
			break;

		case 3:

			break;

		case 4:
			break;

		case 5:
			printObjects(mapPipe, mapCS);
			break;

		case 6:
			//redactPipe(p);
			break;

		case 7:
			//redactCS(cs);
			break;

		case 8:
			//saveObjects(p, cs);
			break;

		case 9:
			//loadObjects(p, cs);
			break;

		case 0:
			cout << "До новых встреч!" << endl;
			return 0;
		}

		cout << "Нажмите Enter...";
		cin.ignore(10000, '\n');
		system("cls");

		printHelp();
	}

	return 0;
}
