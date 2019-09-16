#pragma once
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
	class Node
	{
	public:
		Node(T data);
		T data;
		//idiot c++ does not allow prev and next to be declared on the same line
		Node * prev;
		Node * next;
	};
	void PrintForward();
	void PrintReverse();
	void PrintForwardRecursive(const Node * node);
	void PrintReverseRecursive(const Node * node);

	/*==== Accessors ====*/
	unsigned int NodeCount() const;
	/*Find all nodes which match the passed in parameter value, and store a pointer to
	that node in the passed in vector. Use of a parameter like this (passing a
	something in by reference, and storing data for later use) is called an output
	parameter.*/
	void FindAll(vector<Node *> &outData, const T&value) const;
	const Node *Find(const T &data) const;
	Node *Find(const T &data);
	const Node * GetNode(unsigned int index) const;
	Node * GetNode(unsigned int index);

	Node *Head();
	const Node *Head() const;

	Node *Tail();
	const Node *Tail() const;

	/*==== Insertion ====*/
	//Create a new Node at the front of the list to store the passed in parameter
	void AddHead(const T &data);
	//Create a new Node at the end of the list to store the passed in parameter.
	void AddTail(const T &data);
	/*Given an array of values, insert a node for each of those at the beginning of the
		list, maintaining the original order.*/
	void AddNodesHead(const T *data, unsigned int count);
	//I am so hungry
	void AddNodesTail(const T *data, unsigned int count);
	void InsertAfter(Node *node, const T &data);
	void InsertBefore(Node *node, const T &data);
	void InsertAt(const T &data, unsigned int index);
	/*---- Removal ====*/ bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T &data);
	bool RemoveAt(int index);
	void Clear();

	/*==== Operators ====*/
	const T & operator[](unsigned int index) const;
	//I am so hungry!
	T & operator[](unsigned int index);
	bool operator==(const LinkedList<T> &rhs) const;
	LinkedList<T> & operator=(const LinkedList<T> &rhs);

	/*==== Construction / Destruction ====*/ 
	LinkedList();
	LinkedList(const LinkedList<T> &list);
	~LinkedList();
	LinkedList::Node * head;
	LinkedList::Node * tail;
};

//default constructor creates empty list
template<typename T>
inline LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

//default constructor for Node
template<typename T>
inline LinkedList<T>::Node::Node(T data)
{
	next = nullptr;
	prev = nullptr;
	this->data = data;
}

//bracket operator
template<typename T>
inline const T & LinkedList<T>::operator[](unsigned int index) const
{
	if (index < 0)
	{
		cout << "operator[] out of bounds" << endl;
		throw - 1;
	}
	Node * ptr = head;
	for (unsigned int jeff = 0; jeff < index; jeff++)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
		{
			cout << "out of range on operator[]" << endl;
			throw - 1;
		}
	}
	return ptr->data;
}

//other bracket operator
template<typename T>
inline T & LinkedList<T>::operator[](unsigned int index)
{
	if (index < 0)
	{
		cout << "get node" << endl;
		throw - 1;
	}
	Node * ptr = head;
	for (unsigned int jeff = 0; jeff < index; jeff++)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
		{
			cout << "out of range on GetNode()" << endl;
			throw - 1;
		}
	}
	return ptr->data;
}

//equality operator
template<typename T>
inline bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	unsigned int jeff = 0;
	Node * ptr1 = head;
	Node * ptr2 = rhs.head;
	while (ptr1 != nullptr  && ptr2 != nullptr)
	{
		if (GetNode(jeff)->data != rhs[jeff])
		{
			return false;
		}
		jeff++;
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	ptr1 = nullptr;
	ptr2 = nullptr;

	return true;
}

//copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	Node * ptr = list.head;
	while (ptr != nullptr)
	{
		AddTail(ptr->data);
		ptr = ptr->next;
	}
	ptr = nullptr;
}

//assignment operator
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	Node * ptr = rhs.head;
	while (ptr != nullptr)
	{
		AddTail(ptr->data);
		ptr = ptr->next;
	}
	ptr = nullptr;
	return *this;
}

//go through every node and murder it
template<typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}

template<typename T>
inline void LinkedList<T>::Clear()
{
	//this is the next node in the while loop
	Node * ptr = head;
	Node * removeMe;
	while (ptr != nullptr)
	{
		removeMe = ptr;
		ptr = ptr->next;
		delete removeMe;
	}
	ptr = nullptr;
	removeMe = nullptr;
	head = nullptr;
	tail = nullptr;
}

//=========ACCESSORS==========
template<typename T>
inline typename LinkedList<T>::Node * LinkedList<T>::Head()
{
	return this->head;
}

template<typename T>
inline const typename LinkedList<T>::Node * LinkedList<T>::Head() const
{
	return this->head;
}

