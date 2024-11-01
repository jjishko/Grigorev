#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

#include "misc.h"
#include "NGProgram.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::unordered_map;

/*
Фильтры
*/

void printHelp()
{
	cout << "Инструкции: " << endl;

	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить КС" << endl;
	cout << "3 - Действия с трубами" << endl;
	cout << "4 - Действия с КС" << endl;
	cout << "5 - Просмотр всех объектов" << endl;
	cout << "6 - Сохранить" << endl;
	cout << "7 - Загрузить" << endl;
	cout << "0 - Выход" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	RedirectOutputWrapper cerrOut(std::cerr);
	string time = std::format("{:%d_%m_%Y_%H_%M_%OS}", std::chrono::system_clock::now());
	std::ofstream logfile("logs\\log_" + time + ".txt");

	if (logfile)
		cerrOut.redirect(logfile);

	cout << "Добро пожаловать в высокотехнологичный НГ-менеджер!" << endl;
	printHelp();

	int choice;

	unordered_map<int, Pipe> mapPipe;
	unordered_map<int, CS> mapCS;
	std::unordered_set<int> set;
	
	while (true)
	{
		cout << "Введите нoмер: ";
		checkInput(choice, 0, 7);

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
			chooseAction(mapPipe);
			break;

		case 4:
			chooseAction(mapCS);
			break;

		case 5:
			printAll(mapPipe, mapCS);
			break;

		case 6:
			saveObjects(mapPipe, mapCS);
			break;

		case 7:
			loadObjects(mapPipe, mapCS);
			break;

		case 0:
			cout << "До новых встреч!" << endl;
			return 0;
		}

		cout << "Нажмите Enter...";
 
		if (cin.rdbuf()->in_avail())
		{
			cin.get();
		}

		cin.ignore(10000, '\n');
		std::cerr << endl;
		system("cls");

		printHelp();
	}

	return 0;
}
