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
	cout << "����������: " << endl;

	cout << "1 - �������� �����" << endl;
	cout << "2 - �������� ��" << endl;
	cout << "3 - �������� ���� ��������" << endl;
	cout << "4 - ������������� �����" << endl;
	cout << "5 - ������������� ��" << endl;
	cout << "6 - ���������" << endl;
	cout << "7 - ���������" << endl;
	cout << "0 - �����" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	cout << "����� ���������� � ������������������� ��-��������!" << endl;
	printHelp();

	unsigned short choice;
	Pipe p;
	CS cs;
	
	while (true)
	{
		cout << "������� �o���: ";
		cin >> choice;

		if (cin.fail() || choice > 7 || choice < 0)
		{
			cout << "������� ���������� �����!" << endl << endl;

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
			cout << "�� ����� ������!" << endl;
			return 0;
		}

		cout << "������� Enter...";
		flush();
		system("cls");
		printHelp();
	}

	return 0;
}
