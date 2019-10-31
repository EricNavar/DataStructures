#pragma once
using namespace std;
class Graph
{
    public:
    void insertEdge(int from, int to, int weight);
    //returns true if there is an edge between the vertices from and to
    bool isEdge(int from, int to);
    //returns the weight of the edge between the vertices from and to
    int getWeight(int from, int to);  
    //return an array of integers representing vertices adjacent to vertex
    int* getAdjacent(int vertex);  
    //print the result of running Dijkstra's algorithm with a source vertex of T
    //string printDijkstra(int source);
};