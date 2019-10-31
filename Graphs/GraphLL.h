#pragma once
#include <vector>
#include "VertexListNode.h"
#include "Graph.h"
#include "Edge.h"

//Graph with an adjacency List implemented with a Linked List
class GraphLL : public Graph
{
public:  
	GraphLL();
	void insertVertex(int vertex);
	void insertVertices(vector<int> vertices);
	void insertEdge(int from, int to, int weight);
	bool isVertex(int vertex);
	vector<Edge> getEdges();
	vector<int> getVertices();
	const static int MAXNUMVERTICES = 100;
	int vertexConverter[MAXNUMVERTICES] = {-1}; //convert vertex number into index in table
	//vector<vector<int>> getConnectedComponents();
private:
	bool undirected;
	int numVertices;
	vector<VertexListNode> adjacencyList;  //vector of vertices
	void insertEdgeHelper(int from, int to, int weight);
};

vector<int> GraphLL::getVertices()
{
	vector<int> result;
	for (VertexListNode v : adjacencyList)
		result.push_back(v.name);
	return result;
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

GraphLL::GraphLL()
{
	numVertices = 0;
	undirected = true;
	fill_n(vertexConverter, 100, -1);
}

void GraphLL::insertEdge(int from, int to, int weight)
{
	if (!isVertex(from))
		insertVertex(from);
	if (!isVertex(to))
		insertVertex(to);
	insertEdgeHelper(from, to, weight);
	//undirected graph edges go both ways
	if (undirected)
		insertEdgeHelper(to, from, weight);
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

void GraphLL::insertVertices(vector<int> vertices)
{
	for (int i : vertices)
		insertVertex(i);
}

//vertex between 0 and 99
void GraphLL::insertVertex(int vertex)
{
	VertexListNode *newVertex = new VertexListNode(vertex, true, -999, nullptr);
	adjacencyList.push_back(*newVertex);
	vertexConverter[vertex] = numVertices++;
}

bool GraphLL::isVertex(int vertex)
{
	return vertexConverter[vertex] != -1;
}