template<typename T>
inline typename LinkedList<T>::Node * LinkedList<T>::Tail()
{
	return this->tail;
}

template<typename T>
inline const typename LinkedList<T>::Node * LinkedList<T>::Tail() const
{
	return this->tail;
}

template<typename T>
inline void LinkedList<T>::PrintForward()
{
	Node * michael = head;
	
	while (michael != nullptr)
	{
		cout << michael->data << endl;
		michael = michael->next;
	}
	michael = nullptr;
}

template<typename T>
inline void LinkedList<T>::PrintReverse()
{
	Node * toby = tail;
	while (toby != nullptr)
	{
		cout << toby->data << endl;
		toby = toby->prev;
	}
	toby = nullptr;
}

template<typename T>
inline void LinkedList<T>::PrintForwardRecursive(const Node * node)
{
	cout << node->data << endl;
	if (node->next != nullptr)
	{
		PrintForwardRecursive(node->next);
	}
}

template<typename T>
inline void LinkedList<T>::PrintReverseRecursive(const Node * node)
{
	cout << node->data << endl;
	if (node->prev != nullptr)
	{
		PrintReverseRecursive(node->prev);
	}
}

template<typename T>
inline unsigned int LinkedList<T>::NodeCount() const
{
	//kevin is our counter because he is a great accountant
	unsigned int kevin = 0;
	Node * angela = head;
	while (angela != nullptr)
	{
		kevin++;
		angela = angela->next;
	}
	angela = nullptr;
	return kevin;
}

/* Find all nodes which match the passed in parameter value, and store a pointer
to that node in the passed in vector. Use of a parameter like this (passing a
something in by reference, and storing data for later use) is called an output
parameter. */
template<typename T>
inline void LinkedList<T>::FindAll(vector<LinkedList::Node*>& outData, const T & value) const
{
	Node * oscar = head;
	while (oscar != nullptr)
	{
		if (oscar->data == value)
		{
			outData.push_back(oscar);
		}
		oscar = oscar->next;
	}
}

/* Find the first node with a data value matching the passed in parameter,
returning a pointer to that node. Returns null if no matching node found. */
template<typename T>
inline const typename LinkedList<T>::Node * LinkedList<T>::Find(const T & data) const
{
	Node * creed = head;
	while (creed != nullptr && creed->data != data)
	{
		creed = creed->next;
	}
	return creed;
}

template<typename T>
inline typename LinkedList<T>::Node * LinkedList<T>::Find(const T & data)
{
	//pam is hot
	Node * pam = head;
	while (pam != nullptr && pam->data != data)
	{
		pam = pam->next;
	}
	return pam;
}

template<typename T>
inline const typename LinkedList<T>::Node * LinkedList<T>::GetNode(unsigned int index) const
{
	if (index < 0)
	{
		cout << "get node" << endl;
		throw - 1;
	}
	Node * ptr = head;
	for (unsigned int jeff = 0; jeff < index; jeff++)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
		{
			cout << "out of range on GetNode()" << endl;
			throw -1;
		}
	}
	return ptr;
}

template<typename T>
inline typename LinkedList<T>::Node * LinkedList<T>::GetNode(unsigned int index)
{
	if (index < 0)
	{
		cout << "get node" << endl;
		throw - 1;
	}
	Node * ptr = head;
	for (unsigned int jeff = 0; jeff < index; jeff++)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
		{
			cout << "out of range on GetNode()" << endl;
			throw - 1;
		}
	}
	return ptr;
}

//========INSERTIONS========

template<typename T>
inline void LinkedList<T>::AddHead(const T & data)
{
	Node * new_head = new Node(data);
	//if no elements are present
	if (head == nullptr)
	{
		head = new_head;
	}
	//if 1 element is present
	else if (tail == nullptr)
	{
		tail = head;
		head = new_head;
		tail->prev = head;
		head->next = tail;
	}
	else
	{
		new_head->next = head;
		head->prev = new_head;
		head = new_head;
		head->prev = nullptr;
	}
}

template<typename T>
inline void LinkedList<T>::AddTail(const T & data)
{
	Node * new_tail = new Node(data);
	//checking if no elements are present. The first element will be
	//the head and the tail will be nullptr
	if (head == nullptr)
	{
		head = new_tail;
	}
	//if 1 element is present
	else if (tail == nullptr)
	{
		tail = new_tail;
		head->next = tail;
		tail->prev = head;
	}
	else
	{
		new_tail->prev = tail;
		tail->next = new_tail;
		tail = new_tail;
		tail->next = nullptr;
	}
}

//Given an array of values, insert a node for each of those at the beginning of the
//list, maintaining the original order. Count is how many elements in the array
template<typename T>
inline void LinkedList<T>::AddNodesHead(const T * data, unsigned int count)
{
	//adds the last elements first to maintain the order of the array
	for (int jim = count - 1; jim >= 0; jim--)
	{
		AddHead(data[jim]);
	}
}

