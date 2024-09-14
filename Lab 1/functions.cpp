#include <iostream>
#include <string>

#include "functions.h"

#define FLUSH cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

using std::string;
using std::cout;
using std::cin;
using std::endl;

void resetInput()
{
	cout << "Введите корректное значение!" << endl << endl;

	cin.clear();
	FLUSH	
}

int addPipe(Pipe& p)
{
	string kmMarkInp;
	float lengthInp, diameterInp;
	bool isUnderRepairInp;
	
	while (true)
	{
		cout << "Введите километровую отметку (название): ";
		std::getline(cin, kmMarkInp);

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		p.kmMark = kmMarkInp;
		break;
	}
	

	while (true)
	{
		cout << "Введите длину трубы: ";
		cin >> lengthInp;

		if (lengthInp <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		p.length = lengthInp;
		break;
	}
	

	while (true)
	{
		cout << "Введите диаметр трубы: ";
		cin >> diameterInp;

		if (diameterInp <= 0 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		p.diameter = diameterInp;
		break;
	}
	

	while (true)
	{
		cout << "Труба в ремонте? (1 - да, 0 - нет): ";
		cin >> isUnderRepairInp;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		p.isUnderRepair = isUnderRepairInp;
		break;
	}
	
	return 0;
}

int addCS(CS& cs)
{
	string nameInp;
	int guildCountInp, guildCountInWorkInp;
	float efficiencyInp;

	while (true)
	{
		cout << "Введите название КС: ";
		std::getline(cin, nameInp);

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		cs.name = nameInp;
		break;
	}


	while (true)
	{
		cout << "Введите кол-во цехов: ";
		cin >> guildCountInp;

		if (guildCountInp < 1 || cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		cs.guildCount = guildCountInp;
		break;
	}


	while (true)
	{
		cout << "Введите кол-во цехов в работе: ";
		cin >> guildCountInWorkInp;

		if (guildCountInWorkInp <= 0 || guildCountInWorkInp > cs.guildCount
			|| cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		cs.guildCountInWork = guildCountInWorkInp;
		break;
	}


	while (true)
	{
		cout << "Введите коэффициент эффективности КС: ";
		cin >> efficiencyInp;

		if (cin.fail())
		{
			resetInput();
			continue;
		}

		FLUSH
		cs.efficiency = efficiencyInp;
		break;
	}

	return 0;
}
