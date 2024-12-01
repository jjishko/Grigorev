#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <vector>

#include "misc.h"
#include "NGProgram.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::unordered_map;

/*
+ Функции для соединения (создать, вывести, удалить) 
+- Не удалять трубу и кс в газопроводе
+- Изменение статуса трубы
+ Сохранение/загрузка соединения
+ Топологическая сортировка

id 
несколько компонент связности
*/

void printHelp()
{
	cout << "Инструкции: " << endl << endl;

	cout << "1 - Добавить трубу" << endl;
	cout << "2 - Добавить КС" << endl << endl;

	cout << "3 - Действия с трубами" << endl;
	cout << "4 - Действия с КС" << endl << endl;

	cout << "5 - Просмотр всех труб и КС" << endl << endl;

	cout << "6 - Создать соединение (добавить в газопровод)" << endl;
	cout << "7 - Показать весь газопровод" << endl;
	cout << "8 - Удалить соединение" << endl;
	cout << "9 - Топологическая сортировка" << endl << endl;

	cout << "10 - Сохранить" << endl;
	cout << "11 - Загрузить" << endl << endl;

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

	unordered_map<int, CS> mapCS;
	unordered_map<int, Pipe> mapPipe;
	std::vector<Connection> arrConnection;
	
	while (true)
	{
		cout << "Введите нoмер: ";
		checkInput(choice, 0, 11);

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
			addConnection(arrConnection, mapPipe, mapCS);
			break;
		
		case 7:
			printConnection(arrConnection, mapPipe);
			break;

		case 8:
			deleteConnection(arrConnection, mapPipe, mapCS);
			break;

		case 9:
			printConnection(arrConnection, mapPipe);
			topologicalSort(arrConnection);
			break;

		case 10:
			saveObjects(mapPipe, mapCS, arrConnection);
			break;

		case 11:
			loadObjects(mapPipe, mapCS, arrConnection);
			break;

		case 0:
			cout << "До новых встреч!" << endl;
			return 0;
		}

		cout << "Нажмите Enter...";

		cin.ignore(10000, '\n');
		std::cerr << endl;
		system("cls");

		printHelp();
	}

	return 0;
}