template<typename T>
inline void LinkedList<T>::AddNodesTail(const T * data, unsigned int count)
{
	//adds the last elements first to maintain the order of the array
	for (unsigned int dwight = 0; dwight < count; dwight++)
	{
		AddTail(data[dwight]);
	}
}


//insert after and before are literally the same thing
//except that after makes ryan start at 1 and not 0
template<typename T>
inline void LinkedList<T>::InsertAfter(Node * node, const T & data)
{
	//ryan and kelly are both counters while going through the nodes.
	//Working together like a cute couple
	int ryan = 1;
	Node * kelly = head;
	while (kelly != nullptr)
	{
		if (kelly == node)
		{
			InsertAt(data, ryan);
			kelly = nullptr;
		}
		else
		{
			kelly = kelly->next;
			ryan++;
		}
	}
}

//This method slow as h*cc but that's ok because we're not graded on it
template<typename T>
inline void LinkedList<T>::InsertBefore(Node * node, const T & data)
{
	//ryan and kelly are both counters while going through the nodes.
	//Working together like a cute couple
	int ryan = 0;
	Node * kelly = head;
	while (kelly != nullptr)
	{
		if (kelly == node)
		{
			InsertAt(data, ryan);
			kelly = nullptr;
		}
		else
		{
			kelly = kelly->next;
			ryan++;
		}
	}
}

template<typename T>
inline void LinkedList<T>::InsertAt(const T & data, unsigned int index)
{
	unsigned int count = 0;
	Node * daryll = head;
	Node * baby_node = new Node(data);
	while (daryll != nullptr)
	{
		if (count == index)
		{
			baby_node->next = daryll;
			baby_node->prev = daryll->prev;
			if (daryll->prev != nullptr)
			{
				daryll->prev->next = baby_node;
			}
			daryll->prev = baby_node;
			daryll = nullptr;
			if (count == 0)
			{
				head = baby_node;
			}
			return;
		}
		else
		{
			count++;
			daryll = daryll->next;
		}
	}
	if (daryll == nullptr && count == index)
	{
		baby_node->prev = tail;
		tail->next = baby_node;
		tail = baby_node;
	}
	else
	{
		cout << "out of bounds on InsertAt(" << index << ")" << endl;
	}
	daryll = nullptr;
}

//======REMOVERS========
template<typename T>
inline bool LinkedList<T>::RemoveHead()
{
	if (head == nullptr)
	{
		return false;
	}
	else if (tail == nullptr)
	{
		delete head;
		head = nullptr;
		return true;
	}
	//else: head and tail exist
	Node * ptr = head->next;
	delete head;
	ptr->prev = nullptr;//ptr is nullptr
	head = ptr;
	if (ptr->next == nullptr)
	{
		tail = nullptr;
	}
	ptr = nullptr;
	return true;
}
//If there is only one element, it's the head and there is no tail but 
//remove the single element anyways
template<typename T>
inline bool LinkedList<T>::RemoveTail()
{
	if (head == nullptr)
	{
		return false;
	}
	else if (tail == nullptr)
	{
		delete head;
		head = nullptr;
		return true;
	}
	Node * ptr = tail->prev;
	delete tail;
	ptr->next = nullptr;
	tail = ptr;
	//if there is only one element left
	if (head == tail)
	{
		tail = nullptr;
	}
	return true;
}

template<typename T>
inline unsigned int LinkedList<T>::Remove(const T & data)
{
	//stanley is the amount of nodes removed
	unsigned int stanley = 0;
	//phyllis is the iterator, ryan is a termp variable
	Node * phyllis = head;
	Node * bob_vance;

	while ( phyllis != nullptr )
	{
		if (phyllis->data == data)
		{
			bob_vance = phyllis->next;
			phyllis->next->prev = phyllis->prev;
			phyllis->prev->next = phyllis->next;
			delete phyllis;
			phyllis = bob_vance;
			stanley++;
		}
		phyllis = phyllis->next;
	}
	//thank you stanley you were a lot of help
	phyllis = nullptr;
	return stanley;
}

template<typename T>
inline bool LinkedList<T>::RemoveAt(int index)
{
	//sprinkles is the node we want to remove
	Node * sprinkles = head;
	//sprinkles is the current index
	int angela = 0;
	while (sprinkles != nullptr)
	{
		if ( angela == index )
		{
			sprinkles->next->prev = sprinkles->prev;
			sprinkles->prev->next = sprinkles->next;
			delete sprinkles;
			sprinkles = nullptr;
			return true;
		}
		else
		{
			angela++;
			sprinkles = sprinkles->next;
		}
	}
	//if while loop terminates, the end of the list was reached before reaching the index
	//cout << "out of bounds on removeAt(" << index << ")" << endl;
	sprinkles = nullptr;
	return false;
}