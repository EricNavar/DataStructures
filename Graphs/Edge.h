#pragma once
struct Edge
{
    int weight, from, to;
    Edge(int weight, int from, int to)
    {
        this->weight = weight;
        this->from = from;
        this->to = to;
    }
    bool operator>(const Edge &e) const
    {
        return this->weight > e.weight;
    }
};