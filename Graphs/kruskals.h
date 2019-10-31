#pragma once
#include "GraphLL.h"
#include "UnionFind.h"

vector<Edge> kruskals(GraphLL &g)
{
	UnionFind UF;
	vector<Edge> edges = g.getEdges();
    heapSort(edges);
    vector<Edge> path;
    for (Edge e : edges)
    {
		//if e will not form a cycle then add it
		if (UF.find(e.to) != UF.find(e.from))
		{
			path.push_back(e);
			UF.unite(e);
		}
    }
    return path;
}