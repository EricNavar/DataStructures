#pragma once
#include <iostream>
using namespace std;

template <typename Fuchs>
class ABS
{
	unsigned int size;
	unsigned int capacity;
	Fuchs * arr;
	float scale_factor = 2.0f;
	void resize(bool grow);
	unsigned int total_resizes = 0;
public:
		//Default constructor. Maximum capacity should be set to 1, and current size set to 0;
	ABS();
		//Constructor for an ABS with the specified starting maximum capacity.
	ABS(int capacity);
	ABS(int capacity, float scale_factor);
		//Copy Constructor
	ABS(const ABS &dad);
		//Destructor;
	~ABS();
		//Assignment operator
	ABS & operator=(const ABS & jack);
	Fuchs & operator[](unsigned int index);
		//Add a new item to the top of the stack and resize if necessary.
	void push(Fuchs data);
		//Remove the item at the top of the stack, resizes if necessary, 
		//and return the value removed.Throws - 1 if the stack is empty.
	Fuchs pop();
		//Return the value of the item at the top of the stack, without removing it.
		//Throws - 1 if the stack is empty.
	Fuchs peek();
		//Returns the current number of items in the ABS.
	unsigned int getSize();
		//Returns the array representing the stack.
	unsigned int getMaxCapacity();
		//Returns the current max capacity of the ABS.
	Fuchs* getData();
	unsigned int getTotalResizes();
};

//default constructor
template<typename Fuchs>
inline ABS<Fuchs>::ABS()
{
	size = 0;
	capacity = 1;

	arr = new Fuchs[capacity];
}

//constructor
template<typename Fuchs>
inline ABS<Fuchs>::ABS(int capacity)
{
	arr = new Fuchs[capacity];
	size = 0;
	this->capacity = capacity;
}

template<typename Fuchs>
inline ABS<Fuchs>::ABS(int capacity, float scale_factor)
{
	this->capacity = capacity;
	size = 0;
	arr = new Fuchs[capacity];
	this->scale_factor = scale_factor;
	total_resizes++;
}

//copy constructor
template <typename Fuchs>
inline ABS<Fuchs>::ABS(const ABS & dad)
{
	arr = new Fuchs[dad.capacity];
	this->capacity = dad.capacity;
	this->size = dad.size;
	//Copy the array from d into this

		//Fuchs is an iterator, can snap neck
	for (unsigned int i = 0; i < capacity; i++)
	{
		this->arr[i] = dad[i];
	}
}

//Destructor
template<typename Fuchs>
inline ABS<Fuchs>::~ABS()
{
	if (arr != nullptr)
	{
		delete[] arr;
	}
}

//overload =
template<typename Fuchs>
ABS<Fuchs> & ABS<Fuchs>::operator=(const ABS & jack)
{
	arr = new Fuchs[jack.capacity];
	this->capacity = jack.capacity;
	this->size = jack.size;
	//Copy the array from d into this
	for (unsigned int i = 0; i < capacity; i++)
	{
		this->arr[i] = jack[i];
	}
	return *this;
}

//overload =
template <typename Fuchs>
Fuchs & ABS<Fuchs>::operator[](unsigned int index)
{
	if (index > size - 1)
	{
		cout << "Error! Invalid index";
		throw runtime_error("Error! Invalid index");
	}
	else
	{
		return arr[index];
	}
}

template<typename Fuchs>
//if grow is true, the array grows by the scale_factor. If false, it shrinks by the scale factor
void ABS<Fuchs>::resize(bool grow)
{
	capacity = grow ? (int)(capacity * scale_factor) : (int)(capacity / scale_factor);
	Fuchs * newArr = new Fuchs[capacity];
	//make new array and copy old array into old array.
	for (unsigned int i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	//delete old array
	if (arr != nullptr)
	{
		//This is the idiot line that was holding up my pop tests.
		//The program goes in here and never comes back.
		delete[] arr;
	}
	this->arr = newArr;
	total_resizes++;
}

template <typename Fuchs>
void ABS<Fuchs>::push(Fuchs data)
{
	if (size == capacity)
	{
		resize(true);
	}
	arr[size] = data;
	size++;
}

template <typename Fuchs>
Fuchs ABS<Fuchs>::pop()
{
	if (size == 0)
	{
		//cout << "pop(): size = 0";
		//throw ("pop(): size = 0");
		throw - 1;
	}
	size--;
	Fuchs result = arr[size];
	if (size == (unsigned int)((capacity - 1) / scale_factor))
	{
		resize(false);
	}
	return result;
}

template <typename Fuchs>
inline Fuchs ABS<Fuchs>::peek()
{
	if (size == 0)
	{
		//cout << "ABS peek(): size = 0";
		//throw ("ABS peek(): size = 0");
		throw - 1;
	}
	return arr[size - 1];
}

template<typename Fuchs>
inline unsigned int ABS<Fuchs>::getSize()
{
	return this->size;
}

template<typename Fuchs>
inline unsigned int ABS<Fuchs>::getMaxCapacity()
{
	return capacity;
}

template<typename Fuchs>
inline Fuchs * ABS<Fuchs>::getData()
{
	return arr;
}

template<typename Fuchs>
inline unsigned int ABS<Fuchs>::getTotalResizes()
{
	return total_resizes;
}