#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

#include "functions.h"

#define FLUSH while (cin.get() != '\n');

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

		if (cin.fail())
		{
			cout << "������� ���������� �����!" << endl << endl;

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

			cout << "\n������! ������� ����� �������...";
			FLUSH

			system("cls");
			printHelp();

			break;
		case 2:
			system("cls");
			addCS(cs);

			cout << "\n������! ������� ����� �������...";
			FLUSH

			system("cls");
			printHelp();

			break;
		case 3:
			system("cls");
			printObjects(p, cs);

			cout << "\n\n������! ������� ����� �������...";
			FLUSH

			system("cls");
			printHelp();

			break;
		case 4:
			system("cls");
			redactPipe(p);

			cout << "\n������! ������� ����� �������...";
			FLUSH

			system("cls");
			printHelp();

			break;
		case 5:
			system("cls");
			redactCS(cs);

			cout << "\n������! ������� ����� �������...";
			FLUSH

			system("cls");
			printHelp();

			break;
		case 6:
			break;
		case 7:
			break;
		case 0:
			cout << "�� ����� ������!" << endl;
			return 0;
		default:
			cout << "������� ���������� �����!" << endl << endl;
			break;
		}

	}

	return 0;
}
