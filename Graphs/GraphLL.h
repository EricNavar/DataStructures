#pragma once
#include "VertexListNode.h"
#include "Disjoint_Sets.h"
#include "SortingV.h"
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class GraphLL
{
public:
    GraphLL();
	~GraphLL();
    bool isEdge(int from, int to) const;
    int getWeight(int from, int to) const;
    vector<Edge> getEdges() const;
    void insertEdge(int node1, int node2, int weight);
    void insertEdge(Edge &e);
    void insertEdges(vector<Edge> &edges);
	void removeEdge(int from, int to);
	bool isVertex(int vertex) const;
	vector<int> getVertices() const;
    void insertVertex(int vertex);
    void insertVertices(vector<int> &vertices);
	void removeAllAdjacentEdges(int v);
	void removeAllAdjacentEdges(VertexListNode* v);
	void removeVertex(int v);
	void removeVertices(vector<int>& vertices);
	unsigned int getVertexCount() const;
	const VertexListNode* getAdjacentVertices(int name) const;
	void printGraph() const;
	void removeValue(vector<int>& v, int i) const;
	void printDijkstra(int s) const;
    GraphLL generateMST() const;
    int getInDegree(int v) const;
private:
    bool undirected;
	int numVertices;
	const static int MAXNUMVERTICES = 100;
	//convert vertex number into index in table
	int vertexConverter[MAXNUMVERTICES];
    //prints graph in a format sorted by ascending vertex and edge list
	vector<VertexListNode> adjacencyList;  //vector of vertices
	int findMinIndex(vector<int>& v, unsigned int* d) const;
    void insertEdgeHelper(int from, int to, int weight);
	void removeEdgeHelper(int from, int to);
};

GraphLL::GraphLL()
{
	numVertices = 0;
	undirected = true;
	fill_n(vertexConverter, MAXNUMVERTICES, -1);
}

GraphLL::~GraphLL()
{
	for (int i = 0; i < adjacencyList.size(); i++)
	{
		VertexListNode* removeMe = &adjacencyList[i];
		VertexListNode*v = removeMe->next;
		while (v != nullptr)
		{
			removeMe = v;
			v = v->next;
			delete removeMe;
		}
		v = nullptr;
		removeMe = nullptr;
	}
}

/* Preconditions: From and to are of vertices of the graph
   Postconditions: Returns true if there is an edge between from and to and false otherwise
*/
bool GraphLL::isEdge(int from, int to) const
{
	int index = vertexConverter[from];
	const VertexListNode *theHead = &adjacencyList[index];
	VertexListNode *current = theHead->next;
	while (current != nullptr)
	{
		if (current->name == to)
			return true;
		current = current->next;
	}
	return false;
}

/* Preconditions: From and to are vertices of the graph between which there is an edge
   Postconditions: Returns the weight of the edge between from and to
*/
int GraphLL::getWeight(int from, int to) const
{
	int index = vertexConverter[from];
	const VertexListNode* theHead = &adjacencyList[index];
	VertexListNode* current = theHead->next;
	while (current != nullptr)
	{
		if (current->name == to)
			return current->weight;
		current = current->next;
	}
	return -1;
}

int GraphLL::getInDegree(int v) const
{
	int index = vertexConverter[v];
	const VertexListNode* current = &adjacencyList[index];
	int indegree = 0;
	while (current)
	{
		indegree++;
		current = current->next;
	}
	return indegree;
}

//to avoid duplicates, this will only return edges from
//a to b where a <= b
vector<Edge> GraphLL::getEdges() const
{
	vector<Edge> result;
	for (int i = 0; i < numVertices; i++)
	{
		const VertexListNode *curr = &adjacencyList[i];
		int from = curr->name;
		curr = curr->next;
		while (curr)
		{
			int to = curr->name;
			if (from <= to)
			{
				Edge e(curr->weight, from, to);
				result.push_back(e);
			}
			curr = curr->next;
		}
	}
	return result;
}


void GraphLL::insertEdge(Edge &e)
{
	insertEdge(e.from, e.to, e.weight);
}

void GraphLL::insertEdges(vector<Edge>& edges)
{
	for (Edge e : edges)
		insertEdge(e);
}

/* Preconditions: Node1 and node2 are vertices of the graph
   Postconditions: Inserts a bi-directional between node1 and node2 with the given weight
*/
//code borrowed from Cheryl Resch
void GraphLL::insertEdge(int from, int to, int weight)
{
	if (!isVertex(from))
		insertVertex(from);
	if (!isVertex(to))
		insertVertex(to);
	//edge from from to to
	insertEdgeHelper(from, to, weight);
	//edge from to to from
	if (undirected)
		insertEdgeHelper(to, from, weight);
}

//code borrowed from Cheryl Resch
void GraphLL::insertEdgeHelper(int from, int to, int weight)
{
	int index = vertexConverter[from];
	VertexListNode *current = &adjacencyList[index];
	//Go to the end of this list and add a new vertex
	VertexListNode *newEdge = new VertexListNode(to, false, weight, nullptr);
	while (current->next != NULL)
		current = current->next;
	current->next = newEdge;
}

