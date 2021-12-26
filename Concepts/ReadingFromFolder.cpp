#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream infile;
	infile.open("input/input.txt");
	if (!infile.is_open())
		cout << "file is not open!" << endl;
	string line;
	while (getline(infile, line))
		cout << line << endl;
	return 0;
}