#include <iostream>
#include <string>

#include "functions.h"

#define FLUSH while (cin.get() != '\n');

using std::string;
using std::cout;
using std::cin;
using std::endl;

void resetInput()
{
	cout << "������� ���������� ��������!" << endl << endl;

	cin.clear();
	FLUSH	
}

void addPipe(Pipe& p)
{
	while (true)
	{
		cout << "������� ������������ ������� (��������): ";
		std::getline(cin, p.kmMark);

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}
	

	while (true)
	{
		cout << "������� ����� �����: ";
		cin >> p.length;

		if (p.length <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}
	

	while (true)
	{
		cout << "������� ������� �����: ";
		cin >> p.diameter;

		if (p.diameter <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}
	

	while (true)
	{
		cout << "����� � �������? (1 - ��, 0 - ���): ";
		cin >> p.isUnderRepair;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}
	
}

void addCS(CS& cs)
{
	while (true)
	{
		cout << "������� �������� ��: ";
		std::getline(cin, cs.name);

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		break;
	}


	while (true)
	{
		cout << "������� ���-�� �����: ";
		cin >> cs.guildCount;

		if (cs.guildCount < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}


	while (true)
	{
		cout << "������� ���-�� ����� � ������: ";
		cin >> cs.guildCountInWork;

		if (cs.guildCountInWork <= 0 || cs.guildCountInWork > cs.guildCount
			|| cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}


	while (true)
	{
		cout << "������� ����������� ������������� ��: ";
		cin >> cs.efficiency;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}

}

void printObjects(Pipe& p, CS& cs)
{
	cout << "������������ ������� (��������) �����: " << p.kmMark << endl;
	cout << "����� �����: " << p.length << endl;
	cout << "������� �����: " << p.diameter << endl;
	cout << "������: " << (p.isUnderRepair ? "� �������" : "��������") << endl;

	cout << endl;

	cout << "�������� ��: " << cs.name << endl;
	cout << "���-�� �����: " << cs.guildCount << endl;
	cout << "���-�� ����� � ������: " << cs.guildCountInWork << endl;
	cout << "����������� �������������: " << cs.efficiency << endl;
}

void redactPipe(Pipe& p)
{
	int choice;

	cout << "1) �������� ��-������� (��������) �����" << endl;
	cout << "2) �������� ����� �����" << endl;
	cout << "3) �������� ������� �����" << endl;
	cout << "4) �������� ������ �����" << endl;


	while (true)
	{
		cout << "������� �����: ";
		cin >> choice;

		if (choice < 1 && choice > 4 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		break;
	}

	cout << endl;

	switch (choice)
	{
	case 1:

		while(true)
		{
			cout << "������� ������������ ������� (��������): ";
			std::getline(cin, p.kmMark);

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			break;
		}

		break;

	case 2:

		while (true)
		{
			cout << "������� ����� �����: ";
			cin >> p.length;

			if (p.length <= 0 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 3:

		while (true)
		{
			cout << "������� ������� �����: ";
			cin >> p.diameter;

			if (p.diameter <= 0 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
				break;
		}

		break;

	case 4:

		while (true)
		{
			cout << "����� � �������? (1 - ��, 0 - ���): ";
			cin >> p.isUnderRepair;

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
				break;
		}
		
		break;
	}
		
}

void redactCS(CS& cs)
{
	int choice;

	cout << "1) �������� �������� ��" << endl;
	cout << "2) �������� ���-�� ����� � ��" << endl;
	cout << "3) �������� ���-�� ����� � ������" << endl;
	cout << "4) �������� ����������� ������������� ��" << endl;


	while (true)
	{
		cout << "������� �����: ";
		cin >> choice;

		if (choice < 1 && choice > 4 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
			break;
	}

	cout << endl;

	switch (choice)
	{
	case 1:

		while (true)
		{
			cout << "������� �������� ��: ";
			std::getline(cin, cs.name);

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			break;
		}


	case 2:

		while (true)
		{
			cout << "������� ���-�� �����: ";
			cin >> cs.guildCount;

			if (cs.guildCount < 1 || cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 3:

		while (true)
		{
			cout << "������� ���-�� ����� � ������: ";
			cin >> cs.guildCountInWork;

			if (cs.guildCountInWork <= 0 || cs.guildCountInWork > cs.guildCount
				|| cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;

	case 4:

		while(true)
		{
			cout << "������� ����������� ������������� ��: ";
			cin >> cs.efficiency;

			if (cin.fail())
			{
				resetInput();
				continue;
			}

			FLUSH
			break;
		}

		break;
	}
	
}
