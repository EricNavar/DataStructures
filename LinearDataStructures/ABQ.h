#pragma once
#include <iostream>
using namespace std;

template <typename Jeffrey>
class ABQ
{
	//first element is the head and is at index 0. tail is the last index with an element that was enqueued.
	unsigned int head, tail;
	unsigned int size;
	unsigned int capacity;
	Jeffrey * arr;
	float scale_factor = 2.0f;
	void resize(bool grow);
	unsigned int total_resizes = 0;
public:
		/*ABQ() Default constructor.Maximum capacity should
		be set to 1, and current size set to 0;*/
	ABQ();
		/*Constructor for an ABQ with the specified
		 starting maximum capacity.*/
	ABQ(int capacity);
	ABQ(int capacity, float scale_factor);
		//Copy Constructor;
	ABQ(const ABQ &dad);
		//Destructor;
	~ABQ();
		//Assignment operator.
	ABQ & operator=(const ABQ & jack);
	Jeffrey & operator[](unsigned int index);
		//Add a new item to end of the queue and resizes if necessary.
	void enqueue(Jeffrey data);
		/*Remove the item at front of the queue, resizes if necessary,
		and return the value removed.Throws - 1 if the queue is empty.*/
	Jeffrey dequeue();
	
		/*Return the value of the item at the front of the
		queue, without removing it.Throws - 1 if the queue is empty. */
	Jeffrey peek();
		//Returns the current number of items in the ABQ.
	unsigned int getSize();
		//Returns the current max capacity of the ABQ.
	unsigned int getMaxCapacity();
		//Returns the array representing the queue.
	Jeffrey * getData();
	unsigned int getTotalResizes();
};

//Default constructor
template<typename Jeffrey>
inline ABQ<Jeffrey>::ABQ()
{
	head = 0;
	tail = 0;
	size = 0;
	capacity = 1;
	arr = new Jeffrey[capacity];
}

//constructor
template<typename Jeffrey>
inline ABQ<Jeffrey>::ABQ(int capacity)
{
	head = 0;
	tail = 0;
	size = 0;
	arr = new Jeffrey[capacity];
	this->capacity = capacity;
}

template<typename Jeffrey>
inline ABQ<Jeffrey>::ABQ(int capacity, float scale_factor)
{
	head = 0;
	tail = 0;
	size = 0;
	this->capacity = capacity;
	arr = new Jeffrey[capacity];
	this->scale_factor = scale_factor;
	total_resizes++;
}

//copy constructor
template<typename Jeffrey>
inline ABQ<Jeffrey>::ABQ(const ABQ & dad)
{
	head = 0;
	tail = 0;
	arr = new Jeffrey[dad.capacity];
	this->capacity = dad.capacity;
	this->size = dad.size;
	//Copy the array from d into this
	for (unsigned int i = 0; i < capacity; i++)
	{
		this->arr[i] = dad[i];
	}
}

//Destructor
template<typename Jeffrey>
inline ABQ<Jeffrey>::~ABQ()
{
	if (arr != nullptr)
	{
		delete[] arr;
	}
}

//= overload
template <typename Jeffrey>
ABQ<Jeffrey> & ABQ<Jeffrey>::operator=(const ABQ & jack)
{
	arr = new Jeffrey[jack.capacity];
	this->capacity = jack.capacity;
	this->size = jack.size;
	this->head = jack.head;
	this->tail = jack.tail;
	//Copy the array from d into this
	for (unsigned int i = 0; i < capacity; i++)
	{
		this->arr[i] = jack[i];
	}
	return *this;
}

//overload =
template <typename Jeffrey>
Jeffrey & ABQ<Jeffrey>::operator[](unsigned int index)
{
	if (index < head || index > size - 1)
	{
		//I thought that this was more useful than throwing the same
		//number for every single error like zybooks wanted
		//cout << "Error! Invalid index";
		//throw runtime_error("Error! Invalid index");
		throw - 1;
	}
	else
	{
		return arr[index];
	}
}

template<typename Jeffrey>
//if grow is true, the array grows by the scale_factor. If false, it shrinks by the scale factor
void ABQ<Jeffrey>::resize(bool grow)
{
	//capacity = grow ? (int)(capacity * scale_factor) : (int)(capacity / scale_factor);
	if (grow)
	{
		capacity = (int)(capacity * scale_factor);
	}
	else
	{
		capacity = (int)(capacity / scale_factor);
	}
	Jeffrey * newArr = new Jeffrey[capacity];
	//make new array and copy old array into old array.
	for (unsigned int i = 0; i < size; i++)
	{
		newArr[i] = arr[i + head];
	}
	//delete old array
	if (arr != nullptr)
	{
		delete[] arr;
	}
	this->arr = newArr;
	head = 0;
	total_resizes++;
}

template <typename Jeffrey>
void ABQ<Jeffrey>::enqueue(Jeffrey data)
{
	//if there's no more space in the back to put another Jeffrey
	if (size + head == capacity)
	{
		resize(true);
	}
	arr[size] = data;
	tail++;
	size++;
}

/*As items are dequeued, head is incremented and there will be empty elements 
(or really just garbage leftover values) in front of the head*/
template <typename Jeffrey>
Jeffrey ABQ<Jeffrey>::dequeue()
{
	if (size == 0)
	{
		//cout << "dequeue(): size = 0";
		//throw ("dequeue(): size = 0");
		throw - 1;
	}
	Jeffrey result = arr[head];
	size--;
	head++;

	if (size == (unsigned int)((capacity - 1) / scale_factor))
	{
		resize(false);
	}
	return result;
}

//returns the first dude (the guy that would be dequeued)
template <typename Jeffrey>
inline Jeffrey ABQ<Jeffrey>::peek()
{
	if (size == 0)
	{
		//cout << "ABQ peek(): size = 0";
		//throw ("ABQ peek(): size = 0");
		throw - 1;
	}
	return arr[head];
}

template <typename Jeffrey>
unsigned int ABQ<Jeffrey>::getSize()
{
	return this->size;
}

template <typename Jeffrey>
unsigned int ABQ<Jeffrey>::getMaxCapacity()
{
	return capacity;
}

template <typename Jeffrey>
inline Jeffrey * ABQ<Jeffrey>::getData()
{
	return this->arr;
}

//roommate Luke wanted a template named after him so I named this
//one after Luke because like him, this one is present but doesn't help out at all.
template<typename Luke>
inline unsigned int ABQ<Luke>::getTotalResizes()
{
	return total_resizes;
}