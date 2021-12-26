#include <iostream>
#include <string>
#include <vector>
using namespace std;

void testFunction(int *&index);

int main()
{
	int foo[12];
	int* index = foo;
	testFunction(index);
	testFunction(index);
	for (int i : foo)
		cout << i << " ";
	return 0;
}

void testFunction(int *&index)
{
	index[0] = 1;
	index[1] = 2;
	index[2] = 3;
	index += 3;
}