#include "Edge.h"

struct UnionFind
{
	const static int MAXNUMVERTICES = 100;
	int id[MAXNUMVERTICES];
	int size[MAXNUMVERTICES];
	UnionFind();
	int find(int i);
	void unite(int p, int q);
	void unite(Edge e);
};

int UnionFind::find(int i)
{
    while(i != id[i])
        i = id[i];
    return i;
}

// Initialization
UnionFind::UnionFind()
{
	for(int i = 0; i < MAXNUMVERTICES; i++)
	{
		id[i] = i;
		size[i] = 1;
	}
}

//Union by size
void UnionFind::unite(int p, int q)
{
    int i = find(p);
    int j = find(q);
    if(i == j) return;

    if(size[i] < size[j])
	{
        id[i] = j;
        size[j] += size[i];
    }
	else
	{
        id[j] = i;
        size[i] += size[j];
    }
}

void UnionFind::unite(Edge e)
{
	unite(e.to, e.from);
}