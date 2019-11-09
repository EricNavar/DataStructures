#define GET_VARIABLE_NAME(Variable) (#Variable)
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
using namespace std;

class TestClass
{
public:
	void printNumber(int a);
	int tripleNumber(int a);
};


template <typename T>
class TemplateClass
{
public:
	void printT(T a);
};

template <typename T>
void TemplateClass<T>::printT(T a)
{
	cout << a << endl;
}

void TestClass::printNumber(int a)
{
	cout << a << endl;
}

int TestClass::tripleNumber(int n)
{
	return n * 3;
}

int doubleNumber(int n)
{
	return n * 2;
}

template <typename T>
void do_something(T val, function<void(T)> p)
{
	cout << "Invoking the function\n";
	p(val);
	cout << "Function invoked\n";
}

void tester(int a, int b, int(*adder)(int, int))
{
	cout << adder(a, b) << endl;
}

void tester2(vector<int> v, int(*adder)(vector<int>))
{
	cout << adder(v) << endl;
}

void tester3(int a, TestClass t, void(TestClass::* printer)(int))
{
	//t.*printer(a);
}

int add(int a, int b) { return a + b; }

int addVector(vector<int> v)
{
	int sum = 0;
	for (int i : v)
		sum += i;
	return sum;
}

//for free functions
template<typename R, typename P>
void timeFunction(P p, R(test)(P p))
{
	const clock_t start = clock();
	test(p);
	const clock_t finish = clock();
	cout << GET_VARIABLE_NAME(user_test) << " took " << finish - start << " milliseconds.\n";
}

//for member methods
template<typename R, typename P, typename C>
void timeFunction(C c, P p, R(C:: * test)(P p))
{
	const clock_t start = clock();
	(c.*test)(p);
	const clock_t finish = clock();
	cout << GET_VARIABLE_NAME(user_test) << " took " << finish - start << " milliseconds.\n";
}

int main(int argc, char* argv[]) {

	//free functions
	int(*ptr)(int, int) = add;
	int(*ptr2)(vector<int>) = addVector;
	vector<int> v = { 1,2,3,4,5 };
	tester(2, 3, ptr);
	tester(2, 3, add);
	tester2(v, ptr2);
	tester2(v, addVector);

	timeFunction(2, doubleNumber);
	timeFunction<int, int>(2, doubleNumber);

	//using class methods
	TestClass t;
	void (TestClass:: * ptr3)(int) = &TestClass::printNumber;
	(t.*ptr3)(100);
	(t.* & TestClass::printNumber)(100);

	//lambdas
	auto lambda = []() { cout << "Hello World!"; };
	do_something<int>(5, [](int val) { cout << val << "\n"; });

	//class method pointers
	
	
	int (TestClass:: * ptr4)(int) = &TestClass::tripleNumber;
	timeFunction(t, 2, ptr4);

	//template class method pointers
	cout << "template classes" << endl;
	void (TemplateClass<int>:: * ptr5)(int) = &TemplateClass<int>::printT;
	//timeFunction(2, ptr5);

	return 0;
}