void GraphLL::removeEdge(int from, int to)
{
	removeEdgeHelper(from, to);
	if (undirected)
		removeEdgeHelper(to, from);
}

void GraphLL::removeEdgeHelper(int from, int to)
{
	int index = vertexConverter[from];
	VertexListNode* prev = &adjacencyList[index];
	VertexListNode* current = prev->next;
	while (current != nullptr)
	{

		if (current->name == to)
		{
			prev->next = current->next;
			delete current;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

unsigned int GraphLL::getVertexCount() const
{
	return adjacencyList.size();
}

bool GraphLL::isVertex(int vertex) const
{
	return vertexConverter[vertex] != -1;
}

vector<int> GraphLL::getVertices() const
{
	vector<int> vertices;
	for (VertexListNode v : adjacencyList)
		vertices.push_back(v.name);
	return vertices;
}

//vertex between 0 and 99
void GraphLL::insertVertex(int vertex)
{
	VertexListNode *newVertex = new VertexListNode(vertex, true, -999, nullptr);
	adjacencyList.push_back(*newVertex);
	vertexConverter[vertex] = numVertices++;
}

//remove the linked list for v in the adjacency list
void GraphLL::removeAllAdjacentEdges(int v)
{
	int index = vertexConverter[v];
	VertexListNode* head = &adjacencyList[index];
	removeAllAdjacentEdges(head);
}

void GraphLL::removeAllAdjacentEdges(VertexListNode* v)
{
	VertexListNode* removeMe;
	while (v != nullptr)
	{
		removeMe = v;
		v = v->next;
		delete removeMe;
	}
	v = nullptr;
	removeMe = nullptr;
}

void GraphLL::removeVertex(int v)
{
	removeAllAdjacentEdges(v);
	int index = vertexConverter[v];
	adjacencyList.erase(adjacencyList.begin() + index);
	vertexConverter[v] = -1;
}

void GraphLL::removeVertices(vector<int>& vertices)
{
	for (int v : vertices)
		removeVertex(v);
}

void GraphLL::insertVertices(vector<int>& vertices)
{
	for (int i : vertices)
		insertVertex(i);
}

/* Preconditions: The graph is connected
   Postconditions: Returns a new graph object containing only the edges representing
   the minimum spanning tree of the graph
*/
GraphLL GraphLL::generateMST() const
{
    GraphLL dad;
    Disjoint_Sets mom;
	vector<Edge> edges = getEdges();
    heapSort(edges);
    for (Edge e : edges)
    {
		//if e will not form a cycle then add it
		if (mom.find(e.to) != mom.find(e.from))
		{
			dad.insertEdge(e);
			mom.union_set(e.from, e.to);
		}
    }
    return dad;
}

//Prints all edges
void GraphLL::printGraph() const
{
	for (Edge e : getEdges())
		cout << "from " << e.from << " to " << e.to << ", weight: " << e.weight << endl;
}

//returns index of smallest element in array
int GraphLL::findMinIndex(vector<int>& v, unsigned int* d) const
{
	int smallest_index = v[0];
	int size = v.size();
	for (int i : v)
		if (d[i] < d[smallest_index])
			smallest_index = i;
	return smallest_index;
}

void GraphLL::removeValue(vector<int>& v, int i) const
{
	v.erase(find(v.begin(), v.end(), i));
}

//Disjkstra's algorithm
void GraphLL::printDijkstra(int s) const
{
	unsigned int dist[MAXNUMVERTICES];
	int prev[MAXNUMVERTICES];
	//set distance elements to the largest possible value
	memset(dist, -1, sizeof(unsigned int) * MAXNUMVERTICES);
	dist[s] = 0;
	VertexListNode* current = getAdjacentVertices(s)->next;
	while (current != nullptr)
	{
		dist[current->name] = current->weight;
		prev[current->name] = s;
		current = current->next;
	}
	vector<int> S = { s };
	//initialize not S with everything but v
	vector<int> notS(getVertices());
	removeValue(notS, s);

	while (!notS.empty())
	{
		for (int u : notS)
		{
			//find the smallest d[u]
			int min = findMinIndex(notS, dist);
			removeValue(notS, min);
			S.push_back(min);
			current = getAdjacentVertices(min)->next;
			while (current)
			{
				//update shortest path if applicable
				if (dist[min] + current->weight < dist[current->name])
				{
					dist[current->name] = dist[min] + current->weight;
					prev[current->name] = min;
				}
				current = current->next;
			}
		}
	}
	for (int i : getVertices())
		if (i != s)
			cout << i << " " << dist[i] << " " << prev[i] << endl;
}

const VertexListNode* GraphLL::getAdjacentVertices(int name) const
{
	int index = vertexConverter[name];
	const VertexListNode* dad = &adjacencyList[index];
	return dad;
}