#ifndef ORIENTED_GRAPH_H
#define ORIENTED_GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "graph_vertex.hpp"

class OrientedGraph
{
    public:
        OrientedGraph(void);
        void build_graph(const std::string &filename);
    private:
        GraphVertex_ptr _origin;
        std::map<char,GraphVertex_ptr> _vertexes;

        GraphVertex_ptr get_vertex(char name);
};

#endif
