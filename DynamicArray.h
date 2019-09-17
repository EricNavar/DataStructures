#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class DynamicArray
{
	unsigned int capacity;
	unsigned int size;
	T * arr;
public:
	/*==Accessors==*/
	unsigned int GetCapacity() const;
	unsigned int GetSize() const;
	const T * GetData() const;

	//return a specific element from the internal array
	const T & operator[](unsigned int index) const;
	T & operator[](unsigned int index);

	//Just like the brackets operator
	const T &At(unsigned int index) const;
	T &At(unsigned int index);

	/*==Mutators==*/
	//Add an item onto the end of an array if there is room
	//If not, the array will have to be resized to make space for one more
	void Add(const T &data);
	void Resize(unsigned int newSize);
	//removes an element from the array and resizes it to fill the gap
	void Remove(unsigned int index);

	/*==Trilogy of Evil==*/
	DynamicArray();
	DynamicArray(int size);
	~DynamicArray();
	DynamicArray(const DynamicArray &d);
	DynamicArray operator=(const DynamicArray &d);
};

template<typename T>
unsigned int DynamicArray<T>::GetCapacity() const
{
	return this->capacity;
}

template<typename T>
unsigned int DynamicArray<T>::GetSize() const
{
	return this->size;
}

template<typename T>
const T * DynamicArray<T>::GetData() const
{
	return this->arr;
}

template<typename T>
void DynamicArray<T>::Add(const T & data)
{
	if (size < capacity)
	{
		arr[size] = data;
		size++;
	}
	else
	{
		//resizes to increase capacity by one, then add element
		Resize(this->size + 1);
		arr[this->capacity - 1] = data;
	}
}

template<typename T>
//cuts off the last elements if shrinking.
void DynamicArray<T>::Resize(unsigned int newSize)
{
	if (newSize < 0)
		throw runtime_error("Error! Invalid size");
	cout << "Resizing... old capacity: " << this->capacity << " New capacity: " << newSize << endl;
	//make new array and copy old array into old array.
	T * newArr = new T[newSize];
	for (unsigned int i = 0; i < newSize && i < capacity; i++)
		newArr[i] = arr[i];
	//delete olf array
	if (arr != nullptr)
	{
		delete[] arr;
	}
	arr = newArr;
	capacity = newSize;
	size = newSize;
}

template<typename T>
void DynamicArray<T>::Remove(unsigned int index)
{
	if (index > capacity - 1 || index < 0 || size == 0)
	{
		throw runtime_error("Error! Invalid index");
	}
	else
	{
		//Go to the element that you want to get rid of and move all the elements after that back one. 
		for (unsigned int i = index + 1; i < this->capacity; i++)
			arr[i - 1] = arr[i];
		size--;
	}
}

//default constructor
template<typename T>
DynamicArray<T>::DynamicArray()
{
	this->capacity = 0;
	this->size = 0;
	this->arr = nullptr;
}

//constructor
template<typename T>
DynamicArray<T>::DynamicArray(int capacity)
{
	this->capacity = capacity;
	this->size = 0;
	this->arr = new T[capacity];
}

//Destructor
template<typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] arr;
	arr = nullptr;
}

//copy constructor
template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> & d)
{
	arr = new T[d.capacity];
	this->capacity = d.capacity;
	this->size = d.size;
	//Copy the array from d into this
	for (unsigned int i = 0; i < capacity; i++)
		this->arr[i] = d[i];
}

//operator=
template<typename T>
DynamicArray<T> DynamicArray<T>::operator=(const DynamicArray<T> & d)
{
	this->capacity = d.capacity;
	this->size = d.size;
	arr = new T[capacity];
	//Copy the array from d into this
	for (unsigned int i = 0; i < capacity; i++)
		At(i) = d[i];
	return *this;
}

template<typename T>
T & DynamicArray<T>::operator[](unsigned int index)
{
	if (index > capacity - 1)
		throw runtime_error("Error! Invalid index");
	else
		return arr[index];
}

template<typename T>
const T & DynamicArray<T>::operator[](unsigned int index) const
{	
	if (index > capacity - 1)
		throw runtime_error("Error! Invalid index");
	else
		return arr[index];
}

template<typename T>
const T & DynamicArray<T>::At(unsigned int index) const
{
	if (index > capacity - 1)
		throw runtime_error("Error! Invalid index");
	else
		return arr[index];
}

template<typename T>
T & DynamicArray<T>::At(unsigned int index)
{
	if (index > capacity - 1)
		throw runtime_error("Error! Invalid index");
	else
		return arr[index];
}