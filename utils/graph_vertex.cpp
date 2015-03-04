#include "graph_vertex.hpp"

GraphVertex::GraphVertex(char name):
    _name(name)
{
}

void GraphVertex::set_name(char name)
{
    _name = name;
}

char GraphVertex::get_name(void) const
{
    return _name;
}

void GraphVertex::add_edge(GraphVertex_ptr vertex,Cost cost)
{
    _connections.push_back(std::make_pair(vertex,(Cost) cost));
}