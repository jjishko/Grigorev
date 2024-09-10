#include <iostream>
#include <string>

#include "structures.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void help()
{
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
	cout << "Инструкции: " << endl;
	help();

	unsigned short ch;
	
	while (true)
	{
		cout << "Введите нoмер: ";
		cin >> ch;

		if (cin.fail())
		{
			cout << "Введите корректный номер!" << endl << endl;

			cin.clear();
			while (cin.get() != '\n');
			continue;
		}

		switch (ch)
		{
		case 1:
			break;
		case 2:
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
}
