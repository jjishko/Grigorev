#include <iostream>
#include <string>

#include "structures.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void help()
{
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
	cout << "����������: " << endl;
	help();

	unsigned short ch;
	
	while (true)
	{
		cout << "������� �o���: ";
		cin >> ch;

		if (cin.fail())
		{
			cout << "������� ���������� �����!" << endl << endl;

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
			cout << "�� ����� ������!";
			return 0;
		default:
			cout << "������� ���������� �����!" << endl << endl;
			break;
		}

	}
}
