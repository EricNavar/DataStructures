#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	ostream os(cout.rdbuf());
	os << "Test sentence\n";

	filebuf fb;
	fb.open("test.txt", std::ios::out);
	std::ostream os(&fb);
	os << "Test sentence\n";
	fb.close();
	return 0;
}