//
//  Graph.h
//  
//
//  Created by Eric Navar on 11/8/20.
//

#pragma once
#include <vector>
#include "VertexListNode.h"
#include "Edge.h"
#include "UnionFind.h"
#include "../Sorting/SortingV.h"
using namespace std;

class GraphLL
{
public:
    GraphLL();
    bool isEdge(int from, int to); //returns true if there is an edge between the vertices from and to
    int getWeight(int from, int to); //returns the weight of the edge between the vertices from and to
    vector<Edge> getEdges();
    void insertEdge(int node1, int node2, int weight);  //inserts new edge in graph
    void insertEdge(Edge &e);
    void insertEdges(vector<Edge> &edges);
	bool isVertex(int vertex);
	vector<int> getVertices();
    void insertVertex(int vertex);
    void insertVertices(vector<int> &vertices);
    GraphLL generateMST();
private:
    bool undirected;
	int numVertices;
	const static int MAXNUMVERTICES = 100;
	//convert vertex number into index in table
	int vertexConverter[MAXNUMVERTICES];
    //prints graph in a format sorted by ascending vertex and edge list
	vector<VertexListNode> adjacencyList;  //vector of vertices
    void insertEdgeHelper(int from, int to, int weight);
};

GraphLL::GraphLL()
{
	numVertices = 0;
	undirected = true;
	fill_n(vertexConverter, 100, -1);
}

/* Preconditions: From and to are of vertices of the graph
   Postconditions: Returns true if there is an edge between from and to and false otherwise
*/
bool GraphLL::isEdge(int from, int to)
{
	int index = vertexConverter[from];
	VertexListNode *theHead = &adjacencyList[index];
	VertexListNode *current = theHead;
	while (current && current->name != to)
		if (current->name == to)
			return true;
	return false;
}

/* Preconditions: From and to are vertices of the graph between which there is an edge
   Postconditions: Returns the weight of the edge between from and to
*/
int GraphLL::getWeight(int from, int to)
{
    int index = vertexConverter[from];
	VertexListNode *theHead = &adjacencyList[index];
	VertexListNode *current = theHead;
	while (current && current->name != to)
		if (current->name == to)
			return current->weight;
	return -1;
}

//to avoid duplicates, this will only return edges from
//a to b where a <= b
vector<Edge> GraphLL::getEdges()
{
	vector<Edge> result;
	for (int i = 0; i < numVertices; i++)
	{
		VertexListNode *curr = &adjacencyList[i];
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


/* Preconditions: Node1 and node2 are vertices of the graph
   Postconditions: Inserts a bi-directional between node1 and node2 with the given weight
*/
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

void GraphLL::insertEdge(Edge &e)
{
	insertEdge(e.from, e.to, e.weight);
}

void GraphLL::insertEdges(vector<Edge> &edges)
{
	for (Edge e : edges)
		insertEdge(e);
}

void GraphLL::insertEdgeHelper(int from, int to, int weight)
{
	int index = vertexConverter[from];
	VertexListNode *theHead = &adjacencyList[index];
	VertexListNode *current = theHead;
	//Go to the end of this list and add a new vertex
	VertexListNode *newEdge = new VertexListNode(to, false, weight, nullptr);
	while (current->next != NULL)
		current = current->next;
	current->next = newEdge;
}

bool GraphLL::isVertex(int vertex)
{
	return vertexConverter[vertex] != -1;
}

//vertex between 0 and 99
void GraphLL::insertVertex(int vertex)
{
	VertexListNode *newVertex = new VertexListNode(vertex, true, -999, nullptr);
	adjacencyList.push_back(*newVertex);
	vertexConverter[vertex] = numVertices++;
}

void GraphLL::insertVertices(vector<int> &vertices)
{
	for (int i : vertices)
		insertVertex(i);
}

/* Preconditions: The graph is connected
   Postconditions: Returns a new graph object containing only the edges representing
   the minimum spanning tree of the graph
*/
GraphLL GraphLL::generateMST()
{
    GraphLL dad;
    UnionFind mom;
	vector<Edge> edges = getEdges();
    heapSort(edges);
    for (Edge e : edges)
    {
		//if e will not form a cycle then add it
		if (mom.find(e.to) != mom.find(e.from))
		{
			dad.insertEdge(e);
			mom.unite(e);
		}
    }
    return dad;
}