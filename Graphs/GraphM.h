#include "Graph.h"
//Graph with an adjacency matrix
class GraphM:public Graph
{
public:
	GraphM();
	void insertEdge(int to, int from, int weight);
private:
	const static int MAXNUMVERTICES = 100;
	int theGraph[MAXNUMVERTICES][MAXNUMVERTICES];
	bool undirected;
};

GraphM::GraphM()
{
	undirected = true;
}

void GraphM::insertEdge(int to, int from, int weight)
{
	theGraph[to][from] = weight;
	theGraph[from][to] = weight;
}