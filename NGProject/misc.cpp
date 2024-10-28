#include <iostream>
#include <string>

#include "misc.h"

using std::string;
using std::cin;
using std::endl;

void inputLine(string& str, std::istream& in)
{
	std::getline(in, str);
	std::cerr << str << endl;
}