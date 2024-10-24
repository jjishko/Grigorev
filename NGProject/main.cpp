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
�������
���� (bool, ��� ������ (noskipws)?)
*/

void printHelp()
{
	cout << "����������: " << endl;

	cout << "1 - �������� �����" << endl;
	cout << "2 - �������� ��" << endl;
	cout << "3 - ������������� �����" << endl;
	cout << "4 - ������������� ��" << endl;
	cout << "5 - �������� ���� ��������" << endl;
	cout << "6 - ������� �����" << endl;
	cout << "7 - ������� ��" << endl;
	cout << "8 - ���������" << endl;
	cout << "9 - ���������" << endl;
	cout << "0 - �����" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	RedirectOutputWrapper cerrOut(std::cerr);
	string time = std::format("{:%d_%m_%Y_%H_%M_%OS}", std::chrono::system_clock::now());
	std::ofstream logfile("logs\\log_" + time + ".txt");

	if (logfile)
		cerrOut.redirect(logfile);

	cout << "����� ���������� � ������������������� ��-��������!" << endl;
	printHelp();

	int choice;

	unordered_map<int, Pipe> mapPipe;
	unordered_map<int, CS> mapCS;
	std::unordered_set<int> set;

	while (true)
	{
		cout << "������� �o���: ";
		checkInput(choice, 0, 9);

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
			batchRedacting(mapPipe, editPipes);
			break;

		case 4:
			batchRedacting(mapCS, editCS);
			break;

		case 5:
			printObjects(mapPipe, mapCS);
			break;

		case 6:
			batchRedacting(mapPipe, deletePipes);
			break;

		case 7:
			batchRedacting(mapCS, deleteCS);
			break;

		case 8:
			saveObjects(mapPipe, mapCS);
			break;

		case 9:
			loadObjects(mapPipe, mapCS);
			break;

		case 0:
			cout << "�� ����� ������!" << endl;
			return 0;
		}

		cout << "������� Enter...";
		cin.get();
		cin.ignore(10000, '\n');
		std::cerr << endl;
		system("cls");

		printHelp();
	}

	return 0;
}
