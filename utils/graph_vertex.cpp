#include "graph_vertex.hpp"

GraphVertex::GraphVertex(const std::string &name):
    _name(name)
{
}

void GraphVertex::set_name(const std::string &name)
{
    _name = name;
}

std::string GraphVertex::get_name(void) const
{
    return _name;
}

void GraphVertex::add_edge(GraphVertex_ptr vertex,Cost cost)
{
    _connections.push_back(std::make_pair(vertex,cost));
}

std::list<Edge> GraphVertex::get_edges(void) const
{
    return _connections;
}
