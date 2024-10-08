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
��������� �������� (����������, ��������, ��������������)
�������
����������� � checkInput
*/

void printHelp()
{
	cout << "����������: " << endl;

	cout << "1 - �������� �����" << endl;
	cout << "2 - �������� ��" << endl;
	cout << "3 - ������� �����" << endl;
	cout << "4 - ������� ��" << endl;
	cout << "5 - �������� ���� ��������" << endl;
	cout << "6 - ������������� �����" << endl;
	cout << "7 - ������������� ��" << endl;
	cout << "8 - ���������" << endl;
	cout << "9 - ���������" << endl;
	cout << "0 - �����" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	cout << "����� ���������� � ������������������� ��-��������!" << endl;
	printHelp();

	int choice;

	unordered_map<int, Pipe> mapPipe;
	unordered_map<int, CS> mapCS;

	while (true)
	{
		cout << "������� �o���: ";
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
			cout << "�� ����� ������!" << endl;
			return 0;
		}

		cout << "������� Enter...";
		cin.ignore(10000, '\n');
		system("cls");

		printHelp();
	}

	return 0;
}
