#include "oriented_graph.hpp"

OrientedGraph::OrientedGraph(void)
{
}

void OrientedGraph::build_graph(const std::string &filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        file.close();
    }
    else
    {
        throw std::runtime_error("Couldn't read file " + filename);
    }
}