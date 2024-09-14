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

			cout << "\n������! ������� Enter...";
			cin.get();
			FLUSH

			system("cls");
			printHelp();

			break;
		case 2:
			system("cls");
			addCS(cs);

			cout << "\n������! ������� Enter...";
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
			cout << "�� ����� ������!";
			return 0;
		default:
			cout << "������� ���������� �����!" << endl << endl;
			break;
		}

	}

	return 0;
}
