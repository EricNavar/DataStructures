#pragma once
struct Edge
{
    bool visited;
    int weight, from, to;
    Edge(int weight, int from, int to)
    {
        this->weight = weight;
        this->from = from;
        this->to = to;
        visited = false;
    }
    bool operator>(const Edge &e) const
    {
        return this->weight > e.weight;
    }
};